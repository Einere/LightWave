package com.example.einere.myapplication;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.i("ConnectToServerActivity", "onServiceConnected()");
            binder = IConnectionService.Stub.asInterface(service);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i("ConnectToServerActivity", "onServiceDisconnected()");
        }
    };
    private IConnectionService binder = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // bind service
        Intent intent = new Intent(this, ConnectionService.class);
        intent.setPackage(getPackageName());
        bindService(intent, connection, BIND_ADJUST_WITH_ACTIVITY);
    }

    public void connectToServer(View v){
        Intent intent = new Intent(this, ConnectToServerActivity.class);
        startActivity(intent);
    }

    public void sendData(View v){
        try {
            binder.send();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public void receiveData(View v){
        try {
            binder.receive();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
