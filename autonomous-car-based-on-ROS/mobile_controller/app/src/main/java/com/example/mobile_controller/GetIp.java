package com.example.mobile_controller;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class GetIp extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.getip);

        final EditText edt_ip = (EditText) findViewById(R.id.edt_ip);
        final Button btn_ip = (Button) findViewById(R.id.btn_ip);
        btn_ip.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                intent.putExtra("ip_num", edt_ip.getText().toString());
                Toast.makeText(GetIp.this, edt_ip.getText().toString(), Toast.LENGTH_SHORT).show();
                startActivity(intent);
            }
        });


    }

}
