#include <iostream>
#include "interval.h"
#include <algorithm>

interval operator+(const interval& a, const interval& b) {
	return interval(a.inf() + b.inf(), a.sup() + b.sup());
}

interval operator-(const interval& a, const interval& b) {
	return interval(a.inf() - b.sup(), a.sup() - b.inf());
}

interval operator*(const interval& a, const interval& b) {
	double minVal = std::min(a.inf() * b.inf(), std::min(a.inf() * b.sup(), std::min(a.sup() * b.inf(), a.sup() * b.sup())));
	double maxVal = std::max(a.inf() * b.inf(), std::max(a.inf() * b.sup(), std::max(a.sup() * b.inf(), a.sup() * b.sup())));
	return interval(minVal, maxVal);
}

interval re(const interval& a)
{
	return interval((double)1 / a.sup(), (double)1 / a.inf());
}

interval operator/(const interval& a, const interval& b)
{
	interval bRe;
	bRe = re(b);
	return a * bRe;
}
