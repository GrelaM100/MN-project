#include "hansen_arith.h"


interval reduce(const hansen_interval& a) {
    interval a_reduced = interval(0, 0);
    a_reduced = a_reduced + a.center();

    for (int i = 0; i < a.r().size(); i++) {
        a_reduced = a_reduced + a.r()[i] * a.v()[i];
    }
    
    return a_reduced;
}


hansen_interval operator+(const hansen_interval& a, const hansen_interval& b)
{
    interval center_sum(a.center() + b.center());
    std::vector <interval> v_sum;

    for (int i = 0; i < a.v().size(); i++) {
        v_sum.push_back(a.v()[i] + b.v()[i]);
    }

    return hansen_interval(center_sum, v_sum, a.r());
}

hansen_interval operator-(const hansen_interval& a, const hansen_interval& b)
{
    interval center_sum(a.center() - b.center());
    std::vector <interval> v_sum;

    for (int i = 0; i < a.v().size(); i++) {
        v_sum.push_back(a.v()[i] - b.v()[i]);
    }

    return hansen_interval(center_sum, v_sum, a.r());
}

hansen_interval operator*(const hansen_interval& a, const hansen_interval& b)
{
    interval c_center = a.center() * b.center();
    std::vector <interval> c_v;
    interval vi;
    interval rj_vj_sum = interval(0, 0);

    for (int i = 0; i < a.v().size(); i++) {
        c_center = c_center + (interval(0, a.r()[1].radius() * a.r()[1].radius()) * a.v()[i] * b.v()[i]);
    }

    for (int i = 0; i < a.v().size(); i++) {
        vi = a.center() * b.v()[i] + b.center() * a.v()[i];

        for (int j = 0; j < b.v().size(); j++) {
            if (i != j) {
                rj_vj_sum = rj_vj_sum + (b.r()[j] * b.v()[j]);
            }    
        }

        vi = vi + (interval(-1, 1) * a.v()[i] * rj_vj_sum);
        c_v.push_back(vi);
    }

    return hansen_interval(c_center, c_v, a.r());
}

hansen_interval operator/(const hansen_interval& a, const hansen_interval& b) 
{
    interval c_center = a.center() / b.center();
    std::vector <interval> c_v;
    interval vi;
    interval rj_vj_sum = interval(0, 0);

    for (int i = 0; i < a.v().size(); i++) {
        vi = b.center() * a.v()[i] - a.center() * b.v()[i];

        for (int j = 0; j < b.v().size(); j++) {
            if (i != j) {
                rj_vj_sum = rj_vj_sum + (b.r()[j] * b.v()[j]);
            }
        }

        vi = vi / (b.center() * (b.center() +  rj_vj_sum));
        c_v.push_back(vi);
    }
    return hansen_interval(c_center, c_v, a.r());
}