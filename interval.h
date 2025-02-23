#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

class interval {
public:
	double min, max;

	interval() : min(+INF), max(-INF) {}
	interval(double min, double max) : min(min), max(max) {}

	double size() const {
		return max - min;
	}

	bool contains(double x) const {
		return (x <= max) && (x >= min);
	}

	bool surrounds(double x) const {
		return (x < max) && (x > min);
	}

	double clamp(double x) const {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	static const interval empty, universe;
};

const interval interval::empty    = interval(+INF, -INF);
const interval interval::universe = interval(-INF, +INF);

#endif
