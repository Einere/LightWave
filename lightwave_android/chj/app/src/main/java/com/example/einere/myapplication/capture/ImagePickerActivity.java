package com.example.einere.myapplication.capture;

import android.content.Intent;
import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.resource.bitmap.RoundedCorners;
import com.bumptech.glide.request.RequestOptions;
import com.example.einere.myapplication.R;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class ImagePickerActivity extends AppCompatActivity {
    final String TAG = "ImagePickerActivity";
    int itemWidth = 0;
    int itemHeight = 0;
    int horizontalItemNumber = 2;
    int verticalItemNumber = 3;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_picker);

        //작업정보고유번호, 마커고유번호 가져오기
        Intent intent = getIntent();
        Bundle bundleData = intent.getBundleExtra("ID_NUM");
        String work_num = bundleData.getString("work_num");
        // id_number
        String c_point_num = bundleData.getString("c_point_num");
        Log.d(TAG, String.format("work_num : %s, c_point_num : %s", work_num, c_point_num));

        // get dynamic item size
        DisplayMetrics displaymetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displaymetrics);
        itemWidth = displaymetrics.widthPixels / horizontalItemNumber;
        itemHeight = displaymetrics.heightPixels / verticalItemNumber;
        Log.d(TAG, String.format("width : %d, height : %d", itemWidth, itemHeight));

        // set recycler view
        RecyclerView recyclerView = findViewById(R.id.recycler);
        recyclerView.setLayoutManager(new GridLayoutManager(this, horizontalItemNumber));
        ImagePickerAdapter adapter = new ImagePickerAdapter();
        recyclerView.setAdapter(adapter);

        // get directory by path
        String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + work_num + "/" + c_point_num;
        File file = new File(filePath);

        // filter only file
        File[] files = file.listFiles();
        List<String> filePathList = new ArrayList<>();
        if(files != null){
            for (File f : files) {
                if (f.isFile()) {
                    filePathList.add(f.getAbsolutePath());
                }
            }
            adapter.addAll(filePathList);
        }
        else{
            Toast.makeText(this, "folder is empty...", Toast.LENGTH_SHORT).show();
        }
    }

    class ImagePickerAdapter extends RecyclerView.Adapter<MyHolder> {
        List<String> fileList = new ArrayList<>();
        ArrayList<Uri> selectedList = new ArrayList<>();
        int maxCount = 5;

        @NonNull
        @Override
        public MyHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int viewType) {
            View itemView;
            if (viewType == R.layout.image_picker_image_item) {
                itemView = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.image_picker_image_item, viewGroup, false);
            } else {
                itemView = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.image_picker_button_item, viewGroup, false);
            }
            return new MyHolder(itemView);
        }

        @Override
        public void onBindViewHolder(@NonNull MyHolder myHolder, int position) {
            // if button
            if (position == fileList.size()) {
                // set size
                // 높이 설정이 되긴 하지만, 같은 행의 다른 아이템의 높이에 영향을 받는 듯 하다.
                /*myHolder.button.getLayoutParams().width = itemWidth / 2;
                myHolder.button.getLayoutParams().height = itemHeight / 2;*/

                // set click listener
                myHolder.button.setOnClickListener(v -> {
                    if (selectedList.size() != 0) {
                        Intent intent = new Intent();
                        intent.putParcelableArrayListExtra("selected", selectedList);
                        setResult(RESULT_OK, intent);
                        finish();
                    } else {
                        Toast.makeText(ImagePickerActivity.this, "no image selected...", Toast.LENGTH_SHORT).show();
                    }
                });
            }
            // if imageView
            else {
                // set size
                /*myHolder.imageView.getLayoutParams().width = itemWidth;
                myHolder.imageView.getLayoutParams().height = itemHeight;*/

                // set click listener
                myHolder.imageView.setOnClickListener(v -> {
                    ImageView iv_tmp = (ImageView) v;
                    if (iv_tmp.getColorFilter() == null) {
                        // if select max count
                        if (selectedList.size() >= maxCount) {
                            Toast.makeText(ImagePickerActivity.this, "already selected max images", Toast.LENGTH_SHORT).show();
                            return;
                        }

                        // make gray scale matrix
                        ColorMatrix matrix = new ColorMatrix();
                        matrix.setSaturation(0);

                        // make color filter
                        ColorFilter colorFilter = new ColorMatrixColorFilter(matrix);

                        // set filter to ImageView
                        iv_tmp.setColorFilter(colorFilter);
                        iv_tmp.setImageAlpha(128);

                        // add at selected list
                        selectedList.add(Uri.fromFile(new File(fileList.get(position))));

                        // check
                        for (Uri uri : selectedList) {
                            Log.d(TAG, String.format("selected Uri : %s", uri.toString()));
                        }
                    } else {
                        // clear filter
                        iv_tmp.setColorFilter(null);
                        iv_tmp.setImageAlpha(255);

                        // remove from selected list
                        selectedList.remove(Uri.fromFile(new File(fileList.get(position))));

                        // check
                        for (Uri uri : selectedList) {
                            Log.d(TAG, String.format("selected Uri : %s", uri.toString()));
                        }
                    }
                });

                // set image by Glide
                Glide.with(myHolder.itemView.getContext())
                        .load(fileList.get(position))
                        .override(itemWidth, itemHeight)
                        .apply(new RequestOptions().transform(new RoundedCorners(20)))
                        .into(myHolder.imageView);
            }
        }

        @Override
        public int getItemCount() {
            // for button
            return fileList.size() + 1;
        }

        @Override
        public int getItemViewType(int position) {
            return (position == fileList.size()) ? R.layout.image_picker_button_item : R.layout.image_picker_image_item;
        }

        void addAll(List<String> fileList) {
            this.fileList.addAll(fileList);
            notifyDataSetChanged();
        }


    }

    class MyHolder extends RecyclerView.ViewHolder {
        ImageView imageView;
        Button button;

        MyHolder(@NonNull View itemView) {
            super(itemView);
            imageView = itemView.findViewById(R.id.iv_image_picker_item);
            button = itemView.findViewById(R.id.btn_image_picker_complete);
        }
    }

}