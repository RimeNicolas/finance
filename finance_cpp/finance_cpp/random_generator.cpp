#include "random_generator.h"

RandomGenerator::RandomGenerator(unsigned int seed) {
	this->seed = seed & this->mod;
}

int RandomGenerator::randint() {
	this->seed = (this->seed * 1103515245U + 12345U) & mod;
	return this->seed;
}