#include "gaussNumerical.h"
#define _USE_MATH_DEFINES
#include <cmath>

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

double dfGauss(double x)
{
	return exp(-0.5 * x * x)/(sqrt(2*M_PI));
}

double cdfGauss(double x, double mean, double var)
{
	double z = (x - mean) / sqrt(var);
	unsigned int N(100000);
	double tmp(0.0);
	double dz = abs(z) / N;
	double z_(0.0);
	while(z_ < abs(z))
	{
		tmp += dfGauss(z_);
		z_ += dz;
	}
	return 0.5 + sgn(z) * dz * tmp;
}