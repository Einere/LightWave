package com.example.jun.juntest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    public static String SERV_IP = null;
    EditText et_ip1, et_ip2, et_ip3, et_ip4;
    private TCP_Client tc;
    private boolean tcon = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et_ip1 = (EditText) findViewById(R.id.et_ip1);
        et_ip2 = (EditText) findViewById(R.id.et_ip2);
        et_ip3 = (EditText) findViewById(R.id.et_ip3);
        et_ip4 = (EditText) findViewById(R.id.et_ip4);
    }

    // 함수명 변경이 좋을 듯. ex) onClickConnect
    public void myclick(View v) {
        SERV_IP = et_ip1.getText().toString() + "." + et_ip2.getText().toString() + "." + et_ip3.getText().toString() + "." +
                et_ip4.getText().toString();
        tcon = true;
        tc = new TCP_Client();
        tc.execute(this);
    }

    // 함수명 변경이 좋을 듯. ex) onClickDisconnect
    public void cancleclick(View v) {
        if (tcon) {
            tc.onCancelled();
            tcon = false;
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (tcon) {
            tc.onCancelled();
        }
    }
}
