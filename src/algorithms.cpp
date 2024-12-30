#include "algorithms.h"
#include "stdlib.h"

namespace RTC {

float clamp(float lowerLimit, float upperLimit, float input) {
    if (input > upperLimit) {
        return upperLimit;
    } else if (input < lowerLimit) {
        return lowerLimit;
    } else {
        return input;
    }
}

float mapper(float lowerLimit, float upperLimit, int pixelIndex, int width) {
    if (pixelIndex < 0 || pixelIndex >= width) {
        exit(1);
    }
    return lowerLimit + pixelIndex * (upperLimit - lowerLimit) * 1.0 / width;
}

bool roughlyEquals(float a, float b, float epsilon) {
    if (abs(a - b) < epsilon) {
        return 1;
    }
    return 0;
}

}  // namespace RTC