//============================================================================
// Name        : One.cpp
// Author      : Zhiyong Ban
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include "TA_class.h"
#include <fstream>

#include "2D TAceo Nernst CV.h"
#include "TwoDgrids CV.h"
using namespace std;

int main() {

//	omp_set_num_threads(32);

	double h0 = 1e-4;
	double omega = 1.05;

	double deltaT = 1e-6;
	double maxT = 0.008;
	double maxZ = 6*sqrt(maxT);
	double maxR = 6*sqrt(maxT) + 1;
	int No_Timesteps = (int)(maxT / deltaT);

	// create Z,R girds
	TwoD_grids grids(h0, omega);
	grids.makeZgrids(maxZ);
	grids.makeRgrids(maxR);

	//No. of R grids
	int n = grids.sizeofR();
	//No. of Z grids
	int m = grids.sizeofZ();
	//No. of R grids within the electrode
	int ne = grids.sizeofNE();

	cout<<"delta T: "<<deltaT<<endl;
	cout<<"max T: "<<maxT<<endl;
	cout<<"max Z: "<<maxZ<<endl;
	cout<<"max R: "<<maxR<<endl;
	cout<<"No. of R: "<<n<<endl;
	cout<<"No. of Z: "<<m<<endl;
	cout<<"No. of NE: "<<ne<<endl;

	//create concentration grids
	double** Ck = new double*[n];
	double**C = new double*[n];
	vector<double> CR;
	CR.resize(n);

	//initialise the concentration grids, Ck[i][j] represents Ck[R-grid][Z-grid]
	for (int i = 0; i < n; ++i) {
		Ck[i] = new double [m];
		C[i] = new double [m];

		for (int j = 0; j < m; ++j) {
			Ck[i][j] = 1.0;
			C[i][j] = 1.0;
		}
	}

	//set the ThomasCoefficients
	ThomasCoefficients coe(m, n, deltaT);
	coe.Z_abc(*grids.Zgrid());
	coe.Zne_abc(*grids.Zgrid());
	coe.R_abc(*grids.Rgrid());

	//create TA
	ThomasAlgorithm taz(coe.Z_b);
	ThomasAlgorithm tar(coe.R_b);

	fstream JandT ("J and T.txt", ofstream::out);
	fstream CvsT ("C.txt",ofstream::out);

	cout<<"Total: "<<No_Timesteps<<endl;


	//Start Simulation, loop for each timestep
	for (int k = 0; k <No_Timesteps; ++k) {

		cout<< k<<endl;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				C[i][j] = Ck[i][j];
			}
		}

		//Z sweep
		//#pragma omp parallel for
		for (int i = 1; i < n-1; ++i) {
			Ck[i][m-1] = 1.0;

			for (int j = 1; j < m-1; ++j) {
			//set column d in the TA
				Ck[i][j] = -C[i-1][j] * coe.R_a[i]
						   -C[i][j] * (-coe.R_a[i]-coe.R_c[i])
						   -C[i][j] * 2.0/ deltaT
						   -C[i+1][j] * coe.R_c[i];
			}
			//two cases: in the electrode or out of the electrode, then solve TA
			if (i < ne) {
				Ck[i][0] = 0;
				taz.Solve_TA(coe.Z_a, coe.Z_b, coe.Z_c,Ck[i], Ck[i]);
			} else {
				Ck[i][0] = 0;
				taz.Solve_TA(coe.Zne_a, coe.Zne_b, coe.Zne_c,Ck[i], Ck[i]);
			}
		}

		//copy concentration grids
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				C[i][j] = Ck[i][j];
			}
		}

		//compute flux
		double flux = 0.0;
		for (int i = 1; i <= ne; ++i) {
			double J2 = (Ck[i][1]-Ck[i][0])* (grids.Rgrid()->at(i));
			double J1 = (Ck[i-1][1] - Ck[i-1][0])*(grids.Rgrid()->at(i-1));
			flux -= (0.5/h0)*(J1+J2)*((grids.Rgrid()->at(i))-(grids.Rgrid()->at(i-1)));
		}

		JandT<<k*deltaT<<"\t"<<flux<<"\n";

		//R sweep
//		#pragma omp parallel for
		for (int j = 1; j < m-1; ++j) {
			//Set column d in the TA
			Ck[0][j]= 0;
			Ck[n-1][j] = 1.0;
			for (int i = 1; i < n-1; ++i) {
				Ck[i][j] = -C[i][j-1] * coe.Z_a[j]
						-C[i][j] * (-coe.Z_a[j] - coe.Z_c[j])
						-C[i][j] * 2.0/deltaT
						-C[i][j+1] * coe.Z_c[j];
			}

			//Copy the specific row in the Ck vector to a one dimension vector CR
			for (int l = 0; l < n; ++l) {
				CR[l] = Ck[l][j];
			}

			//Solve TA
			tar.Solve_TA(coe.R_a,coe.R_b,coe.R_c, CR, CR);

			//Return the values in CR to the row in CK
			for (int l = 0; l < n; ++l) {
				Ck[l][j] = CR[l];
			}
		}

		//record the concentration at every point on the electrode
		for (int l = 1; l < ne; ++l) {
			CvsT<<Ck[l][0]<<' ';
		}
		CvsT<<'\n';
	}

	CvsT.close();
	JandT.close();
    cout<<">>>finish"<<endl;

    for (int i = 0; i < n; ++i) {
		delete [] Ck[i];
		delete [] C[i];
	}
    delete[] Ck;
    delete[] C;

	return 0;
}


