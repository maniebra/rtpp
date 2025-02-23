#include "rtpp.h"
#include "hittable_list.h"
#include "./hittables/sphere.h"
#include "camera.h"

#include <iostream>

int main() {
	
	// image
	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -2), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.2, -42.5), 100));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 200;
	cam.samples_per_pixel = 50;

	cam.render(world);
}
