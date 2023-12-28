package com.example.wifihandler;

import android.os.AsyncTask;

import androidx.appcompat.app.AppCompatActivity;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class MDNSClient {
    private static final String HOSTNAME = "arduino"; // 아두이노의 호스트 이름
    private static final String DEFAULT_IP_ADDRESS = "192.168.104.241"; // 기본 IP 주소
    private static final String DEFAULT_IP_ADDRESS2 = "192.168.33.49";

    public interface OnIPAddressResolvedListener {
        void onIPAddressResolved(String ipAddress);
    }
    public interface OnIPAddressResolvedListener2 {
        void onIPAddressResolved2(String ipAddress2);
    }

    public static void getArduinoIPAddress(OnIPAddressResolvedListener listener) {
        new ResolveIPAddressTask(listener).execute();
    }
    public static void getArduinoIPAddress2(OnIPAddressResolvedListener2 listener) {
        new ResolveIPAddressTask2(listener).execute();
    }

    private static class ResolveIPAddressTask extends AsyncTask<Void, Void, String> {
        private final OnIPAddressResolvedListener listener;

        public ResolveIPAddressTask(OnIPAddressResolvedListener listener) {
            this.listener = listener;
        }


        @Override
        protected String doInBackground(Void... voids) {
            try {
                InetAddress address = InetAddress.getByName(HOSTNAME);
                return address.getHostAddress();
            } catch (UnknownHostException e) {
                e.printStackTrace();
                return null;
            }
        }

        @Override
        protected void onPostExecute(String ipAddress) {
            if (listener != null) {
                if (ipAddress != null) {
                    listener.onIPAddressResolved(ipAddress);
                } else {
                    listener.onIPAddressResolved(DEFAULT_IP_ADDRESS2);


                }
            }
        }

    }
    private static class ResolveIPAddressTask2 extends AsyncTask<Void, Void, String> {
        private final OnIPAddressResolvedListener2 listener;

        public ResolveIPAddressTask2(OnIPAddressResolvedListener2 listener) {
            this.listener = listener;
        }


        @Override
        protected String doInBackground(Void... voids) {
            try {
                InetAddress address = InetAddress.getByName(HOSTNAME);
                return address.getHostAddress();
            } catch (UnknownHostException e) {
                e.printStackTrace();
                return null;
            }
        }

        @Override
        protected void onPostExecute(String ipAddress2) {
            if (listener != null) {
                if (ipAddress2 != null) {
                    listener.onIPAddressResolved2(ipAddress2);
                } else {

                    listener.onIPAddressResolved2(DEFAULT_IP_ADDRESS);

                }
            }
        }

    }
}
