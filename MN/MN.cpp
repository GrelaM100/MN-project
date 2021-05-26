#include <iostream>
#include "interval.h"
#include "hansen_arith.h"
#include "hansen_intervals_parser.h"
#include "interval_matrix.h"
#include "system_of_linear_equations.h"
#include "hansen_interval_matrix.h"

using namespace std;

void print(std::vector<interval> const& input)
{
    cout << "I = ";
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
    cout << "\n";
}
void print(std::vector<hansen_interval> const& input)
{
    cout << "I = ";
    for (int i = 0; i < input.size(); i++) {
        std::cout << reduce(input.at(i)) << ' ';
    }

    cout << "\n";
}

vector<interval> solve(system_of_linear_equations sole) {
    interval_matrix A = sole.A();
    interval_matrix b = sole.b();
    cout << "A =\n" << A << "\n";
    cout << "b = \n" << b << "\n";
    int n = A.get_rows();
    int m = A.get_cols();
    vector<interval> I(n);
    if (n < m) {
        cout << "Uklad nieoznaczony, posiada nieskonczenie wiele rozwiazan.\n";
        return(I);
    }
    if (n > m) {
        cout << "Uklad sprzeczny, nie posiada rozwiazania.\n";
        return(I);
    }


    interval a;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            a = A(j, i) / A(i, i);
            for (int k = 0; k < n; k++) {
                A(j, k) = A(j, k) - a * A(i, k);
            }
            b(j, 0) = b(j, 0) - a * b(i, 0);
        }
    }

    I.at(n - 1) = b(n - 1, 0) / A(n - 1, n - 1);
    for (int i = n - 2; i >= 0; i--) {
        a = b(i, 0);
        for (int j = n - 1; j > i; j--) {
            a = a - A(i, j) * I.at(j);
        }
        I.at(i) = a / A(i, i);
    }
    cout << "Rozwiazanie ukladu rownan:\n";
    print(I);
    return(I);
}

vector<hansen_interval> solve_using_hansen(system_of_linear_equations_hansen_form sole) {
    hansen_interval_matrix A = sole.A();
    hansen_interval_matrix b = sole.b();
    int n = A.get_rows();
    int m = A.get_cols();
    vector<hansen_interval> I(n);
    if (n < m) {
        cout << "Uklad nieoznaczony, posiada nieskonczenie wiele rozwiazan.\n";
        return(I);
    }
    if (n > m) {
        cout << "Uklad sprzeczny, nie posiada rozwiazania.\n";
        return(I);
    }
    hansen_interval a;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            a = A(j, i) / A(i, i);
            for (int k = 0; k < n; k++) {
                A(j, k) = A(j, k) - a * A(i, k);
            }
            b(j, 0) = b(j, 0) - a * b(i, 0);
        }
    }

    I.at(n - 1) = b(n - 1, 0) / A(n - 1, n - 1);
    for (int i = n - 2; i >= 0; i--) {
        a = b(i, 0);
        for (int j = n - 1; j > i; j--) {
            a = a - A(i, j) * I.at(j);
        }
        I.at(i) = a / A(i, i);
    }
    cout << "Rozwiazanie ukladu rownan z wykorzystaniem arytmetyki Hansena:\n";
    print(I);
    return(I);
}


void run_example() { //kod testowy
    cout << "Przykladowe rownanie:\n";
    interval a1, a2, a3, a4, b1, b2;
    std::vector <interval> intervals;
    std::vector <hansen_interval> hansen_intervals;

    a1 = interval(1, 5);
    a2 = interval(3, 9);
    a3 = interval(2, 3);
    a4 = interval(9, 10);
    b1 = interval(1, 4);
    b2 = interval(1, 10);


    intervals.push_back(a1);
    intervals.push_back(a2);
    intervals.push_back(a3);
    intervals.push_back(a4);
    intervals.push_back(b1);
    intervals.push_back(b2);

    hansen_intervals = hansen_parser::parse(intervals);

    vector<vector<hansen_interval>> matA1 = { {hansen_intervals[0], hansen_intervals[1]}, {hansen_intervals[2], hansen_intervals[3]} };
    vector<vector<hansen_interval>> matb1 = { {hansen_intervals[4]},{hansen_intervals[5]} };
    hansen_interval_matrix A1 = hansen_interval_matrix(matA1);
    hansen_interval_matrix B1 = hansen_interval_matrix(matb1);



    vector<vector<interval>> matA = { {intervals[0], intervals[1]}, {intervals[2], intervals[3]} };
    vector<vector<interval>> matb = { {intervals[4]},{intervals[5]} };
    interval_matrix A = interval_matrix(matA);
    interval_matrix b = interval_matrix(matb);


    system_of_linear_equations sole = system_of_linear_equations(A, b);
    vector<interval> I = solve(sole);

    system_of_linear_equations_hansen_form sole_hansen = system_of_linear_equations_hansen_form(A1, B1);
    vector<hansen_interval> I1 = solve_using_hansen(sole_hansen);
}


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


    run_example();

    return 0;
}
