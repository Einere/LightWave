package com.example.myapplication;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.LinkAddress;
import android.net.LinkProperties;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.os.Build;
import android.os.Handler;
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
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.InterruptedIOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

public class TCPServerActivity extends AppCompatActivity {
    private final String TAG = "TCPServerActivity";
    private Handler handler;

    // manage for clients connected to server
    private ArrayList<EchoThread> threadList = null;
    private ReentrantLock lock = null;
    private ServerThread thread = null;

    // constant
    protected static final int MSG_ID = 1;
    protected static final int QUIT_ID = 2;
    private int port = 6000;

    // views
    private Button btStart = null;
    private Button btStop = null;
    private TextView tvLog = null;
    private EditText etPort = null;


    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // get views
        btStart = findViewById(R.id.bt_start);
        btStop = findViewById(R.id.bt_stop);
        tvLog = findViewById(R.id.tv_server_log);
        etPort = findViewById(R.id.et_server_port);
        btStart.setEnabled(true);
        btStop.setEnabled(false);

        // set handler
        handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case MSG_ID: {
                        tvLog.append((String) msg.obj + "\n");
                        break;
                    }
                    case QUIT_ID: {
                        tvLog.setText((String) msg.obj);
                        btStart.setEnabled(true);
                        btStop.setEnabled(false);
                        Toast.makeText(TCPServerActivity.this, (String) msg.obj, Toast.LENGTH_SHORT).show();
                        break;
                    }
                    default: {
                        break;
                    }
                }
                super.handleMessage(msg);
            }
        };

        // show ip address
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            initialNetwork();
        } else {
//            displayIPAddress();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if (thread != null) {
            // make new thread to terminate work thread without activity's state
            new Thread() {
                @Override
                public void run() {
                    thread.quit();
                    thread = null;
                }
            }.start();
        }
    }

    public void onClickStart(View v) {
        // set port number
        try {
            port = Integer.parseInt(etPort.getText().toString());
        } catch (NumberFormatException e) {
            port = 6000;
        }

        // start server thread
        if (thread == null) {
            try {
                thread = new ServerThread(port);
                thread.start();
                tvLog.setText("service thread is started.\n");
                btStart.setEnabled(false);
                btStop.setEnabled(true);
            } catch (IOException e) {
                tvLog.setText("service thread can't be started.\n");
            }
        } else {
            Toast.makeText(this, "service thread is running", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickStop(View v) {
        if (thread != null) {
            btStop.setEnabled(false);

            new Thread() {
                @Override
                public void run() {
                    thread.quit();

                    try {
                        sleep(500);
                        if (thread.isAlive()) {
                            sleep(2000);
                        }
                    } catch (InterruptedException e) {
                        Log.e(TAG, "error occur", e);
                    }

                    thread = null;
                    Message m = new Message();
                    m.what = QUIT_ID;
                    m.obj = ("service is stopped");
                    handler.sendMessage(m);
                }
            }.start();
        }
    }

    @TargetApi(Build.VERSION_CODES.M)
    private void initialNetwork() {
        final ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkRequest.Builder builder = new NetworkRequest.Builder();

        builder.addCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET);
        NetworkRequest request = builder.build();
        ConnectivityManager.NetworkCallback callback = new ConnectivityManager.NetworkCallback() {
            @Override
            public void onAvailable(Network network) {
                super.onAvailable(network);

                cm.unregisterNetworkCallback(this);

                // print ip address
                LinkProperties lp = cm.getLinkProperties(network);
                List<LinkAddress> link = lp.getLinkAddresses();

                for (LinkAddress la : link) {
                    InetAddress address = la.getAddress();

                    // if loopback
                    if (address.isLoopbackAddress()) continue;

                    // if IPv4, send ip to main thread
                    if (address instanceof Inet4Address) {
                        Message m = new Message();
                        m.what = MSG_ID;
                        m.obj = (String) (lp.getInterfaceName() + "'s ip : " + address.getHostAddress());
                        handler.sendMessage(m);
                    }
                }
            }
        };

        if (cm != null) {
            cm.registerNetworkCallback(request, callback);
            cm.requestNetwork(request, callback);
        }
    }

    class ServerThread extends Thread {
        private boolean loop = false;
        private ServerSocket server = null;

        ServerThread(int port) throws IOException {
            super();

            // make server socket
            server = new ServerSocket(port);
            server.setSoTimeout(3000);

            threadList = new ArrayList<EchoThread>();
            lock = new ReentrantLock();
            loop = true;
        }

        @Override
        public void run() {
            while (loop) {
                try {
                    Log.d(TAG, "AAAA");
                    // accept, get client socket
                    Socket sock = server.accept();
                    EchoThread thread = new EchoThread(sock);
                    thread.start();

                    // add client socket to list
                    lock.lock();
                    threadList.add(thread);
                    lock.unlock();
                } catch (InterruptedIOException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    Message m = new Message();
                    m.what = QUIT_ID;
                    m.obj = ("error occur in server thread");
                    handler.sendMessage(m);
                    break;
                }
            }

            // if loop is false, close server socket
            try {
                if (server != null) {
                    server.close();
                    server = null;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        void quit() {
            clearList();
            loop = false;
        }

        void clearList() {
            if (!threadList.isEmpty()) {
                lock.lock();
                for (EchoThread thread : threadList) {
                    thread.quit();
                }
                lock.unlock();
            }
        }
    }

    class EchoThread extends Thread {
        private Socket sock = null;
        private InetAddress inetAddress = null;

        private OutputStream out = null;
        private InputStream in = null;
        private PrintWriter pw = null;
        private BufferedReader br = null;

        EchoThread(Socket sock) {
            this.sock = sock;
        }

        @Override
        public void run() {
            try {
                // get address
                inetAddress = sock.getInetAddress();

                // send message to main thread
                Message m = new Message();
                m.what = MSG_ID;
                m.obj = ("connected from " + inetAddress.getHostAddress());
                handler.sendMessage(m);

                // get stream
                out = sock.getOutputStream();
                in = sock.getInputStream();
                pw = new PrintWriter(new OutputStreamWriter(out));
                br = new BufferedReader(new InputStreamReader(in));
            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                // read data from client
                String line = null;
                while ((line = br.readLine()) != null) {
                    // send read data to client
                    pw.println(line);
                    pw.flush();

                    // send message to main thread
                    Message m2 = new Message();
                    m2.what = MSG_ID;
                    m2.obj = line;
                    handler.sendMessage(m2);
                }
            } catch (InterruptedIOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                Log.e(TAG, "error occur..." + e);
            } finally {
                // send message to main thread
                Message m3 = new Message();
                m3.what = MSG_ID;
                m3.obj = ("disconnected from " + inetAddress.getHostAddress());
                handler.sendMessage(m3);

                // free resource
                try {
                    lock.lock();
                    threadList.remove(this);
                    lock.unlock();

                    if (sock != null) {
                        sock.close();
                        sock = null;
                    }
                    if (pw != null) {
                        pw.close();
                        pw = null;
                    }
                    if (br != null) {
                        br.close();
                        br = null;
                    }
                } catch (Exception e) {
                    Log.e(TAG, "error occur" + e);
                }

            }
        }

        void quit() {
            if (sock != null) {
                try {
                    sock.close();
                    sock = null;
                } catch (IOException e) {
                    Log.e(TAG, "error occur" + e);
                }
            }
        }
    }

}
