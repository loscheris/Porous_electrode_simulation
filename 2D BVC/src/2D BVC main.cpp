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
#include <fstream>
#include <ctime>

#include "2D TAceo BVC.h"
#include "TA_class.h"
#include "TwoDgrids.h"
using namespace std;

int main() {
	//start timing
	time_t Start;
	Start = time(NULL);

	//set thread
	omp_set_num_threads(16);
	int No = omp_get_max_threads();

	double ca = 1.0;
	double cb = 0.0;

	//constants
	double h0 = 1e-4;
	double omega = 1.1;
	double K =1e5;
	double alpha = 0.5;
	double db = 1.6;
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
		Ck[i] = new double [2*m];
		C[i] = new double [2*m];
		x[i] = new double [2*m];
		for (int j = 0; j < m; ++j) {
			Ck[i][j] = ca;
			C[i][j] = ca;
			x[i][j] = ca;
		}
		for (int j = m; j < 2*m; ++j) {
			Ck[i][j] = cb;
			C[i][j] = cb;
			x[i][j] = cb;
		}
	}

	//variables to copy the concentration grids and keep multi-threading safe in R sweep
	double **CR = new double* [2*m];
	double **x2 = new double* [2*m];
	for (int i = 0; i < m; ++i) {
		CR[i] = new double [n];
		x2[i] = new double [n];
		for (int j = 0; j < n; ++j) {
			CR[i][j] = ca;
			x2[i][j] = ca;
		}
	}
	for (int i = m; i < 2*m; ++i) {
		CR[i] = new double [n];
		x2[i] = new double [n];
		for (int j = 0; j < n; ++j) {
			CR[i][j] = cb;
			x2[i][j] = cb;
		}
	}

	//set the ThomasCoefficients
	ThomasCoefficients coe(m, n, deltaT, K, alpha, db, h0);
	coe.Z_abc(*grids.Zgrid());
	coe.Zne_abc(*grids.Zgrid());
	coe.R_abc(*grids.Rgrid());

	//create TA, for Z and R sweeps
	ThomasAlgorithm **taz = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		taz[i] = new ThomasAlgorithm (coe.zb);
	}
	ThomasAlgorithm **tar = new ThomasAlgorithm* [No];
	for (int i = 0; i < No; ++i) {
		tar[i] = new ThomasAlgorithm(coe.rb);
	}

	//create file
	fstream JandT ("J and T.txt", ofstream::out);
	fstream mass ("mass.txt", ofstream::out);
	fstream cona ("data_ConcentrationsA.txt", ofstream::out);
	fstream conb ("data_ConcentrationsB.txt", ofstream::out);

	//Start Simulation, loop for each timestep
	for (int k = 0; k <No_Timesteps; ++k) {


		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 2*m; ++j) {
				C[i][j] = x2[j][i];
				Ck[i][j] = x2[j][i];
			}
		}

		double totalmass = 0.0;
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				totalmass += M_PI*(Ck[i][m-1-j]+Ck[i][m+j])
						*(pow(grids.Rgrid()->at(i),2)-pow(grids.Rgrid()->at(i-1),2))
						*(grids.Zgrid()->at(j)-grids.Zgrid()->at(j-1));
			}
		}
		mass<<totalmass<<"\n";

		//Z sweep
		#pragma omp parallel for
		for (int i = 1; i < n-1; ++i) {
			Ck[i][0] = ca;
			Ck[i][2*m-1] = cb;

			for (int j = 1; j < m-1; ++j) {
			//set column d in the TA
				Ck[i][j] = -C[i-1][j] * coe.ra[i]
						   -C[i][j] * (-coe.ra[i]-coe.rc[i])
						   -C[i][j] * 2.0/ deltaT
						   -C[i+1][j] * coe.rc[i];
			}
			for (int j = m+1; j < 2*m-1; ++j) {
				Ck[i][j] = -C[i-1][j] * coe.rba[i]
						   -C[i][j] * (-coe.rba[i]-coe.rbc[i])
						   -C[i][j] * 2.0/ deltaT
						   -C[i+1][j] * coe.rbc[i];
			}
			Ck[i][m-1] = 0.0;
			Ck[i][m] = 0.0;

			//two cases: in the electrode or out of the electrode, then solve TA
			if (i < ne) {
				taz[omp_get_thread_num()]->Solve_TA(coe.za, coe.zb, coe.zc,x[i], Ck[i]);
			} else {
				taz[omp_get_thread_num()]->Solve_TA(coe.znea, coe.zneb, coe.znec,x[i], Ck[i]);
			}
		}
		//copy concentration grids
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 2*m; ++j) {
				C[i][j] = x[i][j];
				Ck[i][j] = x[i][j];
			}
		}

		//output concentration profile at certain timestep
