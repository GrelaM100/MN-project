#include <iostream>
#include <fstream> 
#include <string>
#include <time.h>
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
    cout << "\n\nRozwiazanie ukladu rownan metoda Gaussa:\n";
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
    cout << "\nRozwiazanie ukladu rownan metoda Gaussa z wykorzystaniem arytmetyki Hansena:\n";
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

system_of_linear_equations create_example(int input) {
    vector<interval> rows;
    vector<vector<interval>> matA;
    vector<vector<interval>> matB;
    interval element;
    int n = rand() % 4 + 3;
    //int n = 2;
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
            if (rows.size() != n) {
                cout << "Niewlasciwa liczba argumentow. Powinno zostac podane " << n * 2 << " liczb\n";
                break;
            }
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

system_of_linear_equations_hansen_form create_hansen_example(system_of_linear_equations sole) {

    int n = sole.A().get_rows();
    vector<vector<hansen_interval>> matA;
    vector<vector<hansen_interval>> matB;
    interval_matrix A = sole.A();
    interval_matrix b = sole.b();
    vector <interval> intervals;
    vector<hansen_interval> hansen_intervals;
    vector<hansen_interval> rows;
    //hansen_interval_matrix hansen_matrix;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            intervals.push_back(A(i, j));
        }
    }
    for (int i = 0; i < n; i++) {
        intervals.push_back(b(i, 0));
    }
    hansen_intervals = hansen_parser::parse(intervals);
    //cout << hansen_intervals[0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rows.push_back(hansen_intervals[i*n + j]);
        }
        matA.push_back(rows);
        rows.clear();
    }
    for (int i = 0; i < n; i++) {
        rows.push_back(hansen_intervals[n * n + i]);
        matB.push_back(rows);
        rows.clear();
    }

    hansen_interval_matrix A_hansen = hansen_interval_matrix(matA);
    hansen_interval_matrix B_hansen = hansen_interval_matrix(matB);
    cout << "Czy chcesz wyswietlic macierz przedzialow w postaci Hansena [t/n]?\n";
    string input;
    cin >> input;
    if (input == "t") {
        cout << "\nMacierz A:\n" << A_hansen;
        cout << "\nMacierz B:\n" << B_hansen;
    }
    system_of_linear_equations_hansen_form sole_hansen = system_of_linear_equations_hansen_form(A_hansen, B_hansen);
    return (sole_hansen);
}

void example1() {
    interval a1, a2, a3;
    vector <interval> intervals;
    vector<hansen_interval> hansen_intervals;
    vector<vector<interval>> matA;
    vector<vector<interval>> matB;
    vector<vector<hansen_interval>> hansen_matA;
    vector<vector<hansen_interval>> hansen_matB;


    a1 = interval(1, 2);
    a2 = interval(2, 7);
    a3 = interval(2, 3);
    intervals.push_back(a1);
    intervals.push_back(a2);
    intervals.push_back(a3);
    hansen_intervals = hansen_parser::parse(intervals);
    matA = { { intervals[0], intervals[1] }, { intervals[0]+intervals[1], intervals[0] + intervals[2] } };
    matB = { { intervals[0] }, { intervals[1]} };
    hansen_matA = { { hansen_intervals[0], hansen_intervals[1] }, { hansen_intervals[0] + hansen_intervals[1], hansen_intervals[0] + hansen_intervals[2] } };
    hansen_matB = { { hansen_intervals[0] }, { hansen_intervals[1]} };

    interval_matrix A = interval_matrix(matA);
    interval_matrix B = interval_matrix(matB);
    hansen_interval_matrix hansen_A = hansen_interval_matrix(hansen_matA);
    hansen_interval_matrix hansen_B = hansen_interval_matrix(hansen_matB);
    //cout << A_hansen;
    system_of_linear_equations sole = system_of_linear_equations(A, B);
    system_of_linear_equations_hansen_form sole_hansen = system_of_linear_equations_hansen_form(hansen_A, hansen_B);


    cout << "Przyklad 1: (wspolczynniki w dokumentacji)";

    vector<interval> I = solve(sole);
    vector<hansen_interval> I_hansen = solve_using_hansen(sole_hansen);

}

