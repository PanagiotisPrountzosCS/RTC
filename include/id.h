#pragma once

#include "stdint.h"

namespace RTC {

class ID {
public:
    ID();
    uint64_t getId() const;
    uint64_t existingIds() const;

    bool operator==(const ID& rhs) const;

private:
    uint64_t id;
    static uint64_t currentId;
};

}  // namespace RTC