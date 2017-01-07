#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

//m_No_Spacesteps: the total length of grids
//m_deltaX: the difference between neighbouring grids in linear case
//m_exp_deltaX: value of delta x in exponential case
//m_exp_base: the base of exponential in exponential case


class One_d_Grids {

private:
    vector<double> grid;
    int m_No_Spacesteps;
    double m_deltaX;
    double m_exp_deltaX;
    double m_exp_base;

public:
    vector<double> conc;
	One_d_Grids(int No_Spacesteps);
	~One_d_Grids();
	void set_grid(double deltaX);
	void set_grid(double exp_deltaX, double exp_base);
	void set_initialconc(double initialconc);
	void set_initialconc(double initialconc, double spike);
	void set_FisrtAndLastconc(vector<double> new_conc, double theta);
	void set_FisrtAndLastconc(double firstconc, double lastconc);
    void concvsgrid();
    double get_gradient(int pst);
    vector<double> *get_grid();
    vector<double> *get_conc();
};

