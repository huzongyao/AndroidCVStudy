//
// Created by huzongyao on 2021/2/22.
//

#ifndef LEARNOPENCV4A_OPENCVAPI_HPP
#define LEARNOPENCV4A_OPENCVAPI_HPP

#include <jni.h>
#include <android/bitmap.h>

// com.hzy.open.learncv4a.ndk
//Java_com_hzy_open_learncv4a_ndk_OpenCVApi_getVersionString
#define JNI_FUNC(x) Java_com_hzy_opencv_study_ndk_OpenCVApi_##x

#ifdef __cplusplus
extern "C" {
#endif

#include "logger.hpp"

JNIEXPORT jint JNICALL
JNI_FUNC(simpleProcess)(JNIEnv *env, jclass clazz, jobject bmp, jstring options);

JNIEXPORT jstring JNICALL
JNI_FUNC(getVersionString)(JNIEnv *env, jclass type);

JNIEXPORT jint JNICALL
JNI_FUNC(writeYUV420Bitmap)(JNIEnv *env, jclass clazz,
                            jobject y_data, jint y_stride,
                            jobject uv_data, jint uv_stride,
                            jobject bmp);


JNIEXPORT jint JNICALL
JNI_FUNC(cameraYUVToBitmap)(JNIEnv *env, jclass clazz, jobject y_data, jint y_stride,
                            jobject uv_data, jint uv_stride, jobject temp_bmp, jobject out_bmp,
                            jint rotation, jboolean is_mirror);

JNIEXPORT jint JNICALL
JNI_FUNC(bitmapRotate)(JNIEnv *env, jclass clazz, jobject src,
                       jobject dst, jint rotation);

JNIEXPORT jstring JNICALL
JNI_FUNC(readQRCode)(JNIEnv *env, jclass clazz, jobject bmp);

#ifdef __cplusplus
}
#endif

#endif //LEARNOPENCV4A_OPENCVAPI_HPP