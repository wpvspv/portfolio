package com.example.mh.sole_beer;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.provider.Settings;
import android.support.annotation.NonNull;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.content.ContextCompat;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import com.kakao.kakaolink.KakaoLink;
import com.kakao.kakaolink.KakaoTalkLinkMessageBuilder;
import com.kakao.util.exception.KakaoException;

class DBHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "alcohol.db";
    private static final int DATABASE_VERSION = 1;
    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE contacts ( _id INTEGER PRIMARY KEY AUTOINCREMENT, kind TEXT, name TEXT, ABV NUMERIC, vintage INTEGER, country TEXT);");
    }
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS contacts");
        onCreate(db);
    }
}

@SuppressWarnings("deprecation")
    public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {

    DBHelper helper;
    SQLiteDatabase db;

    private static final int MY_PERMISSION_STORAGE = 1111;
    private static final int REQUEST_TAKE_PHOTO = 2222;
    private static final int REQUEST_TAKE_ALBUM = 3333;
    private static final int REQUEST_IMAGE_CROP = 4444;

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
    FrameLayout container;

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
    final ImageView[] cups = new ImageView[8];
    final ImageView[] bottles = new ImageView[6];

    // 술 저장고 사용 코드
    ImageButton Btn_KoreaBeer;
    ImageButton Btn_OverseasBeer;
    ImageButton Btn_Soju;
    ImageButton Btn_Cacktail;
    ImageButton Btn_Makgulri;
    ImageButton Btn_Wine;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        helper = new DBHelper(this);
        try {
            db = helper.getWritableDatabase(); //데이터베이스 객체를 얻음
        } catch (SQLiteException ex) {
            db = helper.getReadableDatabase();
        }


        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        Now_liquor_Image = (ImageView) findViewById(R.id.ID_Now_liquor);
        Now_Volume_text = (TextView) findViewById(R.id.ID_Check_Now_Volume);
        Now_Volumezan_text = (TextView) findViewById(R.id.ID_Check_Now_Volume_Zan);
        Btn_SojuCup = (ImageButton) findViewById(R.id.ID_btn_SojuCup);
        Btn_Initialization = (ImageButton) findViewById(R.id.ID_Initialization);
        Btn_OneShot = (ImageButton) findViewById(R.id.ID_btn_OneShot);
        Btn_Camera = (ImageButton) findViewById(R.id.ID_btn_Camera);
        Btn_album = (ImageButton) findViewById(R.id.btn_album);
        cups[0] = (ImageView) findViewById(R.id.ID_cup1);
        cups[1] = (ImageView) findViewById(R.id.ID_cup2);
        cups[2] = (ImageView) findViewById(R.id.ID_cup3);
        cups[3] = (ImageView) findViewById(R.id.ID_cup4);
        cups[4] = (ImageView) findViewById(R.id.ID_cup5);
        cups[5] = (ImageView) findViewById(R.id.ID_cup6);
        cups[6] = (ImageView) findViewById(R.id.ID_cup7);
        cups[7] = (ImageView) findViewById(R.id.ID_cup8);
        bottles[0] = (ImageView) findViewById(R.id.ID_bottle1);
        bottles[1] = (ImageView) findViewById(R.id.ID_bottle2);
        bottles[2] = (ImageView) findViewById(R.id.ID_bottle3);
        bottles[3] = (ImageView) findViewById(R.id.ID_bottle4);
        bottles[4] = (ImageView) findViewById(R.id.ID_bottle5);
        bottles[5] = (ImageView) findViewById(R.id.ID_bottle6);
        Btn_kakaoLink = (ImageButton) findViewById(R.id.ID_kakaorink);

        // 임시 카메라 이미지
        ID_Camera = (ImageView) findViewById(R.id.ID_Camera);
        // 혈중알코올 사용 코드
        Blood_RadioGroup = (RadioGroup) findViewById(R.id.ID_blood_radiogroup);
        Blood_Man = (RadioButton) findViewById(R.id.ID_blood_man);
        Blood_Woman = (RadioButton) findViewById(R.id.ID_blood_woman);

        Blood_Weight = (EditText) findViewById(R.id.ID_blood_weight);
        Blood_Volume = (EditText) findViewById(R.id.ID_blood_volume);
        Blood_Con = (EditText) findViewById(R.id.ID_blood_Concentration);
        Blood_Time = (EditText) findViewById(R.id.ID_blood_time);

        btnBlood = (Button) findViewById(R.id.ID_blood_check);
        // 술 저장고 사용 코드
        Btn_KoreaBeer = (ImageButton) findViewById(R.id.ID_KoreaBeer);
        Btn_OverseasBeer = (ImageButton) findViewById(R.id.ID_OverSeasBeer);
        Btn_Soju = (ImageButton) findViewById(R.id.ID_Soju);
        Btn_Cacktail = (ImageButton) findViewById(R.id.ID_Cacktail);
        Btn_Makgulri = (ImageButton) findViewById(R.id.ID_Makgulri);
        Btn_Wine = (ImageButton) findViewById(R.id.ID_Wine);
        checkPermission();


        // 탭 설정
        // 주량 측정 사용 코드

    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {


        int id = item.getItemId();

        Fragment fragment = null;
        String title = getString(R.string.app_name);

        if (id == R.id.Estimate_Drink_Menu_Button) {
            fragment = new Fragment_Drink();
            title = "주량 측정";
        } else if (id == R.id.Estimate_Blood_Menu_Button) {
            fragment = new Fragment_Blood();
            title = "혈중알코올 측정";
        } else if (id == R.id.Liquor_Store_Menu_Button) {
            fragment = new Fragment_Liquor_Store();
            title = "술 저장고";
        } else if (id == R.id.Drink_Average_Menu_Button) {

        }
        if(fragment != null)
        {
            FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
            ft.replace(R.id.conent_fragment_layout, fragment);
            ft.commit();
        }
        if(getSupportActionBar() != null)
        {
            getSupportActionBar().setTitle(title);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }




    private  void checkPermission()
    // 권한 체크
    {
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
        {
            if(ActivityCompat.shouldShowRequestPermissionRationale(this,Manifest.permission.WRITE_EXTERNAL_STORAGE)){
                new AlertDialog.Builder(this)
                        .setTitle("알림")
                        .setMessage("저장소 권한이 거부되었습니다. 사용을 원하시면 설정에서 해당 권한을 직접 허용하셔야 합니다.")
                        .setNeutralButton("설정", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                                intent.setData(Uri.parse("Package : " + getPackageName() ));
                                startActivity(intent);
                            }
                        })
                        .setPositiveButton("확인", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                finish();
                            }
                        })
                        .setCancelable(false)
                        .create()
                        .show();
            }
            else
            {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,Manifest.permission.READ_EXTERNAL_STORAGE}, MY_PERMISSION_STORAGE);
            }
        }
    }
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
    // 권한 체크 확인
    {
        switch (requestCode)
        {
            case MY_PERMISSION_STORAGE:
                for(int i =0; i < grantResults.length;i++)
                {
                    if(grantResults[i] < 0)
                    {
                        Toast.makeText(this, "해당 권한을 활성화 하셔야합니다.", Toast.LENGTH_SHORT).show();
                        return;
                    }
                }
                break;
        }
    }

    public void captureCamera()
    {
        String state = Environment.getExternalStorageState();
        // 외장 메모리 검사
        if(Environment.MEDIA_MOUNTED.equals(state))
        {
            Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            if(takePictureIntent.resolveActivity(getPackageManager()) != null)
            {
                File photoFile = null;
                try{
                    photoFile = createImageFile();
                } catch (IOException ex){
                    Log.e("captureCamera Error", ex.toString());
                }
                if(photoFile != null)
                {
                    // getUriForFile의 두번째 인자는 Manifest provier의 authorites와 일치해야함
                    Uri providerURI = FileProvider.getUriForFile(this, "com.shuvic.alumni.cameraalbum", photoFile);
                    imageUri = providerURI;
                    // 인텐트에 전달할 떄는 FileProvier의 Return 값인 content://로만!!, provierURI 값에 카메라 데이터를 넣어 보냄
                    takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, providerURI);

                    startActivityForResult(takePictureIntent, REQUEST_TAKE_PHOTO);
                }
            }

        }
        else
        {
            Toast.makeText(this, "저장공간이 접근 불가능한 기기입니다.", Toast.LENGTH_SHORT).show();
            return;
        };
    }
    public File createImageFile() throws  IOException{
        // Create an image file name
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        String imageFileName = "JPEG_" + timeStamp + ".jpg";
        File imageFile = null;
        File storageDir = new File(Environment.getExternalStorageDirectory() + "/Pictures", "Sole_Drink");
        if(!storageDir.exists())
        {
            Log.i("mCurrentPhotoPath1", storageDir.toString());
            storageDir.mkdir();
        }
        imageFile = new File(storageDir, imageFileName);
        mCurrentPhotoPath = imageFile.getAbsolutePath();

        return imageFile;
    }
    public void getAlbum()
    {
        Log.i("getAlbum", "Call");
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setType("image/*");
        intent.setType(MediaStore.Images.Media.CONTENT_TYPE);
        startActivityForResult(intent, REQUEST_TAKE_ALBUM);
    }
    public void galleryAddPic()
    {
        Log.i("galleryAddPic","Call");
        Intent mediaScanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
        // 해당 경로에 있는 파일을 객체화 (새로 파일을 만든다는 것으로 이해하면 안 됨)
        File f = new File(mCurrentPhotoPath);
        Uri contentUri = Uri.fromFile(f);
        mediaScanIntent.setData(contentUri);
        sendBroadcast(mediaScanIntent);
        Toast.makeText(this, "사진이 앨범에 저장되었습니다.", Toast.LENGTH_SHORT).show();
    }
    public void cropImage()
    {
        Log.i("cropImage", "Call");
        Log.i("cropImage", "photoURI : " + photoURI + " / albumURI : "  + albumURI);
        Intent cropIntent = new Intent("com.android.camera.action.CROP");

        // 50x50 픽셀 미만은 편집할 수 없다는 문구 처리 + 갤러리, 포터 둘다 호환하는 방법
        cropIntent.setFlags(Intent.FLAG_GRANT_WRITE_URI_PERMISSION);
        cropIntent.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        cropIntent.setDataAndType(photoURI, "image/*");
        // cropIntent.putExtra("outputX",200);   =>  crop한 이미지의 x축 크기.
        // cropIntent.putExtra("outputY", 200);  =>  crop한 이미지의 y축 크기.
        cropIntent.putExtra("aspectX",1);
        cropIntent.putExtra("aspectY",1);
        cropIntent.putExtra("scale", true);
        cropIntent.putExtra("output", albumURI);
        startActivityForResult(cropIntent,REQUEST_IMAGE_CROP);
    }
    public  void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case REQUEST_TAKE_PHOTO:
                if (resultCode == Activity.RESULT_OK) {
                    try {
                        Log.i("REQUEST_TAKE_PHOTO", "OK");
                        galleryAddPic();

                        ID_Camera.setImageURI(imageUri);
                    } catch (Exception e) {
                        Log.e("REQUEST_TAKE_PHOTO", e.toString());
                    }
                }
                else {
                    Toast.makeText(this, "사진찍기를 취소하였습니다.", Toast.LENGTH_SHORT).show();
                }
                break;
            case REQUEST_TAKE_ALBUM:
                if (resultCode == Activity.RESULT_OK) {
                    if (data.getData() != null) {
                        try {
                            File albumFile = null;
                            albumFile = createImageFile();
                            photoURI = data.getData();
                            albumURI = Uri.fromFile(albumFile);
                            cropImage();
                        } catch (Exception e) {
                            Log.e("TAKE_ALBUM_SINGLE ERROR", e.toString());
                        }
                    }
                }
                break;
            case REQUEST_IMAGE_CROP:
                if (resultCode == Activity.RESULT_OK) {
                    galleryAddPic();
                    ID_Camera.setImageURI(albumURI);
                }
                break;
        }
    }

    public void sendKaKao()
    // 카카오에 캡쳐한파일 보내기
    {

        String message = "[혼술 인증]\n 현재 마신 량은 씨바알";
        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, message );
        intent.setPackage("com.kakao.talk");
        startActivity(intent);
        sendImageKakao(CaptrueUri);
    }
    public void sendImageKakao(Uri uri)
    // 카카오에 캡쳐한 파일 받아서 보내기
    {

        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("image/jpg");
        intent.putExtra(Intent.EXTRA_STREAM, uri);
        intent.setPackage("com.kakao.talk");
        startActivity(Intent.createChooser(intent, "Choose"));
    }

    public void mOnCaptureClick(View v)
    // 캡쳐버튼클릭
    {

        View rootView = getWindow().getDecorView();
        File screenShot = ScreenShot(rootView);
        if(screenShot!=null){
            //갤러리에 추가
            sendBroadcast(new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE, Uri.fromFile(screenShot)));
        }


        sendKaKao();
    }

    public File ScreenShot(View view)
    //화면 캡쳐하기
    {
        view.setDrawingCacheEnabled(true);  //화면에 뿌릴때 캐시를 사용하게 한다
        Bitmap screenBitmap = view.getDrawingCache();   //캐시를 비트맵으로 변환
        SimpleDateFormat formatter = new SimpleDateFormat("yyyyMMddHHmmss");// 년월일시분초
        Date currentTime_1 = new Date();
        dateString = formatter.format(currentTime_1) + ".jpg"; // 캡쳐 파일 이름을 시간으로 저장

        File file = new File(Environment.getExternalStorageDirectory()+"/Pictures/Sole_Drink", dateString);  //Pictures폴더 screenshot.png 파일

        Toast.makeText(this, Environment.getExternalStorageDirectory() + "/Pictures/Sole_Drink" + dateString, Toast.LENGTH_SHORT).show();

        File dirName = new File(Environment.getExternalStorageDirectory()+"/Pictures/Sole_Drink");  //디렉토리를 지정합니다.
        String name = dateString; //공유할 이미지 파일 명
        File Final = new File(dirName, name); //image 파일의 경로를 설정합니다
        CaptrueUri = Uri.fromFile(Final);
        FileOutputStream os = null;
        try{
            os = new FileOutputStream(file);
            screenBitmap.compress(Bitmap.CompressFormat.PNG, 90, os);   //비트맵을 PNG파일로 변환
            os.close();
        }catch (IOException e){
            e.printStackTrace();
            return null;
        }
        view.setDrawingCacheEnabled(false);

        // CaptrueUri = Uri.fromFile(file); // savefile은 MMS로 보낼 이미지 파일의 File 형식의 변수입니다.
        Toast.makeText(this, "" + CaptrueUri, Toast.LENGTH_SHORT).show();
        return file;
    }

}

/*









// 주량 측정 사용 코드







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
                Intent intent = new Intent(getApplicationContext(),Calc_Blood_Alcohol.class);
                intent.putExtra("Sex", Blood_Sex);
                intent.putExtra("Weight", blood_weight);
                intent.putExtra("Concentration", blood_concentration);
                intent.putExtra("Volume", blood_volume);
                intent.putExtra("Time", blood_time);
                startActivity(intent);
            }
        });

        // 술 저장고 인텐트 코드
        Btn_KoreaBeer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "KoreaBeer");
                startActivity(store_intent);
            }
        });
        Btn_OverseasBeer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "OverseasBeer");
                startActivity(store_intent);
            }
        });
        Btn_Soju.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "Soju");
                startActivity(store_intent);
            }
        });
        Btn_Cacktail.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "Cacktail");
                startActivity(store_intent);
            }
        });
        Btn_Makgulri.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "Makgulri");
                startActivity(store_intent);
            }
        });
        Btn_Wine.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent store_intent = new Intent(getApplicationContext(), Liquor_Store.class);
                store_intent.putExtra("Liquor_kind", "Wine");
                startActivity(store_intent);
            }
        });













        */