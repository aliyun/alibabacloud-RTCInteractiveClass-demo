package com.alivc.liveclass.model;

/**
 * @author haihua.whh
 * @Date 2021/6/16 1:55 下午
 **/
public class IMLoginResult {
    private String accessToken;
    private String refreshToken;
    private long accessTokenExpiredTime;

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

    public long getAccessTokenExpiredTime() {
        return accessTokenExpiredTime;
    }

    public void setAccessTokenExpiredTime(long accessTokenExpiredTime) {
        this.accessTokenExpiredTime = accessTokenExpiredTime;
    }

    @Override
    public String toString() {
        return "IMLoginResult{" +
            "accessToken='" + accessToken + '\'' +
            ", refreshToken='" + refreshToken + '\'' +
            ", accessTokenExpiredTime=" + accessTokenExpiredTime +
            '}';
    }
}
