package com.example.einere.myapplication;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class PictureList extends BaseAdapter{
    Context             mContext        = null;
    ArrayList<Picture> mData = null;
    LayoutInflater mLayoutInflater = null;
    String  listenername = null;

    class ViewHolder
    {
        TextView pictureName;
        Button btn_selectGallery;
        Button btn_pictureInformation;
        Button btn_sendData;
        Button btn_memo;
    }

    public PictureList(Context context, ArrayList<Picture> data)
    {
        mContext        = context;
        mData = data;
        mLayoutInflater = LayoutInflater.from(mContext);
    }

    public int getCount()
    {
        return mData.size();
    }

    public long getItemId( int position )
    {
        return position;
    }

    public Picture getItem( int position )
    {
        return mData.get( position );
    }

    @Override
    public View getView(final int position,
                        View convertView,
                        ViewGroup parent )
    {
        View        itemLayout = convertView;
        ViewHolder  viewHolder = null;

        //리스너 파일 이름

        // 1. 어댑터뷰가 재사용할 뷰를 넘겨주지 않은 경우에만 새로운 뷰를 생성한다.
        if( itemLayout == null )
        {
            itemLayout = mLayoutInflater.inflate( R.layout.picturelist, null );

            viewHolder = new ViewHolder();
            viewHolder.pictureName = (TextView) itemLayout.findViewById( R.id.txt_pictureName );
            viewHolder.btn_selectGallery = (Button) itemLayout.findViewById( R.id.btn_selectGallery );
            viewHolder.btn_pictureInformation = (Button) itemLayout.findViewById( R.id.btn_pictureInformation );
            viewHolder.btn_sendData = (Button) itemLayout.findViewById( R.id.btn_sendData );
            viewHolder.btn_memo = (Button) itemLayout.findViewById( R.id.btn_memo );
            itemLayout.setTag( viewHolder );
        }
        else
        {
            viewHolder = (ViewHolder)itemLayout.getTag();

        }
        viewHolder.pictureName.setText( mData.get(position).pname );

        //메모버튼
        viewHolder.btn_memo.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(mContext, MemoActivity.class);

                listenername = mData.get(position).pname;
                String txt_filename = listenername;
                int idx = txt_filename.indexOf(".");
                txt_filename = txt_filename.substring(0, idx)+".txt";

                Bundle bundleData = new Bundle();
                bundleData.putString("txt_File",txt_filename);
                intent.putExtra("TXT_FILE", bundleData);
                mContext.startActivity(intent);
            }
        });

        //전송버튼
        viewHolder.btn_sendData.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

            }
        });

        //정보보기버튼
        viewHolder.btn_pictureInformation.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

            }
        });

        //사진보기버튼
        viewHolder.btn_selectGallery.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

            }
        });

        return itemLayout;
    }
}
