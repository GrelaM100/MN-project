﻿#include <iostream>
#include "interval.h"
#include "hansen_arith.h"
#include "hansen_intervals_parser.h"
#include "interval_matrix.h"
#include "system_of_linear_equations.h"
#include "system_of_linear_equations_hansen_form.h"
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
    /*std::vector<std::vector<interval>> matA = { {interval(3), interval(1)}, {interval(3), interval(2)} };
    std::vector<std::vector<interval>> matb = { {interval(1,1)}, {interval(0,0)} };*/
    std::vector<std::vector<interval>> matA = { {interval(0, 1), interval(1, 2)}, {interval(-2), interval(-1, 2)} };
    std::vector<std::vector<interval>> matb = { {interval(0,2)}, {interval(0,0)} };
    interval_matrix A = interval_matrix(matA);
    interval_matrix b = interval_matrix(matb);
    system_of_linear_equations sole = system_of_linear_equations(A, b);
    std::cout << sole << std::endl << std::endl;
    std::cout << b * A;
    std::cout << A.invert_matrix();
    std::cout << sole.krawczyk_method() << std::endl << std::endl;
    system_of_linear_equations_hansen_form soleH = hansen_parser::parse_sole(sole);
    std::cout << soleH << std::endl << std::endl;
    std::cout << soleH.krawczyk_method() << std::endl << std::endl;
    return 0;
}

