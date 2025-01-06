#pragma once

#include "object.h"
#include "tuple.h"

namespace RTC {

class Sphere : public Object {
public:
    Sphere(const Point& cent, float rad);

    Point center;
    float radius;
};

}  // namespace RTC