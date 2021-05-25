#include "hansen_interval_matrix.h"
#include <iostream>

hansen_interval_matrix::hansen_interval_matrix(unsigned rows, unsigned cols, const hansen_interval& initial)
{
	_matrix.resize(rows);
	for (unsigned i = 0; i < _matrix.size(); i++) {
		_matrix[i].resize(cols, initial);
	}

	_rows = rows;
	_cols = cols;
}

hansen_interval_matrix::hansen_interval_matrix(const hansen_interval_matrix& matrix) {
	_matrix = matrix._matrix;
	_rows = matrix.get_rows();
	_cols = matrix.get_cols();
}

hansen_interval_matrix::hansen_interval_matrix(const std::vector<std::vector<hansen_interval>>& matrix)
{
	_matrix.resize(matrix.size());

	for (unsigned i = 0; i < _matrix.size(); i++) {
		_matrix[i].resize(matrix[i].size());
	}

	for (unsigned i = 0; i < matrix.size(); i++) {
		for (unsigned j = 0; j < matrix[i].size(); j++) {
			_matrix[i][j] = matrix[i][j];
		}
	}

	_rows = matrix.size();
	_cols = matrix[0].size();
}



hansen_interval_matrix::~hansen_interval_matrix() {}

hansen_interval_matrix& hansen_interval_matrix::operator=(const hansen_interval_matrix& matrix) {
	if (&matrix == this)
		return *this;

	unsigned new_rows = matrix.get_rows();
	unsigned new_cols = matrix.get_cols();

	_matrix.resize(new_rows);
	for (unsigned i = 0; i < _matrix.size(); i++) {
		_matrix[i].resize(new_cols);
	}

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			_matrix[i][j] = matrix(i, j);
		}
	}
	_rows = new_rows;
	_cols = new_cols;

	return *this;
}

hansen_interval_matrix hansen_interval_matrix::operator+(const hansen_interval_matrix& matrix) {
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[i][j] + matrix(i, j);
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator+=(const hansen_interval_matrix& matrix) {
	unsigned rows = matrix.get_rows();
	unsigned cols = matrix.get_cols();

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			this->_matrix[i][j] = _matrix[i][j] + matrix(i, j);
		}
	}

	return *this;
}

hansen_interval_matrix hansen_interval_matrix::operator-(const hansen_interval_matrix& matrix) {
	unsigned rows = matrix.get_rows();
	unsigned cols = matrix.get_cols();
	hansen_interval_matrix result(rows, cols, hansen_interval());

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->_matrix[i][j] - matrix(i, j);
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator-=(const hansen_interval_matrix& matrix) {
	unsigned rows = matrix.get_rows();
	unsigned cols = matrix.get_cols();

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			this->_matrix[i][j] = _matrix[i][j] - matrix(i, j);
		}
	}

	return *this;
}

hansen_interval_matrix hansen_interval_matrix::operator*(const hansen_interval_matrix& matrix) {
	unsigned rows = this->get_rows();
	unsigned cols = matrix.get_cols();
	hansen_interval_matrix result(rows, cols, hansen_interval());

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			for (unsigned k = 0; k < this->get_cols(); k++) {
				result(i, j) = result(i, j) + this->_matrix[i][k] * matrix(k, j);
			}
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator*=(const hansen_interval_matrix& matrix) {
	hansen_interval_matrix result = (*this) * matrix;
	(*this) = result;
	return *this;
}

hansen_interval_matrix hansen_interval_matrix::transpose() {
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[j][i];
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator+(const hansen_interval& inter)
{
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[i][j] + inter;
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator-(const hansen_interval& inter)
{
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[i][j] - inter;
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator*(const hansen_interval& inter)
{
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[i][j] * inter;
		}
	}

	return result;
}

hansen_interval_matrix& hansen_interval_matrix::operator/(const hansen_interval& inter)
{
	hansen_interval_matrix result(_rows, _cols, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result(i, j) = this->_matrix[i][j] / inter;
		}
	}

	return result;
}

std::vector<hansen_interval> hansen_interval_matrix::operator*(const std::vector<hansen_interval>& vect)
{
	std::vector<hansen_interval> result(vect.size(), hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		for (unsigned j = 0; j < _cols; j++) {
			result[i] = this->_matrix[i][j] * vect[j];
		}
	}

	return result;
}

std::vector<hansen_interval> hansen_interval_matrix::diag_vec() {
	std::vector<hansen_interval> result(_rows, hansen_interval());

	for (unsigned i = 0; i < _rows; i++) {
		result[i] = this->_matrix[i][i];
	}

	return result;
}

hansen_interval& hansen_interval_matrix::operator()(const unsigned& row, const unsigned& col) {
	return this->_matrix[row][col];
}

const hansen_interval& hansen_interval_matrix::operator()(const unsigned& row, const unsigned& col) const {
	return this->_matrix[row][col];
}

unsigned hansen_interval_matrix::get_rows() const {
	return this->_rows;
}

unsigned hansen_interval_matrix::get_cols() const {
	return this->_cols;
}