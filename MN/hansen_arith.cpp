#include "hansen_arith.h"

hansen_interval operator+(const hansen_interval& a, const hansen_interval& b)
{
    interval center_sum(a.center() + b.center());
    std::vector <interval> zeta_coefficients_sum;
    for (int i = 0; i < a.zeta_coefficients().size(); i++) {
        zeta_coefficients_sum.push_back(a.zeta_coefficients()[i] + b.zeta_coefficients()[i]);
    }
    return hansen_interval(center_sum, zeta_coefficients_sum);
}

hansen_interval operator-(const hansen_interval& a, const hansen_interval& b)
{
    interval center_sum(a.center() - b.center());
    std::vector <interval> zeta_coefficients_sum;
    for (int i = 0; i < a.zeta_coefficients().size(); i++) {
        zeta_coefficients_sum.push_back(a.zeta_coefficients()[i] - b.zeta_coefficients()[i]);
    }
    return hansen_interval(center_sum, zeta_coefficients_sum);
}