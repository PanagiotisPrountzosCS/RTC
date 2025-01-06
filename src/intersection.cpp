#include <memory>

#include "intersection.h"

namespace RTC {

Intersection::Intersection(float iTime,
                           std::shared_ptr<Object> intersectedObject_Sptr) {
    intersectedObject_S = intersectedObject_Sptr;
    intersectionTime = iTime;
}

bool Intersection::operator<(const Intersection& rhs) const {
    return intersectionTime < rhs.intersectionTime;
}

bool Intersection::operator<(const float rhs) const {
    return intersectionTime < rhs;
}

bool Intersection::operator==(const Intersection& rhs) const {
    return (intersectionTime == rhs.intersectionTime &&
            intersectedObject_S == rhs.intersectedObject_S);
}

}  // namespace RTC