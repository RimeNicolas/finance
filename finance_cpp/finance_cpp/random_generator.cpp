#include "random_generator.h"

RandomGenerator::RandomGenerator(unsigned int seed, const unsigned int mod,
	const unsigned int a, const unsigned int c) 
	: mod(mod), a(a), c(c) {
	this->seed = seed & this->mod;
	this->mod_inv = 1.0 / static_cast<double>(this->mod);
}

unsigned int RandomGenerator::randbasics() {
	seed = (seed * a + c) & mod;
	return seed;
}

double RandomGenerator::randuniform01() {
	return randbasics() * mod_inv;
}

RandomGeneratorLewis::RandomGeneratorLewis(unsigned int seed)
	: RandomGenerator(seed, 0x7fffffff, 16807, 12345U) {}

double RandomGeneratorLewis::random_exponential(const double theta) {
	return -theta * std::log(randuniform01());
}

std::pair<double, double> RandomGeneratorLewis::box_muller() {
	const double r = -2 * std::log(randuniform01());
	const double v = 2 * m_pi * randuniform01();
	return std::pair<double, double>(std::sqrt(r)*std::cos(v), std::sqrt(r)*std::sin(v));
}

std::pair<double, double> RandomGeneratorLewis::box_muller_opt() {
	double x(2), u1(0), u2(0);
	while (x > 1) {
		u1 = 2 * randuniform01() - 1;
		u2 = 2 * randuniform01() - 1;
		x = u1 * u1 + u2 * u2;
	}
	const double y(std::sqrt(-2 * std::log(x) / x));
	return std::pair<double, double>(u1 * y, u2 * y);
}

