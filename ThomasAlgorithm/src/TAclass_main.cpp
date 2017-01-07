#include <iostream>
#include <vector>
#include "TA_class.h"
using namespace std;



int main() {
	vector<double> a;
	vector<double> b;
	vector<double> c;
	vector<double> d;
	vector<double> x(5,1);

	a.push_back(0);
	a.push_back(3);
	a.push_back(3);
	a.push_back(5);
	a.push_back(0);

	b.push_back(1);
	b.push_back(2);
	b.push_back(2);
	b.push_back(2);
	b.push_back(1);

	c.push_back(0);
	c.push_back(1);
	c.push_back(4);
	c.push_back(1);
	c.push_back(0);

	d.push_back(2);
	d.push_back(16);
	d.push_back(37);
	d.push_back(36.7);
	d.push_back(6.7);

	//x should = 2, 3, 4, 5, 6.7

	ThomasAlgorithm Test(d);
	Test.Solve_TA(a, b, c, x, d);


	return 0;
}
