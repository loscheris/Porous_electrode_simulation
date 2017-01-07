/*
 * ThomasCoefficients.h
 *
 *  Created on: 20 Oct 2015
 *      Author: jesu2419
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;



class ThomasCoefficients {
private:
	int No_Z, No_R;
	double deltaT;
	double K;
	double alpha;
	double theta;
	double db;
	double h;
	vector<double> Z_a, Z_b, Z_c;
	vector<double> Zne_a,Zne_b,Zne_c;


public:
	vector<double> za,zb,zc;
	vector<double>	znea,zneb,znec;
	vector<double> ra, rb, rc;
	vector<double> rba,rbb,rbc;
	ThomasCoefficients(int No_Z, int No_R, double deltaT,double K,double alpha, double db, double h);
	void Z_abc(vector<double> &Z);
	void Zne_abc(vector<double> &Z);
	void R_abc(vector<double> &R);
	void updatetheta(double theta);

    void print();
	~ThomasCoefficients();
};


