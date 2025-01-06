#pragma once

#include <iostream>

namespace RTC {

class Tuple {
public:
    Tuple();

    Tuple(float a, float b, float c, float d);

    friend std::ostream& operator<<(std::ostream& os, const Tuple& rhs);

    bool operator==(const Tuple& rhs) const;

    float magnitude() const;

    void normalize();

    float x;
    float y;
    float z;
    float w;
    // w == 1 when Tuple represents a point;
    // 0 when it represents a vector;
};

class Point : public Tuple {
public:
    Point(float a, float b, float c);
    Point();
};

class Vector : public Tuple {
public:
    Vector(float a, float b, float c);
    Vector();
};

Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& rhs);
Tuple operator*(const float& scalar, const Tuple& rhs);
Tuple operator*(const Tuple& lhs, const float& scalar);
Tuple operator/(const Tuple& lhs, const float& scalar);

Point operator+(const Point& lhs, const Vector& rhs);
Point operator+(const Vector& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Vector& rhs);
Point operator-(const Point& rhs);

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator-(const Point& lhs, const Point& rhs);
Vector operator-(const Vector& rhs);
Vector operator*(const Vector& lhs, const float& rhs);
Vector operator*(const float& lhs, const Vector& rhs);
Vector operator/(const Vector& lhs, const float& rhs);
Vector operator^(const Vector& lhs, const Vector& rhs);

float operator*(const Vector& lhs, const Vector& rhs);
}  // namespace RTC