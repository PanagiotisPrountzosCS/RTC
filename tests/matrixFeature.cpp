#include <gtest/gtest.h>

#include <cmath>

#include "matrix.h"

namespace RTCTests {

TEST(matrixFeature, constructor) {
    std::vector<std::vector<float>> input = {{1, 2, 3, 4},
                                             {5.5, 6.5, 7.5, 8.5},
                                             {9, 10, 11, 12},
                                             {13.5, 14.5, 15.5, 16.5}};

    RTC::Matrix newMatrix(input);

    ASSERT_FLOAT_EQ(newMatrix.data[0][0], 1);
    ASSERT_FLOAT_EQ(newMatrix.data[0][3], 4);
    ASSERT_FLOAT_EQ(newMatrix.data[1][0], 5.5);
    ASSERT_FLOAT_EQ(newMatrix.data[1][2], 7.5);
    ASSERT_FLOAT_EQ(newMatrix.data[2][2], 11);
    ASSERT_FLOAT_EQ(newMatrix.data[3][0], 13.5);
    ASSERT_FLOAT_EQ(newMatrix.data[3][2], 15.5);

    std::vector<std::vector<float>> twobytwo = {{-3, 5}, {1, -2}};

    RTC::Matrix twoDee(twobytwo);

    ASSERT_FLOAT_EQ(twoDee.data[0][0], -3);
    ASSERT_FLOAT_EQ(twoDee.data[0][1], 5);
    ASSERT_FLOAT_EQ(twoDee.data[1][0], 1);
    ASSERT_FLOAT_EQ(twoDee.data[1][1], -2);

    std::vector<std::vector<float>> threeee = {
        {-3, 5, 0}, {1, -2, -7}, {0, 1, 1}};

    RTC::Matrix threeD(threeee);

    ASSERT_FLOAT_EQ(threeD.data[0][0], -3);
    ASSERT_FLOAT_EQ(threeD.data[0][1], 5);
    ASSERT_FLOAT_EQ(threeD.data[0][2], 0);
    ASSERT_FLOAT_EQ(threeD.data[1][0], 1);
    ASSERT_FLOAT_EQ(threeD.data[1][1], -2);
    ASSERT_FLOAT_EQ(threeD.data[1][2], -7);
    ASSERT_FLOAT_EQ(threeD.data[2][0], 0);
    ASSERT_FLOAT_EQ(threeD.data[2][1], 1);
    ASSERT_FLOAT_EQ(threeD.data[2][2], 1);
}

TEST(matrixFeature, equalityOperator) {
    std::vector<std::vector<float>> fourbfour = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};

    RTC::Matrix a{fourbfour};
    RTC::Matrix b{fourbfour};

    ASSERT_EQ(a, b);

    std::vector<std::vector<float>> other = {
        {2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}};

    RTC::Matrix c{other};

    ASSERT_FALSE(a == c);
}

TEST(matrixFeature, multiplicationOperator) {
    std::vector<std::vector<float>> inA = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};

    std::vector<std::vector<float>> inB = {
        {-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};

    RTC::Matrix A(inA);
    RTC::Matrix B(inB);
    auto C = A * B;

    std::vector<std::vector<float>> inExpected = {{20, 22, 50, 48},
                                                  {44, 54, 114, 108},
                                                  {40, 58, 110, 102},
                                                  {16, 26, 46, 42}};

    RTC::Matrix Expected(inExpected);

    ASSERT_EQ(C, Expected);
}

