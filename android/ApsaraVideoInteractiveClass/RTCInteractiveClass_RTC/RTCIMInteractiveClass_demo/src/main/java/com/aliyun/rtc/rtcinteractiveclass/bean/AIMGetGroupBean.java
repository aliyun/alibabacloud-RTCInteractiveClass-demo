package com.aliyun.rtc.rtcinteractiveclass.bean;

public class AIMGetGroupBean {

    /**
     * code : 200
     * data : $2$12501672$EAUNIT
     * server : 1623982693106
     */

    private int code;
    private String data;
    private long server;

    public boolean isSuccessful() {
        return code == 200;
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public long getServer() {
        return server;
    }

    public void setServer(long server) {
        this.server = server;
    }
}
