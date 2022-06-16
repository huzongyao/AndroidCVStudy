package com.hzy.opencv.study.activity;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hzy.opencv.study.databinding.ActivitySplashBinding;
import com.hzy.opencv.study.ndk.OpenCVApi;

@SuppressLint("CustomSplashScreen")
public class SplashActivity extends AppCompatActivity {

    private ActivitySplashBinding mB;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mB = ActivitySplashBinding.inflate(getLayoutInflater());
        setContentView(mB.getRoot());
        mB.textVersion.setText("OpenCV " + OpenCVApi.getVersionString());
    }
}