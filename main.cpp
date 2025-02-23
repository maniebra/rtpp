#include "rtpp.h"
#include "hittable_list.h"
#include "./hittables/sphere.h"
#include "camera.h"

#include <iostream>

int main() {
	
	// image
	hittable_list world;

	auto material_lmbase = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_lambr1 = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_metal1   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.33);
	auto material_metal2  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<sphere>(point3(0, 0, -2), 0.5, material_lambr1));
	world.add(make_shared<sphere>(point3(0, -100.5, -1.5), 100, material_lmbase));
	world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_metal1));
	world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_metal2));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = HD;
	cam.samples_per_pixel = 10;
	cam.max_depth = 50;

	cam.render(world);
}
