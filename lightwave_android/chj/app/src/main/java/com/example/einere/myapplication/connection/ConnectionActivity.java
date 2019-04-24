package com.example.einere.myapplication.connection;

import android.Manifest;
import android.content.Intent;
import android.os.Bundle;
import android.os.RemoteException;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.PopupMenu;
import android.widget.Toast;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.SocketManager;
import com.example.einere.myapplication.main.MainActivity;

import org.json.JSONException;
import org.json.JSONObject;

public class ConnectionActivity extends AppCompatActivity {
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    final int STATUS_NORMAL = 2;
    final int STATUS_ABNORMAL = 4;
    private final String TAG = "ConnectionActivity";

    // for socket transmission
    String ip = "";
    int port = 0;
    String userName = null;
    SocketManager socketManager = null;

    // views
    EditText et_ip1 = null;
    EditText et_ip2 = null;
    EditText et_ip3 = null;
    EditText et_ip4 = null;
    EditText et_port = null;
    EditText et_user_name = null;
    Button btn_connect_to_server = null;
    Button btn_pop_up_menu = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connection);
        Log.i(TAG, "onCreate()");

        // get views
        et_ip1 = findViewById(R.id.et_ip1);
        et_ip2 = findViewById(R.id.et_ip2);
        et_ip3 = findViewById(R.id.et_ip3);
        et_ip4 = findViewById(R.id.et_ip4);
        et_port = findViewById(R.id.et_port);
        et_user_name = findViewById(R.id.et_user_name);
        btn_connect_to_server = findViewById(R.id.btn_connect_to_server);
        btn_pop_up_menu = findViewById(R.id.btn_pop_up_menu);

        // request permission
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.CAMERA,
                Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 0);

        // register event listener
        btn_connect_to_server.setOnClickListener(v -> {
            try {
                connectToServer();
            } catch (RemoteException e) {
                Toast.makeText(this, "connection failed...", Toast.LENGTH_SHORT).show();
            }
        });
        btn_pop_up_menu.setOnClickListener(v -> popup());
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i(TAG, "onResume()");

        // get SocketManager instance
        socketManager = SocketManager.getInstance();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    public void connectToServer() throws RemoteException {
        // get ip, user name from EditText
        ip = String.format("%s.%s.%s.%s", et_ip1.getText(), et_ip2.getText(), et_ip3.getText(), et_ip4.getText());
        port = Integer.parseInt(et_port.getText().toString());
        userName = et_user_name.getText().toString();

        // set socket and connect to server
        socketManager.setSocket(ip, port);
        socketManager.connect();

        // send user name to server
        // notice to server that connected mobile's user name
        // so server can register it to currently connected user list
        if (socketManager.getStatus() == STATUS_DISCONNECTED) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (socketManager.getStatus() == STATUS_CONNECTED) {
            socketManager.setUserName(userName);
            JSONObject packet = new JSONObject();
            JSONObject data = new JSONObject();
            try {
                packet.put("method", "POST");
                packet.put("subject", "meta");
                data.put("userName", userName);
                packet.put("data", data);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            socketManager.send(packet.toString());
            Toast.makeText(this, "Connected!", Toast.LENGTH_SHORT).show();

            // need to receive work data...
            String receivedData = socketManager.receive();
            Log.d(TAG, String.format("received data : %s", receivedData));

            // 스테이터스 값이 2이면 넘어가고 4이면 에러처리
            int returnStatus = STATUS_ABNORMAL;

            if(receivedData != null) {
                try {
                    JSONObject parsedData = new JSONObject(receivedData);
                    returnStatus =  parsedData.getInt("status");
                    Log.d(TAG, String.format("status : %d", returnStatus));
                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (NullPointerException e){
                    e.printStackTrace();
                }
            }

            if(returnStatus == STATUS_NORMAL) {
                // go to main activity
                Intent intent = new Intent(this, MainActivity.class);
                startActivity(intent);
            }
            else if (returnStatus == STATUS_ABNORMAL) {
                Toast.makeText(this, "잘못된 요청입니다. 재시도해주세요.", Toast.LENGTH_SHORT).show();
            }

        } else {
            Toast.makeText(this, "retry to connect...", Toast.LENGTH_SHORT).show();
        }
    }

    public void popup(){
        //Creating the instance of PopupMenu
        PopupMenu popup = new PopupMenu(this, btn_pop_up_menu);
        //Inflating the Popup using xml file
        popup.getMenuInflater().inflate(R.menu.pop_up_menu, popup.getMenu());

        //registering popup with OnMenuItemClickListener
        popup.setOnMenuItemClickListener(item -> {
            Toast.makeText(getBaseContext(),"You Selected : " + item.getTitle(),Toast.LENGTH_SHORT).show();
            return true;
        });

        popup.show();//showing popup menu
    }
}
