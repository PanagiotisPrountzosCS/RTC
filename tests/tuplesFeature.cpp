#include <gtest/gtest.h>

#include <cmath>

#include "tuple.h"

namespace RTCTests {

TEST(tuplesFeature, constructor) {
    RTC::Tuple a{4.3, -4.2, 3.1, 1};

    ASSERT_FLOAT_EQ(a.x, 4.3);
    ASSERT_FLOAT_EQ(a.y, -4.2);
    ASSERT_FLOAT_EQ(a.z, 3.1);
    ASSERT_FLOAT_EQ(a.w, 1);

    RTC::Tuple b{4.3, -4.2, 3.1, 0};

    ASSERT_FLOAT_EQ(b.x, 4.3);
    ASSERT_FLOAT_EQ(b.y, -4.2);
    ASSERT_FLOAT_EQ(b.z, 3.1);
    ASSERT_FLOAT_EQ(b.w, 0);
}

TEST(tuplesFeature, vector) {
    RTC::Vector a(4, -4, 3);

    ASSERT_FLOAT_EQ(a.x, 4);
    ASSERT_FLOAT_EQ(a.y, -4);
    ASSERT_FLOAT_EQ(a.z, 3);
    ASSERT_FLOAT_EQ(a.w, 0);
}

TEST(tuplesFeature, point) {
    RTC::Point a(4, -4, 3);

    ASSERT_FLOAT_EQ(a.x, 4);
    ASSERT_FLOAT_EQ(a.y, -4);
    ASSERT_FLOAT_EQ(a.z, 3);
    ASSERT_FLOAT_EQ(a.w, 1);
}

TEST(tuplesFeature, addTuples) {
    RTC::Tuple a(3, -2, 5, 1);
    RTC::Tuple b(-2, 3, 1, 0);
    auto c = a + b;

    RTC::Tuple expected(1, 1, 6, 1);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, pointMinusPoint) {
    RTC::Point a(3, 2, 1);
    RTC::Point b(5, 6, 7);
    auto c = a - b;

    RTC::Tuple expected(-2, -4, -6, 0);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, pointMinusVector) {
    RTC::Point a(3, 2, 1);
    RTC::Vector b(5, 6, 7);
    auto c = a - b;

    RTC::Tuple expected(-2, -4, -6, 1);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, vectorMinusVector) {
    RTC::Vector a(3, 2, 1);
    RTC::Vector b(5, 6, 7);
    auto c = a - b;

    RTC::Tuple expected(-2, -4, -6, 0);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, negateVector) {
    RTC::Vector zero;
    RTC::Vector v(1, -2, 3);
    auto c = zero - v;

    RTC::Tuple expected(-1, 2, -3, 0);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, negateTuple) {
    RTC::Tuple a(1, -2, 3, -4);
    auto c = -a;

    RTC::Tuple expected(-1, 2, -3, 4);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, multiplyByScalar) {
    RTC::Tuple a(1, -2, 3, -4);
    auto c = a * 3.5;

    RTC::Tuple expected(3.5, -7, 10.5, -14);
    ASSERT_EQ(c, expected);

    c = a * 0.5;

    expected = RTC::Tuple (0.5, -1, 1.5, -2);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, divideByScalar) {
    RTC::Tuple a(1, -2, 3, -4);
    auto c = a / 2;

    RTC::Tuple expected(0.5, -1, 1.5, -2);
    ASSERT_EQ(c, expected);
}

TEST(tuplesFeature, magnitude) {
    RTC::Vector v(1, 0, 0);

    ASSERT_FLOAT_EQ(v.magnitude(), 1);

    v = RTC::Vector(0, 1, 0);

    ASSERT_FLOAT_EQ(v.magnitude(), 1);

    v = RTC::Vector(0, 0, 1);

    ASSERT_FLOAT_EQ(v.magnitude(), 1);

    v = RTC::Vector(1, 2, 3);

    ASSERT_FLOAT_EQ(v.magnitude(), sqrt(14));

    v = RTC::Vector(-1, -2, -3);

    ASSERT_FLOAT_EQ(v.magnitude(), sqrt(14));
}

TEST(tuplesFeature, normalize) {
    RTC::Vector v(4, 0, 0);
    v.normalize();

    ASSERT_FLOAT_EQ(v.x, 1);
    ASSERT_FLOAT_EQ(v.y, 0);
    ASSERT_FLOAT_EQ(v.z, 0);

    v = RTC::Vector(1, 2, 3);
    v.normalize();

    ASSERT_FLOAT_EQ(v.x, 0.26726124);
    ASSERT_FLOAT_EQ(v.y, 0.53452247);
    ASSERT_FLOAT_EQ(v.z, 0.80178368);

    ASSERT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(tuplesFeature, dotProduct) {
    RTC::Vector a(1, 2, 3);
    RTC::Vector b(2, 3, 4);
    auto c = a * b;

    ASSERT_FLOAT_EQ(c, 20);
}

TEST(tuplesFeature, crossProduct) {
    RTC::Vector a(1, 2, 3);
    RTC::Vector b(2, 3, 4);
    auto c = a ^ b;

    ASSERT_FLOAT_EQ(c.x, -1);
    ASSERT_FLOAT_EQ(c.y, 2);
    ASSERT_FLOAT_EQ(c.z, -1);

    c = b ^ a;

    ASSERT_FLOAT_EQ(c.x, 1);
    ASSERT_FLOAT_EQ(c.y, -2);
    ASSERT_FLOAT_EQ(c.z, 1);
}

}  // namespace RTCTests