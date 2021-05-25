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

	interval& operator()(const unsigned& row, const unsigned& col);
	const interval& operator()(const unsigned& row, const unsigned& col) const;

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