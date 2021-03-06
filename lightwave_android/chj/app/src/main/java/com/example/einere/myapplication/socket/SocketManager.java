package com.example.einere.myapplication.socket;

import android.app.Application;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.example.einere.myapplication.IConnectionService;

public class SocketManager extends Application {
    private static final SocketManager instance = new SocketManager();
    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.i("SocketManager", "onServiceConnected()");
            binder = IConnectionService.Stub.asInterface(service);
            // we use instance, need to set instance's binder
            instance.setBinder(binder);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i("SocketManager", "onServiceDisconnected()");
        }
    };
    private IConnectionService binder = null;
    private String userName = "unknown";

    public SocketManager() {
        Log.i("SocketManager", "SocketManager()");
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i("SocketManager", "onCreate()");

        // get context
        Context context = getApplicationContext();

        // bind service
        Intent intent = new Intent(context, SocketService.class);
        context.bindService(intent, connection, BIND_AUTO_CREATE);
    }

    public static SocketManager getInstance() {
        return instance;
    }

    public void setBinder(IConnectionService binder) {
        this.binder = binder;
    }

    public int getStatus() throws RemoteException {
        return binder.getStatus();
    }

    public void setSocket(String ip, int port) throws RemoteException {
        binder.setSocket(ip, port);
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public void connect() throws RemoteException {
        binder.connect();

    }

    public void disconnect() throws RemoteException {
        binder.disconnect();
    }

    public void send(String packet) throws RemoteException {
        binder.send(packet);
    }

    public String receive() throws RemoteException {
        return binder.receive();
    }
}
