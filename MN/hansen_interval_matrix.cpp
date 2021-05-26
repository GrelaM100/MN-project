#include "hansen_interval_matrix.h"
#include <iostream>
#include "hansen_intervals_parser.h"

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
	unsigned rows = _rows;
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

std::vector<std::vector<double>> hansen_interval_matrix::subMatrix(std::vector<std::vector<double>> mat) {
	if (mat.size() != mat[0].size()) {
		throw std::runtime_error("Matrix is not quadratic");
	}

	std::vector<std::vector<double>> solution(mat.size(), std::vector<double>(mat.size()));
	std::vector<std::vector<double>> subVect(mat.size() - 1, std::vector<double>(mat.size() - 1));

	for (std::size_t i = 0; i < mat.size(); i++) {
		for (std::size_t j = 0; j < mat[0].size(); j++) {

			int p = 0;
			for (size_t x = 0; x < mat.size(); x++) {
				if (x == i) {
					continue;
				}
				int q = 0;

				for (size_t y = 0; y < mat.size(); y++) {
					if (y == j) {
						continue;
					}

					subVect[p][q] = mat[x][y];
					q++;
				}
				p++;
			}
			solution[i][j] = pow(-1, i + j) * determinant(subVect);
		}
	}
	return solution;
}

double hansen_interval_matrix::determinant(std::vector<std::vector<double>> mat)
{
	double determinant = 0;
	if (mat.size() == 1 && mat[0].size() == 1) {
		return mat[0][0];
	}
	if (mat.size() == 2 && mat[0].size() == 2) {
		return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
	}
	std::vector<std::vector<double>> temp;
	int sign = 1;
	for (int i = 0; i < mat.size(); i++) {
		subMatrix(mat);
		determinant += sign * mat[0][i] * hansen_interval_matrix::determinant(temp);
		sign = -sign;
	}
	return determinant;
}

std::vector<std::vector<double>> hansen_interval_matrix::matrix_values(int inf_or_sup)
{
	std::vector<std::vector<double>> matrix;
	std::vector<double> cols;

	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix[i].size(); j++) {
			if (inf_or_sup == 0) {
				cols.push_back(reduce(_matrix[i][j]).inf());
			}
			else {
				cols.push_back(reduce(_matrix[i][j]).sup());
			}
		}
		matrix.push_back(std::vector<double>(cols));
		cols.clear();
	}

	return matrix;
}

std::vector<std::vector<double>> hansen_interval_matrix::adj(std::vector<std::vector<double>> m)
{
	std::vector<std::vector<double>> adj(m.size(), std::vector<double>(m[0].size()));
	if (determinant(m) == 1) {
		throw std::runtime_error("Determinan is 0");
	}

	int s = 1;
	std::vector<std::vector<double>> temp;
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			temp = subMatrix(m);
			s = ((i + j) % 2 == 0) ? 1 : -1;
			adj[j][i] = (s) * (determinant(temp));
		}
	}
	return adj;
}

std::vector<std::vector<double>> hansen_interval_matrix::transpose_double(const std::vector<std::vector<double>> m_to_transpose)
{
	std::vector<std::vector<double>> solution(m_to_transpose[0].size(), std::vector<double>(m_to_transpose.size()));

	for (size_t i = 0; i < m_to_transpose.size(); i++) {
		for (size_t j = 0; j < m_to_transpose[0].size(); j++) {
			solution[j][i] = m_to_transpose[i][j];
		}
	}
	return solution;
}

std::vector<std::vector<double>> hansen_interval_matrix::inv(std::vector<std::vector<double>> m)
{
	if (determinant(m) == 0) {
		throw std::runtime_error("Determinant is 0");
	}
	double d = 1.0 / determinant(m);
	std::vector<std::vector<double>> solution(m.size(), std::vector<double>(m.size()));

	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m.size(); j++) {
			solution[i][j] = m[i][j] * d;
		}
	}

	return transpose_double(subMatrix(solution));
}