TEST(matrixFeature, matrixTimesTuple) {
    std::vector<std::vector<float>> inA = {
        {1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};

    RTC::Matrix A(inA);

    RTC::Tuple b(1, 2, 3, 1);

    RTC::Tuple expected(18, 24, 33, 1);

    ASSERT_EQ(expected, A * b);
}

TEST(matrixFeature, matrixTimesIdentity) {
    std::vector<std::vector<float>> inA = {
        {0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}};

    RTC::Matrix A(inA);

    RTC::Matrix I(4);

    ASSERT_TRUE(I * A == A);
}

TEST(matrixFeature, transpose) {
    std::vector<std::vector<float>> inA = {
        {0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}};

    RTC::Matrix A(inA);

    std::vector<std::vector<float>> inExpected = {
        {0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}};

    RTC::Matrix expected(inExpected);

    ASSERT_EQ(A.transpose(), expected);

    RTC::Matrix I(4);

    ASSERT_EQ(I.transpose(), I);
}

TEST(matrixFeature, determinant) {
    std::vector<std::vector<float>> inA = {{1, 5}, {-3, 2}};
    RTC::Matrix A(inA);

    ASSERT_EQ(A.determinant(), 17);
}

TEST(matrixFeature, submatrix) {
    std::vector<std::vector<float>> inA = {{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};
    RTC::Matrix A(inA);

    RTC::Matrix expected({{-3, 2}, {0, 6}});

    ASSERT_EQ(A.submatrix(0, 2), expected);

    RTC::Matrix B(
        {{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}});
    auto newExpected = RTC::Matrix({{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}});

    ASSERT_EQ(newExpected, B.submatrix(2, 1));
}

TEST(matrixFeature, minor) {
    RTC::Matrix A({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

    ASSERT_FLOAT_EQ(25, A.minor(1, 0));
}

TEST(matrixFeature, cofactor) {
    RTC::Matrix A({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

    ASSERT_FLOAT_EQ(-25, A.cofactor(1, 0));
    ASSERT_FLOAT_EQ(-12, A.cofactor(0, 0));
}

TEST(matrixFeature, biggerDeterminants) {
    RTC::Matrix A({{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}});

    ASSERT_FLOAT_EQ(56, A.cofactor(0, 0));
    ASSERT_FLOAT_EQ(12, A.cofactor(0, 1));
    ASSERT_FLOAT_EQ(-46, A.cofactor(0, 2));
    ASSERT_FLOAT_EQ(-196, A.determinant());

    RTC::Matrix B(
        {{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}});

    ASSERT_FLOAT_EQ(690, B.cofactor(0, 0));
    ASSERT_FLOAT_EQ(447, B.cofactor(0, 1));
    ASSERT_FLOAT_EQ(210, B.cofactor(0, 2));
    ASSERT_FLOAT_EQ(51, B.cofactor(0, 3));
    ASSERT_FLOAT_EQ(-4071, B.determinant());
}

TEST(matrixFeature, isInvertible) {
    RTC::Matrix A({{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}});

    ASSERT_TRUE(A.isInvertible());

    RTC::Matrix B(
        {{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});

    ASSERT_FALSE(B.isInvertible());
}

TEST(matrixFeature, invert) {
    RTC::Matrix A(
        {{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
    RTC::Matrix expected({{0.218045, 0.451128, 0.240602, -0.045113},
                          {-0.808271, -1.456767, -0.443609, 0.520677},
                          {-0.078947, -0.223684, -0.052632, 0.197368},
                          {-0.522556, -0.81391, -0.300752, 0.306391}});

    ASSERT_FLOAT_EQ(A.determinant(), 532);
    ASSERT_FLOAT_EQ(A.cofactor(2, 3), -160);
    ASSERT_FLOAT_EQ(A.cofactor(3, 2), 105);
    ASSERT_EQ(A.inverse(), expected);
}

TEST(matrixFeature, moreInverse) {
    RTC::Matrix A(
        {{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}});
    RTC::Matrix AInverese({{-0.15385, -0.15385, -0.28205, -0.53846},
                           {-0.07692, 0.12308, 0.02564, 0.03077},
                           {0.35897, 0.35897, 0.43590, 0.92308},
                           {-0.69231, -0.69231, -0.76923, -1.92308}});

    ASSERT_EQ(A.inverse(), AInverese);

    RTC::Matrix B(
        {{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}});
    RTC::Matrix BInverse({{-0.04074, -0.07778, 0.14444, -0.22222},
                          {-0.07778, 0.03333, 0.36667, -0.33333},
                          {-0.02901, -0.14630, -0.10926, 0.12963},
                          {0.17778, 0.06667, -0.26667, 0.33333}});

    ASSERT_EQ(B.inverse(), BInverse);
}

TEST(matrixFeature, AtimesBtimesBInverse) {
    RTC::Matrix A(
        {{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}});

    RTC::Matrix B({{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}});

    auto C = A * B;
    ASSERT_EQ(C * B.inverse(), A);
}

TEST(matrixFeature, matrixTimesScalar) {
    RTC::Matrix A({{1, 1}, {2, 3}});
    ASSERT_EQ(A * 2, RTC::Matrix({{2, 2}, {4, 6}}));
}

}  // namespace RTCTests