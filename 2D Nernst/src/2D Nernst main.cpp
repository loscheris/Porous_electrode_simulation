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
#include "TwoDgrids.h"
#include "2D TAceo Nernst.h"
#include <ctime>
using namespace std;

int main() {
	//start timing
	time_t Start;
	Start = time(NULL);

	//set thread
	omp_set_dynamic(0);
	omp_set_num_threads(16);
	int No = omp_get_max_threads();
	cout << "test";
	//constants
	double theta_i = 20.0;
	double theta_v = -20.0;
	double sigma = 10000;
	double deltaTheta= 0.01;
	double h0 = 1e-4;
	double omega = 1.05;
	double deltaT = deltaTheta / sigma ;
	double maxT = 2*fabs(theta_v-theta_i)/sigma;
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

	cout<<"max T: "<<maxT<<endl;
	cout<<"max Z: "<<maxZ<<endl;
	cout<<"max R: "<<maxR<<endl;
	cout<<"No. of R: "<<n<<endl;
	cout<<"No. of Z: "<<m<<endl;
	cout<<"No. of NE: "<<ne<<endl;
	cout<<"No. of Timesteps: "<<No_Timesteps<<endl;
	cout<<"No threads: "<<No<<endl;


	//create concentration grids Ck/C, x is used to store the result of TA and keep multi-threading safe.
	double** Ck = new double*[n];
	double** C = new double*[n];
	double** x = new double* [n];
	//initialise the concentration grids
	for (int i = 0; i < n; ++i) {
		Ck[i] = new double [m];
		C[i] = new double [m];
		x[i] = new double [m];
		for (int j = 0; j < m; ++j) {
			Ck[i][j] = 1.0;
			C[i][j] = 1.0;
			x[i][j] = 1.0;
		}
	}

	//variables to copy the concentration grids and keep multi-threading safe in R sweep
	double **CR = new double* [m];
	double **x2 = new double* [m];
	for (int i = 0; i < m; ++i) {
		CR[i] = new double [n];
		x2[i] = new double [n];
		for (int j = 0; j < n; ++j) {
			CR[i][j] = 1.0;
			x2[i][j] = 1.0;
		}
	}

	//set the ThomasCoefficients
	ThomasCoefficients coe(m, n, deltaT);
	coe.Z_abc(*grids.Zgrid());
	coe.Zne_abc(*grids.Zgrid());
	coe.R_abc(*grids.Rgrid());


	//create TA, for Z and R sweeps
	ThomasAlgorithm **taz = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		taz[i] = new ThomasAlgorithm (coe.Z_b);
	}
	ThomasAlgorithm **tar = new ThomasAlgorithm* [No];
	for (int i = 0; i < No; ++i) {
		tar[i] = new ThomasAlgorithm(coe.R_b);
	}

	//create file
	fstream JandTheta ("J and Theta.txt", ofstream::out);
	double Theta = theta_i;
	//Start Simulation, loop for each timestep
	for (int k = 0; k <No_Timesteps; ++k) {
		if (k < No_Timesteps/2) {Theta -= deltaTheta;}
		else{Theta += deltaTheta;}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				C[i][j] = x2[j][i];
				Ck[i][j] = x2[j][i];
			}
		}

		//Z sweep
		#pragma omp parallel for
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
				Ck[i][0] = 1.0 / (1.0 + exp(-Theta));
				taz[omp_get_thread_num()]->Solve_TA(coe.Z_a, coe.Z_b, coe.Z_c,x[i], Ck[i]);
			} else {
				Ck[i][0] = 0;
				taz[omp_get_thread_num()]->Solve_TA(coe.Zne_a, coe.Zne_b, coe.Zne_c,x[i], Ck[i]);
			}
		}

		//copy concentration grids
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				C[i][j] = x[i][j];
				Ck[i][j] = x[i][j];
			}
		}

		//compute flux
		double flux = 0.0;
		for (int i = 1; i <= ne; ++i) {
			double J2 = (Ck[i][1]-Ck[i][0])* (grids.Rgrid()->at(i));
			double J1 = (Ck[i-1][1] - Ck[i-1][0])*(grids.Rgrid()->at(i-1));
			flux -= (0.5/h0)*(J1+J2)*((grids.Rgrid()->at(i))-(grids.Rgrid()->at(i-1)));
		}
		JandTheta<<Theta<<"\t"<<flux<<"\n";


		//R sweep
		#pragma omp parallel for
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
				CR[j][l] = Ck[l][j];
			}

			//Solve TA
			tar[omp_get_thread_num()]->Solve_TA(coe.R_a,coe.R_b,coe.R_c, x2[j], CR[j]);

		}
		cout<<k<<endl;
	}

	//delete dynamic allocated memory
    for (int i = 0; i < n; ++i) {
		delete [] Ck[i];
		delete [] C[i];
		delete [] x[i];
	}

    for (int i = 0; i < m; ++i) {
		delete [] CR[i];
		delete [] x2[i];
	}

    delete[] x2;
    delete[] CR;
    delete[] x;
    delete[] Ck;
    delete[] C;

	JandTheta.close();
    double totaltime;
    totaltime = difftime(time(NULL),Start);
    cout << "time: " << totaltime<< " s"<< endl;
    cout<<">>>finish"<<endl<<endl;
	return 0;
}


