//============================================================================
// Name        : One.cpp
// Author      : Zhiyong Ban
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include "TA_class.h"
#include <fstream>

#include "1D grid Nernst.h"
#include "1D TAceo Nernst.h"
using namespace std;

int main() {

	double theta_i = 20.0;
	double theta_v = -20.0;
	double sigma = 100.0;
	double deltaX = 2e-4;
	double deltaTheta= 0.02;
	double deltaT = deltaTheta / sigma ;
	double maxT = 2*fabs(theta_v-theta_i)/sigma;
	double maxX = 6*sqrt(maxT);
	int No_Timesteps = (int)(maxT / deltaT);
	int No_Spacesteps = (int)(maxX / deltaX);

	//compute the ThomasCoefficients a,b,c
	ThomasCoefficients *TA_coe = new ThomasCoefficients(deltaT,deltaX,No_Spacesteps);
	TA_coe->Set_abc();

	//initialise concentrations and grids
	One_d_Grids *grid = new One_d_Grids(No_Spacesteps);
	grid->set_grid(deltaX);
	grid->set_initialconc(1.0);

	//create ThomasAlgorithm
	ThomasAlgorithm *TA = new ThomasAlgorithm(grid->conc);

	//create files to store J and ThetaValue
	fstream JandTheta ("J and Theta.txt", ofstream::out);

	//initialise Theta
	double Theta = theta_i;

	//Compute the J and Theta values at each timestep
	for (int i = 0; i < No_Timesteps; ++i) {

		//renew the value of Theta at each timestep
		if (i < No_Timesteps/2) {Theta -= deltaTheta;}
		else{Theta += deltaTheta;}

		//Reset the first and last concentrations (boundary conditions)
		grid->set_FisrtAndLastconc(grid->conc,Theta);

        //solve the ThomasAlgorithm using previous concentration values, and rewrite the solutions to the grid.conc
        TA->Solve_TA(*TA_coe->get_a(),*TA_coe->get_b(),*TA_coe->get_c(), grid->conc, grid->conc);

        //ouput the Theta and J values at each timestep
        JandTheta<<Theta<<"\t"<<grid->get_gradient(1)<<"\n";
	}

	//close files
	JandTheta.close();
    cout<<"finish"<<endl;
	return 0;
}
