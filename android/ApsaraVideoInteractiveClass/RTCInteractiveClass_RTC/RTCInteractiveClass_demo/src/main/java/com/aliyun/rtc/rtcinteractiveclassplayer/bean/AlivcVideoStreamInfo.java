package com.aliyun.rtc.rtcinteractiveclassplayer.bean;

import android.os.Parcel;
import android.os.Parcelable;
import android.support.annotation.Nullable;

import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.device.utils.StringUtils;

public class AlivcVideoStreamInfo implements Parcelable {

    private String userId;
    private String userName;
    private AliRtcEngine.AliVideoCanvas aliVideoCanvas;
    private boolean isLocalStream;
    private boolean isTeacher;
    private boolean muteLocalMic, muteLocalCamera,muteMic,muteCamera;
    private AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack;

    private AlivcVideoStreamInfo(Builder builder) {
        if (builder != null) {
            this.userId = builder.userId;
            this.userName = builder.userName;
            this.aliVideoCanvas = builder.aliVideoCanvas;
            this.isLocalStream = builder.isLocalStream;
            this.isTeacher = builder.isTeacher;
            this.muteLocalCamera = builder.muteLocalCamera;
            this.muteLocalMic = builder.muteLocalMic;
            this.muteMic = builder.muteMic;
            this.muteCamera = builder.muteCamera;
            this.aliRtcVideoTrack = builder.aliRtcVideoTrack;
        }
    }

    protected AlivcVideoStreamInfo(Parcel in) {
        userId = in.readString();
        userName = in.readString();
        isLocalStream = in.readByte() != 0;
        isTeacher = in.readByte() != 0;
        muteLocalMic = in.readByte() != 0;
        muteLocalCamera = in.readByte() != 0;
        muteMic = in.readByte() != 0;
        muteCamera = in.readByte() != 0;
    }

    public static final Creator<AlivcVideoStreamInfo> CREATOR = new Creator<AlivcVideoStreamInfo>() {
        @Override
        public AlivcVideoStreamInfo createFromParcel(Parcel in) {
            return new AlivcVideoStreamInfo(in);
        }

        @Override
        public AlivcVideoStreamInfo[] newArray(int size) {
            return new AlivcVideoStreamInfo[size];
        }
    };

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public AliRtcEngine.AliVideoCanvas getAliVideoCanvas() {
        return aliVideoCanvas;
    }

    public void setAliVideoCanvas(AliRtcEngine.AliVideoCanvas aliVideoCanvas) {
        this.aliVideoCanvas = aliVideoCanvas;
    }

    public boolean isMuteLocalMic() {
        return muteLocalMic;
    }

    public void setMuteLocalMic(boolean muteLocalMic) {
        this.muteLocalMic = muteLocalMic;
    }

    public boolean isMuteLocalCamera() {
        return muteLocalCamera;
    }

    public void setMuteLocalCamera(boolean muteLocalCamera) {
        this.muteLocalCamera = muteLocalCamera;
    }

    public boolean isMuteMic() {
        return muteMic;
    }

    public void setMuteMic(boolean muteMic) {
        this.muteMic = muteMic;
    }

    public boolean isMuteCamera() {
        return muteCamera;
    }

    public void setMuteCamera(boolean muteCamera) {
        this.muteCamera = muteCamera;
    }

    public boolean isLocalStream() {
        return isLocalStream;
    }

    public void setLocalStream(boolean localStream) {
        isLocalStream = localStream;
    }

    public boolean isTeacher() {
        return isTeacher;
    }

    public void setTeacher(boolean teacher) {
        isTeacher = teacher;
    }

    public AliRtcEngine.AliRtcVideoTrack getAliRtcVideoTrack() {
        return aliRtcVideoTrack;
    }

    public void setAliRtcVideoTrack(AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
        this.aliRtcVideoTrack = aliRtcVideoTrack;
    }

    @Override
    public boolean equals(@Nullable Object obj) {
        return obj instanceof AlivcVideoStreamInfo && StringUtils.equals(((AlivcVideoStreamInfo) obj).userId, this.userId);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(userId);
        dest.writeString(userName);
        dest.writeByte((byte) (isLocalStream ? 1 : 0));
        dest.writeByte((byte) (isTeacher ? 1 : 0));
        dest.writeByte((byte) (muteLocalMic ? 1 : 0));
        dest.writeByte((byte) (muteLocalCamera ? 1 : 0));
        dest.writeByte((byte) (muteMic ? 1 : 0));
        dest.writeByte((byte) (muteCamera ? 1 : 0));
    }

    public static class Builder {
        private String userId;
        private String userName;
        private AliRtcEngine.AliVideoCanvas aliVideoCanvas;
        private boolean isLocalStream;
        private boolean isTeacher;
        private boolean muteLocalMic, muteLocalCamera,muteMic,muteCamera;
        private AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack;

        public Builder setUserId(String userId) {
            this.userId = userId;
            return this;
        }

        public Builder setUserName(String userName) {
            this.userName = userName;
            return this;
        }

        public Builder setAliVideoCanvas(AliRtcEngine.AliVideoCanvas aliVideoCanvas) {
            this.aliVideoCanvas = aliVideoCanvas;
            return this;
        }

        public Builder setLocalStream(boolean localStream) {
            isLocalStream = localStream;
            return this;
        }
        public Builder setTeacher(boolean teacher) {
            isTeacher = teacher;
            return this;
        }

        public Builder setMuteLocalMic(boolean muteLocalMic) {
            this.muteLocalMic = muteLocalMic;
            return this;
        }

        public Builder setAliRtcVideoTrack(AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
            this.aliRtcVideoTrack = aliRtcVideoTrack;
            return this;
        }

        public Builder setMuteLocalCamera(boolean muteLocalCamera) {
            this.muteLocalCamera = muteLocalCamera;
            return this;
        }
        public Builder setMuteMic(boolean muteMic) {
            this.muteMic = muteMic;
            return this;
        }
        public Builder setMuteCamera(boolean muteCamera) {
            this.muteCamera = muteCamera;
            return this;
        }

        public AlivcVideoStreamInfo build() {
            return new AlivcVideoStreamInfo(this);
        }
    }
}
