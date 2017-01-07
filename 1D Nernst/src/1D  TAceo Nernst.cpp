/*
 * ThomasCoefficients.cpp
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include "1D TAceo Nernst.h"

using namespace std;

//deltaT,deltaX are used to compute the lambda value
//No_spacesteps is used to define the size of a,b,c
ThomasCoefficients::ThomasCoefficients(double deltaT, double deltaX, int No_Spacesteps) {
	lambda = deltaT / (deltaX*deltaX);
	m_spacesteps = No_Spacesteps;
    TA_a.resize(m_spacesteps-1);
    TA_b.resize(m_spacesteps);
    TA_c.resize(m_spacesteps-1);
}


//compute values for a,b,c;
void ThomasCoefficients::Set_abc(){
	//compute vector a:
	TA_a[m_spacesteps-2]=0;
	for (int i = 0; i < m_spacesteps-2; ++i)
		TA_a[i] = -lambda;

	//compute vector b and c:
	TA_b[0] = 1;
	TA_b[m_spacesteps-1] = 1;
	TA_c[0] = 0;
	for (int j = 1; j < m_spacesteps-1; ++j) {
		TA_b[j] = 2.0*lambda +1.0;
		TA_c [j]= -lambda;
	}
}


void ThomasCoefficients::print(){
	fstream abc("ThomasCoefficients.txt", fstream::out);
	for (int i = 0; i < m_spacesteps-1; ++i) {
		abc<<TA_a[i]<<"\t"<<TA_b[i]<<"\t"<<TA_c[i]<<"\n";
	}
	abc<<"\t"<<TA_b[m_spacesteps-1]<<endl;
}

//return vector a,b,c
vector<double>* ThomasCoefficients::get_a(){return &TA_a;}
vector<double>* ThomasCoefficients:: get_b(){return &TA_b;}
vector<double>* ThomasCoefficients::get_c(){return &TA_c;}

ThomasCoefficients::~ThomasCoefficients() {}

