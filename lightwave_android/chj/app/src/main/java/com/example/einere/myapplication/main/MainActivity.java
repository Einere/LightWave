package com.example.einere.myapplication.main;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.capture.CaptureActivity;
import com.example.einere.myapplication.history.TaskHistoryListActivity;
import com.example.einere.myapplication.socket.SocketManager;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    private final String TAG = "MainActivity";
    private SocketManager socketManager = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(TAG, "onCreate()");

        // set listener
        findViewById(R.id.btn_new_capture).setOnClickListener(v -> goToNewCapture());
        findViewById(R.id.btn_continue_capture).setOnClickListener(v -> goToContinueCapture());
//        findViewById(R.id.btn_check_history).setOnClickListener(v -> goToCheckHistory());
    }

    @Override
    protected void onResume() {
        super.onResume();

        // get socket manager
        socketManager = SocketManager.getInstance();
        Log.i(TAG, "onResume()");
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    public void goToNewCapture() {
        // request work data to server
        JSONObject packet = new JSONObject();
        try {
            packet.put("method", "GET");
            packet.put("subject", "task");
            socketManager.send(packet.toString());
        } catch (JSONException e) {
            Toast.makeText(this, "error at make json...", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        } catch (RemoteException e) {
            Toast.makeText(this, "maybe socket error...", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }

        // receive & parse requested data
        String receivedData = null;
        try {
            receivedData = socketManager.receive();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        Log.d(TAG, String.format("received data : %s", receivedData));

        JSONObject parsedData;
        try {
            parsedData = new JSONObject(receivedData);

            // check status
            if (parsedData.getInt("status") == 2) {
                // go to CaptureActivity
                Intent intent = new Intent(this, CaptureActivity.class);
                intent.putExtra("method", "new");
                try {
                    JSONObject data = (JSONObject) parsedData.get("data");
                    // work id
                    intent.putExtra("id", data.getString("id"));
                    // work name
                    intent.putExtra("taskName", data.getString("taskName"));
                    // location number
                    intent.putExtra("landNo", data.getString("landNo"));
                    // work information (memo?)
                    intent.putExtra("taskDesc", data.getString("taskDesc"));
                    // receivedData
                    intent.putExtra("receivedData", receivedData);
                } catch (Exception e) {
                    e.printStackTrace();
                }

                startActivity(intent);
            } else {
                Toast.makeText(this, String.format("서버로부터 비정상적인 데이터를 수신했습니다. %s", parsedData.getString("message")), Toast.LENGTH_SHORT).show();
            }
        } catch (NullPointerException e) {
            Toast.makeText(this, "서버로부터 데이터를 받지 못했습니다.", Toast.LENGTH_SHORT).show();
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public void goToContinueCapture() {
        Intent intent = new Intent(this, CaptureActivity.class);
        intent.putExtra("method", "new");
        String path = Environment.getExternalStorageDirectory() + "/workHistory/beforeHistory.txt";
        File file = new File(path);
        if (!file.exists()) {
            Toast.makeText(this, "전 작업이 없습니다", Toast.LENGTH_SHORT).show();
        } else {
            StringBuilder sb = new StringBuilder();
            try {
                InputStream is = new FileInputStream(path);
                BufferedReader reader = new BufferedReader(new InputStreamReader(is));

                // read line
                String line;
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
                    // work id
                    intent.putExtra("id", data.getString("id"));
                    // work name
                    intent.putExtra("taskName", data.getString("taskName"));
                    // location number
                    intent.putExtra("landNo", data.getString("landNo"));
                    // work information (memo?)
                    intent.putExtra("taskDesc", data.getString("taskDesc"));
                    // receivedData
                    intent.putExtra("receivedData", sb.toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }

                startActivity(intent);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void goToCheckHistory() {
        Intent intent = new Intent(this, TaskHistoryListActivity.class);
        startActivity(intent);
    }
}
