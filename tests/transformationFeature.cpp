#include <gtest/gtest.h>

#include <cmath>

#include "algorithms.h"
#include "canvas.h"
#include "color.h"
#include "globaldefinitions.h"
#include "matrix.h"

namespace RTCTests {

TEST(transformationFeature, translationTimesPoint) {
    auto translationMatrix = RTC::translation(5, -3, 2);
    RTC::Point p(-3, 4, 5);
    auto result = translationMatrix * p;
    RTC::Point expectedResult(2, 1, 7);

    ASSERT_EQ(result, expectedResult);

    auto inverseTranslation = translationMatrix.inverse();

    ASSERT_EQ(p, inverseTranslation * result);
}

TEST(transformationFeature, translateVector) {
    auto translationMatrix = RTC::translation(5, -3, 2);
    RTC::Vector v(-3, 4, 5);
    auto result = translationMatrix * v;
    RTC::Vector expectedResult(-3, 4, 5);

    ASSERT_EQ(result, expectedResult);
}

TEST(transformationFeature, scalePoint) {
    auto scalingMatrix = RTC::scaling(2, 3, 4);
    RTC::Point p(-4, 6, 8);
    auto result = scalingMatrix * p;
    RTC::Point expectedResult(-8, 18, 32);

    ASSERT_EQ(result, expectedResult);
}

TEST(transformationFeature, scaleVector) {
    auto scalingMatrix = RTC::scaling(2, 3, 4);
    RTC::Vector v(-4, 6, 8);
    auto result = scalingMatrix * v;
    RTC::Vector expectedResult(-8, 18, 32);

    ASSERT_EQ(result, expectedResult);
}

TEST(transformationFeature, inverseScalingTimesVector) {
    auto scalingMatrix = RTC::scaling(2, 3, 4).inverse();
    RTC::Vector v(-4, 6, 8);
    auto result = scalingMatrix * v;
    RTC::Vector expectedResult(-2, 2, 2);

    ASSERT_EQ(result, expectedResult);
}

TEST(transformationFeature, reflectPoint) {
    auto scalingMatrix = RTC::scaling(-1, 1, 1);
    RTC::Point p(2, 3, 4);
    auto result = scalingMatrix * p;
    RTC::Point expectedResult(-2, 3, 4);

    ASSERT_EQ(result, expectedResult);
}

TEST(transformationFeature, rotateX) {
    auto halfQuarter = RTC::rotateX(PI / 4);
    auto fullQuarter = RTC::rotateX(PI / 2);
    RTC::Point p(0, 1, 0);

    RTC::Point halfQuartP(0, sqrt(2) / 2, sqrt(2) / 2);
    RTC::Point fullQuartP(0, 0, 1);

    ASSERT_EQ(halfQuartP, halfQuarter * p);
    ASSERT_EQ(fullQuartP, fullQuarter * p);

    RTC::Point inverseQuartP(0, sqrt(2) / 2, -sqrt(2) / 2);

    ASSERT_EQ(halfQuarter.inverse() * p, inverseQuartP);
}

TEST(transformationFeature, rotateY) {
    auto halfQuarter = RTC::rotateY(PI / 4);
    auto fullQuarter = RTC::rotateY(PI / 2);
    RTC::Point p(0, 0, 1);

    RTC::Point halfQuartP(sqrt(2) / 2, 0, sqrt(2) / 2);
    RTC::Point fullQuartP(1, 0, 0);

    ASSERT_EQ(halfQuartP, halfQuarter * p);
    ASSERT_EQ(fullQuartP, fullQuarter * p);
}

TEST(transformationFeature, rotateZ) {
    auto halfQuarter = RTC::rotateZ(PI / 4);
    auto fullQuarter = RTC::rotateZ(PI / 2);
    RTC::Point p(0, 1, 0);

    RTC::Point halfQuartP(-sqrt(2) / 2, sqrt(2) / 2, 0);
    RTC::Point fullQuartP(-1, 0, 0);

    ASSERT_EQ(halfQuartP, halfQuarter * p);
    ASSERT_EQ(fullQuartP, fullQuarter * p);
}

TEST(transformationFeature, shear) {
    auto transform = RTC::shearing(1, 0, 0, 0, 0, 0);
    RTC::Point p(2, 3, 4);
    RTC::Point expectedResult(5, 3, 4);

    ASSERT_EQ(transform * p, expectedResult);
}

TEST(transformationFeature, moreShear) {
    auto transform1 = RTC::shearing(0, 1, 0, 0, 0, 0);
    RTC::Point p(2, 3, 4);
    RTC::Point expectedResult(6, 3, 4);

    ASSERT_EQ(transform1 * p, expectedResult);

    auto transform2 = RTC::shearing(0, 0, 1, 0, 0, 0);
    expectedResult = RTC::Point(2, 5, 4);

    ASSERT_EQ(transform2 * p, expectedResult);

    auto transform3 = RTC::shearing(0, 0, 0, 1, 0, 0);
    expectedResult = RTC::Point(2, 7, 4);

    ASSERT_EQ(transform3 * p, expectedResult);

    auto transform4 = RTC::shearing(0, 0, 0, 0, 1, 0);
    expectedResult = RTC::Point(2, 3, 6);

    ASSERT_EQ(transform4 * p, expectedResult);

    auto transform5 = RTC::shearing(0, 0, 0, 0, 0, 1);
    expectedResult = RTC::Point(2, 3, 7);

    ASSERT_EQ(transform5 * p, expectedResult);
}

TEST(transformationFeature, chain) {
    RTC::Point p(1, 0, 1);
    auto A = RTC::rotateX(PI / 2);
    auto B = RTC::scaling(5, 5, 5);
    auto C = RTC::translation(10, 5, 7);

    auto p2 = A * p;
    RTC::Point expectedp2(1, -1, 0);
    ASSERT_TRUE(p2 == expectedp2);

    auto p3 = B * p2;
    RTC::Point expectedp3(5, -5, 0);
    ASSERT_TRUE(p3 == expectedp3);

    auto p4 = C * p3;
    RTC::Point expectedp4(15, 0, 7);
    ASSERT_TRUE(p4 == expectedp4);
}

TEST(transformationFeature, clockPoints) {
    auto width = 100;
    auto height = 100;
    RTC::Color white(1, 1, 1);
    RTC::Color black(0, 0, 0);
    RTC::Tuple start(0, 1, 0, 1);
    RTC::Canvas finalCanvas(width, height);
    auto rotationStep = RTC::rotateZ(-PI / 6);

    for (uint64_t i = 0; i < width; i++) {
        for (uint64_t j = 0; j < height; j++) {
            finalCanvas.writePixel(i, height - 1 - j, black);
        }
    }

    for (int i = 0; i < 12; i++) {
        auto x = RTC::realToIndex(-2, 2, start.x, width);
        auto y = RTC::realToIndex(-2, 2, start.y, height);
        finalCanvas.writePixel(x, y, white);
        start = rotationStep * start;
    }

    ASSERT_TRUE(finalCanvas.toPPM("clock.ppm"));
}

}  // namespace RTCTests