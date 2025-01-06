#include <gtest/gtest.h>

#include "ray.h"
#include "sphere.h"

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

TEST(sphereFeature, intersectSphere) {
    RTC::Point center(0, 0, 0);

    auto s = std::make_shared<RTC::Sphere>(center, 1);

    ASSERT_EQ(s->objectId.getId(), 0);

    // create a sphere, and a ray, then check if it intersects it;
    RTC::Point origin(0, 0, -5);
    RTC::Vector direction(0, 0, 1);

    RTC::Ray ray(origin, direction);

    auto result = intersect(s, ray);
    ASSERT_TRUE(!result.empty());
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].intersectionTime, 4);
    ASSERT_EQ(result[1].intersectionTime, 6);
    ASSERT_EQ(result[0].intersectedObject_S, s);
    ASSERT_EQ(result[1].intersectedObject_S, s);

    origin = RTC::Point(0, 1, -5);
    ray = RTC::Ray(origin, direction);

    result = intersect(s, ray);
    ASSERT_TRUE(!result.empty());
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].intersectionTime, 5);
    ASSERT_EQ(result[1].intersectionTime, 5);
    ASSERT_EQ(result[0].intersectedObject_S, s);
    ASSERT_EQ(result[1].intersectedObject_S, s);

    origin = RTC::Point(0, 2, -5);
    ray = RTC::Ray(origin, direction);

    result = intersect(s, ray);
    ASSERT_TRUE(result.empty());
}

TEST(sphereFeature, rayInSphere) {
    RTC::Point center(0, 0, 0);

    auto s = std::make_shared<RTC::Sphere>(center, 1);

    RTC::Point origin(0, 0, 0);
    RTC::Vector direction(0, 0, 1);

    RTC::Ray ray(origin, direction);

    auto result = intersect(s, ray);
    ASSERT_TRUE(!result.empty());
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].intersectionTime, -1);
    ASSERT_EQ(result[1].intersectionTime, 1);
    ASSERT_EQ(result[0].intersectedObject_S, s);
    ASSERT_EQ(result[1].intersectedObject_S, s);
}

TEST(sphereFeature, sphereBehindRay) {
    RTC::Point center(0, 0, 0);

    auto s = std::make_shared<RTC::Sphere>(center, 1);

    RTC::Point origin(0, 0, 5);
    RTC::Vector direction(0, 0, 1);

    RTC::Ray ray(origin, direction);

    auto result = intersect(s, ray);
    ASSERT_TRUE(!result.empty());
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].intersectionTime, -6);
    ASSERT_EQ(result[1].intersectionTime, -4);
    ASSERT_EQ(result[0].intersectedObject_S, s);
    ASSERT_EQ(result[1].intersectedObject_S, s);
}

TEST(intersectionFeature, constructor) {
    RTC::Point center(0, 0, 0);
    auto s = std::make_shared<RTC::Sphere>(center, 1);

    RTC::Intersection i(3.5, s);

    ASSERT_EQ(s, i.intersectedObject_S);
    ASSERT_EQ(3.5, i.intersectionTime);
    ASSERT_EQ(i.intersectedObject_S, s);
}

TEST(intersectionFeature, aggregate) {
    RTC::Point center(0, 0, 0);
    auto s = std::make_shared<RTC::Sphere>(center, 1);

    RTC::Intersection i1(1, s);
    RTC::Intersection i2(2, s);

    RTC::Intersections xs({i1, i2});

    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].intersectionTime, 1);
    ASSERT_EQ(xs[1].intersectionTime, 2);
    ASSERT_EQ(xs[0].intersectedObject_S, s);
    ASSERT_EQ(xs[1].intersectedObject_S, s);
}

TEST(intersectionFeature, hit) {
    RTC::Point center(0, 0, 0);
    auto s = std::make_shared<RTC::Sphere>(center, 1);

    RTC::Intersection i1(1, s);
    RTC::Intersection i2(2, s);

    RTC::Intersections xs({i1, i2});

    ASSERT_EQ(i1, *hit(xs));

    i1 = RTC::Intersection (-1, s);
    i2 = RTC::Intersection (1, s);

    xs = RTC::Intersections ({i1, i2});

    ASSERT_EQ(i2, *hit(xs));

    i1 = RTC::Intersection (-2, s);
    i2 = RTC::Intersection (-1, s);

    xs = RTC::Intersections ({i1, i2});

    ASSERT_EQ(nullptr, hit(xs));

    i1 = RTC::Intersection (5, s);
    i2 = RTC::Intersection (7, s);
    RTC::Intersection i3(-3, s);
    RTC::Intersection i4(2, s);

    xs = RTC::Intersections ({i1, i2, i3, i4});

    ASSERT_EQ(i4, *hit(xs));
}

}  // namespace RTCTests