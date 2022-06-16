//
// Created by huzongyao on 2021/2/26.
//

#include "YUVUtils.hpp"

int YUV420ToARGB(const uint8_t *src_y,
                 int src_stride_y,
                 const uint8_t *src_uv,
                 int src_stride_uv,
                 uint8_t *dst_argb,
                 int dst_stride_argb,
                 int width,
                 int height) {
    return libyuv::NV12ToARGB(src_y, src_stride_y, src_uv, src_stride_uv,
                              dst_argb, dst_stride_argb, width, height);
}

int RGBABmpRotate(const uint8_t *src_argb,
                  int src_stride_argb,
                  uint8_t *dst_argb,
                  int dst_stride_argb,
                  int src_width,
                  int src_height,
                  int degree) {
    auto mode = RotationMode(degree);
    return libyuv::ARGBRotate(src_argb, src_stride_argb, dst_argb, dst_stride_argb,
                              src_width, src_height, mode);
}
