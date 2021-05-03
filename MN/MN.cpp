#include <iostream>
#include "interval.h"

int main()
{
    interval x, y, a, b, c, d;
    x = interval(-5, 3);
    y = interval(1, 2);
    a = x + y;
    b = x - y;
    c = x * y;
    d = x / y;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    return 0;
}

