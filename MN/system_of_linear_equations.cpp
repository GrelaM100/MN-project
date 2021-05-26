#include "system_of_linear_equations.h"
#include <iostream>

system_of_linear_equations::system_of_linear_equations(const interval_matrix& A, interval_matrix& b)
{
	_A = A;
	_b = b;
}

interval_matrix system_of_linear_equations::krawczyk_method()
{
	interval_matrix A_inv = _A.midpoint().invert_matrix();
	interval_matrix YA = A_inv * _A;
	interval_matrix Yb = A_inv * _b;
	interval_matrix I = interval_matrix(YA.get_rows(), YA.get_cols(), interval(0, 0));
	for (int i = 0; i < I.get_rows(); i++) {
		for (int j = 0; j < I.get_cols(); j++) {
			if (i == j) {
				I(i, j) = interval(1);
			}		
		}
	}
	interval_matrix E = I - YA;
	interval x = interval(-1, 1) * interval(Yb.matrix_norm()) / interval((1 - E.matrix_norm()));
	interval_matrix X(_b.get_rows(), _b.get_cols(), interval(0));
	for (int i = 0; i < _b.get_rows(); i++) {
		for (int j = 0; j < _b.get_cols(); j++) {
			X(i, j) = x;
		}
	}

	interval_matrix X_k(_b.get_rows(), _b.get_cols(), interval(0));
	for (int i = 0; i < 100; i++) {
		X_k = Yb + E * X;
		X_k = X_k.intersections(X);
		//std::cout << "X" << i + 1 << ": " << X_k << std::endl;
		X = interval_matrix(X_k);
	}

	return X_k;
}

