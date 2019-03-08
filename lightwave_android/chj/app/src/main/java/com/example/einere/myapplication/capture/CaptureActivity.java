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
import android.media.Image;
import android.net.ConnectivityManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.support.v4.app.FragmentActivity;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.einere.myapplication.GpsInfo;
import com.example.einere.myapplication.ListViewActivity;
import com.example.einere.myapplication.R;
import com.example.einere.myapplication.SocketManager;
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
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import gun0912.tedbottompicker.TedBottomPicker;

public class CaptureActivity extends FragmentActivity implements SensorEventListener, OnMapReadyCallback, GoogleMap.OnMarkerClickListener{
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
    String captureName = null;
    String actualPath = null;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_capture);

        //googlemap
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.Googlemap);
        mapFragment.getMapAsync(this); //getMapAsync must be called on the main thread.

        // get views
        rv_selectedImage = findViewById(R.id.rv_selectedImage);
      // tv_azimuth = findViewById(R.id.tv_azimuth);

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
        findViewById(R.id.btn_select_picture).setOnClickListener(v -> selectPicture());
        findViewById(R.id.btn_send_data).setOnClickListener(v -> sendData());
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        // 구글 맵 객체를 불러온다.
        mMap = googleMap;

        // 서울 여의도에 대한 위치 설정
        LatLng seoul = new LatLng(37.52487, 126.92723);
        LatLng seoul2 = new LatLng(37.62487, 126.52723);

        // 구글 맵에 표시할 마커에 대한 옵션 설정
        MarkerOptions makerOptions = new MarkerOptions();
        makerOptions
                .position(seoul)
                .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_YELLOW))
                .title("원하는 위치(위도, 경도)에 마커를 표시했습니다.");

        MarkerOptions makerOptions2 = new MarkerOptions();
        makerOptions2
                .position(seoul2)
                .title("원하는 위치(위도, 경도)에 마커를 표시했습니다.");
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

    public void refreshClick(View v){
        mMap.clear();

    }

    @Override
    public boolean onMarkerClick(Marker marker){


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

    void capture() {
        TedBottomPicker.with(this)
                .show(uri -> {
                    String scheme = uri.getScheme();
                    if (scheme != null && scheme.equals("file")) {
                        Log.d(TAG, uri.getLastPathSegment());
                    }
                    recyclerAdapter.addUri(uri);
                });
    }

    void selectPicture() {
        TedBottomPicker.with(this)
                .setSelectMaxCount(5)
                .setSelectMaxCountErrorText("최대 5장까지 선택가능합니다")
                .setPeekHeight(1600)
                .showTitle(true)
                .setCompleteButtonText("확인")
                .setEmptySelectionText("사진을 선택해주세요")
                .showMultiImage(uriList -> {
                    recyclerAdapter.addUriList(uriList);
                });
    }

    /* ******************* socket methods start ******************* */
    public void clickPoint(View v) {
        Intent intent = new Intent(this, ListViewActivity.class);
        startActivity(intent);
    }

    public void sendData() {
        // check manager status
        try{
            if (socketManager.getStatus() == STATUS_CONNECTED) {
                // get uri list
                List<Uri> uriList = recyclerAdapter.getUriList();

                // make json object
                JSONObject packet = new JSONObject();
                packet.put("code", 101);
                packet.put("userName", socketManager.getUserName());

                // put uri data
                int i = 0;
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                for(Uri uri : uriList){
                    tmpBitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                    tmpBitmap.compress(Bitmap.CompressFormat.JPEG, 100, stream);
                    byte[] bytes = stream.toByteArray();
                    String serialized = Base64.encodeToString(bytes, Base64.NO_WRAP);
                    packet.put(String.format(Locale.KOREA ,"image%d", i), serialized);
                    i++;
                }
                socketManager.send(packet.toString());
            } else {
                Toast.makeText(this, "not connected to server or no selected image", Toast.LENGTH_SHORT).show();
            }
        }
        catch (RemoteException e){
            Toast.makeText(this, "RemoteException occurred!", Toast.LENGTH_SHORT).show();
        }
        catch (JSONException e){
            Toast.makeText(this, "JSONException occurred!", Toast.LENGTH_SHORT).show();
        }
        catch (FileNotFoundException e){
            Toast.makeText(this, "FileNotFoundException occurred!", Toast.LENGTH_SHORT).show();
        }
        catch (IOException e){
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
    /*public void singlePick() {
        TedBottomPicker.with(this)
                .show(uri -> {
                    String scheme = uri.getScheme();
                    if (scheme.equals("file")) {
                        Log.d(TAG, uri.getLastPathSegment());
                    }
                    recyclerAdapter.addUri(uri);
                });
    }

    public void multiPick() {
        TedBottomPicker.with(this)
                .setSelectMaxCount(5)
                .setSelectMaxCountErrorText("최대 5장까지 선택가능합니다")
                .setPeekHeight(1600)
                .showTitle(true)
                .setCompleteButtonText("확인")
                .setEmptySelectionText("사진을 선택해주세요")
                .showMultiImage(uriList -> {
                    recyclerAdapter.addAll(uriList);
                });
    }*/

    /*public void capture(View v) {
        String state = Environment.getExternalStorageState();
        if (Environment.MEDIA_MOUNTED.equals(state)) {
            Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            if (intent.resolveActivity(getPackageManager()) != null) {
                File photoFile = null;
                photoFile = createImageFile();

                if (photoFile != null) {
                    Uri photoUri = FileProvider.getUriForFile(this, getPackageName(), photoFile);
                    intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
                    startActivityForResult(intent, CAMERA_CODE);
                }
            }
        }
    }

    public void selectGallery(View v) {
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setDataAndType(android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI, "image/*");
        startActivityForResult(intent, GALLERY_CODE);
    }

    public File createImageFile() {
        File dir = new File(Environment.getExternalStorageDirectory() + "/path/");
        if (!dir.exists()) {
            dir.mkdirs();
        }
        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.US).format(new Date());
        captureName = String.format("%s.png", timeStamp);

        File storageDir = new File(Environment.getExternalStorageDirectory().getAbsoluteFile() + "/path/" + captureName);
        actualPath = storageDir.getAbsolutePath();

        return storageDir;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            switch (requestCode) {
                case GALLERY_CODE: {
                    if (data != null) {
                        sendPicture(data.getData()); //갤러리에서 가져오기
                    }
                    break;
                }
                case CAMERA_CODE: {
                    getPictureForPhoto(); //카메라에서 가져오기
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    public int dpToPx(int dp) {
        float density = getResources().getDisplayMetrics().density;
        return Math.round((float) dp * density);
    }

    private void addPicture(Bitmap bitmap) {
        // use ImageView
        ImageView iv_tmp = new ImageView(this);
        iv_tmp.setImageBitmap(bitmap);
        iv_tmp.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        iv_tmp.setPadding(5, 5, 5, 5);
        iv_tmp.setMaxHeight(dpToPx(100));
        iv_tmp.setMaxWidth(dpToPx(100));
        iv_tmp.setAdjustViewBounds(true);
        int index = recyclerAdapter.addUri(bitmap);
        recyclerAdapter.notifyItemInserted(index);
    }

    public void getPictureForPhoto() {
        Log.i(TAG, "getPictureForPhoto() called");

        Bitmap bitmap = BitmapFactory.decodeFile(actualPath);
        ExifInterface exif = null;
        try {
            exif = new ExifInterface(actualPath);
        } catch (IOException e) {
            e.printStackTrace();
        }
        int exifOrientation;
        int exifDegree;

        if (exif != null) {
            exifOrientation = exif.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);
            exifDegree = exifOrientationToDegrees(exifOrientation);
        } else {
            exifDegree = 0;
        }

        // create tmp image view, set bitmap image
        addPicture(rotate(bitmap, exifDegree));
    }

    private void sendPicture(Uri imgUri) {
        // path 경로
        String imagePath = getRealPathFromURI(imgUri);
        ExifInterface exif = null;
        try {
            exif = new ExifInterface(imagePath);
        } catch (IOException e) {
            e.printStackTrace();
        }

        int exifOrientation = 0;
        if (exif != null) {
            exifOrientation = exif.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);
        }
        int exifDegree = exifOrientationToDegrees(exifOrientation);

        // translate bitmap from real path
        Bitmap bitmap = BitmapFactory.decodeFile(imagePath);

        // create tmp image view, set bitmap image
        addPicture(rotate(bitmap, exifDegree));
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

    private int exifOrientationToDegrees(int exifOrientation) {
        if (exifOrientation == ExifInterface.ORIENTATION_ROTATE_90) {
            return 90;
        } else if (exifOrientation == ExifInterface.ORIENTATION_ROTATE_180) {
            return 180;
        } else if (exifOrientation == ExifInterface.ORIENTATION_ROTATE_270) {
            return 270;
        }
        return 0;
    }

    private Bitmap rotate(Bitmap src, float degree) {
        // Matrix 객체 생성
        Matrix matrix = new Matrix();
        // 회전 각도 셋팅
        matrix.postRotate(degree);
        // 이미지와 Matrix 를 셋팅해서 Bitmap 객체 생성
        return Bitmap.createBitmap(src, 0, 0, src.getWidth(), src.getHeight(), matrix, true);
    }*/
    /* ******************* camera & gallery methods end ******************* */
}
