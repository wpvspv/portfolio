package com.example.mobile_controller;

import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.Intent;//음성인식 관련 패키지
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.ActivityCompat;//오디오녹음 권한 허용창 생성에 필요
import android.support.v4.content.ContextCompat;//오디오녹음 권한 허용창 생성에 필요
import android.support.v7.app.AppCompatActivity;
import android.speech.RecognizerIntent;//음성인식 관련 패키지
import android.speech.RecognitionListener;//음성인식 관련 패키지
import android.speech.SpeechRecognizer;//음성인식 관련 패키지
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.MediaController;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    View dialogView;
    String tmp;
    Integer speed=100;
    private char m;

    private static final String TAG = "MainActivity";
    private String html="";
    private Handler mHandler;
    private Socket socket;

    private BufferedReader reader;
    private BufferedWriter writer;
    private DataOutputStream output;
    private DataOutputStream front;
    
    private String ip;
    private int port=9999;           //prot번호
    private char massage;

    Intent intent;
    SpeechRecognizer stt;
    int flag;
    AlertDialog.Builder builder;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Intent inIntent = getIntent();
        ip=inIntent.getStringExtra("ip_num");
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[] {Manifest.permission.RECORD_AUDIO}, 5);
            Toast.makeText(MainActivity.this, "허용하지 않을 경우 음성인식기능에 제한이 발생할 수 있습니다.", Toast.LENGTH_LONG).show();
        }
        final Button exit = findViewById(R.id.exit_btn);
        final ImageButton go = findViewById(R.id.go);
        final ImageButton back = findViewById(R.id.back);
        final ImageButton left = findViewById(R.id.left);
        final ImageButton right = findViewById(R.id.right);
        final ImageButton speedUp = findViewById(R.id.speedUp);
        final ImageButton speedDown = findViewById(R.id.speedDown);

        final TextView speedView = findViewById(R.id.speedView);
        final TextView voice_text = findViewById(R.id.voice_text);

        //final Switch autoDriveMode = findViewById(R.id.autoDriveMode);
        final Switch voiceControl = findViewById(R.id.voiceControl);

        //final WebView stream = findViewById(R.id.stream); //webview 사용할 시
        final VideoView stream = findViewById(R.id.stream); //videoview 사용할 시
        //SharedPreference에서 속도 값을 가져와서 속도계에 출력
        //SharedPreferences sp = getSharedPreferences("SPEED", MODE_PRIVATE);
        //speed = sp.getInt("speed", 80);
        //speedView.setText(speed.toString());

        //전진 버튼 리스너 -> 이미지변경
 /*       go.setOnTouchListener(new RepeatListener(400, 100,new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //go.setBackgroundResource(R.drawable.up_pushed);
                MyClientTask myclientTask_down_W = new MyClientTask(ip,port, 'W');
                myclientTask_down_W.execute();

                left.setOnTouchListener(new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        switch(event.getAction())
                        {
                            case MotionEvent.ACTION_DOWN:
                                left.setBackgroundResource(R.drawable.left_pushed);
                                MyClientTask myclientTask_down_Q = new MyClientTask(ip,port, 'Q');
                                myclientTask_down_Q.execute();
                                break;

                            case MotionEvent.ACTION_UP:
                                left.setBackgroundResource(R.drawable.left_button);
                                MyClientTask myclientTask_up_W = new MyClientTask(ip,port, 'W');
                                myclientTask_up_W.execute();
                                break;
                        }

                        return false;
                    }
                });






            }
        }));

  */
        exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MyClientTask myclientTask_down_I = new MyClientTask(ip,port, 'I');
                myclientTask_down_I.execute();
                finish();
            }
        });
        /*//webview 사용할 시
        stream.setPadding(0,0,0,0);
        stream.getSettings().setBuiltInZoomControls(true); //줌기능 추가
        stream.getSettings().setSupportZoom(true);
        stream.getSettings().setDisplayZoomControls(false);
        stream.getSettings().setJavaScriptEnabled(true); //자바스크립트 기능 추가
        stream.getSettings().setLoadWithOverviewMode(true); //콘텐츠가 웹뷰보다 클 경우 스크린 크기에 맞게 조절
        stream.getSettings().setUseWideViewPort(true); //wide view port를 사용
        //stream.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.SINGLE_COLUMN); //사이즈 자동 맞추기

        String stream_url="http://"+ip+":8080/javascript_simple.html";
        stream.loadUrl(stream_url);
        */

        //MediaController controller = new MediaController(MainActivity.this);

        String stream_url="http://"+ip+":8080/javascript_simple.html";
        stream.setVideoPath(stream_url);
        stream.setMediaController(new MediaController(this));
        stream.requestFocus();
        stream.start();



        go.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d(TAG,"버튼 클릭");

                switch(event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                        Log.d(TAG,"다운");
                        go.setBackgroundResource(R.drawable.up_pushed);
                        MyClientTask myclientTask_down_W = new MyClientTask(ip,port, 'W');
                        myclientTask_down_W.execute();
                        m='W';
                        System.out.println(m);
                        //왼쪽 앞으로
                        if(m=='W') {
                            left.setOnTouchListener(new View.OnTouchListener() {
                                @Override
                                public boolean onTouch(View v, MotionEvent event) {
                                    Log.d(TAG, "버튼 클릭");
                                    switch (event.getAction()) {
                                        case MotionEvent.ACTION_DOWN:
                                            Log.d(TAG, "다운");
                                            left.setBackgroundResource(R.drawable.left_pushed);
                                            MyClientTask myclientTask_down_Q = new MyClientTask(ip, port, 'Q');
                                            myclientTask_down_Q.execute();
                                            m='Q';
                                            System.out.println(m);
                                            break;

                                        case MotionEvent.ACTION_UP:
                                            Log.d(TAG, "업");
                                            left.setBackgroundResource(R.drawable.left_button);
                                            MyClientTask myclientTask_up_Q = new MyClientTask(ip, port, 'W');
                                            myclientTask_up_Q.execute();
                                            m='S';
                                            System.out.println(m);
                                            break;
                                    }
                                    return false;
                                }
                            });

                            //오른쪽 앞으로
                            right.setOnTouchListener(new View.OnTouchListener() {
                                @Override
                                public boolean onTouch(View v, MotionEvent event) {
                                    Log.d(TAG, "버튼 클릭");
                                    switch (event.getAction()) {
                                        case MotionEvent.ACTION_DOWN:
                                            Log.d(TAG, "다운");
                                            right.setBackgroundResource(R.drawable.right_pushed);
                                            MyClientTask myclientTask_down_E = new MyClientTask(ip, port, 'E');
                                            myclientTask_down_E.execute();
                                            m='E';
                                            System.out.println(m);
                                            break;

                                        case MotionEvent.ACTION_UP:
                                            Log.d(TAG, "업");
                                            right.setBackgroundResource(R.drawable.right_button);
                                            MyClientTask myclientTask_up_W = new MyClientTask(ip, port, 'W');
                                            myclientTask_up_W.execute();
                                            m='S';
                                            System.out.println(m);
                                            break;
                                    }
                                    return false;
                                }
                            });

                        }
                        break;
                    //전진버튼 땠을 때
                    case MotionEvent.ACTION_UP:
                        Log.d(TAG,"업");
                        go.setBackgroundResource(R.drawable.up_button);
                        MyClientTask myclientTask_up_S = new MyClientTask(ip,port, 'S');
                        myclientTask_up_S.execute();
                        m='S';
                        System.out.println(m);
                        break;
                }
                return false;
            }
        });

        //후진 버튼 리스너 -> 이미지 변경
        back.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                        back.setBackgroundResource(R.drawable.down_pushed);
                        MyClientTask myclientTask_down_X = new MyClientTask(ip,port, 'X');
                        myclientTask_down_X.execute();
                        m='X';
                        System.out.println(m);
                        //왼쪽 뒤로
                        if(m=='X') {
                            left.setOnTouchListener(new View.OnTouchListener() {
                                @Override
                                public boolean onTouch(View v, MotionEvent event) {
                                    Log.d(TAG, "버튼 클릭");
                                    switch (event.getAction()) {
                                        case MotionEvent.ACTION_DOWN:
                                            Log.d(TAG, "다운");
                                            left.setBackgroundResource(R.drawable.left_pushed);
                                            MyClientTask myclientTask_down_Z = new MyClientTask(ip, port, 'Z');
                                            myclientTask_down_Z.execute();
                                            m='Z';
                                            System.out.println(m);
                                            break;

                                        case MotionEvent.ACTION_UP:
                                            Log.d(TAG, "업");
                                            left.setBackgroundResource(R.drawable.left_button);
                                            MyClientTask myclientTask_up_X = new MyClientTask(ip, port, 'X');
                                            myclientTask_up_X.execute();
                                            m='S';
                                            System.out.println(m);
                                            break;
                                    }
                                    return false;
                                }
                            });

                            //오른쪽 뒤로
                            right.setOnTouchListener(new View.OnTouchListener() {
                                @Override
                                public boolean onTouch(View v, MotionEvent event) {
                                    Log.d(TAG, "버튼 클릭");
                                    switch (event.getAction()) {
                                        case MotionEvent.ACTION_DOWN:
                                            Log.d(TAG, "다운");
                                            right.setBackgroundResource(R.drawable.right_pushed);
                                            MyClientTask myclientTask_down_C = new MyClientTask(ip, port, 'C');
                                            myclientTask_down_C.execute();
                                            m='C';
                                            System.out.println(m);
                                            break;

                                        case MotionEvent.ACTION_UP:
                                            Log.d(TAG, "업");
                                            right.setBackgroundResource(R.drawable.right_button);
                                            MyClientTask myclientTask_up_X = new MyClientTask(ip, port, 'X');
                                            myclientTask_up_X.execute();
                                            m='S';
                                            System.out.println(m);
                                            break;
                                    }
                                    return false;
                                }
                            });

                        }
                        break;

                    case MotionEvent.ACTION_UP:
                        back.setBackgroundResource(R.drawable.down_button);
                        MyClientTask myclientTask_up_S = new MyClientTask(ip,port, 'S');
                        myclientTask_up_S.execute();
                        m='S';
                        System.out.println(m);
                        break;
                }

                return false;
            }
        });

        //속도 증가 버튼 리스너 -> 이미지 변경
        speedUp.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                        speedUp.setBackgroundResource(R.drawable.speed_up_pushed);
                        break;

                    case MotionEvent.ACTION_UP:
                        speedUp.setBackgroundResource(R.drawable.speed_up_button);
                        MyClientTask myclientTask_down_U = new MyClientTask(ip,port, 'U');
                        myclientTask_down_U.execute();
                        tmp = speedView.getText().toString();
                        speed = Integer.parseInt(tmp);
                        if(speed >= 250) speed = 250;
                        else             speed += 10;
                        speedView.setText(speed.toString());
                        break;
                }

                return false;
            }
        });

        //속도 감소 버튼 -> 이미지 변경
        speedDown.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                        speedDown.setBackgroundResource(R.drawable.speed_down_pushed); break;

                    case MotionEvent.ACTION_UP:
                        speedDown.setBackgroundResource(R.drawable.speed_down_button);
                        MyClientTask myclientTask_down_J = new MyClientTask(ip,port, 'J');
                        myclientTask_down_J.execute();
                        tmp = speedView.getText().toString();
                        speed = Integer.parseInt(tmp);
                        if(speed <= 50) speed = 50;
                        else           speed -= 10;
                        speedView.setText(speed.toString());
                        break;
                }

                return false;
            }
        });
