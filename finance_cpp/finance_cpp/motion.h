#include <utility>
#include <array>

class RandomGeneratorLewis;

template<typename T, const size_t n>
class BrownianMotion {
public:
	BrownianMotion(T final_time);
	std::array<T, n> standard_motion(T mu, T sigma);

private:
	T final_time;
	T delta_t;
	T sqrt_delta_t;
	const size_t n_steps;
	RandomGeneratorLewis rgl;
};

template<typename T, const size_t n>
inline BrownianMotion<T, n>::BrownianMotion(T final_time)
	: final_time(final_time), n_steps(n), rgl(0) {
	this->delta_t = this->final_time / (this->n_steps - 1);
	std::cout << "delta t = " << delta_t << std::endl;
	this->sqrt_delta_t = std::sqrt(this->delta_t);
}

template<typename T, const size_t n>
std::array<T, n> inline BrownianMotion<T, n>::standard_motion(T mu, T sigma) {
	std::array<T, n> v = { 0 };
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
