package com.aliyun.rtc.rtcinteractiveclassplayer.network;

import java.util.Map;

import okhttp3.RequestBody;

public class OkHttpCientManager {

    private OkhttpClient okhttpClient;

    private OkHttpCientManager() {
        if (okhttpClient == null) {
            okhttpClient = new OkhttpClient();
        }
    }

    private static final class OkHttpCientManagerInstance {
        private static final OkHttpCientManager INSTANCE = new OkHttpCientManager();
    }

    public static OkHttpCientManager getInstance() {
        return OkHttpCientManagerInstance.INSTANCE;
    }

    public void doGet(String url, Map<String, String> params, final OkhttpClient.HttpCallBack callBack) {
        if (okhttpClient != null) {
            okhttpClient.doGet(url, params, callBack);
        }
    }

    public void doPost(String url, RequestBody body, final OkhttpClient.HttpCallBack callBack) {
        if (okhttpClient != null) {
            okhttpClient.doPost(url, body, callBack);
        }
    }
}
