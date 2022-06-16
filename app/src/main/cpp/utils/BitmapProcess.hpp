//
// Created by huzongyao on 2021/3/2.
//

#ifndef LEARNOPENCV4A_BITMAPPROCESS_HPP
#define LEARNOPENCV4A_BITMAPPROCESS_HPP

#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
#include <json.hpp>

using namespace nlohmann;
using namespace cv;

int processBmp(void *pixels, AndroidBitmapInfo &info, const char *options);

#endif //LEARNOPENCV4A_BITMAPPROCESS_HPP
