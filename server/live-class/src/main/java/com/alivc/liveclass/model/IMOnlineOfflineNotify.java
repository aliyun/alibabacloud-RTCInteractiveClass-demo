package com.alivc.liveclass.model;

/**
 * IM服务端回调信息；https://help.aliyun.com/document_detail/204917.htm
 * @author haihua.whh
 * @Date 2021/7/27 11:10 下午
 **/
public class IMOnlineOfflineNotify {
    String appUid;
    int status;
    String time;
    String sessionId;
    String clientAppKey;

    public String getAppUid() {
        return appUid;
    }

    public void setAppUid(String appUid) {
        this.appUid = appUid;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getSessionId() {
        return sessionId;
    }

    public void setSessionId(String sessionId) {
        this.sessionId = sessionId;
    }

    public String getClientAppKey() {
        return clientAppKey;
    }

    public void setClientAppKey(String clientAppKey) {
        this.clientAppKey = clientAppKey;
    }

    @Override
    public String toString() {
        return "IMOnlineOfflineNotify{" +
            "appUid='" + appUid + '\'' +
            ", status=" + status +
            ", time='" + time + '\'' +
            ", sessionId='" + sessionId + '\'' +
            ", clientAppKey='" + clientAppKey + '\'' +
            '}';
    }
}
