package com.example.einere.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class ListViewActivity  extends AppCompatActivity {

    ListView mListView = null;
    PictureList pictureList = null;
    TextView txt_pictureName = null;
    ArrayList<Picture> mData = null;
    private final int GALLERY_CODE = 1112;



    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview);
        Log.i("activity_listview", "onCreate()");

        mData = new ArrayList<Picture>();

        //작업이력 디렉토리
        String path = Environment.getExternalStorageDirectory()+"/workHistory/task";
        File file = new File(path);



        //작업 리스트 뽑아오기
        String[] taskList = file.list(new FilenameFilter() {
           public boolean accept(File dir, String filename) {
           Boolean bOK = false;
          if(filename.toLowerCase().endsWith(".txt")) bOK = true;
        return bOK;
    }
});

        for(int i = 0; i < taskList.length; i++){
        Picture picture = new Picture();
            String path2 = Environment.getExternalStorageDirectory()+"/workHistory/task/"+taskList[i];
            File file2 = new File(path2);
            if (!file2.exists()) {
                Toast.makeText(this, "작업이 없습니다", Toast.LENGTH_SHORT).show();
                return;
            } else {
                StringBuilder sb = new StringBuilder();
                try {
                    InputStream is = new FileInputStream(path2);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(is));

                    // read line
                    String line = "";
                    while ((line = reader.readLine()) != null) {
                        sb.append(line).append("\n");
                    }

                    // close stream
                    reader.close();
                    is.close();
                    JSONObject parsedData = new JSONObject();
                    try {
                        parsedData = new JSONObject(sb.toString());
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    try {
                        JSONObject data = (JSONObject) parsedData.get("data");

                        picture.landNo=data.getString("landNo");

                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        int idx = taskList[i].indexOf(".");
        picture.taskName = taskList[i].substring(0, idx);
        mData.add(picture);
        }

        pictureList = new PictureList(this, mData);
        mListView = (ListView)findViewById(R.id.List_view);
        mListView.setAdapter(pictureList);

    }
}
