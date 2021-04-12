package com.example.mh.sole_beer;

import android.net.Uri;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class Fragment_Drink extends Fragment {

    MainActivity main;
    String mCurrentPhotoPath;
    String dateString;
    Uri imageUri;
    Uri photoURI, albumURI;
    Uri CaptrueUri;



    // 주량 측정 사용 코드
    ImageView Now_liquor_Image;
    TextView Now_Volume_text;
    TextView Now_Volumezan_text;
    ImageButton Btn_SojuCup,Btn_Initialization,Btn_OneShot;
    int Now_liquor_volume_beer;
    int Now_liquor_volume_soju;
    int Now_liquor_volume;
    String Now_liquor = "Soju";
    ImageButton Btn_Camera;
    ImageButton Btn_album;
    ImageButton Btn_kakaoLink;
    // 임시
    ImageView ID_Camera;
    final FrameLayout container = null;
    final ImageView[] cups = new ImageView[8];
    final ImageView[] bottles = new ImageView[6];

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.estimate_drink_layout, container, false);

        Now_liquor_Image = (ImageView) view.findViewById(R.id.ID_Now_liquor);
        Now_Volume_text = (TextView) view.findViewById(R.id.ID_Check_Now_Volume);
        Now_Volumezan_text = (TextView) view.findViewById(R.id.ID_Check_Now_Volume_Zan);
        Btn_SojuCup = (ImageButton) view.findViewById(R.id.ID_btn_SojuCup);
        Btn_Initialization = (ImageButton) view.findViewById(R.id.ID_Initialization);
        Btn_OneShot = (ImageButton) view.findViewById(R.id.ID_btn_OneShot);
        Btn_Camera = (ImageButton) view.findViewById(R.id.ID_btn_Camera);
        Btn_album = (ImageButton) view.findViewById(R.id.btn_album);
        cups[0] = (ImageView) view.findViewById(R.id.ID_cup1);
        cups[1] = (ImageView) view.findViewById(R.id.ID_cup2);
        cups[2] = (ImageView) view.findViewById(R.id.ID_cup3);
        cups[3] = (ImageView) view.findViewById(R.id.ID_cup4);
        cups[4] = (ImageView) view.findViewById(R.id.ID_cup5);
        cups[5] = (ImageView) view.findViewById(R.id.ID_cup6);
        cups[6] = (ImageView) view.findViewById(R.id.ID_cup7);
        cups[7] = (ImageView) view.findViewById(R.id.ID_cup8);
        bottles[0] = (ImageView) view.findViewById(R.id.ID_bottle1);
        bottles[1] = (ImageView) view.findViewById(R.id.ID_bottle2);
        bottles[2] = (ImageView) view.findViewById(R.id.ID_bottle3);
        bottles[3] = (ImageView) view.findViewById(R.id.ID_bottle4);
        bottles[4] = (ImageView) view.findViewById(R.id.ID_bottle5);
        bottles[5] = (ImageView) view.findViewById(R.id.ID_bottle6);
        Btn_kakaoLink = (ImageButton) view.findViewById(R.id.ID_kakaorink);
        container = (FrameLayout) view.findViewById(R.id.conent_fragment_layout);


        Btn_Initialization.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (Now_liquor.equals("Beer")) {
                    Now_liquor_volume_beer = 0;
                } else if (Now_liquor.equals("Soju")) {
                    Now_liquor_volume_soju = 0;
                }
                for (int i = 0; i < cups.length; i++) {
                    cups[i].setImageAlpha(0);
                }
                for(int i = 0; i < bottles.length; i++)
                {
                    bottles[i].setImageAlpha(0);
                }
                Now_Volume_text.setText("현재 마신량 :");
                Now_Volumezan_text.setText("0병 0잔");
            }
        });
        Btn_SojuCup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                for(int i = 0; i<bottles.length; i++)
                {
                    bottles[i].setImageAlpha(0);
                }
                if(Now_liquor.equals("Soju")) // 현재 소주 측정일 경우 맥주 측정으로 변경
                {
                    Now_liquor = "Beer";
                    Now_liquor_volume = Now_liquor_volume_beer;
                    for (int i = 0; i < cups.length; i++) {
                        cups[i].setImageAlpha(0);
                        cups[i].setImageResource(R.drawable.final_beercup);
                    }
                    Now_Volume_text.setText("현재 마신량 : " + Now_liquor_volume * 500 + "(cc)");
                    Now_Volumezan_text.setText("");
                }
                else if(Now_liquor.equals("Beer")) // 현재 맥주 측정일 경우 소주 측정으로 변경
                {
                    Now_liquor = "Soju";
                    Now_liquor_volume = Now_liquor_volume_soju;
                    for (int i = 0; i < cups.length; i++) {
                        cups[i].setImageAlpha(0);
                        cups[i].setImageResource(R.drawable.final_sojucup);
                    }
                    for(int i = 0; i< Now_liquor_volume / 8; i++)
                    {
                        bottles[i].setImageAlpha(255);
                    }
                    Now_Volume_text.setText("현재 마신량 : " + Now_liquor_volume * 40 + "(ml)");
                    Now_Volumezan_text.setText(Now_liquor_volume / 8 + "병 " + Now_liquor_volume % 8 + "잔");
                }
                float bottle = Now_liquor_volume / 8;
                float zan = Now_liquor_volume % 8;

                for (int i = 0; i < zan; i++) {
                    cups[i].setImageAlpha(255);
                }
            }
        });
        Btn_OneShot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                float bottle = 0;
                float zan = 0;
                if (Now_liquor.equals("Beer")) {
                    Now_liquor_volume_beer += 1;
                    Now_liquor_volume = Now_liquor_volume_beer;
                    bottle = Now_liquor_volume_beer / 8;
                    zan = Now_liquor_volume_beer % 8;
                    Now_Volume_text.setText("현재 마신량 : " + Now_liquor_volume * 500 + "(cc)");
                } else if (Now_liquor.equals("Soju")) {
                    Now_liquor_volume_soju += 1;
                    Now_liquor_volume = Now_liquor_volume_soju;
                    bottle = Now_liquor_volume / 8;
                    zan = Now_liquor_volume % 8;
                    Now_Volume_text.setText("현재 마신량 : " + Now_liquor_volume * 40 + "(ml)");
                    Now_Volumezan_text.setText(Now_liquor_volume / 8 + "병 " + Now_liquor_volume % 8 + "잔");
                }
                for (int i = 0; i < cups.length; i++) {
                    cups[i].setImageAlpha(0);
                }
                for (int i = 0; i < zan; i++) {
                    cups[i].setImageAlpha(255);
                }
                for(int i = 0; i<bottle; i++)
                {
                    bottles[i].setImageAlpha(255);
                }
            }
        });

        Btn_Camera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                main.captureCamera();
            }
        });
        Btn_album.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                main.getAlbum();
            }
        });
        Btn_kakaoLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                main.mOnCaptureClick(view);
            }
        });



        getActivity().setTitle("주량 측정");
        return view;
    }
}

