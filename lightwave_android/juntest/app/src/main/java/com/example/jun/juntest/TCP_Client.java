package com.example.jun.juntest;

import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.util.Log;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.math.BigInteger;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteOrder;

import static android.content.Context.WIFI_SERVICE;
import static com.example.jun.juntest.MainActivity.SERV_IP;

/**
 * Created by jun on 2018-12-23.
 */

// AsyncTask를 상속하기 보다는 Thread를 상속하는게 좋을 듯.
// 따라서,     
public class TCP_Client extends AsyncTask {
    private Socket sock = null;
    private InetAddress serverAddr;

    @Override
    protected void onCancelled() {
        super.onCancelled();
        if (sock != null) {
            try {
                sock.close();
                sock = null;
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }


    //server ip
    protected static int PORT = 8080;


    // 연결 부분은 doInBackground에서 실행하는 것이 아니라, 생성자나 다른 생명주기함수에서 수행하는 것이 좋아보임.
    // doInBackground는 향후 연결이 된 상태에서, 여러가지 정보를 송수신하는 로직을 수행하는 것이 좋아보임.
    @Override
    protected Object doInBackground(Object... params) {
        //아이피 받는 부분


        // TODO Auto-generated method stub
        try {
            Log.d("TCP", "server connecting");
            serverAddr = InetAddress.getByName(SERV_IP);
            sock = new Socket(serverAddr, PORT);
            DataInputStream input = new DataInputStream(sock.getInputStream());
            DataOutputStream output = new DataOutputStream(sock.getOutputStream());
            try { //	데이터 송신 부분!
                WriteSocket(output);
            } catch (IOException e) {
                Log.e("TCP", "don't send message!");
                e.printStackTrace();
            }
        } catch (UnknownHostException e) { // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 현재 테스트 버전이라 괜찮지만, 나중에는 stream을 필드로 만들고, 인자로는 전송할 데이터를 받는 게 좋을듯.
    // 메소드의 첫글자는 소문자로.
    // 의미가 불분명 하므로 수정하는 것이 좋을듯. ex) sendData 혹은 writeData
    public void WriteSocket(DataOutputStream data) throws IOException {
        //	data send
        data.writeUTF("hiserver");
    }

    // writeSocket()과 같이, stream을 필드로 만들고, 인자는 아무것도 받지 않는 것이 좋을듯.
    // 의미가 불분명 하므로 수정하는 것이 좋을듯. ex) receiveData 혹은 readData
    public void ReadSock(DataInputStream data) throws IOException {
        //	data recieve
        byte[] datafile = null;
        data.read(datafile);
    }

}

