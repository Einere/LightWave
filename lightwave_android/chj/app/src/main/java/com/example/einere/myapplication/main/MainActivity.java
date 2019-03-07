package com.example.einere.myapplication.main;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.example.einere.myapplication.R;
import com.example.einere.myapplication.capture.CaptureActivity;

public class MainActivity extends AppCompatActivity {
    private final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(TAG, "onCreate()");

        // set listener
        findViewById(R.id.btn_new_capture).setOnClickListener(v -> goToNewCapture());
        findViewById(R.id.btn_continue_capture).setOnClickListener(v -> goToContinueCapture());
        findViewById(R.id.btn_check_history).setOnClickListener(v -> goToCheckHistory());
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i(TAG, "onResume()");
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    public void goToNewCapture() {
        Intent intent = new Intent(this, CaptureActivity.class);
        intent.putExtra("method", "new");
        startActivity(intent);
    }

    public void goToContinueCapture() {
        Intent intent = new Intent(this, CaptureActivity.class);
        intent.putExtra("method", "continue");
        startActivity(intent);
    }

    public void goToCheckHistory() {
//        Intent intent = new Intent(this, CaptureActivity.class);
//        startActivity(intent);
    }
}
