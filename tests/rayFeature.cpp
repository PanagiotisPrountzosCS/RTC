#include <gtest/gtest.h>

#include <cmath>

#include "ray.h"

namespace RTCTests {

TEST(rayFeature, constructor) {
    RTC::Point origin(1, 2, 3);
    RTC::Vector direction(4, 5, 6);

    RTC::Ray ray(origin, direction);

    ASSERT_EQ(origin, ray.origin);
    ASSERT_EQ(direction, ray.direction);
}

TEST(rayFeature, position) {
    RTC::Ray ray(RTC::Point(2, 3, 4), RTC::Vector(1, 0, 0));
    RTC::Point expectedResult(2, 3, 4);

    ASSERT_EQ(ray.position(0), expectedResult);

    expectedResult = RTC::Point(3, 3, 4);

    ASSERT_EQ(ray.position(1), expectedResult);

    expectedResult = RTC::Point(1, 3, 4);

    ASSERT_EQ(ray.position(-1), expectedResult);

    expectedResult = RTC::Point(4.5, 3, 4);

    ASSERT_EQ(ray.position(2.5), expectedResult);
}

}  // namespace RTCTests