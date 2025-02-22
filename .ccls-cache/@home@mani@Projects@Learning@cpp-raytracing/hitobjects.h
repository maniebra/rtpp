#ifndef HITOBJECTS
#define HITOBJECTS

#include "vec3.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = center - r.origin();
	
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;

	auto delta = b*b - 4*a*c;
	return (delta > 0);
}

#endif
