
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hitobjects.h"

#include <iostream>

color ray_color(const ray& r) {
	if (hit_sphere(point3(0, 1, -2), 0.5, r)) {
		return color(1, 0, 0);
	}

	vec3 u_dir = unit_vector(r.direction());
	auto a = 0.5 * (u_dir.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1);
}

int main() {
	
	// image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double)(image_width) / image_height;
	auto camera_center = point3(0, 0, 0);

	// viewport
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// pixel deltas
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// UL pixel
	auto viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v;
	auto pixel_origin = viewport_ul + (pixel_delta_v + pixel_delta_u) / 2;

	// render the image
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++){
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto origin = pixel_origin + (i * pixel_delta_u) + (j * pixel_delta_v); 
			auto direction = origin - camera_center;
			
			ray r(origin, direction);

			color clr = ray_color(r);
			write_color(std::cout, clr);
		}
	}

	std::clog << "\rDONE                              \n";
}
