#include "random1.h"
#include <cstdlib>
#include <cmath>

double getZsummation()
{
	double result = 0.0;
	for (unsigned int i = 0; i < 12; i++)
	{
		result += rand() / static_cast<double>(RAND_MAX);
	}
	result -= 6.0;
	return result;
}

double getZBoxMuller()
{
	double x, y, sizeSquared;
	do
	{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while (sizeSquared >= 1.0);
	return x * sqrt(-2 * log(sizeSquared) / sizeSquared);
}
