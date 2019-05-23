package com.example.einere.myapplication.history;

import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.capture.CaptureActivity;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class TaskHistoryList extends BaseAdapter {
    private Context mContext;
    private ArrayList<Task> mData;
    private LayoutInflater mLayoutInflater;
    String listenername = null;

    class ViewHolder {
        TextView taskName;
        TextView landNo;

    }

    TaskHistoryList(Context context, ArrayList<Task> data) {
        mContext = context;
        mData = data;
        mLayoutInflater = LayoutInflater.from(mContext);
    }

    public int getCount() {
        return mData.size();
    }

    public long getItemId(int position) {
        return position;
    }

    public Task getItem(int position) {
        return mData.get(position);
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        View itemLayout = convertView;
        ViewHolder viewHolder;

        //리스너 파일 이름

        // 1. 어댑터뷰가 재사용할 뷰를 넘겨주지 않은 경우에만 새로운 뷰를 생성한다.
        if (itemLayout == null) {
            itemLayout = mLayoutInflater.inflate(R.layout.picturelist, null);

            viewHolder = new ViewHolder();
            viewHolder.taskName = itemLayout.findViewById(R.id.txt_taskName);
            viewHolder.landNo = itemLayout.findViewById(R.id.txt_landNo);
            itemLayout.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder) itemLayout.getTag();

        }
        viewHolder.taskName.setText(mData.get(position).taskName);

        //captureActivity 이동
        itemLayout.setOnClickListener(v -> {
            Intent intent = new Intent(mContext, CaptureActivity.class);
            intent.putExtra("method", "history");
            String path = Environment.getExternalStorageDirectory() + "/workHistory/task/" + mData.get(position).taskName + ".txt";
            File file = new File(path);
            if (!file.exists()) {
                Toast.makeText(mContext, "전 작업이 없습니다", Toast.LENGTH_SHORT).show();
            } else {
                StringBuilder sb = new StringBuilder();
                try {
                    InputStream is = new FileInputStream(path);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(is));

                    // read line
                    String line;
                    while ((line = reader.readLine()) != null) {
                        sb.append(line).append("\n");
                    }

                    // close stream
                    reader.close();
                    is.close();
                    JSONObject parsedData = new JSONObject();
                    try {
                        parsedData = new JSONObject(sb.toString());
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    try {
                        JSONObject data = (JSONObject) parsedData.get("data");
                        // work id
                        intent.putExtra("id", data.getString("id"));
                        // work name
                        intent.putExtra("taskName", data.getString("taskName"));
                        // location number
                        intent.putExtra("landNo", data.getString("landNo"));
                        // work information (memo?)
                        intent.putExtra("taskDesc", data.getString("taskDesc"));
                        // receivedData
                        intent.putExtra("receivedData", sb.toString());
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                    mContext.startActivity(intent);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        viewHolder.landNo.setText(mData.get(position).landNo);
        return itemLayout;
    }
}
