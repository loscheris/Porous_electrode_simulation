#include "TA_class.h"

ThomasAlgorithm::ThomasAlgorithm (vector<double> &d)
{
	//compute the size of matrix
	size = d.size();

	// define the length of the vectors.
	c_prime.resize(size);
	d_prime.resize(size);
}

//Funtion for solving Thomas Algorithm
void ThomasAlgorithm::Solve_TA(const vector<double> &a, const vector<double> &b, const vector<double> &c, vector<double> &x, const vector<double> &d)
{
	//initialize c', d'
	c_prime[0] = c[0] / b[0];
	d_prime[0] = d[0] / b[0];

	//compute values of c'
	for ( int i = 1; i < size - 1; i++)
	{
		c_prime[i] = c[i] / (b[i] - c_prime[i - 1] * a[i]);
	}

	//compute values of d'
	for ( int j = 1; j < size; j++)
	{
		d_prime[j] = (d[j] - d_prime[j - 1] * a[j]) / (b[j] - c_prime[j - 1] * a[j]);
	}

	//compute values of x
	x[size - 1] = d_prime[size - 1];

	for (int k = size - 2; k >= 0; k--)
	{
		x[k] = d_prime[k] - c_prime[k] * x[k + 1];
	}

	//print values of x
	cout << "x: ";
	for ( int l = 0; l < size; l++)
	{
		if (l != size - 1)
		{
			cout << x[l] << ", ";
		}
		else
		{
			cout << x[l] << endl;
		}
	}
}


