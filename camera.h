#ifndef CAMERA_H
#define CAMERA_H

#include "rtpp.h"
#include "constants.h"
#include "hittable_list.h"

class camera {
public:
	double aspect_ratio      = 1.0; 
	int    image_width       = 100;
	int    samples_per_pixel = 10;
	
	void render(const hittable& world) {
		initialize();
		std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++){
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color(0,0,0);
				for (int sample = 0; sample < samples_per_pixel; sample++){
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, world);
				}

				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}

		std::clog << "\rDONE                              \n";
	}

private:
	int image_height;
	double pixel_samples_scale;
	point3 camera_center;
	point3 pixel_origin;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;
	
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * aspect_ratio;
		auto camera_center = point3(0, 0, 0);

		pixel_samples_scale = 1.0 / samples_per_pixel;

		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel_origin = viewport_ul + 0.5 * (pixel_delta_v + pixel_delta_u);

	}

	color ray_color(const ray& r, const hittable& world) const {
		hit_record rec;
		
		if (world.hit_object(r, interval(0, INF), rec)) {
			vec3 direction = random_on_hemisphere(rec.normal);
			return 0.5 * ray_color(ray(rec.p, direction), world);
		}

		vec3 u_dir = unit_vector(r.direction());
		auto a = 0.5 * (u_dir.y() + 1.0);

		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

	ray get_ray(int i, int j) const {
		auto offset = sample_square();
		auto pixel_sample = pixel_origin
						+ ((i + offset.x()) * pixel_delta_u) 
						+ ((j + offset.y()) * pixel_delta_v);

		auto ray_origin = camera_center;
		auto ray_direction = pixel_sample - ray_origin;
		return ray(ray_origin, ray_direction);
	}

	vec3 sample_square() const {
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}
};

#endif
