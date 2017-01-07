//============================================================================
// Name        : Porous1.cpp
// Author      : Zhiyong Ban
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>
#include <omp.h>
#include "Porous TAceo BV.h"
#include "PorousTwoDgrids.h"
#include <sstream>
#include "TA_class.h"
using namespace std;

int main() {
	//start timing
	time_t Start;
	Start = time(NULL);

	//set thread
	omp_set_num_threads(16);
	int No = omp_get_max_threads();

	//direction = 1 means A -> B, direction = 0 means B -> A
	bool direction = 1;
	double ca;
	double cb;
	double theta_i;
	double theta_v;
	if (direction) {
		theta_i = +20.0;
		theta_v = -20.0;
		ca = 1.0;
		cb = 0.0;
	} else {
		theta_i = -20.0;
		theta_v = +20.0;
		ca = 0.0;
		cb = 1.0;
	}

	//create constants
	double sigma;
	double maxR;
	double height;
	double K;
	double deltaTheta;
	double h0;
	double omega;
	double alpha;
	double db;
	double width;
	int tem_recordtime;
	int index=0;
	string peakheightonly;
	string conconly;
	vector<int> recordtime;
//	recordtime.resize(0);

	//import data from file
	fstream cConfig;
	string strConfigReadout;
	cConfig.open("Parameter.txt", ios::in);
	cConfig >> strConfigReadout;
	cConfig >> peakheightonly;
	cConfig >> strConfigReadout;
	cConfig >> conconly;
	cConfig >> strConfigReadout;
	cConfig >> theta_i;
	cConfig >> strConfigReadout;
	cConfig >> theta_v;
	cConfig >> strConfigReadout;
	cConfig >> sigma;
	cConfig >> strConfigReadout;
	cConfig >> maxR;
	cConfig >> strConfigReadout;
	cConfig >> height;
	cConfig >> strConfigReadout;
	cConfig >> K;
	cConfig >> strConfigReadout;
	cConfig >> deltaTheta;
	cConfig >> strConfigReadout;
	cConfig >> h0;
	cConfig >> strConfigReadout;
	cConfig >> omega;
	cConfig >> strConfigReadout;
	cConfig >> alpha;
	cConfig >> strConfigReadout;
	cConfig >> db;
	cConfig >> strConfigReadout;
	cConfig >> width;
	cConfig >> strConfigReadout;
	while (cConfig>>tem_recordtime){
		recordtime.push_back(tem_recordtime);
	}


	while(peakheightonly!="Y" &&
		  peakheightonly!="N" &&
		  peakheightonly!="y" &&
		  peakheightonly!="n")
	{	cout<<"Do you want to stop the program once peak current is reached(y/n): ";
		cin>>peakheightonly;
	}

	while(conconly!="Y" &&
		  conconly!="N" &&
		  conconly!="y" &&
		  conconly!="n")
	{	cout<<"Do you want to stop the program once concentration is recorded(y/n): ";
		cin>>peakheightonly;
	}


	double deltaT = deltaTheta / sigma ;
	double maxT = 2*fabs(theta_v-theta_i)/sigma;
	double Z = 6*sqrt(maxT);
	double maxZ = Z+height;
	if (Z<1.1*height) {
		maxZ = 1.1*height;
	}
	int No_Timesteps = 2*fabs(theta_v-theta_i)/deltaTheta;

//	sigma=pow10(sigma);
	// create Z,R girds
	TwoD_grids grids(h0, omega);
	grids.makeZgrids(maxZ,height);
	grids.makeRgrids(maxR,width);

	//No. of R grids
	int n = grids.sizeofR();
	//No. of Z grids
	int m = grids.sizeofZ();
	//No. of R grids within the electrode
	int rne = grids.sizeofRNE()-1;
	int zne = grids.sizeofZNE()-1;

	cout<<"Sigma: "<<sigma<<endl;
	cout<<"max R: "<<maxR<<endl;
	cout<<"size of the cylinder: "<<height<<"*"<<width<<endl;
	cout<<"k: "<<K<<endl;
	cout<<"h0: "<<h0<<endl;
	cout<<"omega: "<<omega<<endl;
	cout<<"deltaT: "<<deltaT<<endl;
	cout<<"delta theta: "<<deltaTheta<<endl;
	cout<<"No. of Timesteps: "<<No_Timesteps<<endl;
	cout<<"Db: "<<db<<endl;
	cout<<"alpha: "<<alpha<<endl;
	cout<<"max T: "<<maxT<<endl;
	cout<<"max Z: "<<maxZ<<endl;
	cout<<"theta_i: "<<theta_i<<endl;
	cout<<"theta_v: "<<theta_v<<endl;
	cout<<"No. of R: "<<n<<endl;
	cout<<"No. of Z: "<<m<<endl;
	cout<<"No. of RNE: "<<rne<<endl;
	cout<<"No. of ZNE: "<<zne<<endl;
	cout<<"No. of threads: "<<No<<endl;
	cout<<"Peak Current Only: "<<peakheightonly<<endl;
	cout<<"Concentration profile Only: "<<conconly<<endl;
	cout<<"Record timestep: ";

	cout.flush();
	for (unsigned int i = 0; i < recordtime.size(); ++i) {
		cout<<recordtime[i]<<' ';
		cout.flush();
	}
	cout<<endl;



	//create concentration grids Ck/C, x is used to store the result of TA and keep multi-threading safe.
	double** conca = new double*[n];
	double** concb = new double*[n];
	//initialise the concentration grids
	for (int i = 0; i < n; ++i) {
		conca[i] = new double [m];
		concb[i] = new double [m];

		for (int j = 0; j < m; ++j) {
			conca[i][j] = ca;
			concb[i][j] = cb;
		}

		if (i< rne) {
			for (int j = 0; j < zne; ++j) {
				conca[i][j] = 0.0;
				concb[i][j] = 0.0;
			}
		}
	}

	//z-sweep(1st region) concentrations
	double** dz1 = new double* [rne+2];
	double** xz1 = new double* [rne+2];
	double** dz1_ = new double* [rne+2];
	for (int i = 0; i < rne+2; ++i) {
		dz1[i] = new double [2*(m-zne)];
		xz1[i] = new double [2*(m-zne)];
		dz1_[i] = new double [2*(m-zne)];
		for (int j = 0; j < m-zne; ++j) {
			dz1[i][j] = ca;
			xz1[i][j] = ca;
			dz1_[i][j] = ca;
		}
		for (int j = m-zne; j <2*(m-zne) ; ++j) {
			dz1[i][j] = cb;
			xz1[i][j] = cb;
			dz1_[i][j] = cb;
		}
	}

	//z-sweep(2nd region) concentrations
	double** dz2 = new double*[n-rne];
	double** dz2_ = new double*[n-rne];
	double** xz2 = new double*[n-rne];
	for (int i = 0; i < n-rne; ++i) {
		dz2[i] = new double[2*m];
		dz2_[i] = new double[2*m];
		xz2[i] = new double[2*m];
		for (int j = 0; j < m; ++j) {
			dz2[i][j] = ca;
			dz2_[i][j] = ca;
			xz2[i][j] = ca;
		}
		for (int j = m; j < 2*m; ++j) {
			dz2[i][j] = cb;
			dz2_[i][j] = cb;
			xz2[i][j] = cb;
		}
	}

	//r-sweep(1st region) concentrations
	double** dr1 = new double* [zne+2];
	double** dr1_ = new double* [zne+2];
	double** xr1 = new double* [zne+2];
	for (int i = 0; i < zne+2; ++i) {
		dr1[i] = new double[2*(n-rne)];
		dr1_[i] = new double[2*(n-rne)];
		xr1[i] = new double[2*(n-rne)];
		for (int j = 0; j < n-rne; ++j) {
			dr1[i][j] = ca;
			dr1_[i][j] = ca;
			xr1[i][j] = ca;
		}
		for (int j = n-rne; j < 2*(n-rne); ++j) {
			dr1[i][j] = cb;
			dr1_[i][j] = cb;
			xr1[i][j] = cb;
		}
	}

	//r-sweep(2nd region) concentrations
	double** dr2 = new double* [m-zne];
	double** dr2_ = new double* [m-zne];
	double** xr2 = new double* [m-zne];
	for (int i = 0; i < m-zne; ++i) {
		dr2[i] = new double[2*n];
		dr2_[i] = new double[2*n];
		xr2[i] = new double[2*n];

		for (int j = 0; j < n; ++j) {
			dr2[i][j] = ca;
			dr2_[i][j] = ca;
			xr2[i][j] = ca;
		}
		for (int j = n; j < 2*n; ++j) {
			dr2[i][j] = cb;
			dr2_[i][j] = cb;
			xr2[i][j] = cb;
		}
	}

	//set the ThomasCoefficients
	ThomasCoefficients coe(m, n, zne, rne, deltaT, K, alpha, db, h0);
	coe.Z_abc(*grids.Zgrid());
	coe.Zne_abc(*grids.Zgrid());
    coe.R_abc(*grids.Rgrid());
	coe.Rne_abc(*grids.Rgrid());

	//create TA, for Z and R sweeps
	ThomasAlgorithm **taz = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		taz[i] = new ThomasAlgorithm (coe.zb);
	}
	ThomasAlgorithm **tar = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		tar[i] = new ThomasAlgorithm(coe.rb);
	}
	ThomasAlgorithm **tazne = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		tazne[i] = new ThomasAlgorithm(coe.zneb);
	}
	ThomasAlgorithm **tarne = new ThomasAlgorithm*[No];
	for (int i = 0; i < No; ++i) {
		tarne[i] = new ThomasAlgorithm (coe.rneb);
	}

	string aaa;
	aaa= "nem.txt";
	//create file
