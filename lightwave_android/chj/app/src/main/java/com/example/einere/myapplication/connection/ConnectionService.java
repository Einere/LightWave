package com.example.einere.myapplication.connection;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import com.example.einere.myapplication.IConnectionService;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class ConnectionService extends Service {
    final String TAG = "ConnectionService";
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    final int TIME_OUT = 5000;

    private int status = STATUS_DISCONNECTED;
    private Socket socket = null;
    private SocketAddress socketAddress = null;
    private BufferedReader reader = null;
    private BufferedWriter writer = null;
    private String receivedData = null;
    private Boolean existReceivedData = false;

    IConnectionService.Stub binder = new IConnectionService.Stub() {
        @Override
        public int getStatus() {
            return status;
        }

        @Override
        public void setSocket(String ip, int port) {
            mySetSocket(ip, port);
        }

        @Override
        public void connect() {
            myConnect();
            checkStatus();
        }

        @Override
        public void disconnect() {
            myDisconnect();
        }

        @Override
        public void send(String packet) {
            mySend(packet);
        }

        @Override
        public String receive() {
            String receivedData = myReceive();
            resetReceivedData();
            return receivedData;
        }
    };

    public ConnectionService() {
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i("ConnectionService", "onCreate()");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i("ConnectionService", "onStartCommand()");

        return START_STICKY;
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i("ConnectionService", "onDestroy()");
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        Log.i("ConnectionService", "onBind()");

        return binder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.i("ConnectionService", "onUnbind()");
        return super.onUnbind(intent);
    }

    void mySetSocket(String ip, int port) {
        socketAddress = new InetSocketAddress(ip, port);
        Log.i("ConnectionService", "mySetSocket()");
    }

    void myConnect() {
        Log.i("ConnectionService", "myConnect1()");
        socket = new Socket();
        new Thread(() -> {
            try {
                socket.connect(socketAddress, TIME_OUT);
                writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                status = STATUS_CONNECTED;
                Log.i("ConnectionService", "myConnect2()");
            } catch (IOException e) {
                e.printStackTrace();
                status = STATUS_DISCONNECTED;
            }
        }).start();
    }

    void myDisconnect() {
        try {
            reader.close();
            writer.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        status = STATUS_DISCONNECTED;
    }

    void mySend(String packet) {
        final String myPacket = packet;
        new Thread(() -> {
            Looper.prepare();
            try {
                writer.write(myPacket, 0, myPacket.length());
                writer.flush();
            } catch (IOException e) {
                e.printStackTrace();
                Toast.makeText(ConnectionService.this, "error at send data...", Toast.LENGTH_SHORT).show();
            }
        }).start();
    }

    String myReceive() {
        new Thread(() -> {
            Looper.prepare();
            try{
                Log.d(TAG, "myReceive()'s thread run");
                // polling whether available data is exist...
                // !Thread.currentThread().isInterrupted() &&
                while((receivedData = reader.readLine()) != null){
                    existReceivedData = true;
                    Log.d(TAG, String.format("read data : %s", receivedData));
                }
                Log.d(TAG, "myReceive()'s thread exit while loop");
            }
            catch (IOException e){
                e.printStackTrace();
                Log.d(TAG, "myReceive()'s thread error");
            }
        }).start();

        for(int i = 0; i < 5; i++){
            if(existReceivedData){
                break;
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Log.d(TAG, "no received data, waiting...");
        }
        Log.d(TAG, String.format("myReceive() result : %s", receivedData));
        return receivedData;
    }

    void checkStatus(){
        new Thread(() -> {
            while(status == STATUS_DISCONNECTED){
                try{
                    if(socket.isClosed()){
                        socket.connect(socketAddress, TIME_OUT);
                        writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        status = STATUS_CONNECTED;
                        Log.i("ConnectionService", "myConnect2()");
                    }
                }
                catch(IOException e) {
                    e.printStackTrace();
                    status = STATUS_DISCONNECTED;
                }
            }
        }).start();
    }

    void resetReceivedData(){
        existReceivedData = false;
        receivedData = null;
    }
}
