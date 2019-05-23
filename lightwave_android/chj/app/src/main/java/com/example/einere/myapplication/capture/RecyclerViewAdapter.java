package com.example.einere.myapplication.capture;

import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.example.einere.myapplication.R;

import java.util.ArrayList;
import java.util.List;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.RecyclerViewHolder> {
    private List<Uri> uriList = new ArrayList<>();
    private List<Integer> selectedList = new ArrayList<>();

    @NonNull
    @Override
    public RecyclerViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View view = LayoutInflater.from(viewGroup.getContext())
                .inflate(R.layout.item_image, viewGroup, false);
        return new RecyclerViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerViewHolder holder, int i) {
        Uri uri = uriList.get(i);
        holder.iv_tmp.setImageURI(uri);
        holder.iv_tmp.setOnClickListener(v -> {
            ImageView iv_tmp = (ImageView)v;
            if(iv_tmp.getColorFilter() == null){
                // make gray scale matrix
                ColorMatrix matrix = new ColorMatrix();
                matrix.setSaturation(0);
                // make color filter
                ColorFilter colorFilter = new ColorMatrixColorFilter(matrix);
                // set filter to ImageView
                iv_tmp.setColorFilter(colorFilter);
                iv_tmp.setImageAlpha(128);
                // add selected list
                selectedList.add(i);
            }
            else{
                // clear filter
                iv_tmp.setColorFilter(null);
                iv_tmp.setImageAlpha(255);
                // remove from selected list
                selectedList.remove((Integer) i);
            }
        });
        holder.iv_tmp.setOnLongClickListener(v -> {
            uriList.remove(i);
            notifyDataSetChanged();

            // need to remove item from CaptureActivity.upTextList
            return false;
        });
    }

    @Override
    public int getItemCount() {
        return uriList.size();
    }

    void addUri(Uri uri) {
        uriList.add(uri);
        notifyDataSetChanged();
    }

    void addUriList(List<Uri> uriList) {
        this.uriList.addAll(uriList);
        notifyDataSetChanged();
    }

    void clearUriList() {
        uriList.clear();
        notifyDataSetChanged();
    }

    ArrayList<Uri> getUriList() {
        return new ArrayList<>(uriList);
    }

    ArrayList<Uri> getSelectedUriList(){
        ArrayList<Uri> selectedUriList = new ArrayList<>();
        for(int i : selectedList){
            selectedUriList.add(uriList.get(i));
        }
        return selectedUriList;
    }

    class RecyclerViewHolder extends RecyclerView.ViewHolder {
        ImageView iv_tmp;

        RecyclerViewHolder(View view) {
            super(view);
            this.iv_tmp = (ImageView) view;
        }
    }
}
