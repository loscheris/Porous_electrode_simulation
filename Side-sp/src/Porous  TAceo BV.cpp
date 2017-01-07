/*
 * ThomasCoefficients.cpp
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include "Porous TAceo BV.h"
using namespace std;

ThomasCoefficients::ThomasCoefficients(int maxZ, int maxR, int zne, int rne, double deltaT,
									   double K,double alpha, double db, double h)
{
	this->maxR = maxR;
	this->maxZ = maxZ;
	this->zne = zne;
	this->rne = rne;
	this->deltaT = deltaT;
	this->K = K;
	this->alpha = alpha;
	this->theta = -20;
	this->db = db;
	this-> h = h;
	Z_a.resize(maxZ); Z_b.resize(maxZ); Z_c.resize(maxZ);
	R_a.resize(maxR); R_b.resize(maxR); R_c.resize(maxR);
	za.resize(2*(maxZ-zne)); zb.resize(2*(maxZ-zne));zc.resize(2*(maxZ-zne));
	znea.resize(2*maxZ); zneb.resize(2*maxZ);znec.resize(2*maxZ);
	ra.resize(2*(maxR-rne)); rb.resize(2*(maxR-rne)); rc.resize(2*(maxR-rne));
	rnea.resize(2*maxR); rneb.resize(2*maxR); rnec.resize(2*maxR);
}


//Z coefficients in region 1
void ThomasCoefficients::Z_abc(vector<double> &Z){
	//z coefficient for A
	for (int i = zne+1; i < maxZ-1; ++i) {
		Z_a[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}

	for (int i = 1; i < maxZ-zne-1; ++i) {
		zc[i] = Z_a[maxZ-1-i];
		zb[i] = Z_b[maxZ-1-i];
		za[i] = Z_c[maxZ-1-i];
	}

	//z coefficient for B
	for (int i = zne+1; i < maxZ-1; ++i) {
		Z_a[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}

	for (int i = maxZ-zne+1; i < 2*(maxZ-zne)-1; ++i) {
		zc[i] = Z_c[i+(2*zne-maxZ)];
		zb[i] = Z_b[i+(2*zne-maxZ)];
		za[i] = Z_a[i+(2*zne-maxZ)];
	}

	//boundary conditions
	za[0]=0.0; zb[0] = 1.0; zc[0]=0.0;
	za[maxZ-zne-1] = 1.0;
	zb[maxZ-zne-1] = -1.0;
	zc[maxZ-zne-1] = 0.0;
	za[maxZ-zne] = 0.0;
	zb[maxZ-zne] = -1.0;
	zc[maxZ-zne] = 1.0;
	za[2*(maxZ-zne)-1] = 0.0; zb[2*(maxZ-zne)-1] = 1.0; zc[2*(maxZ-zne)-1] = 0.0;


}

//Z coefficients in region 2
void ThomasCoefficients::Zne_abc(vector<double> &Z){
	for (int i = 1; i < maxZ-1; ++i) {
		Z_a[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = 2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}

	for (int i = 1; i < maxZ-1; ++i) {
		znec[i] = Z_a[maxZ-1-i];
		znea[i] = Z_c[maxZ-1-i];
		zneb[i] = Z_b[maxZ-1-i];
	}

	for (int i = 1; i < maxZ-1; ++i) {
		Z_a[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i]-Z[i-1]));
		Z_c[i] = db*2.0/((Z[i+1]-Z[i-1])*(Z[i+1]-Z[i]));
		Z_b[i] = -Z_a[i]-Z_c[i]-2.0/deltaT;
	}

	for (int i = maxZ+1; i < 2*maxZ-1; ++i) {
		znea[i] = Z_a[i-maxZ];
		zneb[i] = Z_b[i-maxZ];
		znec[i] = Z_c[i-maxZ];
	}

	//boundary conditions
	znea[0] = 0.0; zneb[0] = 1.0; znec[0] = 0.0;
	znea[maxZ-1] = 1.0;
	zneb[maxZ-1] = -1.0;
	znec[maxZ-1] = 0.0;
	znea[maxZ] = 0.0;
	zneb[maxZ] = -1.0;
	znec[maxZ] = 1.0;
	znea[2*maxZ-1] = 0.0; zneb[2*maxZ-1] = 1.0;	znec[2*maxZ-1] = 0.0;
}


//R coefficients in region 1
void ThomasCoefficients::R_abc(vector<double> &R){
	for (int i = rne+1; i < maxR-1; ++i) {
		//R coefficients for A
		R_a[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		R_c[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		R_b[i] = -R_a[i]-R_c[i]-2.0/deltaT;
	}

	for (int i = 1; i < maxR-rne-1; ++i) {
		rc[i] = R_a[maxR-1-i];
		rb[i] = R_b[maxR-1-i];
		ra[i] = R_c[maxR-1-i];
	}

	for (int i = rne+1; i < maxR-1; ++i) {
	//R coefficients for B
		R_a[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		R_c[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		R_b[i] = -R_a[i]-R_c[i]-2.0/deltaT;
	}

	for (int i = maxR-rne+1; i < 2*(maxR-rne)-1; ++i) {
		rc[i] = R_c[i+(2*rne-maxR)];
		rb[i] = R_b[i+(2*rne-maxR)];
		ra[i] = R_a[i+(2*rne-maxR)];
	}

	//boundary conditions
	ra[0]=0.0; rb[0] = -1.0; rc[0] = 1.0;
	ra[maxR-rne-1] = -1.0;
	rb[maxR-rne-1] = 1+K*(h)*exp(-alpha*theta);
	rc[maxR-rne-1] = -K*(h)*exp(theta*(1-alpha));
	ra[maxR-rne] = -(1/db)*(h)*K*exp(-alpha*theta);
	rb[maxR-rne] = 1+(1/db)*(h)*K*exp(theta*(1-alpha));
	rc[maxR-rne] = -1.0;
	ra[2*(maxR-rne)-1] = 1.0; rb[2*(maxR-rne)-1] = -1.0; rc[2*(maxR-rne)-1] = 0.0;
//	fstream coe("coeofz.txt", ofstream::out);
//	for (int i = 0; i < za.size(); ++i) {
//		coe<<za[i]<<'\t'<<zc[i]<<'\n';
//	}
//	coe.close();
}

//R coefficients in region 2
void ThomasCoefficients::Rne_abc(vector<double> &R){
	for (int i = 1; i < maxR-1; ++i) {
		R_a[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		R_c[i] = (1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		R_b[i] = -R_a[i]-R_c[i]-2.0/deltaT;
	}

	for (int i = 1; i < maxR-1; ++i) {
		rnea[i] = R_c[maxR-1-i];
		rneb[i] = R_b[maxR-1-i];
		rnec[i] = R_a[maxR-1-i];
	}

	for (int i = 1; i < maxR-1; ++i) {
		R_a[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i]-R[i-1]) - 1.0/R[i]);
		R_c[i] = db*(1.0/(R[i+1]-R[i-1])) * (2.0/(R[i+1]-R[i]) + 1.0/R[i]);
		R_b[i] = -R_a[i]-R_c[i]-2.0/deltaT;
	}

	for (int i = maxR+1; i < 2*maxR-1; ++i) {
		rnea[i] = R_a[i-maxR];
		rneb[i] = R_b[i-maxR];
		rnec[i] = R_c[i-maxR];
	}

	rnea[0] = 0.0; rneb[0] = -1.0; rnec[0] = 1.0;
	rnea[maxR-1] = 1.0;
	rneb[maxR-1] = -1.0;
	rnec[maxR-1] = 0.0;
	rnea[maxR] = 0.0;
	rneb[maxR] = -1.0;
	rnec[maxR] = 1.0;
	rnea[2*maxR-1] = 1.0; rneb[2*maxR-1] = -1.0; rnec[2*maxR-1] = 0.0;
}

//update theta
void ThomasCoefficients::updatetheta(double theta){
//	zb[maxZ-zne-1] = 1+K*(h)*exp(-alpha*theta);
//	zc[maxZ-zne-1] = -K*(h)*exp(theta*(1-alpha));
//	za[maxZ-zne] = -(1/db)*(h)*K*exp(-alpha*theta);
//	zb[maxZ-zne] = 1+(1/db)*(h)*K*exp(theta*(1-alpha));

	rb[maxR-rne-1] = 1+K*(h)*exp(-alpha*theta);
	rc[maxR-rne-1] = -K*(h)*exp(theta*(1-alpha));
	ra[maxR-rne] = -(1/db)*(h)*K*exp(-alpha*theta);
	rb[maxR-rne] = 1+(1/db)*(h)*K*exp(theta*(1-alpha));
}

ThomasCoefficients::~ThomasCoefficients() {}

