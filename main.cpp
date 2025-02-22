#include "rtpp.h"
#include "hittable_list.h"
#include "./hittables/sphere.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit_object(r, interval(0, INF), rec)) {
	return 0.5 * (rec.normal + color(1,1,1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);
	return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
	
	// image
	hittable_list world;
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = SD;
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	world.add(make_shared<sphere>(point3(0, 0, -2), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -42.5), 100));

	// camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width)) / image_height;
	auto camera_center = point3(0, 0, 0);

	// viewport
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// pixel deltas
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// UL pixel
	auto viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	auto pixel_origin = viewport_ul + 0.5 * (pixel_delta_v + pixel_delta_u);

	// render the image
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++){
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto origin = pixel_origin + (i * pixel_delta_u) + (j * pixel_delta_v); 
			auto direction = origin - camera_center;
			
			ray r(origin, direction);

			color clr = ray_color(r, world);
			write_color(std::cout, clr);
		}
	}

	std::clog << "\rDONE                              \n";
}