//		if (k == 4000) {
//			for (int j = m-1; j>=0; j--) {
//				for (int i = 0; i < n; ++i) {
//					cona<<Ck[i][j]<<'\t';
//				}
//				cona<<'\n';
//			}
//			for (int j = m; j < 2*m; ++j) {
//				for (int i = 0; i < n; ++i) {
//					conb<<Ck[i][j]<<'\t';
//				}
//				conb<<'\n';
//			}
//		}

		//compute flux
		double flux = 0.0;
		for (int i = 1; i <= ne; ++i) {
			double J2 = (Ck[i][m-2]-Ck[i][m-1])* (grids.Rgrid()->at(i));
			double J1 = (Ck[i-1][m-2] - Ck[i-1][m-1])*(grids.Rgrid()->at(i-1));
			flux -= (0.5/h0)*(J1+J2)*((grids.Rgrid()->at(i))-(grids.Rgrid()->at(i-1)));
		}
		JandT<<k*deltaT<<'\t'<<flux<<"\n";


		//R sweep for species A
		#pragma omp parallel for
		for (int j = 1; j < m-1; ++j) {
			//Set column d in the TA
			Ck[0][j]= 0.0;
			Ck[n-1][j] = ca;

			for (int i = 1; i < n-1; ++i) {
				Ck[i][j] = -C[i][j-1] * coe.za[j]
						-C[i][j] * (-coe.za[j] - coe.zc[j])
						-C[i][j] * 2.0/deltaT
						-C[i][j+1] * coe.zc[j];
			}
			//Copy the specific row in the Ck vector to a one dimension vector CR
			for (int l = 0; l < n; ++l) {
				CR[j][l] = Ck[l][j];
			}
			//Solve TA
			tar[omp_get_thread_num()]->Solve_TA(coe.ra,coe.rb,coe.rc, x2[j], CR[j]);
		}


		//R sweep for species B
		#pragma omp parallel for
		for (int j = m+1; j < 2*m-1; ++j) {
			Ck[0][j]= 0.0;
			Ck[n-1][j] = cb;
			for (int i = 1; i < n-1; ++i) {

				Ck[i][j] = -C[i][j-1] * coe.za[j]
						-C[i][j] * (-coe.za[j] - coe.zc[j])
						-C[i][j] * 2.0/deltaT
						-C[i][j+1] * coe.zc[j];
			}
			for (int l = 0; l < n; ++l) {
				CR[j][l] = Ck[l][j];
			}
			tar[omp_get_thread_num()]->Solve_TA(coe.rba,coe.rbb,coe.rbc, x2[j], CR[j]);
		}
	}

	//delete dynamic allocated memory
    for (int i = 0; i < n; ++i) {
		delete [] Ck[i];
		delete [] C[i];
		delete [] x[i];
	}

    for (int i = 0; i < 2*m; ++i) {
		delete [] CR[i];
		delete [] x2[i];
	}

    delete[] x2;
    delete[] CR;
    delete[] x;
    delete[] Ck;
    delete[] C;

	JandT.close();
	mass.close();
	cona.close();
	conb.close();

    double totaltime;
    totaltime = difftime(time(NULL),Start);
    cout << "time: " << totaltime<< " s"<< endl;
    cout<<">>>finish"<<endl<<endl;
	return 0;
}


