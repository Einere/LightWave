package com.example.einere.myapplication;

import android.graphics.Bitmap;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import java.util.List;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.RecyclerViewHolder> {
    private List<Bitmap> bitmaps;

    RecyclerViewAdapter(List<Bitmap> bitmaps) {
        this.bitmaps = bitmaps;
    }

    @NonNull
    @Override
    public RecyclerViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View view = LayoutInflater.from(viewGroup.getContext())
                .inflate(R.layout.item_image, viewGroup, false);
        return new RecyclerViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerViewHolder recyclerViewHolder, int i) {
        Bitmap bitmap = bitmaps.get(i);
        recyclerViewHolder.iv_tmp.setImageBitmap(bitmap);
    }

    @Override
    public int getItemCount() {
        return bitmaps.size();
    }

    public int pushUri(Bitmap bitmap) {
        bitmaps.add(bitmap);
        return bitmaps.size() - 1;
    }

    public void clearUri() {
        bitmaps.clear();
    }

    class RecyclerViewHolder extends RecyclerView.ViewHolder {
        ImageView iv_tmp;

        RecyclerViewHolder(View view) {
            super(view);
            this.iv_tmp = (ImageView) view;
        }
    }
}