//	fstream Jandtheta1 ("J1.txt", ofstream::out);
	fstream Jandtheta2 ("J2.txt", ofstream::out);
	fstream CONCA ("CONCA.txt", ofstream::out);
	fstream CONCB ("CONCB.txt", ofstream::out);
	fstream mass ("mass.txt", ofstream::out);
	double Theta = theta_i;

	//Start Simulation, loop for each timestep
	for (int k = 0; k <No_Timesteps; ++k) {


		if (direction) {
			if (k < No_Timesteps/2) {Theta -= deltaTheta;}
			else{Theta += deltaTheta;}
		} else {
			if (k < No_Timesteps/2) {Theta += deltaTheta;}
			else{Theta -= deltaTheta;}
		}

		coe.updatetheta(Theta);

		//prepare for z sweep
		for (int i = 0; i < rne+2; ++i) {
			for (int j = zne; j < m; ++j) {
				dz1[i][m-1-j] = conca[i][j];
				dz1_[i][m-1-j] = conca[i][j];
				dz1[i][j+m-2*zne] = concb[i][j];
				dz1_[i][j+m-2*zne] = concb[i][j];
			}
		}

		for (int i = rne; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				dz2[i-rne][m-1-j] = conca[i][j];
				dz2_[i-rne][m-1-j] = conca[i][j];
				dz2[i-rne][j+m] = concb[i][j];
				dz2_[i-rne][j+m] = concb[i][j];
			}
		}


		//Z sweep for the 1st region