void example2() {
    interval a1, a2, a3;
    vector <interval> intervals;
    vector<hansen_interval> hansen_intervals;
    vector<vector<interval>> matA;
    vector<vector<interval>> matB;
    vector<vector<hansen_interval>> hansen_matA;
    vector<vector<hansen_interval>> hansen_matB;


    a1 = interval(0.065,0.07);
    a2 = interval(0.0073, 0.057);
    a3 = interval(2, 3);
    intervals.push_back(a1);
    intervals.push_back(a2);
    intervals.push_back(a3);
    hansen_intervals = hansen_parser::parse(intervals);
    matA = { { intervals[0] + intervals[0], intervals[1] + intervals[1] }, { intervals[0] + intervals[1], intervals[0] + intervals[2] } };
    matB = { { intervals[0] }, { intervals[2]} };
    hansen_matA = { { hansen_intervals[0] + hansen_intervals[0], hansen_intervals[1] + hansen_intervals[1]}, { hansen_intervals[0] + hansen_intervals[1], hansen_intervals[0] + hansen_intervals[2] } };
    hansen_matB = { { hansen_intervals[0] }, { hansen_intervals[2]} };

    interval_matrix A = interval_matrix(matA);
    interval_matrix B = interval_matrix(matB);
    hansen_interval_matrix hansen_A = hansen_interval_matrix(hansen_matA);
    hansen_interval_matrix hansen_B = hansen_interval_matrix(hansen_matB);
    //cout << A_hansen;
    system_of_linear_equations sole = system_of_linear_equations(A, B);
    system_of_linear_equations_hansen_form sole_hansen = system_of_linear_equations_hansen_form(hansen_A, hansen_B);

    cout << "\nPrzyklad 2:";
    vector<interval> I = solve(sole);
    vector<hansen_interval> I_hansen = solve_using_hansen(sole_hansen);
}

void example3() {
    interval a1, a2, a3;
    vector <interval> intervals;
    vector<hansen_interval> hansen_intervals;
    vector<vector<interval>> matA;
    vector<vector<interval>> matB;
    vector<vector<hansen_interval>> hansen_matA;
    vector<vector<hansen_interval>> hansen_matB;


    a1 = interval(4, 9);
    a2 = interval(1, 7);
    a3 = interval(2, 3);
    intervals.push_back(a1);
    intervals.push_back(a2);
    intervals.push_back(a3);
    hansen_intervals = hansen_parser::parse(intervals);
    matA = { { intervals[0], intervals[1], intervals[2] }, { intervals[1], intervals[0], intervals[1] }, { intervals[2], intervals[1], intervals[0] } };
    matB = { { intervals[0] }, { intervals[1]}, { intervals[2]} };
    hansen_matA = { { hansen_intervals[0], hansen_intervals[1], hansen_intervals[2] }, { hansen_intervals[1], hansen_intervals[0], hansen_intervals[1] }, { hansen_intervals[2], hansen_intervals[1], hansen_intervals[0] } };
    hansen_matB = { { hansen_intervals[0] }, { hansen_intervals[1]}, { hansen_intervals[2]} };

    interval_matrix A = interval_matrix(matA);
    interval_matrix B = interval_matrix(matB);
    hansen_interval_matrix hansen_A = hansen_interval_matrix(hansen_matA);
    hansen_interval_matrix hansen_B = hansen_interval_matrix(hansen_matB);
    //cout << A_hansen;
    system_of_linear_equations sole = system_of_linear_equations(A, B);
    system_of_linear_equations_hansen_form sole_hansen = system_of_linear_equations_hansen_form(hansen_A, hansen_B);

    cout << "\nPrzyklad 3:";

    vector<interval> I = solve(sole);
    vector<hansen_interval> I_hansen = solve_using_hansen(sole_hansen);
}


int main()
{
    srand(time(NULL));


    example1();
    example2();
    example3();
    int input;
    cout << "\n\nWybierz co chcesz zrobic\n\t1. Wylosuj uklad rownan\n\t2. Wczytaj uklad rownan";
    cin >> input;

    system_of_linear_equations sole = create_example(input);
    system_of_linear_equations_hansen_form sole_hansen = create_hansen_example(sole);
    vector<interval> I = solve(sole);
    vector<hansen_interval> I_hansen = solve_using_hansen(sole_hansen);
    
    system("pause");

    example1();

    return 0;
}
