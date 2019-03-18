package com.example.einere.myapplication.connection;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;

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
            return myReceive();
        }
    };

    /*class ReceiveThread extends AsyncTask<Boolean, String, Boolean> {
        public ReceiveThread() {
            super();
        }

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected Boolean doInBackground(Boolean... booleans) {
            try {
                while (reader.ready()) {
                    String packet = reader.readLine();
                    onProgressUpdate(packet);
                }
            }catch(IOException e){
                e.printStackTrace();
            }

            return null;
        }

        @Override
        protected void onProgressUpdate(String... values) {
            Toast.makeText(ConnectionService.this, values[0], Toast.LENGTH_SHORT).show();
            super.onProgressUpdate(values);
        }

        @Override
        protected void onPostExecute(Boolean aBoolean) {
            super.onPostExecute(aBoolean);
        }

        @Override
        protected void onCancelled(Boolean aBoolean) {
            super.onCancelled(aBoolean);
        }
    }*/

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
        new Thread(new Runnable() {
            @Override
            public void run() {
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
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    writer.write(myPacket, 0, myPacket.length());
                    writer.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            existReceivedData = true;
            super.handleMessage(msg);
        }
    };

    String myReceive() {
        /*ReceiveThread receiveThread = new ReceiveThread();
        receiveThread.execute(true);*/
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    // polling whether available data is exist...
                    while(!Thread.currentThread().isInterrupted() && (receivedData = reader.readLine()) != null){
                        Message message = new Message();
                        handler.sendMessage(message);
                        existReceivedData = true;
                    }
                }
                catch (IOException e){
                    e.printStackTrace();
                }
            }
        }).start();

        /*while(!existReceivedData){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }*/
        for(int i = 0; i < 3; i++){
            if(!existReceivedData){
                break;
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        return receivedData;
    }
}
