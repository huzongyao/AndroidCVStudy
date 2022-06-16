package com.hzy.opencv.study.activity;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hzy.opencv.study.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding mB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mB = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(mB.getRoot());
    }
}