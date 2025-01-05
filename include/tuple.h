#pragma once

#include <iostream>

namespace RTC {

class Tuple {
public:
    Tuple();

    Tuple(float a, float b, float c, float d);

    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator-() const;
    Tuple operator*(const float& scalar) const;
    Tuple operator/(const float& scalar) const;
    float operator*(const Tuple& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Tuple& rhs);

    bool operator==(const Tuple& rhs) const;

    float magnitude();

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
    Point operator+(const Vector& rhs) const;
};

class Vector : public Tuple {
public:
    Vector(float a, float b, float c);
    Vector();
    Vector operator^(const Tuple& rhs) const;
    Point operator+(const Point& rhs) const;
    Vector operator*(const float& rhs) const;
};

}  // namespace RTC