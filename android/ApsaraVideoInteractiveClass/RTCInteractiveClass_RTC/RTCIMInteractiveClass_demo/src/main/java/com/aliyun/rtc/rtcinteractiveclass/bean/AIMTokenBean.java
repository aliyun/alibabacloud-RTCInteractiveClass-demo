package com.aliyun.rtc.rtcinteractiveclass.bean;

public class AIMTokenBean {

    /**
     * code : 200
     * data : {"accessToken":"oauth_cloud_key:duhSRWIAYDbLDJs+YKNgrP9yXyXLB8QKFO9THsphOlzdHEOHvMLUPjnw7ByMMnWuW7tAKhNtn9l0WFlqlJYHbMF0yg5Plmq5VkGPx6S56C4=","refreshToken":"oauth_cloud_key:3vArcW8iYtNKlBlyC9NRxrNqAsMgYctgmquWCP2XqkjtXOE+anADp4n1KEVRmgVM19jnkdbxow+uOcHs1x7z3A==","accessTokenExpiredTime":86400000}
     * server : 1623900916693
     */

    private int code;
    /**
     * accessToken : oauth_cloud_key:duhSRWIAYDbLDJs+YKNgrP9yXyXLB8QKFO9THsphOlzdHEOHvMLUPjnw7ByMMnWuW7tAKhNtn9l0WFlqlJYHbMF0yg5Plmq5VkGPx6S56C4=
     * refreshToken : oauth_cloud_key:3vArcW8iYtNKlBlyC9NRxrNqAsMgYctgmquWCP2XqkjtXOE+anADp4n1KEVRmgVM19jnkdbxow+uOcHs1x7z3A==
     * accessTokenExpiredTime : 86400000
     */

    private DataBean data;
    private long server;

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public DataBean getData() {
        return data;
    }

    public void setData(DataBean data) {
        this.data = data;
    }

    public long getServer() {
        return server;
    }

    public void setServer(long server) {
        this.server = server;
    }

    public static class DataBean {
        private String accessToken;
        private String refreshToken;
        private int accessTokenExpiredTime;

        public String getAccessToken() {
            return accessToken;
        }

        public void setAccessToken(String accessToken) {
            this.accessToken = accessToken;
        }

        public String getRefreshToken() {
            return refreshToken;
        }

        public void setRefreshToken(String refreshToken) {
            this.refreshToken = refreshToken;
        }

        public int getAccessTokenExpiredTime() {
            return accessTokenExpiredTime;
        }

        public void setAccessTokenExpiredTime(int accessTokenExpiredTime) {
            this.accessTokenExpiredTime = accessTokenExpiredTime;
        }
    }
}
