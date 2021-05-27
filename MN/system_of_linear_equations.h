#pragma once
#include "interval_matrix.h"

class system_of_linear_equations {
	interval_matrix _A = interval_matrix(0, 0, interval(0, 0));
	interval_matrix _b = interval_matrix(0, 0, interval(0, 0));
public:
	system_of_linear_equations(const interval_matrix& A, interval_matrix& b);
	interval_matrix A() const { return _A; }
	interval_matrix b() const { return _b; }
	interval_matrix krawczyk_method();
};

inline std::ostream& operator <<(std::ostream& os, const system_of_linear_equations& s) {
	os << "A: " << std::endl;
	os << s.A();
	os << "b: " << std::endl;
	os << s.b();

	return os;
}