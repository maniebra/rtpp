#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel) {
	auto r = pixel.x();
	auto g = pixel.y();
	auto b = pixel.z();

	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif
