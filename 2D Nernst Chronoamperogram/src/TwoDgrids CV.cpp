/*
 * TwoDgrids.cpp
 *
 *  Created on: 3 Nov 2015
 *      Author: jesu2419
 */

#include "TwoDgrids CV.h"

TwoD_grids::TwoD_grids(double h, double omega) {
	m_omega = omega;
	h0 = h;
	mz_h = h;
	mr_h = h;
	Z.push_back(0.0);
	R.push_back(0.0);
	sizeofne = 0;
}

//Make Z girds
void TwoD_grids::makeZgrids(double maxZ){

	while(Z.back() < maxZ){
		Z.push_back(Z.back()+ mz_h);
		mz_h *= m_omega;
	}

//	fstream Zgirds ("Zgrids.txt",ofstream::out);
//	for (int i = 0; i < sizeofZ(); ++i) {
//		Zgirds<<Z[i]<<'\n';
//	}
//	Zgirds.close();
}


//Make R grids
void TwoD_grids::makeRgrids(double maxR){
	while(R.back()<0.5){
		R.push_back(R.back()+mr_h);
		mr_h *= m_omega;
	}

	R.back()= 0.5;

	for (int i = R.size()-2; i >= 0; i--) {
		R.push_back(1-R[i]);
	}
	sizeofne = R.size();


	while(R.back() < maxR){
		R.push_back(R.back()+h0);
		h0 *= m_omega;
	}

//	fstream Rgirds ("Rgrids.txt",ofstream::out);
//	for (int i = 0; i < sizeofR(); ++i) {
//		Rgirds<<R[i]<<'\n';
//	}
//	Rgirds.close();
}



int TwoD_grids::sizeofZ(){return Z.size();}
int TwoD_grids::sizeofNE(){return sizeofne;}
int TwoD_grids::sizeofR(){return R.size();}
vector<double> *TwoD_grids::Zgrid(){return &Z;}
vector<double> *TwoD_grids::Rgrid(){return &R;}



TwoD_grids::~TwoD_grids() {

}


