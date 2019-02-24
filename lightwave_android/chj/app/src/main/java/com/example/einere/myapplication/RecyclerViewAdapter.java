package com.example.einere.myapplication;

import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.RecyclerViewHolder> {
    private List<Uri> uriList = new ArrayList<>();

    RecyclerViewAdapter() {
    }

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
    }

    @Override
    public int getItemCount() {
        return uriList.size();
    }

    public void addUri(Uri uri) {
        uriList.add(uri);
        notifyDataSetChanged();
    }

    void addAll(List<Uri> uriList) {
        this.uriList.addAll(uriList);
        notifyDataSetChanged();
    }

    public void clearUri() {
        uriList.clear();
    }

    class RecyclerViewHolder extends RecyclerView.ViewHolder {
        ImageView iv_tmp;

        RecyclerViewHolder(View view) {
            super(view);
            this.iv_tmp = (ImageView) view;
        }
    }
}
