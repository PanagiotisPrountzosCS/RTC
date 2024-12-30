#pragma once

namespace RTC {

class Color {
public:
    Color(float x, float y, float z);
    Color();

    Color operator+(const Color& rhs) const;

    Color operator-(const Color& rhs) const;

    Color operator*(const float& rhs) const;

    Color operator*(const Color& rhs) const;

    float r;
    float g;
    float b;
};
}  // namespace RTC