#include "point.hh"
#include <string>
#include <sstream>

struct Line {
	const Point p1, p2;
	Line(const Point& p1_in=Point(), const Point& p2_in=Point()) : p1(p1_in), p2(p2_in){}
	double length() const;
	std::string toString() const;
};
