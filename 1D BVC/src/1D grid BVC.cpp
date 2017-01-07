#include "1D grid BVC.h"

//initialise all the private members
One_d_Grids::One_d_Grids(int length) {

	m_No_Spacesteps = length;
	m_deltaX = 0;
	m_exp_deltaX = 0;
	m_exp_base = 0;
	grid.resize(m_No_Spacesteps);
	conc.resize(2*m_No_Spacesteps);
}


//Overload set_grid functions for exponential or linear grids
//For linear girds:
void One_d_Grids::set_grid(double deltaX){
	m_deltaX = deltaX;
	for (int j = 0; j < m_No_Spacesteps; ++j) {
		grid[j]= m_deltaX*(j);
	}
}
//For exponential grids:
void One_d_Grids::set_grid(double exp_deltaX, double exp_base){
	m_exp_deltaX = exp_deltaX;
	m_exp_base= exp_base;

    for (int l = 0; l < m_No_Spacesteps; ++l) {
    	grid[l] = m_exp_deltaX*pow(m_exp_base,l)+grid[l-1];
   	}
}


//Overload set_conc functions for uniform or spike concentrations
//For uniform concentrations
void One_d_Grids::set_initialconcforab(double initialconc_a,double initialconc_b){
	for (int i = 0; i < 2*m_No_Spacesteps; ++i) {
		if (i<m_No_Spacesteps) {
			conc[i] = initialconc_a;
		} else {
			conc[i] =  initialconc_b;
		}

	}
}
//For spike concentrations
void One_d_Grids::set_initialconc(double initialconc, double spike){
	for (int i = 0; i < m_No_Spacesteps; ++i) {
			conc[i] =  initialconc;
		}
	conc[m_No_Spacesteps/2] = spike;
}


//Reset the first and last concentrations
void One_d_Grids::set_FisrtAndLastconc(vector<double> new_conc, double theta){
	//the first concentration is always equal to 1.0/(1.0+exp(-theta))
	conc[0] = 1.0/( 1.0 + exp(-theta));
	//the last concentration is always equal to 1
    conc[m_No_Spacesteps-1] = 1;
}

void One_d_Grids::set_FisrtAndLastconc(double bulkconc_a, double bulkconc_b){
	conc[0] = bulkconc_a;
	conc[m_No_Spacesteps-1] = 0.0;
	conc[m_No_Spacesteps] = 1.0;
	conc[2*m_No_Spacesteps-1] = bulkconc_b;
}

//Save all the values of grids and concentrations.
void One_d_Grids::concvsgrid(){
	fstream GridAndConc ("Grid And Conc.txt", ofstream::out);
	for (int i = 0; i < m_No_Spacesteps; ++i){
		GridAndConc<<grid[i]<<'\t'<<conc[i]<<endl;
	}
	GridAndConc.close();
}


//compute and return the gradient at a specific position
double One_d_Grids::get_gradient(int pst){
	//return -(-conc[pst+1]+4*conc[pst]-3*conc[pst-1])/(2*m_deltaX);
	return (conc[pst]-conc[pst-1])/(m_deltaX);
}


//return the grid and concentration
vector<double>* One_d_Grids::get_grid(){return &grid;}

One_d_Grids::~One_d_Grids(){}


