#include <fstream>

#include "../include/rtweekend.h"

#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/material.h"
#include "../include/sphere.h"
#include "../include/camera.h"

using namespace std;

int main() {

    // World

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


    // Render

    ofstream MyFile("filename.ppm");

    camera cam;
    cam.render(world, MyFile);

    

    MyFile.close();
}