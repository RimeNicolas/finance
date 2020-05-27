#include<array>

template<typename T, size_t dim>
Tensor2<T, dim> cholesky_factorisation(const Tensor2<T, dim> matrix) {
	std::array<std::array<double, dim>, dim> result = { {0} };
	for (size_t i = 0; i < dim; ++i) {
		for (size_t k = 0; k < i; ++k) {
			T value = matrix[i][k];
			for (size_t j = 0; j < k; ++j)
				value -= result[i][j] * result[k][j];
			result[i][k] = value / result[k][k];
		}
		T value = matrix[i][i];
		for (size_t j = 0; j < i; ++j)
			value -= result[i][j] * result[i][j];
		result[i][i] = std::sqrt(value);
	}
	return result;
}
