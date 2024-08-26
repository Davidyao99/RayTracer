#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>

#include "rtweekend.h"
#include "hittable.h"

using namespace std;

class camera {
public:
    /* Public Camera Parameters Here */

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    

    void render(const hittable& world, ofstream& MyFile) {

        this->initialize();

        MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            clog << "\rScanlines remaining: " << image_height - j << ' ' << flush;
            for (int i = 0; i < image_width; i++) {

                color pixel_color = get_sampled_pixel_color(i, j, world);

                hit_record* rec = new hit_record;

                write_color(MyFile, pixel_color);


                //            write_color(MyFile, pixel_color);


            }
        }

        clog << "\rDone. \n";
        
    }

private:
    /* Private Camera Variables Here */
    int image_height = 0;
    double viewport_width = 0;
    double viewport_height = 0;

    double pixel_x_size = 0;
    double pixel_y_size = 0;

    int    max_depth = 2;

    vec3 top_left_pixel = vec3(0, 0, 0);

    void initialize() {
        int image_height = static_cast<int>(image_width / aspect_ratio);
		this->image_height = (image_height < 1) ? 1 : image_height;    // prevent image_height from being 0

        viewport_height = 2.0;
        viewport_width = (static_cast<double>(image_width) / image_height) * viewport_height;

        pixel_x_size = viewport_width / image_width;
        pixel_y_size = viewport_height / image_height;

        top_left_pixel = vec3(-viewport_width / 2, viewport_height / 2, -1);
    }

    color get_sampled_pixel_color(const int x, const int y, const hittable& world) {

		color pixel_color(0, 0, 0);

		for (int s = 0; s < samples_per_pixel; s++) {

			auto pixel_ray = get_pixel_ray(x, y);
			pixel_color += ray_color(pixel_ray, max_depth, world);

		}

		pixel_color /= samples_per_pixel;

        return pixel_color;

	}

    ray get_pixel_ray(const int x, const int y) {

        auto pixel_x = top_left_pixel.x() + x * pixel_x_size;
        auto pixel_y = top_left_pixel.y() - y * pixel_y_size;

        pixel_x += random_double() * pixel_x_size;
        pixel_y -= random_double() * pixel_y_size;

        vec3 pixel = vec3(pixel_x, pixel_y, top_left_pixel.z());

        return ray(vec3(0, 0, 0), pixel);

    }

    color get_norm_color(const vec3 norm) {
        return 0.5 * color(norm.x() + 1, norm.y() + 1, norm.z() + 1);
    }

    color ray_color(const ray& r, int depth, const hittable& world) {

        if (depth < 0) {
            return color(0, 0, 0);
        }

        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {     // if we hit something, min at 0.001 to prevent float rounding errors
            // return 0.5 * color(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
            // vec3 direction = random_on_hemisphere(rec.normal);
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return color(0, 0, 0);
        }

        vec3 unit_ray = unit_vector(r.direction());   // if we did not hit anything
        auto t = 0.5 * (unit_ray.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};

#endif