#pragma omp parallel for
		for (int i = 1; i < rne+1; ++i) {

			for (int j = 1; j < m-zne-1; ++j) {
				dz1[i][j] = -dz1_[i-1][j] * coe.rnec[n-1-i]
						    -dz1_[i][j] * (-coe.rnea[n-1-i]-coe.rnec[n-1-i])
						    -dz1_[i][j] * 2.0/ deltaT
						    -dz1_[i+1][j] * coe.rnea[n-1-i];

			}
			for (int j = m-zne+1; j < 2*(m-zne)-1; ++j) {
				dz1[i][j] = -dz1_[i-1][j] * coe.rnea[i+n]
						    -dz1_[i][j] * (-coe.rnea[i+n]-coe.rnec[i+n])
						    -dz1_[i][j] * 2.0/ deltaT
						    -dz1_[i+1][j] * coe.rnec[i+n];

			}
			dz1[i][0] = ca;
			dz1[i][m-zne-1] = 0.0;
			dz1[i][m-zne] = 0.0;
			dz1[i][2*(m-zne)-1] = cb;
			taz[omp_get_thread_num()]->Solve_TA(coe.za, coe.zb, coe.zc, xz1[i], dz1[i]);
		}

		//Z sweep for the 2nd region
#pragma omp parallel for
		for (int i = rne+1; i < n-1; ++i) {

			for (int j = 1; j < m-1; ++j) {
				dz2[i-rne][j] = -dz2_[i-rne-1][j] * coe.rnec[n-1-i]
							    -dz2_[i-rne][j] * (-coe.rnea[n-1-i]-coe.rnec[n-1-i])
							    -dz2_[i-rne][j] * 2.0/ deltaT
					   	        -dz2_[i-rne+1][j] * coe.rnea[n-1-i];

			}

			for (int j = m+1; j < 2*m-1; ++j) {
				dz2[i-rne][j] = -dz2_[i-rne-1][j] * coe.rnea[i+n]
						        -dz2_[i-rne][j] * (-coe.rnea[i+n]-coe.rnec[i+n])
					            -dz2_[i-rne][j] * 2.0/ deltaT
					     	    -dz2_[i-rne+1][j] * coe.rnec[i+n];
			}

			dz2[i-rne][0] = ca;
			dz2[i-rne][m-1] = 0.0;
			dz2[i-rne][m] = 0.0;
			dz2[i-rne][2*m-1] = cb;
			tazne[omp_get_thread_num()]->Solve_TA(coe.znea, coe.zneb, coe.znec, xz2[i-rne], dz2[i-rne]);
		}


		//copy concentration grids
		for (int i = 1; i < rne+1; ++i) {
			for (int j = zne; j < m; ++j) {
				conca[i][j] = xz1[i][m-1-j];
				concb[i][j] = xz1[i][j+m-2*zne];
			}
		}
		for (int i = rne+1; i < n-1; ++i) {
			for (int j = 0; j < m; ++j) {
				conca[i][j] = xz2[i-rne][m-1-j];
				concb[i][j] = xz2[i-rne][j+m];
			}
		}


		// check mass conservation
		double totalmass = 0.0;
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				totalmass += M_PI*(conca[i][j]+concb[i][j])
						*(pow(grids.Rgrid()->at(i),2)-pow(grids.Rgrid()->at(i-1),2))
						*(grids.Zgrid()->at(j)-grids.Zgrid()->at(j-1));
			}
		}
		mass<<totalmass<<"\n";

