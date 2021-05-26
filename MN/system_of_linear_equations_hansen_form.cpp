#include "system_of_linear_equations_hansen_form.h"
#include "hansen_intervals_parser.h"
#include <iostream>

system_of_linear_equations_hansen_form::system_of_linear_equations_hansen_form(const hansen_interval_matrix& A, hansen_interval_matrix& b)
{
	_A = A;
	_b = b;
}

//hansen_interval_matrix system_of_linear_equations_hansen_form::krawczyk_method()
//{
//	hansen_interval_matrix A_inv = _A.midpoint().invert_matrix();
//	hansen_interval_matrix YA = A_inv * _A;
//	hansen_interval_matrix Yb = A_inv * _b;
//	interval_matrix I =interval_matrix(YA.get_rows(), YA.get_cols(), interval());
//	for (int i = 0; i < I.get_rows(); i++) {
//		for (int j = 0; j < I.get_cols(); j++) {
//			if (i == j) {
//				I(i, j) = interval(1);
//			}
//		}
//	}
//	hansen_interval_matrix E = hansen_parser::parse_matrix(I) - YA;
//	interval x = interval(-1, 1) * interval(Yb.matrix_norm()) / interval((1 - E.matrix_norm()));
//	interval_matrix X(_b.get_rows(), _b.get_cols(), interval(0));
//	for (int i = 0; i < _b.get_rows(); i++) {
//		for (int j = 0; j < _b.get_cols(); j++) {
//			X(i, j) = x;
//		}
//	}
//
//	hansen_interval_matrix X_parsed = hansen_parser::parse_matrix(X);
//	hansen_interval_matrix X_k(_b.get_rows(), _b.get_cols(), hansen_interval());
//	for (int i = 0; i < 100; i++) {
//		X_k = Yb + E * X_parsed;
//		X_k = X_k.intersections(X_parsed);
//		std::cout << "X" << i + 1 << ": " << X_k << std::endl;
//		X_parsed = hansen_interval_matrix(X_k);
//	}
//
//	return X_k;
//}