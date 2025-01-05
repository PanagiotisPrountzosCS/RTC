#include <cmath>
#include <iostream>

#include "algorithms.h"
#include "tuple.h"

namespace RTC {
Tuple::Tuple() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Tuple::Tuple(float a, float b, float c, float d) {
    x = a;
    y = b;
    z = c;
    w = d;
}

Tuple Tuple::operator+(const Tuple& rhs) const {
    Tuple result(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    return result;
}

Tuple Tuple::operator-(const Tuple& rhs) const {
    Tuple result(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    return result;
}

Tuple Tuple::operator-() const {
    Tuple result(-x, -y, -z, -w);
    return result;
}

Tuple Tuple::operator*(const float& scalar) const {
    Tuple result(x * scalar, y * scalar, z * scalar, w * scalar);
    return result;
}

Tuple Tuple::operator/(const float& scalar) const {
    if (scalar == 0) {
        printf("Division by 0, terminating...\n");
        exit(1);
    }
    Tuple result(x / scalar, y / scalar, z / scalar, w / scalar);
    return result;
}

float Tuple::operator*(const Tuple& rhs) const {
    float result = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;

    return result;
}

std::ostream& operator<<(std::ostream& os, const Tuple& rhs) {
    os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w
       << ")\n";
    return os;
}

bool Tuple::operator==(const Tuple& rhs) const {
    if (roughlyEquals(x, rhs.x) && roughlyEquals(y, rhs.y) &&
        roughlyEquals(z, rhs.z) && roughlyEquals(w, rhs.w)) {
        return true;
    }
    return false;
}

Vector Vector::operator^(const Tuple& rhs) const {
    Vector result(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                  x * rhs.y - y * rhs.x);

    return result;
}

Point Point::operator+(const Vector& rhs) const {
    Point result(x + rhs.x, y + rhs.y, z + rhs.z);

    return result;
}

Point Vector::operator+(const Point& rhs) const {
    Point result(x + rhs.x, y + rhs.y, z + rhs.z);

    return result;
}

Vector Vector::operator*(const float& rhs) const {
    Vector result(x * rhs, y * rhs, z * rhs);
    return result;
}

float Tuple::magnitude() { return sqrt(x * x + y * y + z * z + w * w); }

void Tuple::normalize() {
    float mag = magnitude();
    if (mag == 0) {
        printf("Division by 0, terminating...\n");
        exit(1);
    }
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}

Point::Point(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
    w = 1;
}

Point::Point() { w = 1; }

Vector::Vector(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
    w = 0;
}

Vector::Vector() { w = 0; }

}  // namespace RTC