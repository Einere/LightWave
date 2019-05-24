package com.example.einere.myapplication.history;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.einere.myapplication.R;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class TaskHistoryListActivity extends AppCompatActivity {

    ListView mListView = null;
    TaskHistoryList taskHistoryList = null;
    TextView txt_taskName = null;
    ArrayList<Task> mData = null;
    private final int GALLERY_CODE = 1112;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview);
        Log.i("activity_listview", "onCreate()");

        mData = new ArrayList<>();

        //작업이력 디렉토리
        String path = Environment.getExternalStorageDirectory() + "/workHistory/task";
        File file = new File(path);


        //작업 리스트 뽑아오기
        String[] taskList = file.list((dir, filename) -> {
            Boolean bOK = false;
            if (filename.toLowerCase().endsWith(".txt")) bOK = true;
            return bOK;
        });

        for (String s : taskList) {
            Task task = new Task();
            String path2 = Environment.getExternalStorageDirectory() + "/workHistory/task/" + s;
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
                    String line;
                    while ((line = reader.readLine()) != null) {
                        sb.append(line).append("\n");
                    }

                    // close stream
                    reader.close();
                    is.close();

                    // parse history
                    JSONObject parsedData = new JSONObject(sb.toString());
                    JSONObject data = (JSONObject) parsedData.get("data");
                    task.landNo = data.getString("landNo");
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }

            // save file name
            task.taskName = s.split("\\.")[0];
            mData.add(task);
        }

        taskHistoryList = new TaskHistoryList(this, mData);
        mListView = findViewById(R.id.List_view);
        mListView.setAdapter(taskHistoryList);
    }
}
