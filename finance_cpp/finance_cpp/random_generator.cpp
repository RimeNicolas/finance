#include "random_generator.h"

RandomGenerator::RandomGenerator(unsigned int seed, unsigned int mod,
	unsigned int a, unsigned int c) 
	: mod(mod), a(a), c(c) {
	this->seed = seed & this->mod;
	this->mod_inv = 1.0 / static_cast<double>(this->mod);
}

unsigned int RandomGenerator::randbasics() {
	this->seed = (this->seed * a + c) & mod;
	return this->seed;
}

double RandomGenerator::randuniform01() {
	return randbasics() * this->mod_inv;
}

RandomGeneratorLewis::RandomGeneratorLewis(unsigned int seed)
	: RandomGenerator(seed, 0x7fffffff, 16807, 12345U) {}

double RandomGeneratorLewis::random_exponential(double theta) {
	return -theta * std::log(randuniform01());
}

std::pair<double, double> RandomGeneratorLewis::box_muller() {
	double r = -2 * std::log(randuniform01());
	double v = 2 * pi * randuniform01();
	return std::pair<double, double>(std::sqrt(r)*std::cos(v), std::sqrt(r)*std::sin(v));
}

std::pair<double, double> RandomGeneratorLewis::box_muller_opt() {
	double x(2), u1(0), u2(0);
	while (x > 1) {
		u1 = 2 * randuniform01() - 1;
		u2 = 2 * randuniform01() - 1;
		x = u1 * u1 + u2 * u2;
	}
	double y(std::sqrt(-2 * std::log(x) / x));
	return std::pair<double, double>(u1 * y, u2 * y);
}

