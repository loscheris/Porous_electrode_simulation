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

#include "1D grid BVC.h"
#include "1D TAceo BVC.h"
using namespace std;

int main() {
	//direction true: A to B
	//direction false: B to A

	double conca;
	double concb;
	conca = 1.0;
	concb = 0.0;
	double deltaX = 2e-5;
	double deltaT = 2e-6;
	double maxT = 0.008;
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
	fstream JandTime ("J and Time.txt", ofstream::out);
	fstream masstest ("Mass test.txt", ofstream::out);
	//initialise Theta


	//Compute the J and Theta values at each timestep
	for (int i = 1; i < No_Timesteps; ++i) {

		//Reset the first and last concentrations (boundary conditions)
		grid->set_FisrtAndLastconc(conca,concb);

        //solve the ThomasAlgorithm using previous concentration values, and rewrite the solutions to the grid.conc
        TA->Solve_TA(*TA_coe->get_c(),*TA_coe->get_b(),*TA_coe->get_a(), grid->conc, grid->conc);

        //ouput the Theta and J values at each timestep
        JandTime<<i*deltaT<<"\t"<<grid->get_gradient(No_Spacesteps-1)<<"\n";

        for (int j = 1; j < No_Spacesteps; ++j) {
			totalmass = (grid->conc[No_Spacesteps-1-j]+grid->conc[No_Spacesteps +j])*deltaX;
		}
        masstest<<totalmass<<"\n";
	}

	//close files
	JandTime.close();
	masstest.close();
    cout<<"finish"<<endl;
	return 0;
}
