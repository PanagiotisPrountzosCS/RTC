#pragma once

#include <memory>

#include "object.h"
#include "tuple.h"

namespace RTC {

class Ray;

class Intersection {
public:
    Intersection(float Time, std::shared_ptr<Object> intersectedObject_S);

    bool operator<(const Intersection& rhs) const;
    bool operator<(const float rhs) const;
    bool operator==(const Intersection& rhs) const;
    
    std::shared_ptr<Object> intersectedObject_S;
    float intersectionTime;
};

}  // namespace RTC