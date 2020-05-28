#include <utility>
#include <array>

class RandomGeneratorLewis;

template<typename T, const size_t n>
class BrownianMotion {
public:
	BrownianMotion(const T final_time);
	Tensor1<T, n> motion(const T mu, const T sigma);
	Tensor1<T, n> motion(const Tensor1<T, n> mu, const Tensor1<T, n> sigma);

protected:
	T final_time;
	T delta_t;
	T sqrt_delta_t;
	const size_t n_steps;
	RandomGeneratorLewis rgl;
};

template<typename T, const size_t n>
inline BrownianMotion<T, n>::BrownianMotion(const T final_time)
	: final_time(final_time), n_steps(n), rgl(0) {
	this->delta_t = this->final_time / (this->n_steps - 1);
	std::cout << "delta t = " << delta_t << std::endl;
	this->sqrt_delta_t = std::sqrt(this->delta_t);
}

template<typename T, const size_t n>
Tensor1<T, n> inline BrownianMotion<T, n>::motion(const T mu, const T sigma) {
	Tensor1<T, n> v = { 0 };
	std::pair<T, T> z_pair = { 0,0 };
	T z(0);
	for (size_t i(1); i < v.size(); i++) {
		if (i % 2 == 1) {
			z_pair = this->rgl.box_muller_opt();
			z = z_pair.first;
		}
		else {
			z = z_pair.second;
		}
		v[i] = v[i - 1] + mu * delta_t + sigma * sqrt_delta_t * z;
	}
	return v;
}

template<typename T, size_t n>
inline Tensor1<T, n> BrownianMotion<T, n>::motion(const Tensor1<T, n> mu, const Tensor1<T, n> sigma) {
	Tensor1<T, n> v = { 0 };
	std::pair<T, T> z_pair = { 0,0 };
	T z(0);
	for (size_t i(1); i < v.size(); i++) {
		if (i % 2 == 1) {
			z_pair = this->rgl.box_muller_opt();
			z = z_pair.first;
		}
		else {
			z = z_pair.second;
		}
		v[i] = v[i - 1] + mu[i] * delta_t + sigma[i] * sqrt_delta_t * z;
	}
	return v;
}

template<typename T, const size_t n, const size_t d>
class BrownianMotionMultiDim : public BrownianMotion<T, n> {
public:
	BrownianMotionMultiDim(const T final_time);
	Tensor2d<T, n, d> motion(const Tensor1<T, d> mu, const Tensor2<T, d> sigma);
};

template<typename T, const size_t n, const size_t d>
inline BrownianMotionMultiDim<T, n, d>::BrownianMotionMultiDim(const T final_time) 
	: BrownianMotion<T, n>(final_time) {}

template<typename T, const size_t n, const size_t d>
inline Tensor2d<T, n, d> BrownianMotionMultiDim<T, n, d>::motion(const Tensor1<T, d> mu, const Tensor2<T, d> sigma) {
	Tensor1<T, d> z = { 0 };
	Tensor2d<T, n, d> v = { 0 };
	for (size_t i(1); i < n; i++) {
		z = rgl.gauss_array(mu, sigma);
		for (size_t j(0); j < d; j++) {
			v[i][j] = v[i - 1][j] + mu[j] * delta_t + sqrt_delta_t * z[j];
		}
	}
	return v;
}
