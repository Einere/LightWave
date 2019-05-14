package com.example.einere.myapplication.capture;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.RemoteException;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.einere.myapplication.CameraActivity;
import com.example.einere.myapplication.GpsInfo;
import com.example.einere.myapplication.ListViewActivity;
import com.example.einere.myapplication.R;
import com.example.einere.myapplication.SocketManager;
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
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Locale;

public class CaptureActivity extends FragmentActivity implements SensorEventListener, OnMapReadyCallback, GoogleMap.OnMarkerClickListener {
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

    // sensor
    SensorManager sensorManager = null;
    Sensor accelerometer = null;
    Sensor magnetometer = null;
    float[] gravity = null;
    float[] geomagnetic = null;
    TextView tv_azimuth = null;
    private GpsInfo gps;

    // upload ArrayList
    ArrayList<File> upImageList = new ArrayList<>();
    ArrayList<File> upTextList = new ArrayList<>();

    // id_number
    private String pointNum = null;
    private String workNum = "111";

    //image ArrayList
    private ArrayList<Image> images = new ArrayList<>();

    //receivedData
    private String receivedData = null;
    private String taskName = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_capture);

        // google map
//        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.frg_google_map);
//        mapFragment.getMapAsync(this); //getMapAsync must be called on the main thread.
        myMapFragment = (MyMapFragment) getSupportFragmentManager().findFragmentById(R.id.frg_google_map);
        if (myMapFragment != null) {
            myMapFragment.getMapAsync(this);
        }

        // get views
        TextView tv_work_name = findViewById(R.id.tv_work_name);
        TextView tv_location_number = findViewById(R.id.tv_location_number);
        rv_selectedImage = findViewById(R.id.rv_selectedImage);
        tv_azimuth = findViewById(R.id.tv_azimuth);
        et_client_memo = findViewById(R.id.et_client_memo);
        et_server_memo = findViewById(R.id.et_server_memo);

        // set views
        Intent receivedIntent = getIntent();
        String method = receivedIntent.getStringExtra("method");
        if (method != null && method.equals("new")) {
            tv_work_name.setText(receivedIntent.getStringExtra("taskName"));
            tv_location_number.setText(receivedIntent.getStringExtra("landNo"));
            et_server_memo.setText(receivedIntent.getStringExtra("taskDesc"));
            taskName=receivedIntent.getStringExtra("taskDesc");
            workNum = receivedIntent.getStringExtra("id");
            Toast.makeText(this, workNum, Toast.LENGTH_SHORT).show();
            receivedData = receivedIntent.getStringExtra("receivedData");
        }

        // get sensor manager
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magnetometer = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

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
        findViewById(R.id.btn_test).setOnClickListener(v -> checkArrayListForUpload());
        findViewById(R.id.btn_memo_save).setOnClickListener(v -> saveMemo());
        findViewById(R.id.btn_memo_delete).setOnClickListener(v -> deleteMemo());

         //이어하기 내역
        File file = new File(Environment.getExternalStorageDirectory() + "/" + "workHistory");
        if (!file.exists()) {
            file.mkdir();
        }

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

        String taskhistoryPath = Environment.getExternalStorageDirectory() + "/workHistory/"+ taskName +".txt";
        File taskhistoryFile = new File(taskhistoryPath);
        if (taskhistoryFile.exists()) {
            taskhistoryFile.delete();
        }

        try {
            if (!taskhistoryFile.exists()) {
                try {
                    FileOutputStream fos = new FileOutputStream(taskhistoryFile);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            FileOutputStream fos = new FileOutputStream(taskhistoryFile);
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

        // register listener
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_UI);
        sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_UI);
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

       /* // 서울 여의도에 대한 위치 설정
        LatLng seoul = new LatLng(37.52487, 126.92723);
        LatLng seoul2 = new LatLng(37.52440, 126.92750);

        // 구글 맵에 표시할 마커에 대한 옵션 설정
        MarkerOptions makerOptions = new MarkerOptions();
        makerOptions
                .position(seoul)
                .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_YELLOW))
                .title("212");

        MarkerOptions makerOptions2 = new MarkerOptions();
        makerOptions2
                .position(seoul2)
                .title("213");

        // 마커를 생성한다.
        mMap.addMarker(makerOptions);
        mMap.addMarker(makerOptions2);
        mMap.setOnMarkerClickListener(this);

        PolylineOptions poly = new PolylineOptions();
        poly.color(Color.RED);
        poly.width(4);
        poly.add(seoul);
        poly.add(seoul2);
        mMap.addPolyline(poly);*/

       drawMap();
        LatLng seoul = new LatLng(37.52487, 126.92723);
        // 카메라 옵션
        CameraPosition cameraPosition = new CameraPosition.Builder()
                .target(seoul)      // Sets the center of the map to Mountain View
                .zoom(18)                   // Sets the zoom
                .bearing(0)                // Sets the orientation of the camera to east
                .tilt(30)                   // Sets the tilt of the camera to 30 degrees
                .build();

        // 카메라를 여의도 위치로 옮긴다.
        mMap.moveCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));

        // prevent double scroll
        ScrollView sv_root_layout = findViewById(R.id.sv_root_layout);
        myMapFragment.setListener(() -> sv_root_layout.requestDisallowInterceptTouchEvent(true));
    }

    public void refreshClick(View v) {
        drawMap();
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

        // receive & parse requested data
        String receivedData = null;
        try {
            receivedData = socketManager.receive();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        Log.d(TAG, String.format("received data : %s", receivedData));

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

            //도형 점 정보 그림
                JSONObject tmp3 = parcels.getJSONObject(0);
                JSONArray parcelPoints = tmp3.getJSONArray("parcelPoints");
                ArrayList<Double> yParcelPointsList = new ArrayList<>();
                ArrayList<Double> xParcelPointsList = new ArrayList<>();
                for (int j = 0; j < parcelPoints.length(); j++) {
                    JSONObject tmp2 = parcelPoints.getJSONObject(j);
                    double x = tmp2.getDouble("Y");
                    double y = tmp2.getDouble("X");
                    xParcelPointsList.add(x);
                    yParcelPointsList.add(y);
                    if (j != 0) {
                        LatLng poly1 = new LatLng(xParcelPointsList.get(j - 1), yParcelPointsList.get(j- 1));
                        LatLng poly2 = new LatLng(xParcelPointsList.get(j), yParcelPointsList.get(j));
                        PolylineOptions poly = new PolylineOptions();
                        poly.color(Color.RED);
                        poly.width(6);
                        poly.add(poly1);
                        poly.add(poly2);
                        mMap.addPolyline(poly);
                    }
            }

            //작업 점 정보 그림
            for (int i = 0; i < surveyPoints.length(); i++) {
                JSONObject tmp = (JSONObject) surveyPoints.get(i);
                double x = tmp.getDouble("Y");
                double y = tmp.getDouble("X");
                boolean surveyed = tmp.getBoolean("surveyed");
                String serveyID =  tmp.getString("id");
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
        File file2 = new File(Environment.getExternalStorageDirectory() + "/" + workNum);
        if (!file2.exists()) {
            file2.mkdir();
        }
        File file = new File(Environment.getExternalStorageDirectory() + "/" + workNum + "/history");
        if (!file.exists()) {
            file.mkdir();
        }

        String historyPath = Environment.getExternalStorageDirectory() + "/" + workNum + "/history/history.txt";
        File historyFile = new File(historyPath);

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

    @Override
    public boolean onMarkerClick(Marker marker) {
        ArrayList<Uri> uriList = new ArrayList<>();
        pointNum = marker.getTitle();

        // check directory is exist
        File file = new File(Environment.getExternalStorageDirectory() + "/" + workNum);
        if (!file.exists()) {
            file.mkdir();
        }
        File file2 = new File(Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum);
        if (!file2.exists()) {
            file2.mkdir();
        }
        File uploadFile = new File(Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/uploadfile");
        if (!uploadFile.exists()) {
            uploadFile.mkdir();
        }
        File file4 = new File(Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/textfile");
        if (!file4.exists()) {
            file4.mkdir();
        }
        File file5 = new File(Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/memofile");
        if (!file5.exists()) {
            file5.mkdir();
        }

        // 사진파일명 리스트 뽑아오기
        File[] uploadImageList2 = uploadFile.listFiles((dir, name) -> {
            Boolean bOK = false;
            if (name.toLowerCase().endsWith(".png")) bOK = true;
            if (name.toLowerCase().endsWith(".9.png")) bOK = true;
            if (name.toLowerCase().endsWith(".gif")) bOK = true;
            if (name.toLowerCase().endsWith(".jpg")) bOK = true;
            return bOK;
        });


        // 마커의 메모 불러오기
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/memofile/" + workNum + "_" + pointNum + "_" + "memo.txt";
        File clientMemoFile = new File(clientMemoPath);

        if (!clientMemoFile.exists()) {
            et_client_memo.setHint(R.string.no_memo);
        } else {
            StringBuilder sb = new StringBuilder();
            try {
                InputStream is = new FileInputStream(clientMemoPath);
                BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));

                // read line
                String line = "";
                while ((line = reader.readLine()) != null) {
                    sb.append(line).append("\n");
                }

                // close stream
                reader.close();
                is.close();
                et_client_memo.setText(sb.toString());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // if not exist any file in workNum/point/upload
        if (uploadImageList2 == null) {
            return true;
        }

        // 이미지와 텍스트 파일 list에 넣기
        for (File uploadImageFile : uploadImageList2) {
            // prevent to add duplicated image file
            if (!upImageList.contains(uploadImageFile)) upImageList.add(uploadImageFile);
            uriList.add(Uri.parse(uploadImageFile.getAbsolutePath()));

            // get path and fileName
            String path = uploadImageFile.getAbsolutePath();
            String[] splitPath = path.split("/");
            String textFileName = splitPath[splitPath.length - 1];
            textFileName = textFileName.replace(".png", ".txt");
            splitPath[splitPath.length - 2] = "textfile";
            splitPath[splitPath.length - 1] = textFileName;
            String textFilePath = TextUtils.join("/", splitPath);
            Log.d(TAG, String.format("path : %s", path));
            Log.d(TAG, String.format("textFilePath : %s", textFilePath));

            File textFile = new File(textFilePath);
            if (textFile.exists() && !upTextList.contains(textFile)) {
                // prevent to add duplicated text file
                upTextList.add(textFile);
            }
        }

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

    public void clickPoint(View v) {
        Intent intent = new Intent(this, ListViewActivity.class);
        startActivity(intent);
    }

    public void sendData() {
        // check manager status
        try {
            ArrayList<Uri> selectedUriList = recyclerAdapter.getSelectedUriList();
            if (socketManager.getStatus() == STATUS_CONNECTED && selectedUriList.size() > 0) {
                // get uri list
//                ArrayList<Uri> uriList = recyclerAdapter.getSelectedUriList();

                // make data JSONObject
                JSONObject data = new JSONObject();
                data.put("userName", socketManager.getUserName());

                // put serialized picture data
                int i = 0;
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                for (Uri uri : selectedUriList) {
                    Bitmap tmpBitmap = BitmapFactory.decodeFile(uri.getPath());
                    tmpBitmap.compress(Bitmap.CompressFormat.PNG, 100, stream);
                    byte[] bytes = stream.toByteArray();
                    String serialized = Base64.encodeToString(bytes, Base64.NO_WRAP);
                    data.put(String.format(Locale.KOREA, "image%d", i), serialized);
                    Log.d(TAG, String.format("encoded string : %s", serialized));
                    i++;
                }
                // put text data
                i = 0;
                for (File file : upTextList) {
                    data.put(String.format(Locale.KOREA, "text%d", i), getFileContents(file));
                    i++;
                }
                // make packet
                JSONObject packet = makePacket("POST", "survey", data);

                // make data length packet
                JSONObject lengthData = new JSONObject();
                lengthData.put("length", packet.toString().getBytes().length); // 단순히 String의 길이? 혹은 byte?
                Log.d(TAG, String.format(Locale.KOREA, "length : %d, byte : %d", packet.toString().length(), packet.toString().getBytes().length));
                JSONObject lengthPacket = makePacket("POST", "length", lengthData);

                // send packet length to server
                socketManager.send(lengthPacket.toString());

                // send packet to server
                socketManager.send(packet.toString());
                Toast.makeText(this, "send!", Toast.LENGTH_SHORT).show();
                Log.d(TAG, String.format("send data : %s", packet.toString()));

                // receive response packet from server
                socketManager.receive();
            } else {
                Toast.makeText(this, "not connected to server or no selected image", Toast.LENGTH_SHORT).show();
            }
        } catch (RemoteException e) {
            Toast.makeText(this, "RemoteException occurred!", Toast.LENGTH_SHORT).show();
        } catch (JSONException e) {
            Toast.makeText(this, "JSONException occurred!", Toast.LENGTH_SHORT).show();
        }
    }

    public void receiveData(View v) throws RemoteException {
        if (socketManager.getStatus() == STATUS_CONNECTED) {
            socketManager.receive();
        } else {
            Toast.makeText(this, "not connected to server", Toast.LENGTH_SHORT).show();
        }
    }
    /* ******************* socket methods end ******************* */


    /* ******************* sensor methods start ******************* */
    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            gravity = event.values;
        }
        if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
            geomagnetic = event.values;
        }

        if (gravity != null && geomagnetic != null) {
            float[] R = new float[9];
            float[] I = new float[9];

            boolean success = SensorManager.getRotationMatrix(R, I, gravity, geomagnetic);
            if (success) {
                float[] orientation = new float[3];
                SensorManager.getOrientation(R, orientation);

                // orientation contains: azimuth, pitch  and roll
                float azimuth = orientation[0];
                float pitch = orientation[1];
                float roll = orientation[2];

                tv_azimuth.setText(String.format(Locale.KOREA, "azimuth : %f", azimuth));
//                txtPitch.setText("y 좌표:" + String.valueOf(pitch));
//                txtRoll.setText("z 좌표 : " + String.valueOf(roll));
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }
    /* ******************* sensor methods end ******************* */


    /* ******************* GPS methods start ******************* */
    public void Gps() {
        gps = new GpsInfo(this);
        // GPS 사용유무 가져오기
        if (gps.isGetLocation()) {
            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();

            Toast.makeText(
                    getApplicationContext(),
                    "당신의 위치 - \n위도: " + latitude + "\n경도: " + longitude,
                    Toast.LENGTH_LONG).show();
        } else {
            // GPS 를 사용할수 없으므로
            gps.showSettingsAlert();
        }
    }
    /* ******************* GPS methods end ******************* */

    /* ****************** Memo methods start ********************** */
    public void saveMemo() {
        if (pointNum == null) {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
            return;
        }
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/memofile/" + workNum + "_" + pointNum + "_" + "memo.txt";
        File clientMemoFile = new File(clientMemoPath);

        String memoStr = et_client_memo.getText().toString();
        try {
            if (!clientMemoFile.exists()) {
                try {
                    FileOutputStream fos = new FileOutputStream(clientMemoFile);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
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

    public void deleteMemo() {
        if (pointNum == null) {
            Toast.makeText(getBaseContext(), "작업할 마커를 선택해주세요.", Toast.LENGTH_SHORT).show();
            return;
        }
        String clientMemoPath = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/memofile/" + workNum + "_" + pointNum + "_" + "memo.txt";
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
            bundleData.putString("work_num", workNum);
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
            bundleData.putString("work_num", workNum);
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
                    // if use forth method
                    try {
                        ArrayList<Uri> uris = data.getParcelableArrayListExtra("selected");
                        for (Uri uri : uris) {
                            // add to RecyclerView
                            recyclerAdapter.addUri(uri);
                            Log.d(TAG, String.format("received uri : %s", uri.toString()));

                            // get image file path from uri
                            String path = uri.getPath();

                            // 선택한 이미지를 업로드용 폴더에 추가한 후, upImageList에 추가
                            upImageList.add(copyAndReturnFile(path, "IMAGE"));

                            // add text file to upTextList
                            upTextList.add(copyAndReturnFile(path, "TEXT"));
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                        Toast.makeText(this, "failed to receive image data...", Toast.LENGTH_SHORT).show();
                    }
                    break;
                }
                case CAMERA_CODE: {
                    //카메라에서 가져오기
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    public File copyAndReturnFile(String path, String mode) {
        String fileName;
        String filePath;

        // get file name, path
        String[] splitPath = path.split("/");
        fileName = splitPath[splitPath.length - 1];
        if (mode.equals("TEXT")) {
            fileName = fileName.replace(".png", ".txt");
            splitPath[splitPath.length - 1] = "textfile/";
        }
        filePath = TextUtils.join("/", splitPath);
        if (mode.equals("TEXT")) filePath += fileName;
        Log.d(TAG, String.format("path : %s, filePath : %s, fileName : %s", path, filePath, fileName));

        // get file
        File file = new File(filePath);
        if (file.exists()) {
            if (mode.equals("IMAGE")) {
                try {
                    // make streams
                    FileInputStream fis = new FileInputStream(file);
                    FileOutputStream newFos = new FileOutputStream(String.format("%s/%s/%s/%s/%s", Environment.getExternalStorageDirectory(), workNum, pointNum, "uploadfile", fileName));

                    // copy
                    int readCount = 0;
                    byte[] buffer = new byte[1024];
                    while ((readCount = fis.read(buffer, 0, 1024)) != -1) {
                        newFos.write(buffer, 0, readCount);
                    }

                    // close streams
                    newFos.close();
                    fis.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            // return image or text file
            return file;
        }
        return null;
    }
    /* ******************* camera & gallery methods end ******************* */


    /* ******************* text file methods start ******************* */
    public String getFileContents(final File file) {
        final StringBuilder stringBuilder = new StringBuilder();

        try {
            final InputStream inputStream = new FileInputStream(file);
            final BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream, StandardCharsets.UTF_8));
            boolean done = false;

            while (!done) {
                final String line = reader.readLine();
                done = (line == null);

                if (line != null) {
                    stringBuilder.append(line);
                }
            }

            reader.close();
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return stringBuilder.toString();
    }
    /* ******************* text file methods end ******************* */

    /* ******************* ArrayList for upload test methods start ******************* */
    public void checkArrayListForUpload() {
        if (upImageList != null) {
            for (File file : upImageList) {
                Log.d(TAG, String.format("check image : %s", file.getAbsolutePath()));
            }
        }

        if (upTextList != null) {
            for (File file : upTextList) {
                Log.d(TAG, String.format("check text : %s", file.getAbsolutePath()));
                try {
                    FileReader fr = new FileReader(file);
                    BufferedReader br = new BufferedReader(fr);
                    Log.d(TAG, String.format("check text content : %s", br.readLine()));
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    /* ******************* ArrayList for upload test methods end ******************* */
}
