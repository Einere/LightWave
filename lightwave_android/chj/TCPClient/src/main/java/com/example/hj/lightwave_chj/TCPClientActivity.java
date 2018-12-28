package com.example.hj.lightwave_chj;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class TCPClientActivity extends AppCompatActivity {
    private Handler mainHandler = null;
    private Looper looper = null;
    private ServiceHandler serviceHandler = null;
    private HandlerThread thread = null;

    private TCPClient client = null;
    private Socket socket = null;
    private BufferedReader reader = null;
    private BufferedWriter writer = null;

    // views
    private EditText etIp = null;
    private EditText etPort = null;
    private EditText etMessage = null;
    private Button btnConnect = null;
    private Button btnDisconnect = null;
    private Button btnSend = null;
    private TextView tvMessage = null;

    private String ip = null;
    private int port = 6000;
    private final String TAG = "TCPClientActivity";
    private boolean connected = false;

    // constant
    public static final int MSG_CONNECT = 1;
    public static final int MSG_STOP = 2;
    public static final int MSG_CLIENT_STOP = 3;
    public static final int MSG_SERVER_STOP = 4;
    public static final int MSG_START = 5;
    public static final int MSG_ERROR = 6;


    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // get views
        etIp = findViewById(R.id.et_ip);
        etPort = findViewById(R.id.et_client_port);
        etMessage = findViewById(R.id.et_message);
        btnConnect = findViewById(R.id.bt_connect);
        btnDisconnect = findViewById(R.id.bt_disconnect);
        btnSend = findViewById(R.id.bt_send);
        tvMessage = findViewById(R.id.tv_message);

        // set button enable
        setButtonEnable();

        // make thread, start
        thread = new HandlerThread("HandlerThread");
        thread.start();

        // get looper
        looper = thread.getLooper();

        // get service handler
        serviceHandler = new ServiceHandler(looper);

        // make main handler
        mainHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);

                String m = null;
                switch (msg.what) {
                    case MSG_CONNECT: {
                        m = "connected to server";
                        connected = true;
                        setButtonEnable();
                        tvMessage.setText(m);
                        break;
                    }
                    case MSG_CLIENT_STOP: {
                        tvMessage.setText((String) msg.obj);
                        connected = false;
                        setButtonEnable();
                        m = "disconnected by client";
                        break;
                    }
                    case MSG_SERVER_STOP: {
                        tvMessage.setText((String) msg.obj);
                        connected = false;
                        setButtonEnable();
                        m = "disconnected by server";
                        break;
                    }
                    case MSG_START: {
                        m = "success to send";
                        tvMessage.setText((String) msg.obj);
                        break;
                    }
                    default: {
                        m = "error occur";
                        tvMessage.setText((String) msg.obj);
                        break;
                    }
                }
                Toast.makeText(TCPClientActivity.this, m, Toast.LENGTH_SHORT).show();
            }
        };

        // request
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private void setButtonEnable() {
        if (connected) {
            btnConnect.setEnabled(false);
            btnDisconnect.setEnabled(true);
            btnSend.setEnabled(true);
        } else {
            btnConnect.setEnabled(true);
            btnDisconnect.setEnabled(false);
            btnSend.setEnabled(false);
        }
    }

    public void connectClicked(View v) {
        ip = etIp.getText().toString();
        try {
            port = Integer.parseInt(etPort.getText().toString());
        } catch (NumberFormatException e) {
            port = 6000;
            Log.d(TAG, "port number", e);
        }

        if (client == null) {
            try {
                // make thread
                client = new TCPClient(ip, port);
                client.start();
            } catch (Exception e) {
                tvMessage.setText("wrong ip or port");
                Log.d(TAG, "error occur", e);
            }
        }
    }

    public void disconnectClicked(View v) {
        if (client != null) {
            // terminate thread
            serviceHandler.sendEmptyMessage(MSG_CLIENT_STOP);
        }
    }

    public void sendClicked(View v) {
        // get sending message from EditText
        String sendingMessage = etMessage.getText().toString();

        if (!sendingMessage.equals("")) {
            Message msg = serviceHandler.obtainMessage();
            msg.what = MSG_START;
            msg.obj = sendingMessage;
            serviceHandler.sendMessage(msg);
        }
    }

    // send message to server
    class ServiceHandler extends Handler {
        ServiceHandler(Looper looper){
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            switch (msg.what){
                case MSG_START:{
                    Message message = mainHandler.obtainMessage();
                    try{
                        writer.write((String)msg.obj);
                        writer.newLine();
                        writer.flush();
                        message.what = MSG_START;
                    }
                    catch (IOException e){
                        message.what = MSG_ERROR;
                        Log.d(TAG, "error occur", e);
                    }
                    message.obj = msg.obj;
                    mainHandler.sendMessage(message);
                    break;
                }
                case MSG_STOP:{

                }
                case MSG_CLIENT_STOP:{

                }
                case MSG_SERVER_STOP:{
                    // if call quit method in main thread, exception occur
                    client.quit();
                    client = null;
                    break;
                }
            }
        }
    }

    // connect to server, receive message from server
    class TCPClient extends Thread {
        boolean loop = false;
        SocketAddress socketAddress = null;
        String line = null;
        private final int timeout = 6000;

        public TCPClient(String ip, int port) {
            // make socket address
            socketAddress = new InetSocketAddress(ip, port);
        }

        @Override
        public void run() {
            super.run();

            try {
                // make socket
                socket = new Socket();
                socket.setSoTimeout(timeout);
                socket.setSoLinger(true, timeout);

                // connect to server
                socket.connect(socketAddress, timeout);

                // if connected, execute below line
                // get reader & writer
                writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                // make message
                Message msg = mainHandler.obtainMessage();
                msg.what = MSG_CONNECT;
                mainHandler.sendMessage(msg);

                loop = true;
            } catch (Exception e) {
                loop = false;

                Log.d(TAG, "error occur", e);
                Message msg = mainHandler.obtainMessage();
                msg.what = MSG_ERROR;
                msg.obj = "can't crate socket";
                mainHandler.sendMessage(msg);
            }

            while (loop) {
                try {
                    // read message from socket stream
                    line = reader.readLine();

                    // if FIN packet
                    if (line == null) {
                        break;
                    }

                    // render activity using Runnable
                    Runnable renderer = new Runnable() {
                        @Override
                        public void run() {
                            tvMessage.setText(line);
                        }
                    };
                    mainHandler.post(renderer);
                } catch (IOException e) {
                    Log.d(TAG, "error occur", e);
                    break;
                }
            }

            // if disconnected (break while loop)
            try {
                if (writer != null) {
                    writer.close();
                    writer = null;
                }
                if (reader != null) {
                    reader.close();
                    reader = null;
                }
                if (socket != null) {
                    socket.close();
                    socket = null;
                }
                client = null;

                // if disconnect by server
                if (loop) {
                    loop = false;
                    Message msg = mainHandler.obtainMessage();
                    msg.what = MSG_SERVER_STOP;
                    msg.obj = "disconnected by server";
                    mainHandler.sendMessage(msg);
                }
            } catch (IOException e) {
                Log.d(TAG, "error occur", e);
                Message msg = mainHandler.obtainMessage();
                msg.what = MSG_ERROR;
                msg.obj = "can't close socket";
                mainHandler.sendMessage(msg);
            }
        }

        public void quit() {
            loop = false;
            try {
                if (socket != null) {
                    socket.close();
                    socket = null;
                    Message msg = mainHandler.obtainMessage();
                    msg.what = MSG_CLIENT_STOP;
                    msg.obj = "disconnected by client";
                    mainHandler.sendMessage(msg);
                }
            } catch (IOException e) {
                Log.d(TAG, "error occur", e);
            }
        }
    }
}
