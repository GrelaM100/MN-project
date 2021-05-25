#pragma once
#include "interval_matrix.h"
#include "hansen_interval_matrix.h"

class system_of_linear_equations_hansen_form {
	hansen_interval_matrix _A = hansen_interval_matrix(0, 0, hansen_interval());
	hansen_interval_matrix _b = hansen_interval_matrix(0, 0, hansen_interval());
public:
	system_of_linear_equations_hansen_form(const hansen_interval_matrix& A, hansen_interval_matrix& b);
	hansen_interval_matrix A() const { return _A; }
	hansen_interval_matrix b() const { return _b; }
};

inline std::ostream& operator <<(std::ostream& os, const system_of_linear_equations_hansen_form& s) {
	os << "A: " << std::endl;
	os << s.A();
	os << "b: " << std::endl;
	os << s.b();

	return os;
}