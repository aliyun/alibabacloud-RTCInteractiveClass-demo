package com.alivc.liveclass.model;

/**
 * 详见文档：https://help.aliyun.com/document_detail/204921.html
 * @author haihua.whh
 * @Date 2020/12/13 2:02 下午
 **/

public class Result {
    int code;
    Object data;
    long server;

    public Result() {
        this.server = System.currentTimeMillis();
    }

    public Result(int code) {
        this.code = code;
        this.server = System.currentTimeMillis();
    }

    public Result(int code, Object message) {
        this.code = code;
        this.data = message;
        this.server = System.currentTimeMillis();
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data = data;
    }

    public long getServer() {
        return server;
    }

    public void setServer(long server) {
        this.server = server;
    }

    @Override
    public String toString() {
        return "Result{" +
            "code=" + code +
            ", data=" + data +
            ", server=" + server +
            '}';
    }
}
