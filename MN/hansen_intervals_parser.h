#pragma once
#include <vector>
#include "interval.h"
#include "hansen_arith.h"
#include "interval_matrix.h"
#include "hansen_interval_matrix.h"
#include "system_of_linear_equations_hansen_form.h"
#include "system_of_linear_equations.h"
#include <string>

class hansen_parser {
public:
	static std::vector <hansen_interval> parse(std::vector <interval> intervals);
	static std::vector<std::vector<hansen_interval>> parse_vector(std::vector<std::vector<interval>> intervals);
	static hansen_interval_matrix parse_matrix(interval_matrix matrix);
	static system_of_linear_equations_hansen_form parse_sole(system_of_linear_equations sole);
	static void print_intervals_information(interval interval, hansen_interval h_interval, std::string variable);
};