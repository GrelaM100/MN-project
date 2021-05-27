#pragma once
#include <vector>
#include "interval.h"
#include <ostream>

class interval_matrix {
	std::vector<std::vector<interval>> _matrix;
	unsigned _rows;
	unsigned _cols;
public:
	interval_matrix(unsigned rows, unsigned cols, const interval& initial);
	interval_matrix(const interval_matrix& matrix);
	interval_matrix(const std::vector<std::vector<interval>>& matrix);
	virtual ~interval_matrix();

	interval_matrix& operator=(const interval_matrix& matrix);
	interval_matrix operator+(const interval_matrix& matrix);
	interval_matrix& operator+=(const interval_matrix& matrix);
	interval_matrix operator-(const interval_matrix& matrix);
	interval_matrix& operator-=(const interval_matrix& matrix);
	interval_matrix operator*(const interval_matrix& matrix);
	interval_matrix& operator*=(const interval_matrix& matrix);
	interval_matrix transpose();

	interval_matrix& operator+(const interval& inter);
	interval_matrix& operator-(const interval& inter);
	interval_matrix& operator*(const interval& inter);
	interval_matrix& operator/(const interval& inter);

	std::vector<interval> operator*(const std::vector<interval>& vect);
	std::vector<interval> diag_vec();
	std::vector<std::vector<double>> subMatrix(std::vector<std::vector<double>> mat);
	double determinant(std::vector<std::vector<double>> mat);
	std::vector<std::vector<double>> matrix_values(int inf_or_sup = 0);
	std::vector<std::vector<double>> adj(std::vector<std::vector<double>> m);
	std::vector<std::vector<double>> transpose_double(const std::vector<std::vector<double>> m_to_transpose);
	std::vector<std::vector<double>> inv(std::vector<std::vector<double>> m);
	interval_matrix invert_matrix();

	interval& operator()(const unsigned& row, const unsigned& col);
	const interval& operator()(const unsigned& row, const unsigned& col) const;
	double matrix_norm() const;
	double width() const;
	interval_matrix midpoint() const;
	interval_matrix intersections(const interval_matrix& matrix);

	unsigned get_rows() const;
	unsigned get_cols() const;
	std::vector<std::vector<interval>> get_matrix() const;
};

inline std::ostream& operator <<(std::ostream& os, const interval_matrix& m) {
	for (int i = 0; i < m.get_rows(); i++) {
		for (int j = 0; j < m.get_cols(); j++) {
			os << m(i, j) << ", ";
		}
		os << std::endl;
	}

	return os;
}