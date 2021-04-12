package com.example.mh.sole_beer;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.widget.TextView;
import android.widget.Toast;
import static android.icu.text.MessagePattern.ArgType.SELECT;

public class Liquor_Store_KoreaBeer extends Activity {
    String Liquor_kind;
    SQLiteDatabase db;
    DBHelper helper;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.liquorstore_koreabeer);
        TextView tx001_0=(TextView) findViewById(R.id.tx001_0);
        TextView tx001_1=(TextView) findViewById(R.id.tx001_1);
        TextView tx001_2=(TextView) findViewById(R.id.tx001_2);
        TextView tx001_3=(TextView) findViewById(R.id.tx001_3);
        Intent intent = getIntent();
        Liquor_kind = intent.getStringExtra("Liquor_kind");
        Toast.makeText(this, Liquor_kind, Toast.LENGTH_SHORT).show();

        helper = new DBHelper(this);
        try {
            db = helper.getWritableDatabase(); //데이터베이스 객체를 얻음
        } catch (SQLiteException ex) {
            db = helper.getReadableDatabase();
        }

        Cursor cursor = db.rawQuery("SELECT * FROM contacts WHERE kind='와인'",null);
        cursor.moveToFirst();
        tx001_0.setText(cursor.getString(2));
        tx001_1.setText(cursor.getString(3));
        tx001_2.setText(cursor.getString(4));
        tx001_3.setText(cursor.getString(5));
        cursor.moveToNext();


    }
}
