#pragma once

#include <vector>

#include "intersection.h"
#include "intersections.h"
#include "sphere.h"
#include "tuple.h"

namespace std {
template <>
struct hash<RTC::ID> {
    size_t operator()(const RTC::ID& a) const { return a.getId(); }
};
}  // namespace std

namespace RTC {

class Sphere;

class Intersection;

class Ray {
public:
    Ray(Point start, Vector orientation);

    Point position(float t) const;

    Point origin;
    Vector direction;
};

Intersections intersect(std::shared_ptr<Sphere> s, const Ray& r);

std::shared_ptr<Intersection> hit(const Intersections& i);

}  // namespace RTC