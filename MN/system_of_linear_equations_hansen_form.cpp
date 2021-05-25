#include "system_of_linear_equations_hansen_form.h"

system_of_linear_equations_hansen_form::system_of_linear_equations_hansen_form(const hansen_interval_matrix& A, hansen_interval_matrix& b)
{
	_A = A;
	_b = b;
}
