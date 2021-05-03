#pragma once
#include <ostream>

class ostream;

class interval
{
	double _inf;
	double _sup;
public:
	interval() : _inf(0), _sup(0) {};
	interval(double a) : _inf(a), _sup(a) {}
	interval(double a, double b) : _inf(a), _sup(b) {}
	double inf() const { return _inf; }
	double sup() const { return _sup; }
	friend interval operator+(const interval& a, const interval& b);
	friend interval operator-(const interval& a, const interval& b);
	friend interval operator*(const interval& a, const interval& b);
	friend interval re(const interval& a);
	friend interval operator/(const interval& a, const interval& b);
	double centr() { return (_inf + _sup) / 2; }
	double radius() { return (_sup - _inf) / 2; }
	double len() { return _sup - _inf; }
	double modMax() { return std::max(std::abs(_inf), std::abs(_sup)); }
	double modMin() { return std::min(std::abs(_inf), std::abs(_sup)); }
};

inline std::ostream& operator <<(std::ostream& os, const interval& a) {
	os << "[" << a.inf() << ", " << a.sup() << "]";
	return os;
}
