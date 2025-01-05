#include <iostream>

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

float indexToReal(float lowerLimit, float upperLimit, int pixelIndex,
                  int width) {
    if (pixelIndex < 0 || pixelIndex >= width) {
        printf("bad index (iToR)\n");
        exit(1);
    }
    if (width == 0) {
        printf("bad width (iToR)\n");
        exit(1);
    }
    return lowerLimit + pixelIndex * (upperLimit - lowerLimit) * 1.0 / width;
}

int realToIndex(float lowerLimit, float upperLimit, float input, int width) {
    if (input < lowerLimit || input >= upperLimit) {
        printf("bad index (rToI)\n");
        exit(1);
    }
    if (width == 0) {
        printf("bad range (rToI)\n");
        exit(1);
    }
    int result = width * (input - lowerLimit) / (upperLimit - lowerLimit);
    return result;
}

bool roughlyEquals(float a, float b, float epsilon) {
    if (abs(a - b) < epsilon) {
        return 1;
    }
    return 0;
}

}  // namespace RTC