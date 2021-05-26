#pragma once
#include <vector>
#include "hansen_arith.h"
#include <ostream>

class hansen_interval_matrix {
	std::vector<std::vector<hansen_interval>> _matrix;
	unsigned _rows;
	unsigned _cols;
public:
	hansen_interval_matrix(unsigned rows, unsigned cols, const hansen_interval& initial);
	hansen_interval_matrix(const hansen_interval_matrix& matrix);
	hansen_interval_matrix(const std::vector<std::vector<hansen_interval>>& matrix);
	virtual ~hansen_interval_matrix();

	hansen_interval_matrix& operator=(const hansen_interval_matrix& matrix);
	hansen_interval_matrix operator+(const hansen_interval_matrix& matrix);
	hansen_interval_matrix& operator+=(const hansen_interval_matrix& matrix);
	hansen_interval_matrix operator-(const hansen_interval_matrix& matrix);
	hansen_interval_matrix& operator-=(const hansen_interval_matrix& matrix);
	hansen_interval_matrix operator*(const hansen_interval_matrix& matrix);
	hansen_interval_matrix& operator*=(const hansen_interval_matrix& matrix);
	hansen_interval_matrix transpose();

	hansen_interval_matrix& operator+(const hansen_interval& inter);
	hansen_interval_matrix& operator-(const hansen_interval& inter);
	hansen_interval_matrix& operator*(const hansen_interval& inter);
	hansen_interval_matrix& operator/(const hansen_interval& inter);

	std::vector<hansen_interval> operator*(const std::vector<hansen_interval>& vect);
	std::vector<hansen_interval> diag_vec();
	/*std::vector<std::vector<double>> subMatrix(std::vector<std::vector<double>> mat);
	double determinant(std::vector<std::vector<double>> mat);
	std::vector<std::vector<double>> matrix_values(int inf_or_sup = 0);
	std::vector<std::vector<double>> adj(std::vector<std::vector<double>> m);
	std::vector<std::vector<double>> transpose_double(const std::vector<std::vector<double>> m_to_transpose);
	std::vector<std::vector<double>> inv(std::vector<std::vector<double>> m);
	hansen_interval_matrix invert_matrix();*/

	hansen_interval& operator()(const unsigned& row, const unsigned& col);
	const hansen_interval& operator()(const unsigned& row, const unsigned& col) const;
	/*double matrix_norm() const;
	double width() const;
	hansen_interval_matrix midpoint() const;
	hansen_interval_matrix intersections(const hansen_interval_matrix& matrix);*/

	unsigned get_rows() const;
	unsigned get_cols() const;
	//std::vector<std::vector<hansen_interval>> get_matrix() const;
};

inline std::ostream& operator <<(std::ostream& os, const hansen_interval_matrix& m) {
	for (int i = 0; i < m.get_rows(); i++) {
		for (int j = 0; j < m.get_cols(); j++) {
			os << m(i, j) << ", ";
		}
		os << std::endl;
	}

	return os;
}