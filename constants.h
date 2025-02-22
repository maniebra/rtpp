#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>

const auto PI = 3.141592;
const auto INF = std::numeric_limits<double>::infinity();

inline double deg_to_rad(double deg)
{
	return deg * PI / 180.0;
}

#endif
