#pragma once

#include "id.h"

namespace RTC {

class Object {
public:
    bool operator==(const Object& rhs) const;
    ID objectId;
};

}  // namespace RTC