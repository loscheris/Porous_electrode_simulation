/*
 * TwoDgrids.h
 *
 *  Created on: 3 Nov 2015
 *      Author: jesu2419
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


class TwoD_grids {
private:
	vector<double> Z;
	vector<double> R;
	double mz_h;
	double mr_h;
	double h0;
	double m_omega;
	int sizeofne;


public:
	TwoD_grids(double h, double omega);
	void makeZgrids(double maxZ);
	void makeRgrids(double maxR);
	int sizeofZ();
	int sizeofR();
	int sizeofNE();
	vector<double> *Zgrid();
	vector<double> *Rgrid();
	friend class ThomasCoefficients;
	~TwoD_grids();
};

