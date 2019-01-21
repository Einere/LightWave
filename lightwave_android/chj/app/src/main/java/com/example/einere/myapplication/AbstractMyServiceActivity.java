package com.example.einere.myapplication;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

public class AbstractMyServiceActivity extends AppCompatActivity {
    private volatile ConnectionService myService = null;
    private volatile boolean puased = false;

    private final ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.i("AMSActivity", "onServiceConnected()");
            binder = IConnectionService.Stub.asInterface(service);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i("AMSActivity", "onServiceDisconnected()");
        }
    };
    private IConnectionService binder = null;
}
