package com.alivc.base;

import com.alibaba.fastjson.JSONObject;

import org.apache.commons.lang3.StringUtils;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

/**
 * 用于获取远程服务器中ak的信息
 */
public class AkUtil {

    public static JSONObject getAkInfo() throws Exception {
        String accessKeyID = ConfigMapUtil.getValueByKey("accessKeyID");
        String accessKeySecret = ConfigMapUtil.getValueByKey("accessKeySecret");

        JSONObject jsonObject;
        if (StringUtils.isNotBlank(accessKeyID) && StringUtils.isNotBlank(accessKeySecret)) {
            jsonObject = new JSONObject();
            jsonObject.put("AccessKeyId", accessKeyID);
            jsonObject.put("AccessKeySecret", accessKeySecret);
            return jsonObject;

        } else {
            String url = "http://100.100.100.200/latest/meta-data/ram/security-credentials/" + ConfigMapUtil
                .getValueByKey("roleName");
            String response = httpGet(url);
            jsonObject = JSONObject.parseObject(response);
            return jsonObject;
        }
    }

    private static String httpGet(String url) throws Exception {
        CloseableHttpClient httpClient = null;
        try {
            httpClient = HttpClients.createDefault();
            HttpGet httpGet = new HttpGet();
            httpGet.setURI(new URI(url));
            RequestConfig requestConfig = RequestConfig.custom()
                .setConnectTimeout(3000)
                .setSocketTimeout(3000)
                .build();
            httpGet.setConfig(requestConfig);
            HttpResponse result = httpClient.execute(httpGet);
            String str;
            try {
                /** 读取服务器返回过来的json字符串数据 **/
                str = EntityUtils.toString(result.getEntity());
                result.getEntity();

                EntityUtils.consume(result.getEntity());
            } catch (Exception e) {
                e.printStackTrace();
                throw e;
            }
            return str;
        } catch (URISyntaxException e) {
            e.printStackTrace();
            throw e;
        } catch (ClientProtocolException e) {
            e.printStackTrace();
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
            throw e;
        } finally {
            try {
                if (httpClient != null) {
                    httpClient.close();
                }

            } catch (Exception e) {
                e.printStackTrace();
                throw e;
            }
        }
    }

}


