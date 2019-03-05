package com.example.einere.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;

public class ListViewActivity  extends AppCompatActivity {

    ListView mListView = null;
    PictureList pictureList = null;
    TextView txt_pictureName = null;
    ArrayList<Picture> mData = null;
    private final int GALLERY_CODE = 1112;

    public void selectPicture(View v){
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setDataAndType(android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI, "image/*");
        startActivityForResult(intent, GALLERY_CODE);
    }


    public void takePicture(View v){
        Intent intent = new Intent(this, CameraActivity.class);
        startActivity(intent);
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview);
        Log.i("activity_listview", "onCreate()");

        mData = new ArrayList<Picture>();

        //추후에 점에 따라 디렉토리명 바꿈
        String path = Environment.getExternalStorageDirectory()+"/path/";
        File file = new File(path);

        /*추후 위치 방위 에 쓸 예정 및 메모*/
       // File list[] =file.listFiles();


        //사진파일명 리스트 뽑아오기
        String[] imgList = file.list(new FilenameFilter() {
           public boolean accept(File dir, String filename) {
           Boolean bOK = false;
          if(filename.toLowerCase().endsWith(".png")) bOK = true;

          if(filename.toLowerCase().endsWith(".9.png")) bOK = true;

          if(filename.toLowerCase().endsWith(".gif")) bOK = true;

          if(filename.toLowerCase().endsWith(".jpg")) bOK = true;

        return bOK;
    }
});

        for(int i = 0; i < imgList.length; i++){
        Picture picture = new Picture();
        picture.pname = imgList[i];
        mData.add(picture);
        }

        pictureList = new PictureList(this, mData);
        mListView = (ListView)findViewById(R.id.List_view);
        mListView.setAdapter(pictureList);

    }
}
