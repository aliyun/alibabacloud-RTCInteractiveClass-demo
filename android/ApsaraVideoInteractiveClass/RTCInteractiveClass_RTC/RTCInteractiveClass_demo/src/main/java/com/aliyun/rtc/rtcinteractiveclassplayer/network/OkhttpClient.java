package com.aliyun.rtc.rtcinteractiveclassplayer.network;

import android.text.TextUtils;
import android.util.Log;

import com.aliyun.rtc.rtcinteractiveclassplayer.R;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ApplicationContextUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.PackageUtil;

import java.io.IOException;
import java.net.URLEncoder;
import java.security.SecureRandom;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.Map;
import java.util.concurrent.TimeUnit;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLPeerUnverifiedException;
import javax.net.ssl.SSLSession;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.FormBody;
import okhttp3.Interceptor;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;


public class OkhttpClient {

    private static final long CONNECT_TIMEOUT = 15;
    private static final long READ_TIMEOUT = 15;
    private static final long WRITE_TIMEOUT = 15;
    private static final String TAG = OkHttpClient.class.getSimpleName();
    private OkHttpClient okHttpClient;

    public OkhttpClient() {
        initOkHttpClient();
    }

    private void initOkHttpClient() {
        if (okHttpClient == null) {
            okHttpClient = new OkHttpClient();
        }

        okHttpClient = this.okHttpClient.newBuilder()
                       .connectTimeout(CONNECT_TIMEOUT, TimeUnit.SECONDS)
                       .readTimeout(READ_TIMEOUT, TimeUnit.SECONDS)
                       .writeTimeout(WRITE_TIMEOUT, TimeUnit.SECONDS)
                       .sslSocketFactory(createSSLSocketFactory())
                       .addInterceptor(getInterceptor())
                       .hostnameVerifier(getHostNameVerifier())
                       .build();
    }

    public static class TrustAllCerts implements X509TrustManager {

        @Override
        public void checkClientTrusted(X509Certificate[] chain, String authType) throws CertificateException {

        }

        @Override
        public void checkServerTrusted(X509Certificate[] chain, String authType) throws CertificateException {

        }

        @Override
        public X509Certificate[] getAcceptedIssuers() {
            return new X509Certificate[0];
        }


    }

    private static SSLSocketFactory createSSLSocketFactory() {
        SSLSocketFactory ssfFactory = null;
        try {
            SSLContext sc = SSLContext.getInstance("TLS");
            sc.init(null, new TrustManager[] {new TrustAllCerts()}, new SecureRandom());

            ssfFactory = sc.getSocketFactory();
        } catch (Exception e) {
        }

        return ssfFactory;
    }

    private Interceptor getInterceptor() {
        return new MyInterceptor();
    }

    private HostnameVerifier getHostNameVerifier() {
        return new MyHostnameVerifier();
    }

    private static class MyInterceptor implements Interceptor {

        @Override
        public Response intercept(Chain chain) throws IOException {
            Response response = null;
            if (chain != null) {
                String appName = ApplicationContextUtil.getAppContext().getResources().getString(R.string.app_name);
                appName = URLEncoder.encode(appName, "UTF-8");
                Request request = chain.request();
                request = request.newBuilder()
                          .addHeader("Content-Type", "application/x-www-form-urlencoded")
                          .addHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.146 Safari/537.36")
                          /*添加公共参数*/
                          .addHeader("appName", appName)
                          //                .add("moduleName")
                          .addHeader("appVersionCode", String.valueOf(PackageUtil.packageCode(ApplicationContextUtil.getAppContext())))
                          .addHeader("bundleId", PackageUtil.packageName(ApplicationContextUtil.getAppContext()))//包名
                          .build();
                long t1 = System.nanoTime();
                Log.d(TAG, String.format("Sending request %s on %s%n%s",
                                         request.url(), chain.connection(), request.headers()));

                response = chain.proceed(request);

                long t2 = System.nanoTime();
                Log.d(TAG, String.format("Received response for %s in %.1fms%n%s",
                                         response.request().url(), (t2 - t1) / 1e6d, response.headers()));
            }
            return response;
        }
    }

    private static class MyHostnameVerifier implements HostnameVerifier {
        @Override
        public boolean verify(String hostname, SSLSession session) {
            java.security.cert.Certificate[] localCertificates = new java.security.cert.Certificate[0];
            try {
                //获取证书链中的所有证书
                localCertificates = session.getPeerCertificates();
            } catch (SSLPeerUnverifiedException e) {
                e.printStackTrace();
            }
            //打印所有证书内容
            for (Certificate c : localCertificates) {
                Log.d(TAG, "verify: " + c.toString());
            }
            return true;
        }
    }

    public void doGet(String url, Map<String, String> params, final HttpCallBack callBack) {
        Request request = buildGetRequest(url, params);
        if (request != null && okHttpClient != null) {
            okHttpClient.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    if (callBack != null) {
                        callBack.onFaild(e.getMessage());
                    }
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response != null && callBack != null) {
                        String result = response.body().string();
                        if (response.isSuccessful()) {
                            callBack.onSuccess(result);
                        } else {
                            callBack.onFaild(response.message());
                        }
                    }
                }
            });
        }
    }


    public void doPost(String url, RequestBody body, final HttpCallBack callBack) {
        Request request = buildPostRequest(url, body);
        if (request != null && okHttpClient != null) {
            okHttpClient.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    if (callBack != null) {
                        callBack.onFaild(e.getMessage());
                    }
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response != null) {
                        String result = response.body().string();
                        if (callBack != null) {
                            callBack.onSuccess(result);
                        }
                    }
                }
            });
        }
    }

    private Request buildPostRequest(String url, RequestBody body) {
        Request request = null;
        Request.Builder builder = null;
        if (!TextUtils.isEmpty(url)) {
            builder = new Request.Builder()
            .url(url);
        }

        if (body != null && builder != null) {
            request = builder.post(body).build();
        } else if (body == null && builder != null) {
            request = builder.post(new FormBody.Builder().build()).build();
        }

        return request;
    }

    private Request buildGetRequest(String url, Map<String, String> params) {
        Request request = null;
        if (!TextUtils.isEmpty(url)) {
            StringBuilder sb = new StringBuilder(url);
            sb.append("?");
            if (null != params && params.size() > 0) {
                for (Map.Entry<String, String> entry : params.entrySet()) {
                    String key = entry.getKey();
                    String value = entry.getValue();
                    sb.append(key);
                    sb.append("=");
                    sb.append(value);
                    sb.append("&");
                }
            }
            sb.delete(sb.length() - 1, sb.length());//删掉最后一个&符
            request = new Request.Builder()
            .url(sb.toString())
            .get()
            .build();
        }

        return request;
    }

    public interface HttpCallBack {
        void onSuccess(String result);

        void onFaild(String errorMsg);
    }
}