hansen_interval_matrix hansen_interval_matrix::invert_matrix()
{
	std::vector<std::vector<interval>> inverted_matrix;
	std::vector<interval> cols;
	std::vector<std::vector<double>> A_inf, A_sup, A_inf_inv, A_sup_inv;
	A_inf = hansen_interval_matrix::matrix_values(0);
	A_sup = hansen_interval_matrix::matrix_values(1);
	A_inf_inv = hansen_interval_matrix::inv(A_inf);
	A_sup_inv = hansen_interval_matrix::inv(A_sup);

	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix[i].size(); j++) {
			cols.push_back(interval(A_inf_inv[i][j], A_sup_inv[i][j]));
		}
		inverted_matrix.push_back(std::vector<interval>(cols));
		cols.clear();
	}

	hansen_interval_matrix parsed_matrix = hansen_parser::parse_matrix(interval_matrix(inverted_matrix));
	return parsed_matrix;
}


hansen_interval& hansen_interval_matrix::operator()(const unsigned& row, const unsigned& col) {
	return this->_matrix[row][col];
}

const hansen_interval& hansen_interval_matrix::operator()(const unsigned& row, const unsigned& col) const {
	return this->_matrix[row][col];
}

double hansen_interval_matrix::matrix_norm() const
{
	double max = DBL_MIN;
	interval sum;
	interval el;
	for (int i = 0; i < _matrix.size(); i++) {
		sum = interval(0, 0);
		for (int j = 0; j < _matrix[i].size(); j++) {
			el = reduce(_matrix[i][j]);
			sum = sum + el.modMax();
		}
		if (sum.sup() > max) {
			max = sum.sup();
		}
	}

	return max;
}

double hansen_interval_matrix::width() const
{
	double width = DBL_MIN;
	double check;

	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix[i].size(); j++) {
			check = reduce(_matrix[i][j]).sup() - reduce(_matrix[i][j]).inf();
			if (check > width) {
				width = check;
			}
		}
	}
	return width;
}

hansen_interval_matrix hansen_interval_matrix::midpoint() const
{
	std::vector<interval> midpoints;
	std::vector<std::vector<interval>> midpoint_matrix;
	double midpoint;

	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix[i].size(); j++) {
			midpoint = reduce(_matrix[i][j]).centr();
			midpoints.push_back(midpoint);
		}
		midpoint_matrix.push_back(midpoints);
		midpoints.clear();
	}

	hansen_interval_matrix parsed = hansen_parser::parse_matrix(interval_matrix(midpoint_matrix));
	return parsed;
}

hansen_interval_matrix hansen_interval_matrix::intersections(const hansen_interval_matrix& matrix)
{
	double inf, sup;
	std::vector<interval> intersection;
	std::vector<std::vector<interval>> intersections;
	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix[i].size(); j++) {
			if (reduce(_matrix[i][j]).inf() >= reduce(matrix(i, j)).inf()) {
				inf = reduce(_matrix[i][j]).inf();
			}
			else {
				inf = reduce(matrix(i, j)).inf();
			}
			if (reduce(_matrix[i][j]).sup() <= reduce(matrix(i, j)).sup()) {
				sup = reduce(_matrix[i][j]).sup();
			}
			else {
				sup = reduce(matrix(i, j)).sup();
			}
			intersection.push_back(interval(inf, sup));
		}
		intersections.push_back(intersection);
		intersection.clear();
	}

	hansen_interval_matrix parsed = hansen_parser::parse_matrix(interval_matrix(intersections));
	return parsed;
}

unsigned hansen_interval_matrix::get_rows() const {
	return this->_rows;
}

unsigned hansen_interval_matrix::get_cols() const {
	return this->_cols;
}

std::vector<std::vector<hansen_interval>> hansen_interval_matrix::get_matrix() const
{
	return this->_matrix;
}