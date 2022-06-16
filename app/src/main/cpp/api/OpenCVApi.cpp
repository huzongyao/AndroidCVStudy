//
// Created by huzongyao on 2021/2/22.
//

#include "OpenCVApi.hpp"
#include "YUVUtils.hpp"
#include "BitmapProcess.hpp"
#include <opencv2/opencv.hpp>
#include <json.hpp>

using namespace cv;
using namespace nlohmann;

jint JNI_FUNC(simpleProcess)(JNIEnv *env, jclass clazz, jobject bmp, jstring options_) {
    const char *optionJson = env->GetStringUTFChars(options_, nullptr);
    AndroidBitmapInfo info;
    void *pixels;
    AndroidBitmap_getInfo(env, bmp, &info);
    AndroidBitmap_lockPixels(env, bmp, &pixels);
    auto res = processBmp(pixels, info, optionJson);
    AndroidBitmap_unlockPixels(env, bmp);
    env->ReleaseStringUTFChars(options_, optionJson);
    return res;
}

jstring JNI_FUNC(getVersionString)(JNIEnv *env, jclass type) {
    LOGD("getVersionString() --> %s", CV_VERSION);
    return env->NewStringUTF(CV_VERSION);
}

jint JNI_FUNC(writeYUV420Bitmap)(JNIEnv *env, jclass clazz,
                                 jobject y_data, jint y_stride,
                                 jobject uv_data, jint uv_stride,
                                 jobject bmp) {
    auto *y_buf = (uint8_t *) env->GetDirectBufferAddress(y_data);
    auto *uv_buf = (uint8_t *) env->GetDirectBufferAddress(uv_data);
    AndroidBitmapInfo info;
    uint8_t *bmpData;
    AndroidBitmap_getInfo(env, bmp, &info);
    AndroidBitmap_lockPixels(env, bmp, (void **) (&bmpData));
    auto res = YUV420ToARGB(y_buf, y_stride, uv_buf, uv_stride,
                            bmpData, info.stride, info.width, info.height);
    AndroidBitmap_unlockPixels(env, bmp);
    return res;
}


jint JNI_FUNC(cameraYUVToBitmap)(JNIEnv *env, jclass clazz, jobject y_data, jint y_stride,
                                 jobject uv_data, jint uv_stride, jobject temp_bmp,
                                 jobject out_bmp, jint rotation, jboolean is_mirror) {
    auto *y_buf = (uint8_t *) env->GetDirectBufferAddress(y_data);
    auto *uv_buf = (uint8_t *) env->GetDirectBufferAddress(uv_data);
    AndroidBitmapInfo tempInfo, outInfo;
    uint8_t *tempData, *outData;
    AndroidBitmap_getInfo(env, temp_bmp, &tempInfo);
    AndroidBitmap_lockPixels(env, temp_bmp, (void **) (&tempData));
    auto res = libyuv::NV12ToARGB(y_buf, y_stride, uv_buf, uv_stride, tempData,
                                  tempInfo.stride, tempInfo.width, tempInfo.height);
    if (res == 0) {
        AndroidBitmap_getInfo(env, out_bmp, &outInfo);
        AndroidBitmap_lockPixels(env, out_bmp, (void **) (&outData));
        res = libyuv::ARGBRotate(tempData, tempInfo.stride, outData, outInfo.stride,
                                 tempInfo.width, tempInfo.height, RotationMode(rotation));
        if (res == 0 && is_mirror) {
            memcpy(tempData, outData, outInfo.width * outInfo.height * 4);
            res = libyuv::ARGBMirror(tempData, outInfo.stride, outData, outInfo.stride,
                                     outInfo.width, outInfo.height);
        }
        AndroidBitmap_unlockPixels(env, out_bmp);
    }
    AndroidBitmap_unlockPixels(env, temp_bmp);
    return res;
}

jint JNI_FUNC(bitmapRotate)(JNIEnv *env, jclass clazz, jobject src,
                            jobject dst, jint rotation) {
    AndroidBitmapInfo srcInfo, dstInfo;
    uint8_t *srcData, *dstData;
    AndroidBitmap_getInfo(env, src, &srcInfo);
    AndroidBitmap_getInfo(env, dst, &dstInfo);
    AndroidBitmap_lockPixels(env, src, (void **) (&srcData));
    AndroidBitmap_lockPixels(env, dst, (void **) (&dstData));
    auto res = RGBABmpRotate(srcData, srcInfo.stride, dstData, dstInfo.stride,
                             srcInfo.width, srcInfo.height, rotation);
    AndroidBitmap_unlockPixels(env, dst);
    AndroidBitmap_unlockPixels(env, src);
    return res;
}

jstring JNI_FUNC(readQRCode)(JNIEnv *env, jclass clazz, jobject bmp) {
    AndroidBitmapInfo info;
    void *pixels;
    AndroidBitmap_getInfo(env, bmp, &info);
    AndroidBitmap_lockPixels(env, bmp, &pixels);
    Mat image(info.height, info.width, CV_8UC4, pixels);
    Mat points, straight;
    QRCodeDetector detector;
    std::string res = detector.detectAndDecode(image, points, straight);
    AndroidBitmap_unlockPixels(env, bmp);
    if (res.length() > 0) {
        return env->NewStringUTF(res.c_str());
    }
    return env->NewStringUTF("");
}