#include <gtest/gtest.h>

#include <cmath>

#include "algorithms.h"
#include "canvas.h"

namespace RTCTests {

TEST(canvasFeature, constructor) {
    RTC::Canvas newCanvas(10, 20);

    ASSERT_EQ(newCanvas.getWidth(), 10);
    ASSERT_EQ(newCanvas.getHeight(), 20);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            ASSERT_EQ(0, newCanvas.pixelArray[i][j].r);
            ASSERT_EQ(0, newCanvas.pixelArray[i][j].g);
            ASSERT_EQ(0, newCanvas.pixelArray[i][j].b);
        }
    }
}

TEST(canvasFeature, writePixel) {
    RTC::Canvas newCanvas(10, 20);
    RTC::Color red(1, 0, 0);

    newCanvas.writePixel(2, 3, red);

    auto actualColor = newCanvas.pixelArray[2][3];

    ASSERT_EQ(actualColor.r, red.r);
    ASSERT_EQ(actualColor.g, red.g);
    ASSERT_EQ(actualColor.b, red.b);
}

TEST(canvasFeature, makePPM) {
    RTC::Canvas newCanvas(10, 2);
    ASSERT_EQ(newCanvas.getWidth(), 10);
    ASSERT_EQ(newCanvas.getHeight(), 2);
    RTC::Color c(1, 0.8, 0.6);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 2; j++) {
            newCanvas.writePixel(i, j, c);
        }
    }

    newCanvas.toPPM("./output.ppm");
}

// TEST(canvasFeature, makeParabolaPPM) {
//     auto width = 2560;
//     auto height = 1440;
//     RTC::Canvas newCanvas(width, height);
//     // x range will be -3, 3
//     // y range will be 0, 9
//     RTC::Color black(0, 0, 0);
//     RTC::Color curveColor(1, 0, 1);

//     for (int i = 0; i < width; i++) {
//         for (int j = 0; j < height; j++) {
//             auto x = RTC::indexToReal(0, 3 * 6.28, i, width);
//             auto y = RTC::indexToReal(-1.1, 1.1, j, height);
//             if (abs(y - sin(x)) < 0.01) {
//                 newCanvas.writePixel(i, height - 1 - j, curveColor);
//             } else {
//                 newCanvas.writePixel(i, height - 1 - j, black);
//             }
//         }
//     }

//     newCanvas.toPPM("sine.ppm");
// }

}  // namespace RTCTests