#include "color.h"

namespace RTC {

Color::Color(float x, float y, float z) {
    r = x;
    g = y;
    b = z;
}

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color Color::operator+(const Color& rhs) const {
    Color result(r + rhs.r, g + rhs.g, b + rhs.b);

    return result;
}

Color Color::operator-(const Color& rhs) const {
    Color result(r - rhs.r, g - rhs.g, b - rhs.b);

    return result;
}

Color Color::operator*(const float& rhs) const {
    Color result(r * rhs, g * rhs, b * rhs);

    return result;
}

Color Color::operator*(const Color& rhs) const {
    Color result(r * rhs.r, g * rhs.g, b * rhs.b);

    return result;
}

}  // namespace RTC