package com.example.einere.myapplication.main;

import android.content.Intent;
import android.os.Bundle;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.SocketManager;
import com.example.einere.myapplication.capture.CaptureActivity;

import org.json.JSONException;
import org.json.JSONObject;

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
        findViewById(R.id.btn_check_history).setOnClickListener(v -> goToCheckHistory());
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
        try{
            packet.put("method", "GET");
            packet.put("subject", "task");
            socketManager.send(packet.toString());
        }
        catch (JSONException e){
            Toast.makeText(this, "error at make json...", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }
        catch (RemoteException e){
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


        // go to CaptureActivity
        Intent intent = new Intent(this, CaptureActivity.class);
        intent.putExtra("method", "new");
        startActivity(intent);
    }

    public void goToContinueCapture() {
        Intent intent = new Intent(this, CaptureActivity.class);
        intent.putExtra("method", "continue");
        startActivity(intent);
    }

    public void goToCheckHistory() {
//        Intent intent = new Intent(this, CaptureActivity.class);
//        startActivity(intent);
    }
}
