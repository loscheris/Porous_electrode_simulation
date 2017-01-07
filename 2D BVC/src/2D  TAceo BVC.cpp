/*
 * ThomasCoefficients.cpp
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include "2D TAceo BVC.h"
using namespace std;

ThomasCoefficients::ThomasCoefficients(int No_Z, int No_R, double deltaT,double K,double alpha, double db, double h) {
	this->No_R = No_R;
	this->No_Z = No_Z;
	this->deltaT = deltaT;
	this->K = K;
	this->alpha = alpha;
	this->theta = -20;
	this->db = db;
	this-> h = h;
	Z_a.resize(No_Z); Z_b.resize(No_Z); Z_c.resize(No_Z);
	Zne_a.resize(No_Z); Zne_b.resize(No_Z); Zne_c.resize(No_Z);
	za.resize(2*No_Z); zb.resize(2*No_Z);zc.resize(2*No_Z);
	znea.resize(2*No_Z); zneb.resize(2*No_Z);znec.resize(2*No_Z);
	ra.resize(No_R); rb.resize(No_R); rc.resize(No_R);
	rba.resize(No_R); rbb.resize(No_R); rbc.resize(No_R);
}


//compute values for a,b,c;
//when z is within the electrode
void ThomasCoefficients::Z_abc(vector<double> &Z){
	//z coefficient for A
	for (int i = 1; i < No_Z-1; ++i) {
		Z_a[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}
	for (int i = 1; i < No_Z-1; ++i) {
		zc[i] = Z_a[No_Z-1-i];
		zb[i] = Z_b[No_Z-1-i];
		za[i] = Z_c[No_Z-1-i];
	}
	//z coefficient for B
	for (int i = 1; i < No_Z-1; ++i) {
		Z_a[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}
	for (int i = No_Z+1; i < 2*No_Z-1; ++i) {
		zc[i] = Z_c[i-No_Z];
		zb[i] = Z_b[i-No_Z];
		za[i] = Z_a[i-No_Z];
	}

	//boundary conditions
	za[0]=0.0; zb[0]=1.0; zc[0]=0.0;
	za[No_Z-1]= -1.0;
	zb[No_Z-1]=1+K*(h)*exp(-alpha*theta);
	zc[No_Z-1]=-K*(h)*exp(theta*(1-alpha));
	za[No_Z] = -(1/db)*(h)*K*exp(-alpha*theta);
	zb[No_Z] = 1+(1/db)*(h)*K*exp(theta*(1-alpha));
	zc[No_Z] = -1.0;
	za[2*No_Z-1] = 0.0; zb[2*No_Z-1] = 1.0; zc[2*No_Z-1] = 0.0;
}


//when z is out of the electrode
void ThomasCoefficients::Zne_abc(vector<double> &Z){
	for (int i = 1; i < 2*No_Z; ++i) {
		znec[i] = zc[i];
		zneb[i] = zb[i];
		znea[i] = za[i];
	}
	//boundary conditions
	znea[0]=0.0; zneb[0]=1.0; znec[0]=0.0;
	znea[No_Z-1]= 1.0;
	zneb[No_Z-1]= -1.0;
	znec[No_Z-1]= 0.0;
	znea[No_Z] = 0.0;
	zneb[No_Z] = -1.0;
	znec[No_Z] = 1.0;
	znea[2*No_Z-1] = 0.0; zneb[2*No_Z-1] = 1.0;	znec[2*No_Z-1] = 0.0;
}


void ThomasCoefficients::updatetheta(double theta){
	zb[No_Z-1]=1+K*(h)*exp(-alpha*theta);
	zc[No_Z-1]=-K*(h)*exp(theta*(1-alpha));
	za[No_Z] = -(1/db)*(h)*K*exp(-alpha*theta);
	zb[No_Z] = 1+(1/db)*(h)*K*exp(theta*(1-alpha));

}


//R coefficients, similar as the zne (out of electrode)
void ThomasCoefficients::R_abc(vector<double> &R){
	for (int i = 1; i < No_R-1; ++i) {
		//R coefficients for A
		ra[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		rc[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		rb[i] = -ra[i]-rc[i]-2.0/deltaT;

		//R coefficients for B
		rba[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		rbc[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		rbb[i] = -rba[i]-rbc[i]-2.0/deltaT;
	}
	//boundary conditions
	ra[0]=0.0; rb[0] = -1.0; rc[0] = 1.0;
	ra[No_R-1]=0.0; rb[No_R-1] = 1.0; rc[No_R-1]=0.0;
	rba[0] = 0.0; rbb[0] = -1.0; rbc[0] = 1.0;
	rba[No_R-1] = 0.0; rbb[No_R-1] = 1.0; rbc[No_R-1] = 0.0;
}

ThomasCoefficients::~ThomasCoefficients() {}

