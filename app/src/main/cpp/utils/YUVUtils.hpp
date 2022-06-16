//
// Created by huzongyao on 2021/2/26.
//

#ifndef LEARNOPENCV4A_YUVUTILS_HPP
#define LEARNOPENCV4A_YUVUTILS_HPP

#include <libyuv.h>

using namespace libyuv;

int YUV420ToARGB(const uint8_t *src_y,
                 int src_stride_y,
                 const uint8_t *src_uv,
                 int src_stride_uv,
                 uint8_t *dst_argb,
                 int dst_stride_argb,
                 int width,
                 int height);

int RGBABmpRotate(const uint8_t *src_argb,
                  int src_stride_argb,
                  uint8_t *dst_argb,
                  int dst_stride_argb,
                  int src_width,
                  int src_height,
                  int degree);

#endif //LEARNOPENCV4A_YUVUTILS_HPP
