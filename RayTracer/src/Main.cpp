#include <iostream>
#include <fstream>
using namespace std;

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    ofstream MyFile("filename.ppm");

    MyFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            MyFile << ir << ' ' << ig << ' ' << ib << '\n';

            
        }
    }

    MyFile.close();
}