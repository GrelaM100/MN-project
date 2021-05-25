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

	hansen_interval& operator()(const unsigned& row, const unsigned& col);
	const hansen_interval& operator()(const unsigned& row, const unsigned& col) const;

	unsigned get_rows() const;
	unsigned get_cols() const;
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