/*
 * ThomasCoefficients.h
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//TA_a, TA_b and TA_c are the coefficients a,b,c in the ThomasAlgorithm
//a,b,c are all related to lambda
//m_spacesteps is used to determine the size of a,b,c

class ThomasCoefficients {
private:
	double lambda;
	vector<double> TA_a;
	vector<double> TA_b;
	vector<double> TA_c;
	int m_spacesteps;

public:
	ThomasCoefficients(double deltaT, double deltaX, int No_Spacesteps);
	void Set_abc();
    vector<double>* get_a();
    vector<double>* get_b();
    vector<double>* get_c();
    void print();
	~ThomasCoefficients();
};
