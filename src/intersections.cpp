#include <algorithm>

#include "intersections.h"

namespace RTC {

Intersections::Intersections() {
    intersectionsVector_S = std::make_shared<std::vector<Intersection>>();
}

Intersections::Intersections(std::shared_ptr<std::vector<Intersection>> vec_S) {
    intersectionsVector_S = std::move(vec_S);
    std::sort(intersectionsVector_S->begin(), intersectionsVector_S->end());
}

Intersections::Intersections(const std::vector<Intersection>& vec) {
    intersectionsVector_S = std::make_shared<std::vector<Intersection>>(vec);
    std::sort(intersectionsVector_S->begin(), intersectionsVector_S->end());
}

void Intersections::append(const Intersection& i) const {
    intersectionsVector_S->push_back(i);
}

bool Intersections::empty() const { return intersectionsVector_S->empty(); }

size_t Intersections::size() const { return intersectionsVector_S->size(); }
Intersection Intersections::operator[](size_t index) const {
    if (index < 0 || index >= intersectionsVector_S->size()) {
        printf("bad intersections index []\n");
        exit(1);
    }
    return intersectionsVector_S->at(index);
}
}  // namespace RTC