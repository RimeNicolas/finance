#include "random1.h"
#include "simpleMC1.h"
#include <iostream>
#include <cmath>

double simpleMC1(double expiry, double strike, double spot, double vol, double r, unsigned long nbPaths)
{
	double var = vol * vol * expiry;
	double movedSpot = spot * exp(r * expiry - 0.5 * var);

	double runningSum = 0;
	for (unsigned int i = 0; i < nbPaths; i++)
	{
		double payoff = movedSpot * exp(sqrt(var) * getZBoxMuller()) - strike;
		payoff = payoff > 0 ? payoff : 0;
		runningSum += payoff;
	}
	return exp(-r * expiry) * runningSum / nbPaths;
}