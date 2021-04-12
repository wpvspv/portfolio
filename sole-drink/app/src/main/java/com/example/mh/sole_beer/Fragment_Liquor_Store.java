package com.example.mh.sole_beer;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;

public class Fragment_Liquor_Store extends Fragment {
    View view;

    // 술 저장고 사용 코드
    ImageButton Btn_KoreaBeer;
    ImageButton Btn_OverseasBeer;
    ImageButton Btn_Soju;
    ImageButton Btn_Cacktail;
    ImageButton Btn_Makgulri;
    ImageButton Btn_Wine;



    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             Bundle savedInstanceState)
    {
        view = inflater.inflate(R.layout.liquor_store_layout, container, false);
        // 술 저장고 사용 코드
        Btn_KoreaBeer = (ImageButton) view.findViewById(R.id.ID_KoreaBeer);
        Btn_OverseasBeer = (ImageButton) view.findViewById(R.id.ID_OverSeasBeer);
        Btn_Soju = (ImageButton) view.findViewById(R.id.ID_Soju);
        Btn_Cacktail = (ImageButton) view.findViewById(R.id.ID_Cacktail);
        Btn_Makgulri = (ImageButton) view.findViewById(R.id.ID_Makgulri);
        Btn_Wine = (ImageButton) view.findViewById(R.id.ID_Wine);

        getActivity().setTitle("술 저장고");
        Btn_KoreaBeer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_KoreaBeer.class);
                store_intent.putExtra("Liquor_kind", "KoreaBeer");
                startActivity(store_intent);
            }
        });
        Btn_OverseasBeer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_OverseeBeer.class);
                store_intent.putExtra("Liquor_kind", "OverseasBeer");
                startActivity(store_intent);
            }
        });
        Btn_Soju.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_Soju.class);
                store_intent.putExtra("Liquor_kind", "Soju");
                startActivity(store_intent);
            }
        });
        Btn_Cacktail.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_Cacktail.class);
                store_intent.putExtra("Liquor_kind", "Cacktail");
                startActivity(store_intent);
            }
        });
        Btn_Makgulri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_Makgulri.class);
                store_intent.putExtra("Liquor_kind", "Makgulri");
                startActivity(store_intent);
            }
        });
        Btn_Wine.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getActivity(), Liquor_Store_Wine.class);
                store_intent.putExtra("Liquor_kind", "Wine");
                startActivity(store_intent);
            }
        });
        return view;
    }

}
