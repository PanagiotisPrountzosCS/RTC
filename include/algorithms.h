#pragma once

namespace RTC {

float clamp(float lowerLimit, float upperLimit, float input);

float indexToReal(float lowerLimit, float upperLimit, int pixelIndex, int width);

int realToIndex(float lowerLimit, float upperLimit, float input, int width);

bool roughlyEquals(float a, float b, float epsilon = 0.001);

}  // namespace RTC