//		//compute the flux on top electrode
//		double flux1 = 0.0;
//		for (int i = 1; i <= rne; ++i) {
//			double J2 = (conca[i][zne+1]-conca[i][zne])* (grids.Rgrid()->at(i));
//			double J1 = (conca[i-1][zne+1] - conca[i-1][zne])*(grids.Rgrid()->at(i-1));
//			flux1 -= (0.5/h0)*(J1+J2)*((grids.Rgrid()->at(i))-(grids.Rgrid()->at(i-1)));
//		}
//		Jandtheta1<<Theta<<"\t"<<flux1<<"\n";

		//prepare for R sweep, copy concentration
		for (int i = rne; i < n; ++i) {
			for (int j = 0; j < zne+2; ++j) {
				dr1[j][n-1-i] = conca[i][j];
				dr1_[j][n-1-i] = conca[i][j];
				dr1[j][(n-2*rne)+i] = concb[i][j];
				dr1_[j][(n-2*rne)+i] = concb[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = zne; j < m; ++j) {
				dr2[j-zne][n-1-i] = conca[i][j];
				dr2_[j-zne][n-1-i] = conca[i][j];
				dr2[j-zne][i+n] = concb[i][j];
				dr2_[j-zne][i+n] = concb[i][j];
			}
		}


		//R sweep for region 1
#pragma omp parallel for
		for (int i = 1; i < zne+1; ++i) {

			for (int j = 1; j < n-rne-1; ++j) {
				dr1[i][j] = -dr1_[i-1][j] * coe.znec[m-1-i]
						    -dr1_[i][j] * (-coe.znea[m-1-i] - coe.znec[m-1-i])
						    -dr1_[i][j] * 2.0/deltaT
						    -dr1_[i+1][j] * coe.znea[m-1-i];
			}

			for (int j = n-rne+1; j < 2*(n-rne)-1; ++j) {
				dr1[i][j] = -dr1_[i-1][j] * coe.znea[m+i]
				            -dr1_[i][j] * (-coe.znea[m+i] - coe.znec[m+i])
						    -dr1_[i][j] * 2.0/deltaT
						    -dr1_[i+1][j] * coe.znec[m+i];
			}

			dr1[i][0] = 0.0;
			dr1[i][n-rne-1] = 0.0;
			dr1[i][n-rne] = 0.0;
			dr1[i][2*(n-rne)-1] = 0.0;
			tar[omp_get_thread_num()]->Solve_TA(coe.ra, coe.rb, coe.rc, xr1[i], dr1[i]);
		}


		//R sweep for region 2
#pragma omp parallel for
		for (int i = zne+1; i < m-1; ++i){

			for (int j = 1; j < n-1; ++j) {
				dr2[i-zne][j] = -dr2_[i-zne-1][j] * coe.znec[m-1-i]
						        -dr2_[i-zne][j] * (-coe.znea[m-1-i] - coe.znec[m-1-i])
					     	    -dr2_[i-zne][j] * 2.0/deltaT
						        -dr2_[i-zne+1][j] * coe.znea[m-1-i];
			}

			for (int j = n+1; j < 2*n-1; ++j) {
				dr2[i-zne][j] = -dr2_[i-zne-1][j] * coe.znea[m+i]
							    -dr2_[i-zne][j] * (-coe.znea[m+i] - coe.znec[m+i])
							    -dr2_[i-zne][j] * 2.0/deltaT
							    -dr2_[i-zne+1][j] * coe.znec[m+i];
			}

			dr2[i-zne][0] = 0.0;
			dr2[i-zne][n-1] = 0.0;
			dr2[i-zne][n] = 0.0;
			dr2[i-zne][2*n-1] = 0.0;
			tarne[omp_get_thread_num()]->Solve_TA(coe.rnea, coe.rneb, coe.rnec, xr2[i-zne], dr2[i-zne]);
		}

		//copy concentrations
		for (int i = rne; i < n; ++i) {
			for (int j = 1; j < zne+1; ++j) {
				conca[i][j] = xr1[j][n-1-i];
				concb[i][j] = xr1[j][(n-2*rne)+i];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = zne+1; j < m-1; ++j) {
				 conca[i][j] = xr2[j-zne][n-1-i];
				 concb[i][j] = xr2[j-zne][i+n];
			}
		}


		//compute the flux on the side electrode
		double flux2 = 0.0;
		for (int j = 1; j < zne; ++j) {
			double J3 = (conca[rne+1][j]-conca[rne][j]);
			flux2 -= (1/h0)*(J3)*((grids.Zgrid()->at(j))-(grids.Zgrid()->at(j-1)));
		}
		Jandtheta2<<Theta<<"\t"<<flux2<<"\n";


		//output the concentration profile
		if (recordtime.size()!=0 && k == recordtime[index]) {
			for (int j = 0; j < m; j++) {
				for (int l = 0; l < n; ++l){
					CONCA<<conca[l][j]<<'\t';
				}
				CONCA<<'\n';
			}
			for (int j = 0; j < m; ++j) {
				for (int l = 0; l < n; ++l){
					CONCB<<concb[l][j]<<'\t';
				}
						CONCB<<'\n';
			}
			index++;
			if(index == (int)recordtime.size() ){
				CONCA.close();
				CONCB.close();
				if (conconly == "Y" ||conconly== "y") {
					break;
				}
			}

		}

		if ((peakheightonly== "Y"||peakheightonly=="y") && k == 5*No_Timesteps/16) {
			break;
		}

	}

	//Jandtheta1.close();
	Jandtheta2.close();
	mass.close();
    double totaltime;
    totaltime = difftime(time(NULL),Start);
    cout << "time: " << totaltime<< " s"<< endl;
    cout<<">>>finish"<<endl<<endl;
	return 0;
}



