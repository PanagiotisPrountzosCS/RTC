#pragma once
#include "tuple.h"

namespace RTC {

class Ray {
public:
    Ray(Point start, Vector orientation);

    Point position(float t) const;

    Point origin;
    Vector direction;
};

}  // namespace RTC