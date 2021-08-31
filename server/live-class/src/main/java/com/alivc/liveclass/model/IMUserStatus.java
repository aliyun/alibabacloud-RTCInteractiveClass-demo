package com.alivc.liveclass.model;

/**
 * IM 用户在线状态
 * @author haihua.whh
 * @Date 2021/8/5 10:49 上午
 **/
public enum IMUserStatus {
    Online(0),
    Offline(1),
    Logout(2);
    int status;

    IMUserStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }
}
