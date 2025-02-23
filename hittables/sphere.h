#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "../rtpp.h"

class sphere : public hittable {
public:
	sphere(const point3& center, double radius, std::shared_ptr<material> mat)
		: center(center), radius(std::fmax(0, radius)), mat(mat) {}

	bool hit_object(const ray& r, interval t, hit_record& rec) const override
	{
		vec3 oc = center - r.origin();
		
		auto a = dot(r.direction(), r.direction());
		auto b = dot(r.direction(), oc);
		auto c = dot(oc, oc) - radius * radius;

		auto delta = b*b - a*c;
		
		if (delta < 0)
			return false;
		
		auto sqrt_delta = std::sqrt(delta);
		auto sol = (b - sqrt_delta) / a;

		if (not t.surrounds(sol)) {
			sol = (b + sqrt_delta) / a;
			if (! t.surrounds(sol)) {
				return false;
			}
		}

		rec.t = sol;
		rec.p = r.at(rec.t);

		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;

		return true;
	}

private:
	point3 center;
	double radius;
	std::shared_ptr<material> mat;
};

#endif
