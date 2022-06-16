package com.hzy.opencv.study.ndk;

public class OpenCVApi {

    public static native String getVersionString();

    static {
        System.loadLibrary("cv4a");
    }
}
