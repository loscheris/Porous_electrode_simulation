//============================================================================
// Name        : Grids.cpp
// Author      : Zhiyong Ban
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "OnedGrids.h"
#include <vector>
using namespace std;



int main() {

	int length =10;

    One_d_Grids *test = new One_d_Grids(length);

    //set_grid(linear_differece) for linear grids
    //set_grid(exponential delta X, exponential base) for exponential grids
    test->set_grid(1);

    //set_conc(constant) for uniform distribution of concentration
    //set_conc(constant, spike) for spike distribution
    test->set_initialconc(1.0);
    test->concvsgrid();
    cout<< "The gradient is: "<<test->get_gradient(3)<<endl;

    cout<<test->get_grid()->at(9)<<endl;
    cout<<test->get_conc()->at(9)<<endl;

    delete test;
	return 0;
}
