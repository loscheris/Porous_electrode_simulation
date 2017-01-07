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

#include "1D grid NernstC.h"
#include "1D TAceo NernstC.h"
using namespace std;

int main() {
	double deltaX = 2e-5;
	double deltaT = 2e-6;
	double maxT = 0.008;
	int No_Timesteps = (int)(maxT/deltaT);
	double maxX = 6*sqrt(maxT);
	int No_Spacesteps = (int)(maxX/deltaX);

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
	fstream JandT("J and T.txt", ofstream::out);

	//Compute the J and Theta values at each timestep
	for (int i = 0; i < No_Timesteps; ++i) {

		//Reset the first and last concentrations (boundary conditions)
		grid->set_FisrtAndLastconc(0.0,1.0);

        //solve the ThomasAlgorithm using previous concentration values, and rewrite the solutions to the grid.conc
        TA->Solve_TA(*TA_coe->get_a(),*TA_coe->get_b(),*TA_coe->get_c(), grid->conc, grid->conc);

        //ouput the Theta and J values at each timestep
        if (i != 0) {
        	JandT<<i*deltaT<<"\t"<<grid->get_gradient(1)<<"\n";
		}

        if (i==1500) {
			grid->concvsgrid();
        }

	}

	//close files
	JandT.close();
    cout<<"finish"<<endl;
	return 0;
}
