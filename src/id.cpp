#include "id.h"

namespace RTC {

uint64_t ID::currentId = 0;

ID::ID() { id = currentId++; }

bool ID::operator==(const ID& rhs) const { return id == rhs.id; }

uint64_t ID::getId() const { return id; }

uint64_t ID::existingIds() const { return currentId; }
}  // namespace RTC