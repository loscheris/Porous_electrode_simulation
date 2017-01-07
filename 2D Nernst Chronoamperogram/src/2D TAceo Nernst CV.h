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



class ThomasCoefficients {
private:
	int No_Z, No_R;
	double deltaT;

public:
	vector<double> Z_a, Z_b, Z_c;
	vector<double> Zne_a,Zne_b,Zne_c;
	vector<double> R_a, R_b, R_c;

	ThomasCoefficients(int No_Z, int No_R, double deltaT);
	void Z_abc(vector<double> &Z);
	void Zne_abc(vector<double> &Z);
	void R_abc(vector<double> &R);

    void print();
	~ThomasCoefficients();
};


