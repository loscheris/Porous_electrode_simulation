#include <iostream>
#include <vector>
using namespace std;

//For the matrix equation Ax=d, A is n*n matrix
//a is the row below diagonal in matrix A (n-1 elements in a)
//b is the diagonal row in matrix A (n elements in b)
//c is the the row above diagonal in matrix A (n-1 elements in c)
//d is the elements in B (n elements in d)
//x is the solution (n elements in x)
//
//That is:
//|b0 c0 0 ..........0| |x0    | |d0    |
//|a1 b1 c1 0 .......0| |x1    | |d1    |
//|0 a2 b2 c2 0 .....0|*|x2    |=|d2    |
//|...................| |......| |......|
//|0...0 a(n-1) b(n-1)| |x(n-1)| |d(n-1)|


class ThomasAlgorithm
{
private:
	int size;
	vector<double> c_prime;
	vector<double> d_prime;

public:
	ThomasAlgorithm(vector<double> &d);
    void Solve_TA(vector<double> &a, vector<double> &b, vector<double> &c, double* x, double* d);
    void Solve_TA(vector<double> &a, vector<double> &b, vector<double> &c, vector<double> &x, vector<double> &d);
    ~ ThomasAlgorithm(){};
};
