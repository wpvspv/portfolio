package com.example.mh.sole_beer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.widget.Toast;

public class Liquor_Store_Cacktail extends Activity {
    String Liquor_kind;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.liquorstore_cacktail);
        Intent intent = getIntent();
        Liquor_kind = intent.getStringExtra("Liquor_kind");
        Toast.makeText(this, Liquor_kind, Toast.LENGTH_SHORT).show();
    }
}
