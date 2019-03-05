package com.example.einere.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashMap;

public class MemoActivity extends AppCompatActivity {

    private EditText mMemoEdit = null;
    private String txt_filename = null;
    private File file = null;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_memo);
        Log.i("activity_memo", "onCreate()");
        mMemoEdit = (EditText) findViewById(R.id.et_memo);

        //텍스트파일명 받아오기
        Intent intent = getIntent();
        Bundle bundleData = intent.getBundleExtra("TXT_FILE");
        txt_filename = bundleData.getString("txt_File");

        //추후에 점에 따라 디렉토리명 바꿈
        String path = Environment.getExternalStorageDirectory()+"/path/"+txt_filename;
        file = new File(path);

        //메모 불러오기
        if(!file.exists()){
        }else{
            StringBuffer strBuffer = new StringBuffer();
            try{
                InputStream is = new FileInputStream(path);
                BufferedReader reader = new BufferedReader(new InputStreamReader(is));
                String line="";
                while((line=reader.readLine())!=null){
                    strBuffer.append(line+"\n");
                }
                reader.close();
                is.close();
                mMemoEdit.setText(strBuffer.toString());
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_save: {
                String memoStr = mMemoEdit.getText().toString();
                try{
                    if(!file.exists()) {
                        try {
                            FileOutputStream fos = new FileOutputStream(file);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    FileOutputStream fos = new FileOutputStream(file);
                    BufferedWriter buw = new BufferedWriter(new OutputStreamWriter(fos, "UTF8"));
                    buw.write(memoStr);
                    buw.close();
                    fos.close();
                    Toast.makeText(this, "저장완료", Toast.LENGTH_SHORT).show();
                }catch(IOException e){
                    e.printStackTrace();
                }
                Toast.makeText(this, "저장 완료", Toast.LENGTH_LONG).show();
                break;
            }
            case R.id.btn_delete: {
                mMemoEdit.setText("");
                file.delete();
                Toast.makeText(this, "삭제 완료", Toast.LENGTH_LONG).show();
                break;
            }
        }
    }
}