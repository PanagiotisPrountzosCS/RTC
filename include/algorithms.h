#pragma once

namespace RTC {

float clamp(float lowerLimit, float upperLimit, float input);

float mapper(float lowerLimit, float upperLimit, int pixelIndex, int width);

bool roughlyEquals(float a, float b, float epsilon = 0.0001);

}  // namespace RTC