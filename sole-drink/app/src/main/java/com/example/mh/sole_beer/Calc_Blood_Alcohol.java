package com.example.mh.sole_beer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

/**
 * Created by bicus on 2019-05-13.
 */

public class Calc_Blood_Alcohol extends Activity {
    Button btnReturn;
    boolean Sex;
    float blood_sex, blood_volume, blood_concentration, blood_weight, blood_time;
    float Now_Blood_Concentration;
    TextView FinalConcentration;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.blood_alcohol);
        Log.e("여기까지옴", "확인");
        btnReturn = (Button) findViewById(R.id.ID_bloodreturn);
        FinalConcentration = (TextView) findViewById(R.id.ID_blood_FinalConcentration);
        Intent intent = getIntent();
        Sex = intent.getBooleanExtra("Sex", true);
        if(Sex == true)
        {
            blood_sex = 0.86f;
        }
        else{
            blood_sex = 0.64f;
        }
        blood_weight = intent.getFloatExtra("Weight",0);
        blood_volume = intent.getFloatExtra("Volume",0);
        blood_concentration = intent.getFloatExtra("Concentration", 0);
        blood_time = intent.getFloatExtra("Time", 0);

        Now_Blood_Concentration = (((blood_volume * (blood_concentration / 100) * 0.7894f) * 0.7f) /
                (blood_weight * blood_sex * 10f))                   - ((blood_time - 1.5f) * 0.015f) ;

        FinalConcentration.setText(("현재 혈중 알콜 농도 : ") + Now_Blood_Concentration + "%");
        btnReturn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

    }


}
