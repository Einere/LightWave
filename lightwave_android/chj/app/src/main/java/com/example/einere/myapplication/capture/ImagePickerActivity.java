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
    Button btn_select_done = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_picker);

        // set recycler view
        RecyclerView recyclerView = findViewById(R.id.recycler);
        recyclerView.setLayoutManager(new GridLayoutManager(this, 3));
        ImagePickerAdapter adapter = new ImagePickerAdapter();
        recyclerView.setAdapter(adapter);

        // get directory by path
        String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Download";
        File file = new File(filePath);

        // filter only file
        File[] files = file.listFiles();
        List<String> filePathList = new ArrayList<>();
        for (File f : files) {
            if (f.isFile()) {
                filePathList.add(f.getAbsolutePath());
            }
        }
        adapter.addAll(filePathList);
    }

    class ImagePickerAdapter extends RecyclerView.Adapter<MyHolder> {
        List<String> fileList = new ArrayList<>();
        ArrayList<Uri> selectedList = new ArrayList<>();

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
            // set onClickListener
            if(position == fileList.size()){
                myHolder.button.setOnClickListener(v -> {
                    if(selectedList.size() != 0){
                        Intent intent = new Intent();
                        intent.putParcelableArrayListExtra("selected", selectedList);
                        setResult(RESULT_OK, intent);
                        finish();
                    }else{
                        Toast.makeText(ImagePickerActivity.this, "no image selected...", Toast.LENGTH_SHORT).show();
                    }
                });
            }
            else {
                myHolder.imageView.setOnClickListener(v -> {
                    ImageView iv_tmp = (ImageView) v;
                    if (iv_tmp.getColorFilter() == null) {
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
                        for(Uri uri : selectedList){
                            Log.d(TAG, String.format("selected Uri : %s", uri.toString()));
                        }
                    } else {
                        // clear filter
                        iv_tmp.setColorFilter(null);
                        iv_tmp.setImageAlpha(255);

                        // remove from selected list
                        selectedList.remove(Uri.fromFile(new File(fileList.get(position))));

                        // check
                        for(Uri uri : selectedList){
                            Log.d(TAG, String.format("selected Uri : %s", uri.toString()));
                        }
                    }
                });

                // set image by Glide
                Glide.with(myHolder.itemView.getContext())
                        .load(fileList.get(position))
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