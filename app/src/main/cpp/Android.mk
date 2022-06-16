LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=STATIC
# Download OpenCV SDK: https://opencv.org/releases/
include $(LOCAL_PATH)/opencv/jni/OpenCV.mk

# include $(CLEAR_VARS)
LOCAL_MODULE := cv4a

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/utils \
    $(LOCAL_PATH)/opencv/jni/include \
    $(LOCAL_PATH)/libyuv/include \

LOCAL_SRC_FILES := \
	$(wildcard $(LOCAL_PATH)/utils/*.cpp) \
	$(wildcard $(LOCAL_PATH)/api/*.cpp) \
	$(wildcard $(LOCAL_PATH)/libyuv/source/*.cc) \

LOCAL_CFLAGS += -Wall -ffunction-sections -fdata-sections
LOCAL_CXXFLAGS += -Wall -std=c++11 -frtti -fexceptions -ffunction-sections -fdata-sections
LOCAL_LDFLAGS += -Wl,--gc-sections

LOCAL_LDLIBS := -llog -lz -landroid -ljnigraphics -lm

LOCAL_CXXFLAGS += -DLIBYUV_NEON
LOCAL_ARM_NEON  := true

include $(BUILD_SHARED_LIBRARY)