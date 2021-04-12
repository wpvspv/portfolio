package com.example.mh.sole_beer;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class Fragment_Blood extends Fragment {

    // 혈중알코올 사용 코드
    RadioGroup Blood_RadioGroup;
    RadioButton Blood_Man;
    RadioButton Blood_Woman;
    Boolean Blood_Sex = true;
    EditText Blood_Weight;
    EditText Blood_Volume;
    EditText Blood_Con;
    EditText Blood_Time;
    String string;
    Button btnBlood;
    float blood_volume, blood_concentration, blood_weight, blood_time;


    @Override
    public View onCreateView(LayoutInflater inflater,ViewGroup container,
                             Bundle savedInstanceState)
    {
        View view = inflater.inflate(R.layout.estimate_blood_layout, container, false);

        // 혈중알코올 사용 코드
        Blood_RadioGroup = (RadioGroup) view.findViewById(R.id.ID_blood_radiogroup);
        Blood_Man = (RadioButton) view.findViewById(R.id.ID_blood_man);
        Blood_Woman = (RadioButton) view.findViewById(R.id.ID_blood_woman);
        Blood_Weight = (EditText) view.findViewById(R.id.ID_blood_weight);
        Blood_Volume = (EditText) view.findViewById(R.id.ID_blood_volume);
        Blood_Con = (EditText) view.findViewById(R.id.ID_blood_Concentration);
        Blood_Time = (EditText) view.findViewById(R.id.ID_blood_time);
        btnBlood = (Button) view.findViewById(R.id.ID_blood_check);

        getActivity().setTitle("주량 측정");
        // 혈중알코올 코드.
        btnBlood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                string = Blood_Weight.getText().toString();
                blood_weight =  Integer.parseInt(string);
                string = Blood_Con.getText().toString();
                blood_concentration = Integer.parseInt(string);
                string = Blood_Volume.getText().toString();
                blood_volume = Integer.parseInt(string);
                string = Blood_Time.getText().toString();
                blood_time = Integer.parseInt(string);
                if(Blood_Man.isChecked())
                {
                    Blood_Sex = true;
                }
                else{
                    Blood_Sex = false;
                }
                Intent intent = new Intent(getActivity(),Calc_Blood_Alcohol.class);
                intent.putExtra("Sex", Blood_Sex);
                intent.putExtra("Weight", blood_weight);
                intent.putExtra("Concentration", blood_concentration);
                intent.putExtra("Volume", blood_volume);
                intent.putExtra("Time", blood_time);
                startActivity(intent);
            }
        });
        return view;
    }

}
