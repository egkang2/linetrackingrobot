package com.example.wifihandler;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.HashMap;
import java.util.Map;

public class Auto_Control extends AppCompatActivity implements View.OnClickListener, MDNSClient.OnIPAddressResolvedListener,MDNSClient.OnIPAddressResolvedListener2 {
        MDNSClient mdnsClient;

        private ImageButton waypoint1,waypoint2,waypoint3,waypoint4,waypoint5,waypoint6,handle;

        private String getip;
        private String getip2;
        String cmdText;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.auto_control);
            mdnsClient.getArduinoIPAddress(this);
            mdnsClient.getArduinoIPAddress2(this);

            waypoint1 = findViewById(R.id.waypoint1);
            waypoint2 = findViewById(R.id.waypoint2);
            waypoint3 = findViewById(R.id.waypoint3);
            waypoint4 = findViewById(R.id.waypoint4);
            waypoint5 = findViewById(R.id.waypoint5);
            waypoint6 = findViewById(R.id.waypoint6);
            handle=findViewById(R.id.handle);



            waypoint1.setOnClickListener(this);
            waypoint2.setOnClickListener(this);
            waypoint3.setOnClickListener(this);
            waypoint4.setOnClickListener(this);
            waypoint5.setOnClickListener(this);
            waypoint6.setOnClickListener(this);
            handle.setOnClickListener(this);



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
            RequestQueue requestQueue = Volley.newRequestQueue(Auto_Control.this);
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
            RequestQueue requestQueue = Volley.newRequestQueue(Auto_Control.this);
            requestQueue.add(stringRequest);
        }



        public void onClick(View v) {
            WifiManager wifi = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
            if (wifi.isWifiEnabled()) {
                Log.e("MyApp", "Wifi!");


                String ipAddress = getip;
                String ipAddress2 = getip2;
                switch (v.getId()) {
                    case R.id.waypoint1:
                        cmdText ="f"; // 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd1: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);

                        send(cmdText, ipAddress);
                        break;
                    case R.id.waypoint2:
                        cmdText="g"; // 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd2: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);
                        send(cmdText, ipAddress);
                        break;
                    case R.id.waypoint3:
                        cmdText = "h"; // 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd2: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);
                        send(cmdText, ipAddress);
                        break;
                    case R.id.waypoint4:
                        cmdText = "i";// 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd2: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);
                        send(cmdText, ipAddress);
                        break;
                    case R.id.waypoint5:
                        cmdText = "j"; // 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd2: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);
                        send(cmdText, ipAddress);
                        break;
                    case R.id.waypoint6:
                        cmdText = "k"; // 첫 번째 버튼에 대한 int 값
                        Log.d("MyApp", "cmd2: " +cmdText);
                        Log.d("MyApp", "ip: " +ipAddress);
                        send(cmdText, ipAddress);
                        break;
                    case R.id.handle:

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
