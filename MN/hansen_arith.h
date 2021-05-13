#pragma once
#include <vector>
#include "interval.h"
#include <ostream>

class ostream;

class hansen_interval {
	interval _center;
	std::vector <interval> _v;
	std::vector <interval> _r;
public:
	hansen_interval() : _center(0), _v(0), _r(0) {};
	hansen_interval(interval c, std::vector <interval> v, std::vector <interval> z) : _center(c), _v(v), _r(z){};
	hansen_interval(double c, std::vector <interval> v, std::vector <interval> z) : _center(c), _v(v), _r(z) {};
	interval center() const { return _center; }
	std::vector <interval> v() const { return _v; }
	std::vector <interval> r() const { return _r; }
	friend interval reduce(const hansen_interval& a);
	friend hansen_interval operator+(const hansen_interval& a, const hansen_interval& b);
	friend hansen_interval operator-(const hansen_interval& a, const hansen_interval& b);
	friend hansen_interval operator*(const hansen_interval& a, const hansen_interval& b);
	friend hansen_interval operator/(const hansen_interval& a, const hansen_interval& b);
};

inline std::ostream& operator <<(std::ostream& os, const hansen_interval& a) {
	os << a.center();
	//z u¿yte zamiast greckiej litery zeta
	for (unsigned i = 0; i < a.v().size(); i++) {
		os << " + " << a.v()[i] << "z" << i + 1;
	}
	return os;
}