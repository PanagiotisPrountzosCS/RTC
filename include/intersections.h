#include <memory>
#include <vector>

#include "intersection.h"

namespace RTC {

class Intersections {
public:
    Intersections();
    Intersections(std::shared_ptr<std::vector<Intersection>> vec_S);
    Intersections(const std::vector<Intersection>& vec);

    void append(const Intersection& i) const;
    bool empty() const;
    size_t size() const;
    Intersection operator[](size_t index) const;

    std::shared_ptr<std::vector<Intersection>> intersectionsVector_S;
};

}  // namespace RTC