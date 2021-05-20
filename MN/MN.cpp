#include <iostream>
#include "interval.h"
#include "hansen_arith.h"
#include "hansen_intervals_parser.h"

int main()
{
    //kod testowy
    interval x, y;
    std::vector <interval> intervals;
    std::vector <hansen_interval> hansen_intervals;

    x = interval(1, 2);
    y = interval(3, 4);
    
    intervals.push_back(x);
    intervals.push_back(y);

    hansen_intervals = hansen_parser::parse(intervals);
    hansen_parser::print_intervals_information(intervals[0], hansen_intervals[0], "x");
    hansen_parser::print_intervals_information(intervals[1], hansen_intervals[1], "y");
    hansen_parser::print_intervals_information(intervals[0] + intervals[1], hansen_intervals[0] + hansen_intervals[1], "x + y");
    hansen_parser::print_intervals_information(intervals[0] - intervals[1], hansen_intervals[0] - hansen_intervals[1], "x - y");
    hansen_parser::print_intervals_information(intervals[0] * intervals[1], hansen_intervals[0] * hansen_intervals[1], "x * y");
    hansen_parser::print_intervals_information(intervals[0] / intervals[1], hansen_intervals[0] / hansen_intervals[1], "x / y");
    return 0;
}

