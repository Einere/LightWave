package com.example.einere.myapplication;

import android.Manifest;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.ExifInterface;
import android.net.ConnectivityManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.github.chrisbanes.photoview.PhotoView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    final int STATUS_DISCONNECTED = 0;
    final int STATUS_CONNECTED = 1;
    private final int CAMERA_CODE = 1111;
    private final int GALLERY_CODE = 1112;
    private final String TAG = "MainActivity";
    private GpsInfo gps;

    String ip = "";
    int port = 0;
    SocketManager manager = null;
    String workerName = null;

    LinearLayout ll_imageList = null;
    ArrayList<ImageView> iv_picture = null;
    EditText et_ip1 = null;
    EditText et_ip2 = null;
    EditText et_ip3 = null;
    EditText et_ip4 = null;
    EditText et_port = null;
    EditText et_worker_name = null;
    TextView tv_azimuth = null;

    String captureName = null;
    String actualPath = null;
    Bitmap myBitmap = null;

    SensorManager sensorManager = null;
    Sensor accelerometer = null;
    Sensor magnetometer = null;
    float[] gravity = null;
    float[] geomagnetic = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(TAG, "onCreate()");

        // get view
        ll_imageList = findViewById(R.id.ll_image_list);
        iv_picture = new ArrayList<ImageView>();
//        iv_picture.add((ImageView)findViewById(R.id.iv_selectedImage));
        et_ip1 = findViewById(R.id.et_ip1);
        et_ip2 = findViewById(R.id.et_ip2);
        et_ip3 = findViewById(R.id.et_ip3);
        et_ip4 = findViewById(R.id.et_ip4);
        et_port = findViewById(R.id.et_port);
        et_worker_name = findViewById(R.id.et_worker_name);
        tv_azimuth = findViewById(R.id.tv_azimuth);

        // get sensor manager
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magnetometer = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        // request permission
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.CAMERA,
                Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 0);

        // register broadcast receiver
        IntentFilter intentFilter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
        intentFilter.addAction("android.hardware.action.NEW_PICTURE");
        BroadcastReceiver cameraBroadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                Log.i(TAG, String.format("azimuth1 : %s...", tv_azimuth.getText()));
            }
        };
        registerReceiver(cameraBroadcastReceiver, intentFilter);
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i(TAG, "onResume()");

        // get SocketManager instance
        manager = SocketManager.getInstance();

        // register listener
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_UI);
        sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_UI);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

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
                /*txtPitch.setText("y 좌표:" + String.valueOf(pitch));
                txtRoll.setText("z 좌표 : " + String.valueOf(roll));*/
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
    /* ******************* sensor methods end ******************* */

    /* ******************* socket methods start ******************* */
    public void connectToServer(View v) throws RemoteException {
        // get ip, worker name from EditText
        ip = String.format("%s.%s.%s.%s", et_ip1.getText(), et_ip2.getText(), et_ip3.getText(), et_ip4.getText());
        port = Integer.parseInt(et_port.getText().toString());
        workerName = et_worker_name.getText().toString();

        // set socket and connect to server
        manager.setSocket(ip, port);
        manager.connect();

        // send worker name to server
        // notice to server that connected mobile's worker name
        // so server can register it to currently connected worker list
        while (manager.getStatus() == STATUS_DISCONNECTED) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (manager.getStatus() == STATUS_CONNECTED) {
            JSONObject packet = new JSONObject();
            try {
                packet.put("code", 100);
                packet.put("workerName", workerName);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            manager.send(packet.toString());
            Toast.makeText(this, "Connected!", Toast.LENGTH_SHORT).show();
        }
        else{
            Toast.makeText(this, "retry to connect...", Toast.LENGTH_SHORT).show();
        }
    }

    public void clickPoint(View v){
          Intent intent = new Intent(this, ListViewActivity.class);
          startActivity(intent);
    }

    public void sendData(View v) throws RemoteException, JSONException {
        if (manager.getStatus() == STATUS_CONNECTED && myBitmap != null) {
            // make json object
            JSONObject packet = new JSONObject();
            packet.put("code", 101);
            packet.put("workerName", workerName);

            // put bitmap data
            ByteArrayOutputStream stream = new ByteArrayOutputStream();
            myBitmap.compress(Bitmap.CompressFormat.JPEG, 100, stream);
            byte[] bytes = stream.toByteArray();
            String serialized = Base64.encodeToString(bytes, Base64.NO_WRAP);
            Log.i(TAG, serialized);
            packet.put("image", serialized);

            manager.send(packet.toString());
        } else {
            Toast.makeText(this, "not connected to server or no selected image", Toast.LENGTH_SHORT).show();
        }
    }

    public void receiveData(View v) throws RemoteException {
        if (manager.getStatus() == STATUS_CONNECTED) {
            manager.receive();
        } else {
            Toast.makeText(this, "not connected to server", Toast.LENGTH_SHORT).show();
        }
    }
    /* ******************* socket methods end ******************* */

    /* *****************GPS**************************** */
    public void Gps(){
        gps = new GpsInfo(MainActivity.this);
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

    /* ******************* camera & gallery methods start ******************* */
    public void capture(View v) {
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

    private void addPicture(Bitmap bitmap){
        // use ImageView
//        ImageView iv_tmp = new ImageView(this);
//        iv_tmp.setImageBitmap(bitmap);
//        iv_tmp.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
//        iv_tmp.setPadding(5, 5, 5, 5);
//        iv_tmp.setMaxHeight(dpToPx(100));
//        iv_tmp.setMaxWidth(dpToPx(100));
//        iv_tmp.setAdjustViewBounds(true);
//        ll_imageList.addView(iv_tmp);

        // use PhotoView (third-party library)
        PhotoView pv_tmp = new PhotoView(this);
        pv_tmp.setImageBitmap(bitmap);
        pv_tmp.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        pv_tmp.setPadding(5, 5, 5, 5);
        pv_tmp.setMaxHeight(dpToPx(100));
        pv_tmp.setMaxWidth(dpToPx(100));
        pv_tmp.setAdjustViewBounds(true);
        ll_imageList.addView(pv_tmp);
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
    }
    /* ******************* camera & gallery methods end ******************* */
}
