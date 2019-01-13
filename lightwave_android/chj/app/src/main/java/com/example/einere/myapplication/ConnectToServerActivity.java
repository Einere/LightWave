package com.example.einere.myapplication;

import android.app.IntentService;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import java.util.Locale;

public class ConnectToServerActivity extends AppCompatActivity {
    EditText et_ip1 = null;
    EditText et_ip2 = null;
    EditText et_ip3 = null;
    EditText et_ip4 = null;
    EditText et_worker_name = null;

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
        setContentView(R.layout.activity_connect_to_server);
        Log.i("ConnectToServerActivity", "onCreate()");
        // get views
        et_ip1 = findViewById(R.id.et_ip1);
        et_ip2 = findViewById(R.id.et_ip2);
        et_ip3 = findViewById(R.id.et_ip3);
        et_ip4 = findViewById(R.id.et_ip4);
        et_worker_name = findViewById(R.id.et_worker_name);
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i("ConnectToServerActivity", "onResume()");
        // bind service
        Intent intent = new Intent(this, ConnectionService.class);
        intent.setPackage(getPackageName());
        bindService(intent, connection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onPause() {
        super.onPause();

        // unbind service
        unbindService(connection);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    public void onClickConnect(View v){
        String ip = String.format(Locale.KOREA ,"%s.%s.%s.%s", et_ip1.getText(), et_ip2.getText(), et_ip3.getText(), et_ip4.getText());
        try {
            binder.setSocket(ip);
            binder.connect();
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        // go to main activity
        Intent intent = new Intent(this, MainActivity.class);
        intent.putExtra("SERVER_IP", ip);
        startActivity(intent);
    }

    public void onClickDisconnect(View V){
        unbindService(connection);
        Intent intent = new Intent(this, ConnectionService.class);
        intent.setPackage(getPackageName());
        stopService(intent);
    }
}
