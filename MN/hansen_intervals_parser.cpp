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
