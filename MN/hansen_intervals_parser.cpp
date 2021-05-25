#include "hansen_intervals_parser.h"
#include <iostream>

std::vector<hansen_interval> hansen_parser::parse(std::vector<interval> intervals)
{
	std::vector <hansen_interval> parsed_intervals;
	hansen_interval parsed_interval;
	interval c;
	std::vector <interval> v;
	std::vector <interval> r;
	interval r_temp;

	for (int i = 0; i < intervals.size(); i++) {
		c = interval(intervals[i].centr());
		v.clear();
		r.clear();

		for (int j = 0; j < intervals.size(); j++) {
			r_temp = interval(-intervals[j].radius(), intervals[j].radius());
			r.push_back(r_temp);

			if (i == j) {
				v.push_back(interval(1, 1));
			}
			else {
				v.push_back(interval(0, 0));
			}
		}

		parsed_interval = hansen_interval(c, v, r);
		parsed_intervals.push_back(parsed_interval);
	}

	return parsed_intervals;
}

std::vector<std::vector<hansen_interval>> hansen_parser::parse_vector(std::vector<std::vector<interval>> intervals) {
	std::vector<std::vector<hansen_interval>> parsed_intervals;
	for (int i = 0; i < intervals.size(); i++) {
		parsed_intervals.push_back(hansen_parser::parse(intervals[i]));
	}

	return parsed_intervals;
}

hansen_interval_matrix hansen_parser::parse_matrix(interval_matrix matrix)
{
	hansen_interval_matrix hansen_matrix = hansen_interval_matrix(hansen_parser::parse_vector(matrix.get_matrix()));
	return hansen_matrix;
}

system_of_linear_equations_hansen_form hansen_parser::parse_sole(system_of_linear_equations sole) {
	hansen_interval_matrix AH = hansen_parser::parse_matrix(sole.A());
	hansen_interval_matrix bH = hansen_parser::parse_matrix(sole.b());
	system_of_linear_equations_hansen_form sole_h = system_of_linear_equations_hansen_form(AH, bH);
	return sole_h;
}

void hansen_parser::print_intervals_information(interval interval, hansen_interval h_interval, std::string variable)
{
	std::cout << variable << " = " << interval << std::endl;
	std::cout << "Hansen arithmetic: " << reduce(h_interval) << std::endl;
	std::cout << "Linear form: " << h_interval << std::endl;
	std::cout << "Where: " << std::endl;
	for (int i = 0; i < h_interval.r().size(); i++) 
	{
		std::cout << "[" << "z" << i + 1 << "] = " << h_interval.r()[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}