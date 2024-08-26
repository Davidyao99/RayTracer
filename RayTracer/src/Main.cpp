#include <fstream>

#include "../include/rtweekend.h"

#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/camera.h"

using namespace std;

int main() {

    // World

    hittable_list world;

    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));

    // Render

    ofstream MyFile("filename.ppm");

    camera cam;
    cam.render(world, MyFile);

    

    MyFile.close();
}