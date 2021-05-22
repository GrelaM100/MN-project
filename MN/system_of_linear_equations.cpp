#include "system_of_linear_equations.h"

system_of_linear_equations::system_of_linear_equations(const interval_matrix& A, interval_matrix& b)
{
	_A = A;
	_b = b;
}
