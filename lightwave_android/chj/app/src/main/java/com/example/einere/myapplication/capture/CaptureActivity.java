package com.example.einere.myapplication.capture;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.net.ConnectivityManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.support.v4.app.FragmentActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.example.einere.myapplication.CameraActivity;
import com.example.einere.myapplication.GpsInfo;
import com.example.einere.myapplication.ListViewActivity;
import com.example.einere.myapplication.R;
import com.example.einere.myapplication.SocketManager;
import com.example.einere.myapplication.main.MainActivity;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import gun0912.tedbottompicker.TedBottomPicker;
import gun0912.tedbottompicker.TedBottomSheetDialogFragment;

public class CaptureActivity extends FragmentActivity implements SensorEventListener, OnMapReadyCallback, GoogleMap.OnMarkerClickListener {
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    private final int CAMERA_CODE = 1111;
    private final int GALLERY_CODE = 1112;
    private final String TAG = "CaptureActivity";
    private GoogleMap mMap;

    // socket transmission
    SocketManager socketManager = null;

    // RecyclerView
    RecyclerView rv_selectedImage = null;
    RecyclerViewAdapter recyclerAdapter = null;
    Bitmap tmpBitmap = null;

    // sensor
    SensorManager sensorManager = null;
    Sensor accelerometer = null;
    Sensor magnetometer = null;
    float[] gravity = null;
    float[] geomagnetic = null;
    TextView tv_azimuth = null;
    private GpsInfo gps;

    // capture braodcast
    BroadcastReceiver cameraBroadcastReceiver = null;

    // uproad arraylist
    ArrayList<File> up_imagelist = new ArrayList<>();
    ArrayList<File> up_textlist = new ArrayList<>();

    // id_number
    private String c_point_num;
    private String work_num = "111";

