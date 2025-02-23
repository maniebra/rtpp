#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>
#include <random>

const auto PI = 3.141592;
const auto INF = std::numeric_limits<double>::infinity();

inline double deg_to_rad(double deg)
{
	return deg * PI / 180.0;
}

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

#endif
