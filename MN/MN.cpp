#include <iostream>
#include "interval.h"
#include "hansen_arith.h"
#include "hansen_intervals_parser.h"
#include "interval_matrix.h"
#include "system_of_linear_equations.h"
#include "hansen_interval_matrix.h"

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

    //testowanie macierzy i liniowego układu równań
    std::vector<std::vector<interval>> matA = { {interval(2, 4), interval(-1, 1)}, {interval(-1, 1), interval(2, 4)} };
    std::vector<std::vector<interval>> matb = { {interval(-3, 3)}, {interval(0)} };
    interval_matrix A = interval_matrix(matA);
    interval_matrix b = interval_matrix(matb);
    system_of_linear_equations sole = system_of_linear_equations(A, b);
    std::cout << sole << std::endl << std::endl;
    std::cout << hansen_parser::parse_sole(sole) << std::endl;
    
    return 0;
}

