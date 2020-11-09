#include <iostream>
#include <fstream>
#include <array>

#include "random_generator.h"
#include "math_func.h"
#include "motion.h"
#include "print_func.h"


void test_brownian_motion_1d() {
	const size_t n(5);
	BrownianMotion<double, n> bm(10.0);
	std::array<double, n> v1 = bm.motion(1,1);
	Tensor1<double, n> mu = { 1,0,0,1,0 };
	Tensor1<double, n> cov = { 1,2,2,1,2 };
	//std::array<double, n> v2 = bm.motion(mu, cov);
	print_array(v1);
	//print_array(v2);
}

void test_brownian_motion_d() {
	const size_t n(5);
	const size_t d(2);
	BrownianMotionMultiDim<double, n, d> bm(10.0);
	Tensor1<double, d> mu = { 1,0 };
	Tensor2<double, d> cov = { {0} };
	cov[0][0] = 1;
	cov[0][1] = 0.7;
	cov[1][0] = 0.7;
	cov[1][1] = 1;
	Tensor2d<double, n, d> v2 = bm.motion(mu, cov);
	for (size_t i(0); i < n; i++) {
		print_array(v2[i]);
	}
}

int main() {
	test_brownian_motion_d();

	return 0;
}