/*
                    //음성인식 스위치 켜질 경우 -> 사용자가 한 말을 보여주는 커스텀다이얼로그 생성
                    dialogView = getLayoutInflater().inflate(R.layout.voice_dialog, null);//레이아웃을 담는 View객체 생성
                    builder = new AlertDialog.Builder(MainActivity.this);//alertDialog.builder객체 생성 -> 다이얼로그의 각종 setting가능
                    //intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                    //Toast.makeText(MainActivity.this, builder.getClass().getName(), Toast.LENGTH_SHORT).show();
                    builder.setView(dialogView);
                    builder.setTitle("Voice Controlling");//다이얼로그 타이틀
                    builder.setCancelable(false);//다이얼로그 외부 눌러도 종료되지 않게 함
                    //다이얼로그의 종료 버튼 리스너
                    builder.setPositiveButton("종료", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            voiceControl.setChecked(false);
                        }
                    });
                    AlertDialog alertDialog = builder.create();//AlertDialog객체 생성
                    alertDialog.show();
*/

        //음성인식 스위치 리스너
        voiceControl.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                //음성인식 스위치가 켜졌을 때 -> 나머지 버튼 비활성화 및 이미지 변경
                if(isChecked) {
                    go.setEnabled(false);
                    back.setEnabled(false);
                    speedUp.setEnabled(false);
                    speedDown.setEnabled(false);
                    left.setEnabled(false);
                    right.setEnabled(false);

                    go.setBackgroundResource(R.drawable.up_locked);
                    back.setBackgroundResource(R.drawable.down_locked);
                    speedUp.setBackgroundResource(R.drawable.speed_up_locked);
                    speedDown.setBackgroundResource(R.drawable.speed_down_locked);
                    left.setBackgroundResource(R.drawable.left_locked);
                    right.setBackgroundResource(R.drawable.right_locked);

                    Toast.makeText(MainActivity.this, "음성인식을 시작합니다.", Toast.LENGTH_SHORT).show();
                    MyClientTask myclientTask_down_V = new MyClientTask(ip,port, 'V');
                    myclientTask_down_V.execute();
                    flag=1;
                    inputVoice(voice_text);
                }

                //음성인식 스위치가 꺼졌을 때 -> 나머지 버튼 비활성화 및 이미지 변경
                else {
                    go.setEnabled(true);
                    back.setEnabled(true);
                    speedUp.setEnabled(true);
                    speedDown.setEnabled(true);
                    left.setEnabled(true);
                    right.setEnabled(true);

                    go.setBackgroundResource(R.drawable.up_button);
                    back.setBackgroundResource(R.drawable.down_button);
                    speedUp.setBackgroundResource(R.drawable.speed_up_button);
                    speedDown.setBackgroundResource(R.drawable.speed_down_button);
                    left.setBackgroundResource(R.drawable.left_button);
                    right.setBackgroundResource(R.drawable.right_button);

                    MyClientTask myclientTask_down_B = new MyClientTask(ip,port, 'B');
                    myclientTask_down_B.execute();
                    flag=0;
                    inputVoice(voice_text);

                }
            }
        });

        /*
        //자율주행 스위치 리스너
        autoDriveMode.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                //자율주행 스위치가 켜졌을 때 -> 나머지 버튼 비활성화 및 이미지 변경
                if(isChecked) {
                    go.setEnabled(false);
                    back.setEnabled(false);
                    speedUp.setEnabled(false);
                    speedDown.setEnabled(false);
                    left.setEnabled(false);
                    right.setEnabled(false);

                    go.setBackgroundResource(R.drawable.up_locked);
                    back.setBackgroundResource(R.drawable.down_locked);
                    speedUp.setBackgroundResource(R.drawable.speed_up_locked);
                    speedDown.setBackgroundResource(R.drawable.speed_down_locked);
                    left.setBackgroundResource(R.drawable.left_locked);
                    right.setBackgroundResource(R.drawable.right_locked);

                    Toast.makeText(MainActivity.this, "자율주행을 시작합니다.", Toast.LENGTH_LONG).show();
                }

                //자율주행 스위치가 꺼졌을 때 -> 나머지 버튼 비활성화 및 이미지 변경
                else {
                    go.setEnabled(true);
                    back.setEnabled(true);
                    speedUp.setEnabled(true);
                    speedDown.setEnabled(true);
                    left.setEnabled(true);
                    right.setEnabled(true);

                    go.setBackgroundResource(R.drawable.up_button);
                    back.setBackgroundResource(R.drawable.down_button);
                    speedUp.setBackgroundResource(R.drawable.speed_up_button);
                    speedDown.setBackgroundResource(R.drawable.speed_down_button);
                    left.setBackgroundResource(R.drawable.left_button);
                    right.setBackgroundResource(R.drawable.right_button);

                    Toast.makeText(MainActivity.this, "자율주행을 종료합니다.", Toast.LENGTH_LONG).show();
                }
            }
        });
        */
    }

    //음성인식 처리부
    public void inputVoice(final TextView voice_text) {
        if(flag==0)
            Toast.makeText(MainActivity.this, "음성인식을 종료합니다.", Toast.LENGTH_SHORT).show();
        else{
            try {
                intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, this.getPackageName());
                intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, "ko-KR");

                stt = SpeechRecognizer.createSpeechRecognizer(this);
                //Toast.makeText(MainActivity.this, "디버그", Toast.LENGTH_SHORT).show();
                if(flag==1)
                    stt.startListening(intent);

                stt.setRecognitionListener(new RecognitionListener() {
                    @Override
                    public void onReadyForSpeech(Bundle params) {
                        System.out.println("onReadyForSpeech.........................");

                    }
                    @Override
                    public void onBeginningOfSpeech() {
                        if(flag==1){}
                            //Toast.makeText(MainActivity.this, "지금부터 말을 해주세요", Toast.LENGTH_SHORT).show();

                    }
                    @Override
                    public void onRmsChanged(float rmsdB) {
                        System.out.println("onRmsChanged.........................");

                    }
                    @Override
                    public void onBufferReceived(byte[] buffer) {
                        System.out.println("onBufferReceived.........................");
                    }
                    @Override
                    public void onEndOfSpeech() {
                        System.out.println("onEndOfSpeech.........................");
                    }
                    @Override
                    public void onError(int error) {
                        if(flag==1) {
                            if (error == 8)
                                Toast.makeText(MainActivity.this, "잠시 기다려주세요", Toast.LENGTH_SHORT).show();
                            else if (error == 7) {
                                //stt.destroy();
                                //Toast.makeText(MainActivity.this, "천천히 다시 말해주세요.", Toast.LENGTH_SHORT).show();
                                new Handler().postDelayed(new Runnable()
                                {
                                    @Override
                                    public void run()
                                    {
                                        stt.startListening(intent);//딜레이 후 시작할 코드 작성
                                    }
                                }, 600);// 2초 정도 딜레이를 준 후 시작
                            }
                        }
                    }
                    @Override
                    public void onResults(Bundle results) {
                        //stt.destroy();
                        String key = "";
                        key = SpeechRecognizer.RESULTS_RECOGNITION;
                        ArrayList<String> mResult = results.getStringArrayList(key);
                        String[] rs = new String[mResult.size()];
                        mResult.toArray(rs);
                        Toast.makeText(MainActivity.this, rs[0], Toast.LENGTH_SHORT).show();
                        replyAnswer(rs[0], voice_text);
                        if(flag==1)
                            new Handler().postDelayed(new Runnable()
                            {
                                @Override
                                public void run()
                                {
                                    stt.startListening(intent);//딜레이 후 시작할 코드 작성
                                }
                            }, 600);// 2초 정도 딜레이를 준 후 시작

                    }
                    @Override
                    public void onPartialResults(Bundle partialResults) {
                        System.out.println("onPartialResults.........................");
                    }
                    @Override
                    public void onEvent(int eventType, Bundle params) {
                        System.out.println("onEvent.........................");
                    }
                });
                //stt.startListening(intent);
            } catch (Exception e) {
                Toast.makeText(MainActivity.this, e.toString(), Toast.LENGTH_LONG).show();
            }
        }
    }

    //인식된 음성에 따른 출력 결과 처리부
    public void replyAnswer(String input, TextView voice_text) {
        try {
            if(input.equals("앞으로가")) {
                MyClientTask myclientTask_down_W = new MyClientTask(ip,port, 'W');
                myclientTask_down_W.execute();
            }

            else if(input.equals("뒤로가")) {
                MyClientTask myclientTask_down_X = new MyClientTask(ip,port, 'X');
                myclientTask_down_X.execute();
            }

            else if(input.contains("왼쪽") && input.contains("앞으로")) {
                MyClientTask myclientTask_down_Q = new MyClientTask(ip, port, 'Q');
                myclientTask_down_Q.execute();
            }

            else if(input.contains("오른쪽") && input.contains("앞으로")) {
                MyClientTask myclientTask_down_E = new MyClientTask(ip, port, 'E');
                myclientTask_down_E.execute();
            }

            else if(input.contains("왼쪽") && input.contains("뒤로")) {
                MyClientTask myclientTask_down_Z = new MyClientTask(ip, port, 'Z');
                myclientTask_down_Z.execute();
            }

            else if(input.contains("오른쪽") && input.contains("뒤로")) {
                MyClientTask myclientTask_down_C = new MyClientTask(ip, port, 'C');
                myclientTask_down_C.execute();
            }

            else if(input.equals("속도 올려") || input.equals("속도 높여")) {
                MyClientTask myclientTask_down_U = new MyClientTask(ip,port, 'U');
                myclientTask_down_U.execute();
                final TextView speedView = findViewById(R.id.speedView);
                tmp = speedView.getText().toString();
                speed = Integer.parseInt(tmp);
                if(speed >= 250) speed = 250;
                else             speed += 10;
                speedView.setText(speed.toString());
            }

            else if(input.equals("속도 내려") || input.equals("속도 낮춰")) {
                MyClientTask myclientTask_down_J = new MyClientTask(ip,port, 'J');
                myclientTask_down_J.execute();
                final TextView speedView = findViewById(R.id.speedView);
                tmp = speedView.getText().toString();
                speed = Integer.parseInt(tmp);
                if(speed <= 50) speed = 50;
                else             speed -= 10;
                speedView.setText(speed.toString());
            }

            else if(input.equals("정지") || (input.equals("멈춰"))) {
                MyClientTask myclientTask_up_S = new MyClientTask(ip,port, 'S');
                myclientTask_up_S.execute();
            }
/*
            else if(input.equals("종료")) {
                voice_text.append(">> 음성인식 기능이 종료단계에 들어갑니다....");
                finish();
            }
*/
            else {

            }

        } catch(Exception e) {
            Toast.makeText(MainActivity.this, e.toString(), Toast.LENGTH_SHORT).show();
        }
    }

    //소켓연결 및 데이터 전송
    public class MyClientTask extends AsyncTask<Void, Void, Void>{
        String taskIp;
        int taskPort;
        char taskMessage;
        String response="";

        MyClientTask(String ip, int port, char message){
            taskIp=ip;
            taskPort=port;
            taskMessage=message;
        }
        @Override
        protected Void doInBackground(Void... arg0){
            Socket socket = null;
            try{
                socket=new Socket(taskIp,taskPort);
                OutputStream out = socket.getOutputStream();
                out.write(taskMessage);
            }
            catch (UnknownHostException e){
                e.printStackTrace();
                response="UnknownHostException" + e.toString();
            }
            catch (IOException e){
                e.printStackTrace();
                response="IOException"+e.toString();
            }
            finally {
                if(socket!=null){
                    try{
                        socket.close();
                    }
                    catch (IOException e){
                        e.printStackTrace();
                    }
                }
            }
            return null;
        }
    /*
    @Override
    protected void onPostExecute(Void result){

        super.onPostExecute();
    }
    */
    }

    //연속눌림버튼
    public class RepeatListener implements View.OnTouchListener {
        private Handler handler = new Handler();

        private int initialInterval;
        private final int normalInterval;
        private final View.OnClickListener clickListener;
        private View touchedView;

        private Runnable handlerRunnable = new Runnable() {
            @Override
            public void run() {
                if(touchedView.isEnabled()){
                    handler.postDelayed(this, normalInterval);
                    clickListener.onClick(touchedView);
                }
                else{
                    handler.removeCallbacks(handlerRunnable);
                    touchedView.setPressed(false);
                    touchedView=null;
                }
            }
        };

        public RepeatListener(int initialInterval, int normalInterval, View.OnClickListener clickListener){
            if(clickListener==null)
                throw new IllegalArgumentException("null runnable");
            if(initialInterval<0 || normalInterval<0)
                throw new IllegalArgumentException("negative interval");

            this.initialInterval=initialInterval;
            this.normalInterval=normalInterval;
            this.clickListener=clickListener;
        }

        public boolean onTouch(View view, MotionEvent motionEvent){
            switch (motionEvent.getAction()){
                case MotionEvent.ACTION_DOWN:
                    handler.removeCallbacks(handlerRunnable);
                    handler.postDelayed(handlerRunnable, initialInterval);
                    touchedView = view;
                    touchedView.setPressed(true);
                    clickListener.onClick(view);

                    return true;
                case MotionEvent.ACTION_UP:
                    MyClientTask myclientTask_up_W = new MyClientTask(ip,port, 'S');
                    myclientTask_up_W.execute();
                case MotionEvent.ACTION_CANCEL:
                    handler.removeCallbacks(handlerRunnable);
                    touchedView.setPressed(false);
                    touchedView = null;
                    return true;
            }
            return false;
        }
    }

    //소켓연결 프로토타입
    /*
    //소켓 연결
    void connet(){
        mHandler = new Handler();
        Log.w("connect","연결 하는중");
        // 받아오는거
        Thread checkUpdate = new Thread() {
            public void run() {
                try{
                    socket = new Socket(ip,port);
                    output=new DataOutputStream(socket.getOutputStream());
                }catch (IOException e1) {
                    Log.w("서버접속못함", "서버접속못함");
                    e1.printStackTrace();
                }
                try{
                    output=new DataOutputStream(socket.getOutputStream());
                    output.writeBytes("s");

                }
                catch (IOException e){
                    e.printStackTrace();
                    Log.w("버퍼","버퍼생성잘못됨");
                }
            }
        };
        checkUpdate.start();
    }


    @Override
    protected void onStop()
    {
        super.onStop();
        try {
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        final TextView speedView = findViewById(R.id.speedView);

        SharedPreferences sp = getSharedPreferences("SPEED", MODE_PRIVATE);
        SharedPreferences.Editor editor = sp.edit();
        String tmp = speedView.getText().toString();
        editor.putInt("speed", Integer.parseInt(tmp));

        editor.commit();
    }
*/
}

