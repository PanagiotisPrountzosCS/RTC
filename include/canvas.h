#pragma once

#include <stdint.h>

#include "color.h"

namespace RTC {

class Canvas {
public:
    Canvas(uint64_t a, uint64_t b);
    ~Canvas();

    void writePixel(uint64_t i, uint64_t j, const Color& c);

    void toPPM(std::string path);

    uint64_t getWidth();
    uint64_t getHeight();

    Color** pixelArray;

private:
    // these are private to ensure they won't be changed after construction.
    // no setters allowed
    uint64_t width;
    uint64_t height;
};

}  // namespace RTC