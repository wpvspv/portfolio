package com.example.mobile_controller;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class SplashActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        try {
            Thread.sleep(3000); //대기 초 설정
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        //스플래쉬 액티비티가 종료된 후 메인액티비티를 보여주는 부분
        startActivity(new Intent(this, GetIp.class));
        finish();
    }
}
