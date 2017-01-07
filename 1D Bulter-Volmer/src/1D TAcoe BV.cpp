/*
 * ThomasCoefficients.cpp
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include "1D TAcoe BV.h"

using namespace std;

//deltaT,deltaX are used to compute the lambda value
//No_spacesteps is used to define the size of a,b,c
ThomasCoefficients::ThomasCoefficients(double deltaT, double deltaX, int No_Spacesteps) {
	lambda = deltaT / (deltaX*deltaX);
	m_spacesteps = No_Spacesteps;
	m_deltaX = deltaX;
    TA_a.resize(2*m_spacesteps-1);
    TA_b.resize(2*m_spacesteps);
    TA_c.resize(2*m_spacesteps-1);
	db = 1.0;
	K = 1e-1;
	m_theta = 20.0;
	alpha = 0.5;
}


//compute values for a,b,c;
void ThomasCoefficients::Set_abc(){
	//compute vector a:
	TA_a[0]=0.0;
	TA_b[0] = 1.0;

	for (int i = 1; i < 2*m_spacesteps-1; ++i){
		if (i<m_spacesteps) {
			TA_a[i] = -lambda;
			TA_b[i] = 1+2*lambda;
		} else {
			TA_a[i] = -lambda*db;
			TA_b[i] = 1+2*db*lambda;
		}
	}

	TA_a[m_spacesteps-1] = -m_deltaX * K* exp((1-alpha)*m_theta);
	TA_a[m_spacesteps] = -1.0;

	TA_b[m_spacesteps-1] = 1+m_deltaX * K* exp(-alpha*m_theta);
	TA_b[m_spacesteps] = 1 + m_deltaX * K* exp((1-alpha)*m_theta)/db;
	TA_b[2*m_spacesteps-1] = 1.0;

	for (int j = 0; j < 2*m_spacesteps-2; ++j) {
		if (j< m_spacesteps-1) {
			TA_c[j]= -lambda;
		} else {
			TA_c[j]= -lambda*db;
		}
	}
	TA_c[m_spacesteps-2] = -1.0;
	TA_c[m_spacesteps-1] = -m_deltaX * K* exp(-alpha*m_theta)/db;
	TA_c[2*m_spacesteps-2] = 0.0;

}

void ThomasCoefficients::update_abc(double theta){
	m_theta = theta;
	TA_a[m_spacesteps-1] = -m_deltaX * K* exp((1-alpha)*m_theta);
	TA_c[m_spacesteps-1] = -m_deltaX * K* exp(-alpha*m_theta)/db;

	TA_b[m_spacesteps-1] = 1+m_deltaX * K* exp(-alpha*m_theta);
	TA_b[m_spacesteps] = 1 + m_deltaX * K* exp((1-alpha)*m_theta)/db;

}


void ThomasCoefficients::print(){
	fstream abc("ThomasCoefficients.txt", fstream::out);
	for (int i = 0; i < 2*m_spacesteps-1; ++i) {
		abc<<TA_a[i]<<"\t"<<TA_b[i]<<"\t"<<TA_c[i]<<"\n";
	}
	abc<<"\t"<<TA_b[2*m_spacesteps-1]<<endl;
}

//return vector a,b,c
vector<double>* ThomasCoefficients::get_a(){return &TA_a;}
vector<double>* ThomasCoefficients:: get_b(){return &TA_b;}
vector<double>* ThomasCoefficients::get_c(){return &TA_c;}

ThomasCoefficients::~ThomasCoefficients() {}

