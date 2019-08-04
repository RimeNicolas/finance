#include "analyticalFormulas.h"
#include "gaussNumerical.h"
#include <cmath>
double priceCall(double expiry, double strike, double spot, double vol, double r, unsigned long nbPaths)
{
	double d1 = (log(spot / strike) + (r+0.5*vol*vol) * expiry) / (vol*sqrt(expiry));
	return spot*cdfGauss(d1) - exp(-r * expiry)*strike*cdfGauss(d1 - vol*sqrt(expiry));
}


