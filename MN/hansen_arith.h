#pragma once
#include <vector>
#include "interval.h"
#include <ostream>

class ostream;

class hansen_interval {
	interval _center;
	std::vector <interval> _zeta_coefficients;
public:
	hansen_interval() : _center(0), _zeta_coefficients(0) {};
	hansen_interval(interval c, std::vector <interval> z) : _center(c), _zeta_coefficients(z){};
	hansen_interval(double c, std::vector <interval> z) : _center(c), _zeta_coefficients(z) {};
	interval center() const { return _center; }
	std::vector <interval> zeta_coefficients() const { return _zeta_coefficients; }
	friend hansen_interval operator+(const hansen_interval& a, const hansen_interval& b);
	friend hansen_interval operator-(const hansen_interval& a, const hansen_interval& b);
	friend hansen_interval operator*(const hansen_interval& a, const hansen_interval& b);
};

inline std::ostream& operator <<(std::ostream& os, const hansen_interval& a) {
	os << a.center();
	//z u¿yte zamiast greckiej litery zeta
	for (unsigned i = 0; i < a.zeta_coefficients().size(); i++) {
		os << " + " << a.zeta_coefficients()[i] << "z";
	}
	return os;
}