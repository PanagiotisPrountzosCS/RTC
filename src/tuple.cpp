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

float Tuple::magnitude() const { return sqrt(x * x + y * y + z * z + w * w); }

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

Tuple operator+(const Tuple& lhs, const Tuple& rhs) {
    Tuple result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    return result;
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs) {
    Tuple result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return result;
}

Tuple operator-(const Tuple& rhs) {
    Tuple result(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
    return result;
}

Tuple operator*(const float& scalar, const Tuple& rhs) {
    Tuple result(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z,
                 scalar * rhs.w);
    return result;
}

Tuple operator*(const Tuple& lhs, const float& scalar) {
    Tuple result(scalar * lhs.x, scalar * lhs.y, scalar * lhs.z,
                 scalar * lhs.w);
    return result;
}

Tuple operator/(const Tuple& lhs, const float& scalar) {
    Tuple result(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar,
                 lhs.w / scalar);
    return result;
}

Point operator+(const Point& lhs, const Vector& rhs) {
    Point result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    return result;
}

Point operator+(const Vector& lhs, const Point& rhs) {
    Point result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    return result;
}

Point operator-(const Point& lhs, const Vector& rhs) {
    Point result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return result;
}

Point operator-(const Point& rhs) {
    Point result(-rhs.x, -rhs.y, -rhs.z);
    return result;
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    return result;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
    Vector result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return result;
}

Vector operator-(const Point& lhs, const Point& rhs) {
    Vector result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return result;
}

Vector operator-(const Vector& rhs) {
    Vector result(-rhs.x, -rhs.y, -rhs.z);
    return result;
}

Vector operator*(const Vector& lhs, const float& rhs) {
    Vector result(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    return result;
}

Vector operator*(const float& lhs, const Vector& rhs) {
    Vector result(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
    return result;
}

Vector operator/(const Vector& lhs, const float& rhs) {
    Vector result(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    return result;
}

Vector operator^(const Vector& lhs, const Vector& rhs) {
    Vector result(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                  lhs.x * rhs.y - lhs.y * rhs.x);
    return result;
}

float operator*(const Vector& lhs, const Vector& rhs) {
    float result(rhs.x * lhs.x + rhs.y * lhs.y + rhs.z * lhs.z);
    return result;
}

}  // namespace RTC