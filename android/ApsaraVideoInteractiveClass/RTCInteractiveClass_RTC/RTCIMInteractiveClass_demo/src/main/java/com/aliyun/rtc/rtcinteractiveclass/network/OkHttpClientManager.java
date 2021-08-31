package com.aliyun.rtc.rtcinteractiveclass.network;

import java.util.Map;

import okhttp3.RequestBody;

public class OkHttpClientManager {

    private OkhttpClient okhttpClient;

    private OkHttpClientManager() {
        if (okhttpClient == null) {
            okhttpClient = new OkhttpClient();
        }
    }

    private static final class OkHttpClientManagerInstance {
        private static final OkHttpClientManager INSTANCE = new OkHttpClientManager();
    }

    public static OkHttpClientManager getInstance() {
        return OkHttpClientManagerInstance.INSTANCE;
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