    //imgarraylist
    private ArrayList<Image> images = new ArrayList<>();



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_capture);

        //googlemap
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.Googlemap);
        mapFragment.getMapAsync(this); //getMapAsync must be called on the main thread.

        // get views
        rv_selectedImage = findViewById(R.id.rv_selectedImage);
        tv_azimuth = findViewById(R.id.tv_azimuth);

        // get sensor manager
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magnetometer = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        // register camera capture broadcast receiver
        IntentFilter intentFilter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
        intentFilter.addAction("android.hardware.action.NEW_PICTURE");
        cameraBroadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                Log.i(TAG, String.format("azimuth1 : %s...", tv_azimuth.getText()));
                Toast.makeText(getBaseContext(), "captured!!!", Toast.LENGTH_SHORT).show();
            }
        };
        registerReceiver(cameraBroadcastReceiver, intentFilter);

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
    }


    @Override
    public void onMapReady(GoogleMap googleMap) {
        // 구글 맵 객체를 불러온다.
        mMap = googleMap;

        // 서울 여의도에 대한 위치 설정
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
        mMap.addPolyline(poly);
        //카메라 옵션
        CameraPosition cameraPosition = new CameraPosition.Builder()
                .target(seoul)      // Sets the center of the map to Mountain View
                .zoom(18)                   // Sets the zoom
                .bearing(0)                // Sets the orientation of the camera to east
                .tilt(30)                   // Sets the tilt of the camera to 30 degrees
                .build();
        //카메라를 여의도 위치로 옮긴다.
        mMap.moveCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));

    }

    public void refreshClick(View v) {
        mMap.clear();
    }

    @Override
    public boolean onMarkerClick(Marker marker){
        ArrayList<Uri> urilist = new ArrayList<>();
        c_point_num = marker.getTitle();

        File file = new File(Environment.getExternalStorageDirectory()+"/"+work_num);
        if(!file.exists()){
            file.mkdir();
        }
        File file2 = new File(Environment.getExternalStorageDirectory()+"/"+work_num+"/"+c_point_num );
        if(!file2.exists()){
            file2.mkdir();
        }
        //사진파일명 리스트 뽑아오기
        File[] up_imagelist2  = file2.listFiles(new FilenameFilter() {
            public boolean accept(File dir, String filename) {
                Boolean bOK = false;
                if(filename.toLowerCase().endsWith(".png")) bOK = true;

                if(filename.toLowerCase().endsWith(".9.png")) bOK = true;

                if(filename.toLowerCase().endsWith(".gif")) bOK = true;

                if(filename.toLowerCase().endsWith(".jpg")) bOK = true;

                return bOK;
            }
        });

        for(int i = 0; i < up_imagelist2.length; i++){
           up_imagelist.add(up_imagelist2[i]);
           urilist.add(Uri.parse(up_imagelist2[i].getAbsolutePath()));
        }

        //텍스트파일 리스트
        File[] up_textlist2  = file2.listFiles(new FilenameFilter() {
            public boolean accept(File dir, String filename) {
                Boolean bOK = false;
                if(filename.toLowerCase().endsWith(".txt")) bOK = true;
                return bOK;
            }
        });

        for(int i = 0; i < up_textlist2.length; i++){
            up_textlist.add(up_textlist2[i]);
        }

        recyclerAdapter.clearUriList();
        if(urilist!=null) {
            recyclerAdapter.addUriList(urilist);
        }

        return true;
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

        // unregister broadcast receiver
        unregisterReceiver(cameraBroadcastReceiver);
    }


    /* ******************* Ted image picker start ******************* */
    void capture() {
        Intent intent = new Intent(this, CameraActivity.class);
        Bundle bundleData = new Bundle();
        bundleData.putString("c_point_num",c_point_num);
        bundleData.putString("work_num",work_num);
        intent.putExtra("ID_NUM", bundleData);

        startActivity(intent);


       /* TedBottomPicker.with(this)
                .show(uri -> {
                    String scheme = uri.getScheme();
                    if (scheme != null && scheme.equals("file")) {
                        Log.d(TAG, uri.getLastPathSegment());
                    }
                    recyclerAdapter.addUri(uri);
                });*/
    }

    void selectPicture() {
   /*   TedBottomPicker.with(this)
                .setSelectMaxCount(5)
                .setSelectMaxCountErrorText("최대 5장까지 선택가능합니다")
                .setPeekHeight(1600)
                .showTitle(true)
                .setCompleteButtonText("확인")
                .setEmptySelectionText("사진을 선택해주세요")
                .showMultiImage(uriList -> {
                    recyclerAdapter.addUriList(uriList);
                   /* for(int i = 0; i < uriList.size(); i++){
                        String img_fileName = null;
                        String txt_fileName = null;
                        String path = uriList.get(i).getPath();
                        int cut = path.lastIndexOf('/');
                        if(cut != -1){
                           img_fileName = path.substring(cut+1);
                        }
                        int idx = img_fileName.indexOf(".");
                        txt_fileName = img_fileName.substring(0, idx)+".txt";
                      File imgfile = new File(path);
                      up_imagelist.add(imgfile);
                      File txtfile = new File(Environment.getExternalStorageDirectory()+"/"+work_num+"/"+c_point_num+"/"
                              +"textfile"+"/"+txt_fileName);
                      up_textlist.add(txtfile);

                       //갤러리에서 마커폴더로 이미지 이동
                        if(imgfile!=null&&imgfile.exists()){
                            try {
                                FileInputStream fis = new FileInputStream(imgfile);
                                FileOutputStream newfos = new FileOutputStream(Environment.getExternalStorageDirectory()+"/"+work_num+"/"+c_point_num+"/"+img_fileName);
                                int readcount=0;
                                byte[] buffer = new byte[1024];
                                while((readcount = fis.read(buffer,0,1024))!= -1){
                                    newfos.write(buffer,0,readcount);
                                }
                                newfos.close();
                                fis.close();
                                imgfile.delete();
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                        }else {
                        }

                        //임시폴더에서 마커폴더로 텍스트 이동
                        if(txtfile!=null&&txtfile.exists()){
                            try {
                                FileInputStream fis = new FileInputStream(txtfile);
                                FileOutputStream newfos = new FileOutputStream(Environment.getExternalStorageDirectory()+"/"+work_num+"/"+c_point_num+"/"+"textfile/"+txt_fileName);
                                int readcount=0;
                                byte[] buffer = new byte[1024];
                                while((readcount = fis.read(buffer,0,1024))!= -1){
                                    newfos.write(buffer,0,readcount);
                                }
                                newfos.close();
                                fis.close();
                                txtfile.delete();
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                        }else {
                        }
                    }
                });*/

    }
    /* ******************* Ted image picker end ******************* */


    /* ******************* socket methods start ******************* */
    public void clickPoint(View v) {
        Intent intent = new Intent(this, ListViewActivity.class);
        startActivity(intent);
    }

    public void sendData() {
        // check manager status
        try {
            if (socketManager.getStatus() == STATUS_CONNECTED) {
                // get uri list
                List<Uri> uriList = recyclerAdapter.getUriList();

                // make json object
                JSONObject packet = new JSONObject();
                JSONObject data = new JSONObject();
                packet.put("method", "GET");
                packet.put("subject", "test");
                data.put("userName", socketManager.getUserName());

                // put uri data
                int i = 0;
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                for (Uri uri : uriList) {
                    tmpBitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                    tmpBitmap.compress(Bitmap.CompressFormat.JPEG, 100, stream);
                    byte[] bytes = stream.toByteArray();
                    String serialized = Base64.encodeToString(bytes, Base64.NO_WRAP);
                    data.put(String.format(Locale.KOREA, "image%d", i), serialized);
                    i++;
                }
                packet.put("data", data);
                socketManager.send(packet.toString());
                Toast.makeText(this, "send!", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(this, "not connected to server or no selected image", Toast.LENGTH_SHORT).show();
            }
        } catch (RemoteException e) {
            Toast.makeText(this, "RemoteException occurred!", Toast.LENGTH_SHORT).show();
        } catch (JSONException e) {
            Toast.makeText(this, "JSONException occurred!", Toast.LENGTH_SHORT).show();
        } catch (FileNotFoundException e) {
            Toast.makeText(this, "FileNotFoundException occurred!", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            Toast.makeText(this, "IOException occurred!", Toast.LENGTH_SHORT).show();
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
            float R[] = new float[9];
            float I[] = new float[9];

            boolean success = SensorManager.getRotationMatrix(R, I, gravity, geomagnetic);
            if (success) {
                float orientation[] = new float[3];
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


    /* ******************* camera & gallery methods start ******************* */
    public void selectGallery() {
        // first method
        /*Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setDataAndType(android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI, "image/*");*/

        // second method
        /*Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("image/*");
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        startActivityForResult(intent, GALLERY_CODE);*/

        // third method
        /*Intent intent = new Intent();
        intent.setAction(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");
        intent.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true);
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), GALLERY_CODE);*/

        // forth method
        Intent intent = new Intent(this, ImagePickerActivity.class);
        startActivityForResult(intent, GALLERY_CODE);

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
                            Log.d(TAG, String.format("recived uri : %s", uri.toString()));
                            recyclerAdapter.addUri(uri);
                        }
                    } catch (Exception e) {
                        Toast.makeText(this, "failed to receive image data...", Toast.LENGTH_SHORT).show();
                    }

                    /*if (data.getClipData() != null) {
                        // if use third method
                        *//*ClipData clipData = data.getClipData();
                        for (int i = 0; i < clipData.getItemCount(); i++) {
                            Log.d(TAG, String.format("item uri : %s", clipData.getItemAt(i).getUri()));
                        }
                        sendPicture(clipData.getItemAt(0).getUri());*//*

                    } else if (data != null) {
                        //갤러리에서 가져오기
                        sendPicture(data.getData());
                    }*/
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

    private String getRealPathFromURI(Uri contentUri) {
        int column_index = 0;
        String[] proj = {MediaStore.Images.Media.DATA};
        Cursor cursor = getContentResolver().query(contentUri, proj, null, null, null);
        String column = "";

        if (cursor != null && cursor.moveToFirst()) {
            column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            column = cursor.getString(column_index);
            cursor.close();
        }

        return column;
    }
    /* ******************* camera & gallery methods end ******************* */
}
