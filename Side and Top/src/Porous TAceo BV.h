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
	int maxZ, maxR, zne, rne;
	double deltaT;
	double K;
	double alpha;
	double theta;
	double db;
	double h;
	vector<double> Z_a, Z_b, Z_c;
	vector<double> R_a,R_b,R_c;


public:
	vector<double> za,zb,zc;
	vector<double>	znea,zneb,znec;
	vector<double> ra, rb, rc;
	vector<double> rnea,rneb,rnec;
	ThomasCoefficients(int maxZ, int maxR, int zne, int rne, double deltaT,double K,double alpha, double db, double h);
	void Z_abc(vector<double> &Z);
	void Zne_abc(vector<double> &Z);
	void R_abc(vector<double> &R);
	void Rne_abc(vector<double> &R);
	void updatetheta(double theta);

    void print();
	~ThomasCoefficients();
};


