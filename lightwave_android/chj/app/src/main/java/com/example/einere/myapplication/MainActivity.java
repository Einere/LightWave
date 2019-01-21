package com.example.einere.myapplication;

import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    String ip = "10.20.22.177";
    SocketManager manager = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i("MainActivity", "onCreate()");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i("MainActivity", "onResume()");

        // get SocketManager instance
        manager = SocketManager.getInstance();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    public void connectToServer(View v) throws RemoteException {
        manager.setSocket(ip);
        manager.connect();
    }

    public void sendData(View v) throws RemoteException, JSONException {
        if(manager.getStatus() == STATUS_CONNECTED){
            JSONObject packet = new JSONObject();
            packet.put("code", 0);
            packet.put("workerName", "CHJ");
            packet.put("location", "KWU");
            manager.send(packet.toString());
        }
        else {
            Toast.makeText(this, "not connected to server", Toast.LENGTH_SHORT).show();
        }
    }

    public void receiveData(View v) throws RemoteException {
        if(manager.getStatus() == STATUS_CONNECTED){
            manager.receive();
        }
        else {
            Toast.makeText(this, "not connected to server", Toast.LENGTH_SHORT).show();
        }

    }
}
