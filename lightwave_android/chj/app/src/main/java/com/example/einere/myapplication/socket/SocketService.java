package com.example.einere.myapplication.socket;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.util.ArrayMap;
import android.util.Log;
import android.widget.Toast;

import com.example.einere.myapplication.IConnectionService;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.Locale;

public class SocketService extends Service {
    final String TAG = "SocketService";
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    final int TIME_OUT = 5000;
    final int SOCKET_SEND_COMPLETE = 10;
    final int SOCKET_RECEIVE_COMPLETE = 11;
    final int SOCKET_BUFFER_SIZE = 1024 * 10;

    private int status = STATUS_DISCONNECTED;
    private Socket socket = null;
    private SocketAddress socketAddress = null;
    private BufferedReader reader = null;
    private BufferedWriter writer = null;
    private DataOutputStream dosWriter = null;
    private OutputStreamWriter osr = null;
    private String receivedData = null;
    private Boolean existReceivedData = false;

    private ArrayMap<Long, Thread> sendThreadList = new ArrayMap<>();
    private Thread receiveThread = null;
    private Handler handler;

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

    public SocketService() {
        handler = new SocketHandler(sendThreadList, receiveThread);
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i("SocketService", "onCreate()");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i("SocketService", "onStartCommand()");

        return START_STICKY;
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i("SocketService", "onDestroy()");
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        Log.i("SocketService", "onBind()");

        return binder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.i("SocketService", "onUnbind()");
        return super.onUnbind(intent);
    }

    void mySetSocket(String ip, int port) {
        socketAddress = new InetSocketAddress(ip, port);
        Log.i("SocketService", "mySetSocket()");
    }

    void myConnect() {
        Log.i("SocketService", "myConnect1()");
        socket = new Socket();
        new Thread(() -> {
            try {
                socket.connect(socketAddress, TIME_OUT);
                osr = new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8);
                writer = new BufferedWriter(osr);
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
                dosWriter = new DataOutputStream(socket.getOutputStream());

                status = STATUS_CONNECTED;
                Log.i("SocketService", "myConnect2()");
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

        Thread thread = new Thread(() -> {
            Log.d(TAG, String.format("[%d] send data thread start...", Thread.currentThread().getId()));
            Looper.prepare();
            for (int i = 0; i * 1024 < myPacket.length(); i++) {
                try {
                    if (myPacket.length() - i * 1024 < 1024) {
                        writer.write(myPacket, i * 1024, myPacket.length() - i * 1024);
                    } else {
                        writer.write(myPacket, i * 1024, 1024);
                    }
                    writer.flush();
                    Log.d(TAG, String.format("[%d] send data thread offset : %d...", Thread.currentThread().getId(), i * 1024));
                } catch (IOException e) {
                    e.printStackTrace();
                    Toast.makeText(SocketService.this, "error at send data...", Toast.LENGTH_SHORT).show();
                }
            }

            // make message
            Log.d(TAG, String.format(Locale.KOREA, "[%d] make message start", Thread.currentThread().getId()));
            Message message = handler.obtainMessage();
            message.what = SOCKET_SEND_COMPLETE;
            message.arg1 = (int) Thread.currentThread().getId();
            handler.sendMessage(message);
            Log.d(TAG, String.format(Locale.KOREA, "[%d] make message end", Thread.currentThread().getId()));
        });

        sendThreadList.put(thread.getId(), thread);
        Log.d(TAG, String.format("[%d] assign send thread...", Thread.currentThread().getId()));
        thread.start();
    }

    String myReceive() {
        // make receiving thread
        if (receiveThread == null) {
            receiveThread = new Thread(() -> {
                Looper.prepare();
                try {
                    Log.d(TAG, "myReceive()'s thread run");
                    // polling whether available data is exist...
                    // !Thread.currentThread().isInterrupted() &&
                    while ((receivedData = reader.readLine()) != null) {
                        existReceivedData = true;
                        Log.d(TAG, String.format("[%d] read data : %s...", Thread.currentThread().getId(), receivedData));
                        Log.d(TAG, String.format("[%d] read data length : %d...", Thread.currentThread().getId(), receivedData.length()));

                    }
                    Log.d(TAG, "myReceive()'s thread exit while loop");
                } catch (Exception e) {
                    e.printStackTrace();
                    Log.d(TAG, "myReceive()'s thread error");
                }

                // make message
                Message message = handler.obtainMessage();
                message.what = SOCKET_RECEIVE_COMPLETE;
                handler.sendMessage(message);
            });
            Log.d(TAG, "receiving thread assign!!");
        }

        // if thread is not alive
        if (!receiveThread.isAlive()) {
            receiveThread.start();
            Log.d(TAG, "receiving thread start!!");
        }

        for (int i = 0; i < 5; i++) {
            if (existReceivedData) {
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

    void checkStatus() {
        new Thread(() -> {
            while (status == STATUS_DISCONNECTED) {
                try {
                    if (socket.isClosed()) {
                        socket.connect(socketAddress, TIME_OUT);
                        writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8));
                        reader = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
                        status = STATUS_CONNECTED;
                        Log.i("SocketService", "myConnect2()");
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    status = STATUS_DISCONNECTED;
                }
            }
        }).start();
    }

    void resetReceivedData() {
        Log.d(TAG, "resetReceivedData call");
        existReceivedData = false;
        receivedData = null;
        Log.d(TAG, "resetReceivedData end");
    }

    // because of memory leak, need to declare static class...
    static class SocketHandler extends Handler {
        private final String TAG = "SocketHandler";
        final int SOCKET_SEND_COMPLETE = 10;
        final int SOCKET_RECEIVE_COMPLETE = 11;

        private ArrayMap<Long, Thread> sendThreadList;
        private Thread receiveThread;

        SocketHandler(ArrayMap<Long, Thread> sendThreadList, Thread receiveThread) {
            this.sendThreadList = sendThreadList;
            this.receiveThread = receiveThread;
        }

        @Override
        public void handleMessage(Message msg) {
            Log.d(TAG, "handle message start");
            switch (msg.what) {
                case SOCKET_SEND_COMPLETE: {
                    // kill send thread
                    Thread sendThread = sendThreadList.remove((long) msg.arg1);
                    if (sendThread != null) {
                        sendThread.interrupt();
                    }
                    Log.d(TAG, String.format(Locale.KOREA, "[%d]kill sending thread", msg.arg1));
                }
                case SOCKET_RECEIVE_COMPLETE: {
                    // kill receiving thread
                    if (receiveThread != null) {
                        receiveThread.interrupt();
                    }
                    Log.d(TAG, "kill receiving thread");
                }
            }

        }
    }
}
