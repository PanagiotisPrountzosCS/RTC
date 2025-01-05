#include "ray.h"
#include "tuple.h"

namespace RTC {

Ray::Ray(Point start, Vector orientation) {
    origin = start;
    direction = orientation;
}

Point Ray::position(float t) const { return origin + direction * t; }
}  // namespace RTC