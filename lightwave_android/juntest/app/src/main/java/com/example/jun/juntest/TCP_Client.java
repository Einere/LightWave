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

public class TCP_Client extends AsyncTask {
    private Socket sock = null;
    private InetAddress serverAddr;
    @Override
    protected void onCancelled() {
        super.onCancelled();
        if(sock != null){
            try {
                sock.close();
                sock = null;
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    }


    //server ip
    protected static	int	PORT	=	8080;
    @Override protected Object doInBackground(Object... params) {
        //아이피 받는 부분


       // TODO Auto-generated method stub
            try { Log.d("TCP","server connecting");
            serverAddr = InetAddress.getByName(SERV_IP);
            sock = new Socket(serverAddr,PORT);
            DataInputStream input	=	new DataInputStream(sock.getInputStream());
            DataOutputStream output	=	new DataOutputStream(sock.getOutputStream());
            try{ //	데이터 송신 부분!
                 WriteSocket(output);
            } catch(IOException e){
                Log.e("TCP","don't send message!");
                e.printStackTrace();
            }
            }catch (UnknownHostException e) { // TODO Auto-generated catch block
                e.printStackTrace();
            } catch(IOException	e){
                e.printStackTrace(); }
                return null; }

    public void WriteSocket(DataOutputStream data) throws IOException{
        //	data send
         data.writeUTF("hiserver");
    }
    public void ReadSock(DataInputStream	data) throws IOException{
        //	data recieve
         byte[] datafile = null;
         data.read(datafile);
    }

}

