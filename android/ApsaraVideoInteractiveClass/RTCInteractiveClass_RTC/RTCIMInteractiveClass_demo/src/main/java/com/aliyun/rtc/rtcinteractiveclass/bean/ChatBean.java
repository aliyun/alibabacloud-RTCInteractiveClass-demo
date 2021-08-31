package com.aliyun.rtc.rtcinteractiveclass.bean;

import android.os.Parcel;
import android.os.Parcelable;

import java.util.Objects;

public class ChatBean implements Parcelable {

    private String uid;
    private String displayName;
    private String msg;
    private boolean isLocal;

    public ChatBean() {

    }

    public ChatBean(Parcel in) {
        uid = in.readString();
        displayName = in.readString();
        msg = in.readString();
        isLocal = in.readByte() != 0;
    }

    public static final Creator<ChatBean> CREATOR = new Creator<ChatBean>() {
        @Override
        public ChatBean createFromParcel(Parcel in) {
            return new ChatBean(in);
        }

        @Override
        public ChatBean[] newArray(int size) {
            return new ChatBean[size];
        }
    };

    public String getDisplayName() {
        return displayName;
    }

    public ChatBean setDisplayName(String displayName) {
        this.displayName = displayName;
        return this;

    }

    public boolean isLocal() {
        return isLocal;
    }

    public ChatBean setLocal(boolean isLocal) {
        this.isLocal = isLocal;
        return this;
    }

    public String getUid() {
        return uid;
    }

    public ChatBean setUid(String uid) {
        this.uid = uid;
        return this;
    }

    public String getMsg() {
        return msg;
    }

    public ChatBean setMsg(String msg) {
        this.msg = msg;
        return this;

    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ChatBean chatBean = (ChatBean) o;
        return isLocal == chatBean.isLocal &&
                Objects.equals(uid, chatBean.uid) &&
                Objects.equals(msg, chatBean.msg);
    }

    @Override
    public int hashCode() {
        return Objects.hash(uid, isLocal, msg);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        parcel.writeString(uid);
        parcel.writeString(displayName);
        parcel.writeString(msg);
        parcel.writeByte((byte) (isLocal ? 1 : 0));
    }
}
