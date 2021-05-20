#pragma once
#include <vector>
#include "interval.h"
#include "hansen_arith.h"
#include <string>

class hansen_parser {
public:
	static std::vector <hansen_interval> parse(std::vector <interval> intervals);
	static void print_intervals_information(interval interval, hansen_interval h_interval, std::string variable);
};