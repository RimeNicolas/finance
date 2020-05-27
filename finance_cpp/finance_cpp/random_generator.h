#include <utility>
#include <cmath>
#include <array>
//#include "math_func.h"

template<typename T, size_t n> using Tensor1 = std::array<T, n>;
template<typename T, size_t n> using Tensor2 = Tensor1<std::array<T, n>, n>;

template<typename T, size_t dim>
Tensor2<T, dim> cholesky_factorisation(const Tensor2<T, dim> matrix);

constexpr double pi = 3.14159265358979323846;

class RandomGenerator {
public:
	RandomGenerator(unsigned int seed, const unsigned int mod,
		const unsigned int a, const unsigned int c);
	unsigned int randbasics();
	double randuniform01();

protected:
	unsigned int seed;
	const unsigned int mod;
	double mod_inv;
	const unsigned int a;
	const unsigned int c;
};

class RandomGeneratorLewis : public RandomGenerator {
public:
	RandomGeneratorLewis(unsigned int seed);
	double random_exponential(const double theta);
	std::pair<double, double> box_muller();
	std::pair<double, double> box_muller_opt();

	template<typename T, const size_t dim>
	Tensor1<T, dim> normal_array(const Tensor1<T, dim> mu, const Tensor2<T, dim> cov);
};

template<typename T, const size_t dim>
inline Tensor1<T, dim> RandomGeneratorLewis::normal_array(const Tensor1<T, dim> mu, const Tensor2<T, dim> cov) {
	Tensor2<T, dim> A = cholesky_factorisation(cov);
	Tensor1<T, dim> random_array = mu;
	double z1(0);
	std::pair<double, double> z = { 0,0 };
	for (size_t i(0); i < dim; i++) {
		if (i % 2 == 0) {
			z = box_muller();
			z1 = z.first;
		}
		else {
			z1 = z.second;
		}
		for (size_t j(0); j < dim; j++) {
			random_array[j] += A[j][i] * z1;
		}
	}
	return random_array;
}
