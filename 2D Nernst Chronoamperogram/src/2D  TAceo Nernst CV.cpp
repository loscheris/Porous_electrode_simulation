/*
 * ThomasCoefficients.cpp
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include "2D TAceo Nernst CV.h"
using namespace std;

ThomasCoefficients::ThomasCoefficients(int No_Z, int No_R, double deltaT) {
	this->No_R = No_R;
	this->No_Z = No_Z;
	Z_a.resize(No_Z);
	Z_b.resize(No_Z);
	Z_c.resize(No_Z);
	Zne_a.resize(No_Z);
	Zne_b.resize(No_Z);
	Zne_c.resize(No_Z);
	R_a.resize(No_R);
	R_b.resize(No_R);
	R_c.resize(No_R);
	this->deltaT = deltaT;

}

//compute values for a,b,c;
//when z is within the electrode
void ThomasCoefficients::Z_abc(vector<double> &Z){
	for (int i = 1; i < No_Z-1; ++i) {
		Z_a[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}
	Z_b[0] = 1.0;
	Z_b[No_Z-1] = 1.0;
}

//when z is out of the electrode
void ThomasCoefficients::Zne_abc(vector<double> &Z){
	for (int i = 1; i < No_Z-1; ++i) {
		Zne_a[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Zne_c[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Zne_b[i] = -Zne_a[i]-Zne_c[i]-2.0/deltaT;
	}
	Zne_c[0] = 1.0;
	Zne_b[0] = -1.0;
	Zne_b[No_Z-1] = 1.0;
}

//R coefficients, similar as the z (out of electrode)
void ThomasCoefficients::R_abc(vector<double> &R){
	for (int i = 1; i < No_R-1; ++i) {
		R_a[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		R_c[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		R_b[i] = -R_a[i]-R_c[i]-2.0/deltaT;
	}
	R_c[0] = 1.0;
	R_b[0] = -1.0;
	R_b[No_R-1] = 1.0;

}


ThomasCoefficients::~ThomasCoefficients() {}

