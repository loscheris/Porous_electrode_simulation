//============================================================================
// Name        : One.cpp
// Author      : Zhiyong Ban
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//c = 1 mol/m^3
//r = 1e-3 mm
//Da = 1e-9 m^2/s
//Db = 1.1e-9 m^2/s
//k = 0.1 m/s

#include <iostream>
#include <vector>
#include <cmath>
#include "TA_class.h"
#include <fstream>

#include "1D grid BV.h"
#include "1D TAcoe BV.h"
using namespace std;

int main() {
	//direction true: A to B
	//direction false: B to A
	bool direction = 1;
	double theta_i;
	double theta_v;
	double conca;
	double concb;

	if (direction) {
		theta_i = 20.0;
		theta_v = -20.0;
		conca = 1.0;
		concb = 0.0;
	} else {
		theta_i = -20.0;
		theta_v = +20.0;
		conca = 0.0;
		concb = 1.0;
	}

	double sigma = 1;
	double deltaX = 1e-4;
	double deltaTheta= 0.02;
	double deltaT = deltaTheta / sigma ;
	double maxT = 2*fabs(theta_v-theta_i)/sigma;
	double maxX = 6*sqrt(maxT);
	int No_Timesteps = (int)(maxT / deltaT);
	int No_Spacesteps = (int)(maxX / deltaX);
	double totalmass;

	//compute the ThomasCoefficients a,b,c
	ThomasCoefficients *TA_coe = new ThomasCoefficients(deltaT,deltaX,No_Spacesteps);
	TA_coe->Set_abc();

	//initialise concentrations and grids
	One_d_Grids *grid = new One_d_Grids(No_Spacesteps);
	grid->set_grid(deltaX);
	grid->set_initialconcforab(conca,concb);

	//create ThomasAlgorithm
	ThomasAlgorithm *TA = new ThomasAlgorithm(grid->conc);

	//create files to store J and ThetaValue
	fstream JandTheta ("J and Theta.txt", ofstream::out);
	fstream masstest ("Mass test.txt", ofstream::out);
	//initialise Theta
	double Theta = theta_i;

	//Compute the J and Theta values at each timestep
	for (int i = 0; i < No_Timesteps; ++i) {

		//renew the value of Theta at each timestep
		if (direction) {
			if (i < No_Timesteps/2) {Theta -= deltaTheta;}
			else{Theta += deltaTheta;}
		} else {
			if (i < No_Timesteps/2) {Theta += deltaTheta;}
			else{Theta -= deltaTheta;}
		}

		//Reset the first and last concentrations (boundary conditions)
		grid->set_FisrtAndLastconc(conca,concb);

		//update the TA coefficients
		TA_coe->update_abc(Theta);

		//solve the ThomasAlgorithm using previous concentration values, and rewrite the solutions to the grid.conc
        TA->Solve_TA(*TA_coe->get_c(),*TA_coe->get_b(),*TA_coe->get_a(), grid->conc, grid->conc);

        //ouput the Theta and J values at each timestep
        JandTheta<<Theta<<"\t"<<grid->get_gradient(No_Spacesteps-1)<<"\n";

        //test the mass conservation
        for (int j = 1; j < No_Spacesteps; ++j) {
			totalmass = (grid->conc[No_Spacesteps-1-j]+grid->conc[No_Spacesteps +j])*deltaX;
		}
        masstest<<totalmass<<"\n";
	}

	//close files
	JandTheta.close();
	masstest.close();
    cout<<"finish"<<endl;
	return 0;
}
