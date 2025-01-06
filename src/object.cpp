#include "object.h"

namespace RTC {

bool Object::operator==(const Object& rhs) const {
    return objectId.getId() == rhs.objectId.getId();
}

}  // namespace RTC