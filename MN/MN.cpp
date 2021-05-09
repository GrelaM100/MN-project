#include <iostream>
#include "interval.h"
#include "hansen_arith.h"

int main()
{
    //kod testowy
    interval x, y, a, b, c, d;
    hansen_interval h1, h2;
    std::vector <interval> z;

    x = interval(-5, 3);
    y = interval(1, 2);
    z.push_back(y);
    z.push_back(x);
    h1 = hansen_interval(5, z);
    h2 = hansen_interval(3, z);

    a = x + y;
    b = x - y;
    c = x * y;
    d = x / y;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << h1 + h2 << std::endl;
    std::cout << h1 - h2 << std::endl;
    return 0;
}

