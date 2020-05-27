#include <iostream>
#include <fstream>
#include <array>

#include "random_generator.h"
#include "math_func.h"
#include "motion.h"
#include "print_func.h"
//#include "tests.cpp"


void test_brownian_motion() {
	const size_t n(5);
	BrownianMotion<double, n> bm(10.0);
	std::array<double, n> v1 = bm.standard_motion(1,1);
	std::array<double, n> v2 = bm.standard_motion(1,5);
	print_array(v1);
	print_array(v2);
}

int main() {
	test_brownian_motion();

	return 0;
}

