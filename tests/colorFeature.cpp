#include <gtest/gtest.h>

#include "color.h"

namespace RTCTests {

TEST(colorFeature, constructor) {
    // RTC::Color c(-0.5, 0.4, 1.7);

    // ASSERT_FLOAT_EQ(c.r, -0.5);
    // ASSERT_FLOAT_EQ(c.g, 0.4);
    // ASSERT_FLOAT_EQ(c.b, 1.7);
}

TEST(colorFeature, colorPlusColor) {
    RTC::Color a(0.9, 0.6, 0.75);
    RTC::Color b(0.7, 0.1, 0.25);

    auto c = a + b;

    ASSERT_FLOAT_EQ(c.r, 1.6);
    ASSERT_FLOAT_EQ(c.g, 0.7);
    ASSERT_FLOAT_EQ(c.b, 1.0);
}

TEST(colorFeature, colorMinusColor) {
    RTC::Color a(0.9, 0.6, 0.75);
    RTC::Color b(0.7, 0.1, 0.25);

    auto c = a - b;

    ASSERT_FLOAT_EQ(c.r, 0.2);
    ASSERT_FLOAT_EQ(c.g, 0.5);
    ASSERT_FLOAT_EQ(c.b, 0.5);
}

TEST(colorFeature, colorTimesScalar) {
    RTC::Color a(0.2, 0.3, 0.4);

    auto c = a * 2;

    ASSERT_FLOAT_EQ(c.r, 0.4);
    ASSERT_FLOAT_EQ(c.g, 0.6);
    ASSERT_FLOAT_EQ(c.b, 0.8);
}

TEST(colorFeature, colorTimesColor) {
    RTC::Color a(1, 0.2, 0.4);
    RTC::Color b(0.9, 1, 0.1);
    auto c = a * b;

    ASSERT_FLOAT_EQ(c.r, 0.9);
    ASSERT_FLOAT_EQ(c.g, 0.2);
    ASSERT_FLOAT_EQ(c.b, 0.04);
}

}  // namespace RTCTests