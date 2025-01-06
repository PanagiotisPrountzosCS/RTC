#include <algorithm>
#include <cmath>

#include "intersection.h"
#include "ray.h"
#include "sphere.h"
#include "tuple.h"

namespace RTC {

Ray::Ray(Point start, Vector orientation) {
    origin = start;
    direction = orientation;
}

Point Ray::position(float t) const { return origin + direction * t; }

Intersections intersect(std::shared_ptr<Sphere> s, const Ray& r) {
    Vector orig = r.origin - Point(0, 0, 0);  // ray's origin as vector
    Vector cent = s->center - Point(0, 0, 0);
    float a = r.direction * r.direction;
    float b = 2 * (r.direction.x * (r.origin.x - s->center.x) +
                   r.direction.y * (r.origin.y - s->center.y) +
                   r.direction.z * (r.origin.z - s->center.z));
    float c = (orig * orig) + (cent * cent) - 2 * (orig * cent) -
              (s->radius * s->radius);

    float d = (b * b - 4 * a * c);
    if (d < 0) return {};

    Intersections result{};

    d = sqrt(d);
    float t0 = (-b - d) / (2 * a);
    float t1 = (-b + d) / (2 * a);
    result.append(Intersection(t0, s));
    result.append(Intersection(t1, s));

    return result;
}

std::shared_ptr<Intersection> hit(const Intersections& i) {
    if (i.empty()) {
        return nullptr;
    }
    auto result = std::lower_bound(i.intersectionsVector_S->begin(),
                                   i.intersectionsVector_S->end(), 0.0f);
    if (result != i.intersectionsVector_S->end()) {
        //????
        return std::make_shared<Intersection>(*result);
    }
    return nullptr;
}

}  // namespace RTC