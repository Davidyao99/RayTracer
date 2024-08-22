#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"

using namespace std;

bool hit_sphere(const ray& r) {

    vec3 sphere_center = vec3(0, 0, -1);
    double sphere_radius = 0.5;
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), sphere_center - r.at(0));
    auto c = dot(sphere_center - r.at(0), sphere_center - r.at(0)) - sphere_radius * sphere_radius;

    auto discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}

color ray_color(const ray& r) {
    vec3 unit_ray = unit_vector(r.direction());
    auto t = 0.5 * (unit_ray.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

ray get_pixel_ray(const int x, const int y, const int image_width, const int image_height) {

    auto viewport_height = 2.0;
    auto viewport_width = (static_cast<double>(image_width) / image_height) * viewport_height;

    auto pixel_x_size = viewport_width / image_width;
    auto pixel_y_size = viewport_height / image_height;

    vec3 top_left_pixel = vec3(-viewport_width / 2 + pixel_x_size, viewport_height / 2 + pixel_y_size, -1);

    vec3 pixel = vec3(top_left_pixel.x() + x * pixel_x_size, top_left_pixel.y() - y * pixel_y_size, top_left_pixel.z());

    return ray(vec3(0, 0, 0), pixel);

}

int main() {

    auto aspect_ratio = 16.0 / 9.0;

    int image_width = 256;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;    // prevent image_height from being 0


    // Render

    ofstream MyFile("filename.ppm");

    MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        cout << "\rScanlines remaining: " << image_height - j << ' ' << flush;
        for (int i = 0; i < image_width; i++) {
            
            ray r = get_pixel_ray(i, j, image_width, image_height);

            auto pixel_color = ray_color(r);

            bool hit = hit_sphere(r);

            if (hit) {
				write_color(MyFile, color(255, 0, 0));
			} else {
				write_color(MyFile, pixel_color);
			}

//            write_color(MyFile, pixel_color);


        }
    }

    MyFile.close();
}