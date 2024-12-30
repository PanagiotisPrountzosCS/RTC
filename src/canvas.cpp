#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>

#include "algorithms.h"
#include "canvas.h"

namespace RTC {

Canvas::Canvas(uint64_t a, uint64_t b) {
    width = a;
    height = b;
    pixelArray = new Color*[width];
    for (int i = 0; i < width; i++) {
        pixelArray[i] = new Color[height];
    }
}

Canvas::~Canvas() {
    for (int i = 0; i < width; i++) {
        delete pixelArray[i];
    }
    delete pixelArray;
}

void Canvas::writePixel(uint64_t i, uint64_t j, const Color& c) {
    if (i >= width || j >= height) {
        exit(1);
    }
    pixelArray[i][j] = c;
}

void Canvas::toPPM(std::string path) {
    std::ofstream output;
    int ri, gi, bi;
    std::string r, g, b;
    std::string currentString = "";

    output.open(path);
    if (output.is_open()) {
        output << "P3\n";
        output << width << ' ' << height << '\n';
        output << "255\n";

        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                ri = ceil(clamp(0, 255, pixelArray[i][j].r * 255));
                r = std::to_string(ri);
                gi = ceil(clamp(0, 255, pixelArray[i][j].g * 255));
                g = std::to_string(gi);
                bi = ceil(clamp(0, 255, pixelArray[i][j].b * 255));
                b = std::to_string(bi);

                if (currentString.size() + r.size() < 70) {
                    currentString.append(r);
                    currentString.append(" ");
                } else {
                    currentString.pop_back();
                    currentString.append("\n");
                    output << currentString;
                    currentString = r;
                    currentString.append(" ");
                }
                if (currentString.size() + g.size() < 70) {
                    currentString.append(g);
                    currentString.append(" ");
                } else {
                    currentString.pop_back();
                    currentString.append("\n");
                    output << currentString;
                    currentString = g;
                    currentString.append(" ");
                }
                if (currentString.size() + b.size() < 70) {
                    currentString.append(b);
                    currentString.append(" ");
                } else {
                    currentString.pop_back();
                    currentString.append("\n");
                    output << currentString;
                    currentString = b;
                    currentString.append(" ");
                }
            }
            currentString.pop_back();
        output << currentString << '\n';
        currentString = "";
        }
        output.close();
    } else {
        exit(1);
    }
}

uint64_t Canvas::getWidth() { return width; }

uint64_t Canvas::getHeight() { return height; }

}  // namespace RTC