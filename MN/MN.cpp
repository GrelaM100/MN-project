#include <iostream>
#include <fstream> 
#include <string>
#include <time.h>
#include "interval.h"
#include "hansen_arith.h"
#include "hansen_intervals_parser.h"
#include "interval_matrix.h"
#include "system_of_linear_equations.h"
#include "system_of_linear_equations_hansen_form.h"
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
    //cout << "A =\n" << A << "\n";
    //cout << "b = \n" << b << "\n";
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
            a = interval(-0.55, -0.45);
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

vector<interval> split_row(string s) {
    vector<double> list;
    vector<interval> new_row;
    string delimiter = ";";

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(stoi(s));

    interval element;
    for (int i = 0; i < list.size()/2; i++) {
        element = interval(min(list[2*i], list[2*i+1]), max(list[2 * i], list[2 * i + 1]));
        //cout << element << " ";
        new_row.push_back(element);
    }
    return(new_row);
}

system_of_linear_equations create_example() {
    int input;
    cout << "Rozwiazywanie ukladu rownan metoda Gassa.\nWybierz co chcesz zrobic\n\t1. Wylosuj uklad rownan\n\t2. Wczytaj uklad rownan\n";
    cin >> input;
    vector<interval> rows;
    vector<vector<interval>> matA;
    vector<vector<interval>> matB;
    interval element;
    int n = rand() % 4 + 2;
    int a1, a2;
    string row_input;


    switch (input)
    {
    case 1:
        cout << "Losowy przyklad: (wylosowano liczbe zmiennych = " << n << ")\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a1 = rand() % 100+1;
                a2 = rand() % 100+1;
                element = interval(min(a1, a2), max(a1, a2));
                rows.push_back(element);
            }
            matA.push_back(rows);
            rows.clear();
        }

        for (int i = 0; i < n; i++) {
            a1 = rand() % 100 + 1;
            a2 = rand() % 100 + 1;
            element = interval(min(a1, a2), max(a1, a2));
            rows.push_back(element);
            matB.push_back(rows);
            rows.clear();
        }

        break;

    case 2:
        cout << "Podaj liczbe zmiennych\n";
        cin >> n;
        cout << "Podaj kolejne wiersze macierzy A\n\tnp. 2;5;7;4 oznacza [(1,2), (7,4)]\n";
        for (int i = 0; i < n; i++) {
            cin >> row_input;
            rows = split_row(row_input);
            matA.push_back(rows);
        }
        cout << "Podaj kolejne wiersze macierzy b\n";
        for (int i = 0; i < n; i++) {
            cin >> row_input;
            rows = split_row(row_input);
            matB.push_back(rows);
        }
        break;
    default:
        cout << "Nie ma takiej opcji";
        break;
    }
    interval_matrix A = interval_matrix(matA);
    cout << "A:\n" << A;
    interval_matrix b = interval_matrix(matB);
    cout << "b:\n" << b;


    system_of_linear_equations sole = system_of_linear_equations(A, b);
    return (sole);
}

int main()
{
    //kod testowy
    //interval x, y;
    //std::vector <interval> intervals;
    //std::vector <hansen_interval> hansen_intervals;

    //x = interval(1, 2);
    //y = interval(3, 4);

    //intervals.push_back(x);
    //intervals.push_back(y);

    //hansen_intervals = hansen_parser::parse(intervals);
    //hansen_parser::print_intervals_information(intervals[0], hansen_intervals[0], "x");
    //hansen_parser::print_intervals_information(intervals[1], hansen_intervals[1], "y");
    //hansen_parser::print_intervals_information(intervals[0] + intervals[1], hansen_intervals[0] + hansen_intervals[1], "x + y");
    //hansen_parser::print_intervals_information(intervals[0] - intervals[1], hansen_intervals[0] - hansen_intervals[1], "x - y");
    //hansen_parser::print_intervals_information(intervals[0] * intervals[1], hansen_intervals[0] * hansen_intervals[1], "x * y");
    //hansen_parser::print_intervals_information(intervals[0] / intervals[1], hansen_intervals[0] / hansen_intervals[1], "x / y");

    ////testowanie macierzy i liniowego uk�adu r�wna�
    //std::vector<std::vector<interval>> matA = { {interval(2, 4), interval(-1, 1)}, {interval(-1, 1), interval(2, 4)} };
    //std::vector<std::vector<interval>> matb = { {interval(-3, 3)}, {interval(0)} };
    //interval_matrix A = interval_matrix(matA);
    //interval_matrix b = interval_matrix(matb);
    //system_of_linear_equations sole = system_of_linear_equations(A, b);
    //std::cout << sole << std::endl << std::endl;
    //std::cout << hansen_parser::parse_sole(sole) << std::endl;

    ////testowanie macierzy i liniowego uk�adu r�wna�
    ///*std::vector<std::vector<interval>> matA = { {interval(3), interval(1)}, {interval(3), interval(2)} };
    //std::vector<std::vector<interval>> matb = { {interval(1,1)}, {interval(0,0)} };*/
    //std::vector<std::vector<interval>> matA = { {interval(0, 1), interval(1, 2)}, {interval(-2), interval(-1, 2)} };
    //std::vector<std::vector<interval>> matb = { {interval(0,2)}, {interval(0,0)} };
    //interval_matrix A = interval_matrix(matA);
    //interval_matrix b = interval_matrix(matb);
    //system_of_linear_equations sole = system_of_linear_equations(A, b);
    //std::cout << sole << std::endl << std::endl;
    //std::cout << b * A;
    //std::cout << A.invert_matrix();
    //std::cout << sole.krawczyk_method() << std::endl << std::endl;
    //system_of_linear_equations_hansen_form soleH = hansen_parser::parse_sole(sole);
    //std::cout << soleH << std::endl << std::endl;
    //std::cout << soleH.krawczyk_method() << std::endl << std::endl;
    //std::cout << hansen_parser::parse_sole(sole) << std::endl;

    system_of_linear_equations sole = create_example();
    vector<interval> I = solve(sole);
    std::cout << "Rozwiazanie metoda Krawczyka: " << std::endl;
    std::cout << sole.krawczyk_method();

    return 0;
}

