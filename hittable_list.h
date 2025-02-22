#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittables/hittable.h"

#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:
	std::vector<shared_ptr<hittable>> objects;

	hittable_list() {}
	hittable_list(shared_ptr<hittable> objects) { add(objects); }

	void clear() { objects.clear(); }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit_object(const ray& r, interval t, hit_record& rec) const override
	{
		hit_record temp_rec;
		bool hit_anything = false;
		auto closest_object = t.max;

		for (const auto& object : objects) {
			if (object->hit_object(r, interval(t.min, closest_object), temp_rec)) {
				hit_anything = true;
				closest_object = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}
};

#endif
