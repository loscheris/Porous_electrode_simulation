/*
 * TwoDgrids.cpp
 *
 *  Created on: 3 Nov 2015
 *      Author: jesu2419
 */

#include "PorousTwoDgrids.h"

TwoD_grids::TwoD_grids(double h, double omega) {
	m_omega = omega;
	h0 = h;
	mz_h = h;
	mr_h = h;
	Z.push_back(0.0);
	R.push_back(0.0);
	sizeofzne = 0;
	sizeofrne = 0;
}


//Make Z girds
void TwoD_grids::makeZgrids(double maxZ,double height){

	if (height != 0) {
		while(Z.back()+mz_h < height/2){
			Z.push_back(Z.back()+ mz_h);
			mz_h *= m_omega;
		}

		Z.push_back(height/2);

		for (int i = Z.size()-2; i >= 0; i--) {
			Z.push_back(height-Z[i]);
		}

		mz_h = h0;
		sizeofzne = Z.size();

		while(Z.back() < maxZ){
			Z.push_back(Z.back()+mz_h);
			mz_h *= m_omega;
		}
	}else{
		sizeofzne = Z.size();

		while(Z.back() < maxZ){
			Z.push_back(Z.back()+mz_h);
			mz_h *= m_omega;
		}
	}

	fstream Zgirds ("data_GridZ.txt",ofstream::out);
	for (int i = 0; i < sizeofZ(); ++i) {
		Zgirds.precision(10);
		Zgirds<<Z[i]<<'\n';
	}
	Zgirds.close();
}


//Make R grids
void TwoD_grids::makeRgrids(double maxR, double width){
	if (width != 0) {
		while(R.back()< width/2){
			R.push_back(R.back()+mr_h);
			mr_h *= m_omega;
		}

		R.back()= width/2;

		for (int i = R.size()-2; i >= 0; i--) {
			R.push_back(width-R[i]);
		}

		sizeofrne = R.size();
		mr_h = h0;

		while(R.back() < maxR){
			R.push_back(R.back()+mr_h);
			mr_h *= m_omega;
		}
	}else{
		sizeofrne = R.size();

		while(R.back() < maxR){
			R.push_back(R.back()+mr_h);
			mr_h *= m_omega;
		}
	}

	fstream Rgirds ("data_GridR.txt",ofstream::out);
	for (int i = 0; i < sizeofR(); ++i) {
		Rgirds.precision(10);
		Rgirds<<R[i]<<'\n';
	}
	Rgirds.close();
}


int TwoD_grids::sizeofZ(){return Z.size();}
int TwoD_grids::sizeofRNE(){return sizeofrne;}
int TwoD_grids::sizeofZNE(){return sizeofzne;}
int TwoD_grids::sizeofR(){return R.size();}
vector<double> *TwoD_grids::Zgrid(){return &Z;}
vector<double> *TwoD_grids::Rgrid(){return &R;}

TwoD_grids::~TwoD_grids() {}


