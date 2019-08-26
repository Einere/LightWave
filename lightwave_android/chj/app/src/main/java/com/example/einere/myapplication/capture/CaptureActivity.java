package com.example.einere.myapplication.capture;

import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.RemoteException;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.socket.SocketManager;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Objects;

import id.zelory.compressor.Compressor;

public class CaptureActivity extends FragmentActivity implements OnMapReadyCallback, GoogleMap.OnMarkerClickListener {
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    private final int CAMERA_CODE = 1111;
    private final int GALLERY_CODE = 1112;
    private final String TAG = "CaptureActivity";
    private GoogleMap mMap;
    private MyMapFragment myMapFragment;

    // socket transmission
    SocketManager socketManager = null;

    // RecyclerView
    RecyclerView rv_selectedImage = null;
    RecyclerViewAdapter recyclerAdapter = null;

    //memoView
    EditText et_client_memo = null;
    EditText et_server_memo = null;

    // id_number
    private String pointNum = null;
    private String taskId = "111";

    //receivedData
    private String receivedData = null;
    private String taskName = null;

    //새로시작하기 이어하기 = 1 , 히스토리 = 0
    private boolean status = true;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_capture);

        // google map
        myMapFragment = (MyMapFragment) getSupportFragmentManager().findFragmentById(R.id.frg_google_map);
        if (myMapFragment != null) {
            myMapFragment.getMapAsync(this);
        }

        // get views
        TextView tv_work_name = findViewById(R.id.tv_work_name);
        TextView tv_location_number = findViewById(R.id.tv_location_number);
        rv_selectedImage = findViewById(R.id.rv_selectedImage);
        et_client_memo = findViewById(R.id.et_client_memo);
        et_server_memo = findViewById(R.id.et_server_memo);

        // set views
        Intent receivedIntent = getIntent();
        String method = receivedIntent.getStringExtra("method");
        if (method != null && method.equals("new")) {
            tv_work_name.setText(receivedIntent.getStringExtra("taskName"));
            tv_location_number.setText(receivedIntent.getStringExtra("landNo"));
            et_server_memo.setText(receivedIntent.getStringExtra("taskDesc"));
            taskName = receivedIntent.getStringExtra("taskName");
            taskId = receivedIntent.getStringExtra("id");
            Toast.makeText(this, taskId, Toast.LENGTH_SHORT).show();
            receivedData = receivedIntent.getStringExtra("receivedData");
            status = true;
        } else if (method != null && method.equals("history")) {
            tv_work_name.setText(receivedIntent.getStringExtra("taskName"));
            tv_location_number.setText(receivedIntent.getStringExtra("landNo"));
            et_server_memo.setText(receivedIntent.getStringExtra("taskDesc"));
            taskName = receivedIntent.getStringExtra("taskName");
            taskId = receivedIntent.getStringExtra("id");
            Toast.makeText(this, taskId, Toast.LENGTH_SHORT).show();
            receivedData = receivedIntent.getStringExtra("receivedData");
            status = false;
        }

        // make RecyclerView
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        linearLayoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        rv_selectedImage.setLayoutManager(linearLayoutManager);
        recyclerAdapter = new RecyclerViewAdapter();
        rv_selectedImage.setAdapter(recyclerAdapter);

        // set listener
        findViewById(R.id.btn_capture).setOnClickListener(v -> capture());
        findViewById(R.id.btn_select_picture).setOnClickListener(v -> selectGallery());
        findViewById(R.id.btn_send_data).setOnClickListener(v -> sendData());
        findViewById(R.id.btn_memo_save).setOnClickListener(v -> saveMemo());
        findViewById(R.id.btn_memo_delete).setOnClickListener(v -> deleteMemo());
        findViewById(R.id.btn_test_data).setOnClickListener(v -> makeTestTextFile());

        memoHistory();
    }

    public void memoHistory() {
        //이어하기 내역
        File file = new File(Environment.getExternalStorageDirectory() + "/" + "workHistory");
        if (!file.exists()) {
            file.mkdir();
        }

        File file2 = new File(Environment.getExternalStorageDirectory() + "/" + "workHistory/task");
        if (!file2.exists()) {
            file2.mkdir();
        }

        if (status) {
            String historyPath = Environment.getExternalStorageDirectory() + "/workHistory/beforeHistory.txt";
            File historyFile = new File(historyPath);
            if (historyFile.exists()) {
                historyFile.delete();
            }

            try {
                if (!historyFile.exists()) {
                    try {
                        FileOutputStream fos = new FileOutputStream(historyFile);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                FileOutputStream fos = new FileOutputStream(historyFile);
                BufferedWriter buw = new BufferedWriter(new OutputStreamWriter(fos, StandardCharsets.UTF_8));
                buw.write(receivedData);
                buw.close();
                fos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }

        }

        //작업리스트 내역
        String taskHistoryPath = Environment.getExternalStorageDirectory() + "/workHistory/task/" + taskName + ".txt";
        File taskHistoryFile = new File(taskHistoryPath);
        if (taskHistoryFile.exists()) {
            taskHistoryFile.delete();
        }

        try {
            if (!taskHistoryFile.exists()) {
                FileOutputStream fos = new FileOutputStream(taskHistoryFile);
            }
            FileOutputStream fos = new FileOutputStream(taskHistoryFile);
            BufferedWriter buw = new BufferedWriter(new OutputStreamWriter(fos, StandardCharsets.UTF_8));
            buw.write(receivedData);
            buw.close();
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        // get SocketManager instance
        socketManager = SocketManager.getInstance();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }


    /* ******************* google map start ******************* */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        // 구글 맵 객체를 불러온다.
        mMap = googleMap;

        JSONObject parsedData = new JSONObject();
        try {
            parsedData = new JSONObject(receivedData);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mMap.clear();

        try {
            int status = parsedData.getInt("status");

            // if receive error message
            if (status == 4) {
                String message = parsedData.getString("message");
                Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
                return;
            }
            JSONObject data = parsedData.getJSONObject("data");
            JSONArray parcels = data.getJSONArray("parcels");
            JSONArray surveyPoints = data.getJSONArray("surveyPoints");

            double sumX = 0;
            double sumY = 0;
            int sumi = 0;
            //도형 점 정보 그림
            for (int i = 0; i < parcels.length(); i++) {
                JSONObject tmp3 = parcels.getJSONObject(i);
                JSONArray parcelPoints = tmp3.getJSONArray("parcelPoints");
                ArrayList<Double> yParcelPointsList = new ArrayList<>();
                ArrayList<Double> xParcelPointsList = new ArrayList<>();
                for (int j = 0; j < parcelPoints.length(); j++) {
                    sumi++;
                    JSONObject tmp2 = parcelPoints.getJSONObject(j);
                    double x = tmp2.getDouble("Y");
                    double y = tmp2.getDouble("X");
                    sumX += x;
                    sumY += y;
                    xParcelPointsList.add(x);
                    yParcelPointsList.add(y);
                    if (j != 0) {
                        LatLng poly1 = new LatLng(xParcelPointsList.get(j - 1), yParcelPointsList.get(j - 1));
                        LatLng poly2 = new LatLng(xParcelPointsList.get(j), yParcelPointsList.get(j));
                        PolylineOptions poly = new PolylineOptions();
                        poly.color(Color.RED);
                        poly.width(6);
                        poly.add(poly1);
                        poly.add(poly2);
                        mMap.addPolyline(poly);
                    }
                    if (j == parcelPoints.length() - 1) {
                        LatLng poly1 = new LatLng(xParcelPointsList.get(0), yParcelPointsList.get(0));
                        LatLng poly2 = new LatLng(xParcelPointsList.get(j), yParcelPointsList.get(j));
                        PolylineOptions poly = new PolylineOptions();
                        poly.color(Color.RED);
                        poly.width(6);
                        poly.add(poly1);
                        poly.add(poly2);
                        mMap.addPolyline(poly);
                    }
                }
            }

            LatLng center = new LatLng(sumX / sumi, sumY / sumi);
            CameraPosition cameraPosition = new CameraPosition.Builder()
                    .target(center)      // Sets the center of the map to Mountain View
                    .zoom(16)                   // Sets the zoom
                    .bearing(0)                // Sets the orientation of the camera to east
                    .tilt(30)                   // Sets the tilt of the camera to 30 degrees
                    .build();

            // 카메라를 여의도 위치로 옮긴다.
            mMap.moveCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));

            //작업 점 정보 그림
            for (int i = 0; i < surveyPoints.length(); i++) {
                JSONObject tmp = (JSONObject) surveyPoints.get(i);
                double x = tmp.getDouble("Y");
                double y = tmp.getDouble("X");
                boolean surveyed = tmp.getBoolean("surveyed");
                String serveyID = tmp.getString("id");
                LatLng point = new LatLng(x, y);

                MarkerOptions makerOptions = new MarkerOptions();
                if (surveyed) {
                    makerOptions
                            .position(point)
                            .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))
                            .title(serveyID);
                } else {
                    makerOptions
                            .position(point)
                            .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED))
                            .title(serveyID);
                }

                // 마커를 생성한다.
                mMap.addMarker(makerOptions);
                mMap.setOnMarkerClickListener(this);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        memoHistory();

        // prevent double scroll
        ScrollView sv_root_layout = findViewById(R.id.sv_root_layout);
        myMapFragment.setListener(() -> sv_root_layout.requestDisallowInterceptTouchEvent(true));
    }

    public void refreshClick(View v) {
        drawMap();
        memoHistory();
    }

    //작업정보 가져오기
    public void drawMap() {
        // request work data to server
        JSONObject packet = new JSONObject();
        try {
            packet.put("method", "GET");
            packet.put("subject", "task");
            socketManager.send(packet.toString());
        } catch (JSONException e) {
            Toast.makeText(this, "error at make json...", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        } catch (RemoteException e) {
            Toast.makeText(this, "maybe socket error...", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }

        // receive data from server
        try {
            receivedData = socketManager.receive();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        Log.d(TAG, String.format("received data : %s", receivedData));

        // parse received data
        JSONObject parsedData = new JSONObject();
        try {
            parsedData = new JSONObject(receivedData);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mMap.clear();

        try {
            int status = parsedData.getInt("status");

            // if receive error message
            if (status == 4) {
                String message = parsedData.getString("message");
                Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
                return;
            }
            JSONObject data = parsedData.getJSONObject("data");
            JSONArray parcels = data.getJSONArray("parcels");
            JSONArray surveyPoints = data.getJSONArray("surveyPoints");

            double sumX = 0;
            double sumY = 0;
            int sumi = 0;
            //도형 점 정보 그림
            for (int i = 0; i < parcels.length(); i++) {
                JSONObject tmp3 = parcels.getJSONObject(i);
                JSONArray parcelPoints = tmp3.getJSONArray("parcelPoints");
                ArrayList<Double> yParcelPointsList = new ArrayList<>();
                ArrayList<Double> xParcelPointsList = new ArrayList<>();
                for (int j = 0; j < parcelPoints.length(); j++) {
                    sumi++;
                    JSONObject tmp2 = parcelPoints.getJSONObject(j);
                    double x = tmp2.getDouble("Y");
                    double y = tmp2.getDouble("X");
                    sumX += x;
                    sumY += y;
                    xParcelPointsList.add(x);
                    yParcelPointsList.add(y);
                    if (j != 0) {
                        LatLng poly1 = new LatLng(xParcelPointsList.get(j - 1), yParcelPointsList.get(j - 1));
                        LatLng poly2 = new LatLng(xParcelPointsList.get(j), yParcelPointsList.get(j));
                        PolylineOptions poly = new PolylineOptions();
                        poly.color(Color.RED);
                        poly.width(6);
                        poly.add(poly1);
                        poly.add(poly2);
                        mMap.addPolyline(poly);
                    }
                    if (j == parcelPoints.length() - 1) {
                        LatLng poly1 = new LatLng(xParcelPointsList.get(0), yParcelPointsList.get(0));
                        LatLng poly2 = new LatLng(xParcelPointsList.get(j), yParcelPointsList.get(j));
                        PolylineOptions poly = new PolylineOptions();
                        poly.color(Color.RED);
                        poly.width(6);
                        poly.add(poly1);
                        poly.add(poly2);
                        mMap.addPolyline(poly);
                    }
                }
            }

            // 카메라를 여의도 위치로 옮긴다.
            LatLng center = new LatLng(sumX / sumi, sumY / sumi);
            CameraPosition cameraPosition = new CameraPosition.Builder()
                    .target(center)      // Sets the center of the map to Mountain View
                    .zoom(16)                   // Sets the zoom
                    .bearing(0)                // Sets the orientation of the camera to east
                    .tilt(30)                   // Sets the tilt of the camera to 30 degrees
                    .build();
            mMap.moveCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));

            //작업 점 정보 그림
            for (int i = 0; i < surveyPoints.length(); i++) {
                JSONObject tmp = (JSONObject) surveyPoints.get(i);
                double x = tmp.getDouble("Y");
                double y = tmp.getDouble("X");
                boolean surveyed = tmp.getBoolean("surveyed");
                String serveyID = tmp.getString("id");
                LatLng point = new LatLng(x, y);

                MarkerOptions makerOptions = new MarkerOptions();
                if (surveyed) {
                    makerOptions
                            .position(point)
                            .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))
                            .title(serveyID);
                } else {
                    makerOptions
                            .position(point)
                            .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED))
                            .title(serveyID);
                }

                // 마커를 생성한다.
                mMap.addMarker(makerOptions);
                mMap.setOnMarkerClickListener(this);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        File file2 = new File(Environment.getExternalStorageDirectory() + "/" + taskId);
        if (!file2.exists()) {
            file2.mkdir();
        }
        File file = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/history");
        if (!file.exists()) {
            file.mkdir();
        }

        try {
            // save history
            FileOutputStream fos = new FileOutputStream(new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/history/history.txt"));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos, StandardCharsets.UTF_8));
            bw.write(receivedData);

            // close stream
            bw.close();
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public boolean onMarkerClick(Marker marker) {
        ArrayList<Uri> uriList = new ArrayList<>();
        pointNum = marker.getTitle();

        // check directory is exist
        File file = new File(Environment.getExternalStorageDirectory() + "/" + taskId);
        if (!file.exists()) {
            file.mkdir();
        }
        File file2 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum);
        if (!file2.exists()) {
            file2.mkdir();
        }
        File uploadFile = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/uploadfile");
        if (!uploadFile.exists()) {
            uploadFile.mkdir();
        }
        File file4 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/textfile");
        if (!file4.exists()) {
            file4.mkdir();
        }
        File file5 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/memofile");
        if (!file5.exists()) {
            file5.mkdir();
        }

        // 사진파일명 리스트 뽑아오기
        File[] uploadImageList = uploadFile.listFiles((dir, name) -> {
            Boolean bOK = false;
            if (name.toLowerCase().endsWith(".png")) bOK = true;
            if (name.toLowerCase().endsWith(".9.png")) bOK = true;
            if (name.toLowerCase().endsWith(".gif")) bOK = true;
            if (name.toLowerCase().endsWith(".jpg")) bOK = true;
            return bOK;
        });

        // load memo
        loadMemo();

        // if not exist any file in taskId/point/upload
        if (uploadImageList == null) {
            return true;
        }

        // 이미지와 텍스트 파일 list에 넣기
        for (File uploadImageFile : uploadImageList)
            uriList.add(Uri.parse(uploadImageFile.getAbsolutePath()));

        // clear RecyclerView
        recyclerAdapter.clearUriList();
        if (uriList.size() > 0) {
            // add RecyclerView
            recyclerAdapter.addUriList(uriList);
        }

        return true;
    }
    /* ******************* google map end ******************* */


    /* ******************* socket methods start ******************* */
    public JSONObject makePacket(String method, String subject, JSONObject data) {
        JSONObject packet = new JSONObject();
        try {
            packet.put("method", method);
            packet.put("subject", subject);
            packet.put("data", data);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return packet;
    }

    class MyAsyncTask extends AsyncTask<Integer, Integer, Integer> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected Integer doInBackground(Integer... integers) {
            // check manager status
            try {
                ArrayList<Uri> selectedUriList = recyclerAdapter.getSelectedUriList();
                if (socketManager.getStatus() == STATUS_CONNECTED && selectedUriList.size() > 0) {
                    // make data JSONObject
                    JSONObject data = new JSONObject();
                    data.put("userName", socketManager.getUserName());
                    data.put("taskId", Integer.parseInt(taskId));
                    data.put("surveyId", Integer.parseInt(pointNum));

                    // make data packet
                    Compressor compressor = new Compressor(getBaseContext());
                    JSONArray imageList = new JSONArray();
                    JSONArray geometryList = new JSONArray();

                    for (Uri uri : selectedUriList) {
                        // put serialized picture data
                        byte[] bytes = getBytes(new FileInputStream(compressor.compressToFile(new File(uri.getPath()))));
                        imageList.put(Base64.encodeToString(bytes, Base64.NO_WRAP));
                        Log.d(TAG, String.format(Locale.KOREA, "path : %s", uri.toString()));

                        // put geometry data
                        JSONObject geometry = new JSONObject();
                        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(new File(getTextFilePath(uri))), StandardCharsets.UTF_8));
                        geometry.put("azimuth", Double.parseDouble(br.readLine()));
                        geometry.put("latitude", Double.parseDouble(br.readLine()));
                        geometry.put("longitude", Double.parseDouble(br.readLine()));
                        br.close();
                        geometryList.put(geometry);
                        Log.d(TAG, String.format(Locale.KOREA, "geometry : %s", geometry.toString()));
                    }
                    data.put("images", imageList);
                    data.put("geometry", geometryList);

                    // put memo data
                    data.put("memo", et_client_memo.getText());

                    // make data packet
                    JSONObject packet = makePacket("POST", "survey", data);

                    // make data length packet
                    JSONObject lengthData = new JSONObject();
                    lengthData.put("length", packet.toString().getBytes().length);
                    JSONObject lengthPacket = makePacket("POST", "length", lengthData);
                    Log.d(TAG, String.format(Locale.KOREA, "[logging] length packet : %s", lengthPacket.toString()));

                    // logging packet data
                    File log = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/log.txt");
                    OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream(log));
                    osw.write(packet.toString());
                    osw.flush();
                    osw.close();
                    Log.d(TAG, String.format(Locale.KOREA, "[logging] file path : %s", log.getAbsolutePath()));

                    // send packet length to server
                    socketManager.send(lengthPacket.toString());
                    socketManager.receive();

                    // send packet to server
                    socketManager.send(packet.toString());

                    // receive response packet from server
                    socketManager.receive();
                } else {
//                    Toast.makeText(this, "not connected to server or no selected image", Toast.LENGTH_SHORT).show();
                }
            } catch (RemoteException e) {
                e.printStackTrace();
//                Toast.makeText(this, "RemoteException occurred!", Toast.LENGTH_SHORT).show();
            } catch (JSONException e) {
                e.printStackTrace();
//                Toast.makeText(this, "JSONException occurred!", Toast.LENGTH_SHORT).show();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
//                Toast.makeText(this, "file is not found!", Toast.LENGTH_SHORT).show();
            } catch (IOException e) {
                e.printStackTrace();
//                Toast.makeText(this, "error in readLine!", Toast.LENGTH_SHORT).show();
            }
            return 0;
        }

        @Override
        protected void onProgressUpdate(Integer... params) {
        }

        @Override
        protected void onPostExecute(Integer result) {
            super.onPostExecute(result);
        }

        byte[] getBytes(InputStream inputStream) throws IOException {
            ByteArrayOutputStream byteBuffer = new ByteArrayOutputStream();
            int bufferSize = 1024;
            byte[] buffer = new byte[bufferSize];

            int len = 0;
            while ((len = inputStream.read(buffer)) != -1) {
                byteBuffer.write(buffer, 0, len);
            }
            return byteBuffer.toByteArray();
        }

        String getTextFilePath(Uri uri) {
            // get path and fileName
            String[] splitPath = uri.getPath().split("/");
            String textFileName = splitPath[splitPath.length - 1];
            // support png, jpg
            if (textFileName.contains(".png")) textFileName = textFileName.replace(".png", ".txt");
            else if (textFileName.contains(".jpg"))
                textFileName = textFileName.replace(".jpg", ".txt");
            splitPath[splitPath.length - 2] = "textfile";
            splitPath[splitPath.length - 1] = textFileName;

            return TextUtils.join("/", splitPath);
        }
    }

    public void sendData() {
        MyAsyncTask task = new MyAsyncTask();
        task.execute();
    }
    /* ******************* socket methods end ******************* */


    /* ****************** Memo methods start ********************** */
    public void saveMemo() {
        if (pointNum == null) {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
            return;
        }
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/memofile/" + taskId + "_" + pointNum + "_" + "memo.txt";
        File clientMemoFile = new File(clientMemoPath);
        String memoStr = et_client_memo.getText().toString();
        try {
            FileOutputStream fos = new FileOutputStream(clientMemoFile);
            BufferedWriter buw = null;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT) {
                buw = new BufferedWriter(new OutputStreamWriter(fos, StandardCharsets.UTF_8));
            }
            if (buw != null) {
                buw.write(memoStr);
                buw.close();
            }
            fos.close();
            Toast.makeText(this, "저장완료", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void loadMemo() {
        // 마커의 메모 불러오기
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/memofile/" + taskId + "_" + pointNum + "_" + "memo.txt";
        File clientMemoFile = new File(clientMemoPath);

        if (!clientMemoFile.exists()) {
            et_client_memo.setHint(R.string.no_memo);
        } else {
            StringBuilder sb = new StringBuilder();
            try {
                BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(clientMemoPath), StandardCharsets.UTF_8));

                // read line
                String line;
                while ((line = reader.readLine()) != null) {
                    sb.append(line).append("\n");
                }

                // close stream
                reader.close();
                et_client_memo.setText(sb.toString());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void deleteMemo() {
        if (pointNum == null) {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
            return;
        }
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/memofile/" + taskId + "_" + pointNum + "_" + "memo.txt";
        File clientMemoFile = new File(clientMemoPath);
        et_client_memo.setText("");

        if (clientMemoFile.exists()) {
            if (clientMemoFile.delete()) Toast.makeText(this, "삭제 완료", Toast.LENGTH_LONG).show();
            else Toast.makeText(this, "삭제 실패", Toast.LENGTH_LONG).show();
        }
    }
    /* ****************** Memo methods end ********************** */


    /* ******************* camera & gallery methods start ******************* */
    public void capture() {
        if (pointNum != null) {
            Intent intent = new Intent(this, CameraActivity.class);
            Bundle bundleData = new Bundle();
            bundleData.putString("c_point_num", pointNum);
            bundleData.putString("work_num", taskId);
            intent.putExtra("ID_NUM", bundleData);
            startActivity(intent);
        } else {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
        }

    }

    public void selectGallery() {
        // call ImagePickerActivity
        if (pointNum != null) {
            Intent intent = new Intent(this, ImagePickerActivity.class);

            Bundle bundleData = new Bundle();
            bundleData.putString("c_point_num", pointNum);
            bundleData.putString("work_num", taskId);
            intent.putExtra("ID_NUM", bundleData);

            startActivityForResult(intent, GALLERY_CODE);
        } else {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            switch (requestCode) {
                case GALLERY_CODE: {
                    // 갤러리에서 가져온 경우
                    try {
                        ArrayList<Uri> uris = Objects.requireNonNull(data).getParcelableArrayListExtra("selected");
                        for (Uri uri : uris) {
                            // add to RecyclerView
                            recyclerAdapter.addUri(uri);
                            Log.d(TAG, String.format("received uri : %s", uri.toString()));

                            // 선택한 이미지를 업로드용 폴더에 추가
                            backup(uri);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                        Toast.makeText(this, "failed to load image & geometry data...", Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case CAMERA_CODE: {
                    //카메라에서 가져온 경우
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    public void backup(Uri uri) {
        String[] splitPath = uri.getPath().split("/");
        String fileName = splitPath[splitPath.length - 1];
        String filePath = TextUtils.join("/", splitPath);
        Log.d(TAG, String.format("filePath : %s, fileName : %s", filePath, fileName));

        // get file
        File file = new File(filePath);
        if (file.exists()) {
            // if image, copy it to uploadfile directory
            try {
                // make streams
                FileInputStream fis = new FileInputStream(new Compressor(this).compressToFile(file));
                FileOutputStream fos = new FileOutputStream(String.format("%s/%s/%s/%s/%s", Environment.getExternalStorageDirectory(), taskId, pointNum, "uploadfile", fileName));

                // copy to uploadfile directory
                int readCount;
                byte[] buffer = new byte[1024];
                while ((readCount = fis.read(buffer, 0, 1024)) != -1) {
                    fos.write(buffer, 0, readCount);
                }

                // close streams
                fos.close();
                fis.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    /* ******************* camera & gallery methods end ******************* */


    /* ******************* text file methods start ******************* */
    public String getFileContents(final File file) {
        final StringBuilder stringBuilder = new StringBuilder();

        try {
            final BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file), StandardCharsets.UTF_8));

            String string;
            while ((string = reader.readLine()) != null) {
                stringBuilder.append(string);
            }

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return stringBuilder.toString();
    }
    /* ******************* text file methods end ******************* */

    /* ******************* make text file to test start ******************* */
    public void makeTestTextFile() {
        try {
            File textFile = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/textfile/20190707_160717.txt");
            OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream(textFile));
            osw.write("10.10\n");
            osw.write("11.11\n");
            osw.write("12.12\n");
            osw.flush();
            osw.close();

            File textFile2 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/textfile/20190707_160724.txt");
            OutputStreamWriter osw2 = new OutputStreamWriter(new FileOutputStream(textFile2));
            osw2.write("7.7777\n");
            osw2.write("8.8888\n");
            osw2.write("9.99999\n");
            osw2.flush();
            osw2.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    /* ******************* make text file to test end ******************* */
}
