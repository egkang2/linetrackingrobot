package com.example.wifihandler;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.content.Intent;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.HashMap;
import java.util.Map;

public class Handle_Control extends AppCompatActivity implements View.OnClickListener, MDNSClient.OnIPAddressResolvedListener,MDNSClient.OnIPAddressResolvedListener2 {
    MDNSClient mdnsClient;

    private ImageButton forward,right,left,back,stop,auto_mode;

    private String getip;
    private String getip2;
    String cmdText;
    Intent intent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.handle_control);
        mdnsClient.getArduinoIPAddress(this);
        mdnsClient.getArduinoIPAddress2(this);

        forward = findViewById(R.id.forwardbutton);
        right = findViewById(R.id.rightbutton);
        left = findViewById(R.id.leftbutton);
        back = findViewById(R.id.backbutton);
        stop = findViewById(R.id.stopbutton);
        auto_mode = findViewById(R.id.automodebutton);



        forward.setOnClickListener(this);
        right.setOnClickListener(this);
        left.setOnClickListener(this);
        back.setOnClickListener(this);
        stop.setOnClickListener(this);
        auto_mode.setOnClickListener(this);



    }


    public void send(String cmdText, String ipaddress) {
        String url="http://"+ipaddress+"/post";
        // ...
        StringRequest stringRequest = new StringRequest(Request.Method.POST, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Log.e("Status", response.trim());
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Log.e("Status", error.toString());
                    }
                }){
            @Override
            protected Map<String, String> getParams() {
                Map<String, String> params= new HashMap<String, String>();
                String value = String.valueOf(cmdText);
                params.put("data",value);
                Log.e("Status", value);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(Handle_Control.this);
        requestQueue.add(stringRequest);
    }
    public void send2(String cmdText, String ipaddress2) {
        String url="http://"+ipaddress2+"/post";
        // ...
        StringRequest stringRequest = new StringRequest(Request.Method.POST, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Log.e("Status", response.trim());
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Log.e("Status", error.toString());
                    }
                }){
            @Override
            protected Map<String, String> getParams() {
                Map<String, String> params= new HashMap<String, String>();
                String value = String.valueOf(cmdText);
                params.put("data",value);
                Log.e("Status", value);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(Handle_Control.this);
        requestQueue.add(stringRequest);
    }


    
    public void onClick(View v) {
        WifiManager wifi = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (wifi.isWifiEnabled()) {
            Log.e("MyApp", "Wifi!");


            String ipAddress = getip;
            String ipAddress2 = getip2;
            switch (v.getId()) {
                case R.id.forwardbutton:
                     cmdText ="a"; // 첫 번째 버튼에 대한 int 값
                    Log.d("MyApp", "cmd1: " +cmdText);
                    Log.d("MyApp", "ip: " +ipAddress2);

                    send(cmdText, ipAddress2);
                    break;
                case R.id.backbutton:
                     cmdText="b"; // 첫 번째 버튼에 대한 int 값
                    Log.d("MyApp", "cmd2: " +cmdText);
                    Log.d("MyApp", "ip: " +ipAddress2);
                    send(cmdText, ipAddress2);
                    break;
                case R.id.leftbutton:
                    cmdText = "c"; // 첫 번째 버튼에 대한 int 값
                    Log.d("MyApp", "cmd2: " +cmdText);
                    Log.d("MyApp", "ip: " +ipAddress2);
                    send(cmdText, ipAddress2);
                    break;
                case R.id.rightbutton:
                    cmdText = "d";// 첫 번째 버튼에 대한 int 값
                    Log.d("MyApp", "cmd2: " +cmdText);
                    Log.d("MyApp", "ip: " +ipAddress2);
                    send(cmdText, ipAddress2);
                    break;
                case R.id.stopbutton:
                    cmdText = "e"; // 첫 번째 버튼에 대한 int 값
                    Log.d("MyApp", "cmd2: " +cmdText);
                    Log.d("MyApp", "ip: " +ipAddress2);
                    send(cmdText, ipAddress2);
                    break;
                case R.id.automodebutton:
                    intent = new Intent(getApplicationContext(),Auto_Control.class);
                    startActivity(intent);

                    break;







            }
        }else {

        }
    }
    public void onIPAddressResolved(String ipAddress) {
        // IP 주소를 변수에 저장하거나 필요한 로직을 수행합니다.
        if (ipAddress != null) {
            getip = ipAddress; // getip 변수에 IP 주소 저장
            // 추가로 수행할 작업이 있다면 이곳에서 처리합니다.
        }

    }
    public void onIPAddressResolved2(String ipAddress2) {
        // IP 주소를 변수에 저장하거나 필요한 로직을 수행합니다.

        if (ipAddress2 != null) {
            getip2 = ipAddress2; // getip 변수에 IP 주소 저장
            // 추가로 수행할 작업이 있다면 이곳에서 처리합니다.
        }
    }





}