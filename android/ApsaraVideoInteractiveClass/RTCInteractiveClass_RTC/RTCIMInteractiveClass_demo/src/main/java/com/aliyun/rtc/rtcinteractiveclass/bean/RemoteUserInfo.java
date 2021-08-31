package com.aliyun.rtc.rtcinteractiveclass.bean;

import android.view.View;

import com.alivc.rtc.AliRtcEngine;

import java.util.Objects;

/**
 * 远端用户信息
 */
public class RemoteUserInfo {

    // 远端用户ID
    private String userId = "";
    // 远端用户名称
    private String displayName;
    // 是否静音远端用户
    private boolean muteAudioPlaying;
    // 视频流类型
    private AliRtcEngine.AliRtcVideoTrack videoTrack;
    // 是否订阅远端用户的音频流
    private boolean isSubScribedAudio;
    // 是否订阅远端用户的全部视频流
    private boolean isSubScribedAllVideo;
    // 是否订阅远端用户的相机流
    private boolean isSubScribedCamera;
    // 是否订阅远端用户的相机小流
    private boolean isSubScribedCameraSlave;
    // 是否订阅远端用户的屏幕流
    private boolean isSubScribedScreenSharing;
    //是否有音频
    private boolean hasAudio;
    //是否有视频
    private boolean hasVideo;
    // 是否本地用户
    private boolean isLocal;
    // 是否举手
    private boolean isHandUp;
    // 渲染视图
    private View screenPreview;
    private View cameraPreview;
    // 是否新添加的用户
    private boolean isNewAddUser;

    public String getUserId() {
        return userId;
    }

    public boolean isHandUp() {
        return isHandUp;
    }

    public RemoteUserInfo setHandUp(boolean handUp) {
        isHandUp = handUp;
        return this;
    }

    public RemoteUserInfo setUserId(String userId) {
        this.userId = userId;
        return this;
    }

    public String getDisplayName() {
        return displayName;
    }

    public RemoteUserInfo setDisplayName(String displayName) {
        this.displayName = displayName;
        return this;
    }

    public boolean isMuteAudioPlaying() {
        return muteAudioPlaying;
    }

    public RemoteUserInfo setMuteAudioPlaying(boolean muteAudioPlaying) {
        this.muteAudioPlaying = muteAudioPlaying;
        return this;
    }

    public AliRtcEngine.AliRtcVideoTrack getVideoTrack() {
        return videoTrack;
    }

    public RemoteUserInfo setVideoTrack(AliRtcEngine.AliRtcVideoTrack videoTrack) {
        this.videoTrack = videoTrack;
        return this;
    }

    public boolean isSubScribedAudio() {
        return isSubScribedAudio;
    }

    public RemoteUserInfo setSubScribedAudio(boolean subScribedAudio) {
        isSubScribedAudio = subScribedAudio;
        return this;
    }

    public boolean isHasAudio() {
        return hasAudio;
    }

    public RemoteUserInfo setHasAudio(boolean hasAudio) {
        this.hasAudio = hasAudio;
        return this;
    }

    public boolean isHasVideo() {
        return hasVideo;
    }

    public RemoteUserInfo setHasVideo(boolean hasVideo) {
        this.hasVideo = hasVideo;
        return this;
    }

    public boolean isSubScribedAllVideo() {
        return isSubScribedAllVideo;
    }

    public RemoteUserInfo setSubScribedAllVideo(boolean subScribedAllVideo) {
        isSubScribedAllVideo = subScribedAllVideo;
        return this;
    }

    public boolean isSubScribedCamera() {
        return isSubScribedCamera;
    }

    public RemoteUserInfo setSubScribedCamera(boolean subScribedCamera) {
        isSubScribedCamera = subScribedCamera;
        return this;
    }

    public boolean isSubScribedScreenSharing() {
        return isSubScribedScreenSharing;
    }

    public RemoteUserInfo setSubScribedScreenSharing(boolean subScribedScreenSharing) {
        isSubScribedScreenSharing = subScribedScreenSharing;
        return this;
    }

    public boolean isLocal() {
        return isLocal;
    }

    public RemoteUserInfo setLocal(boolean local) {
        isLocal = local;
        return this;
    }

    public View getScreenPreview() {
        return screenPreview;
    }

    public RemoteUserInfo setScreenPreview(View screenPreview) {
        this.screenPreview = screenPreview;
        return this;
    }

    public View getCameraPreview() {
        return cameraPreview;
    }

    public RemoteUserInfo setCameraPreview(View cameraPreview) {
        this.cameraPreview = cameraPreview;
        return this;
    }

    public boolean isNewAddUser() {
        return isNewAddUser;
    }

    public RemoteUserInfo setNewAddUser(boolean newAddUser) {
        isNewAddUser = newAddUser;
        return this;
    }

    public boolean isSubScribedCameraSlave() {
        return isSubScribedCameraSlave;
    }

    public RemoteUserInfo setSubScribedCameraSlave(boolean subScribedCameraSlave) {
        isSubScribedCameraSlave = subScribedCameraSlave;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RemoteUserInfo userInfo = (RemoteUserInfo) o;
        return userId.equals(userInfo.userId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userId);
    }

    @Override
    public String toString() {
        return "RemoteUserInfo{" +
                "userId='" + userId + '\'' +
                ", displayName='" + displayName + '\'' +
                ", muteAudioPlaying=" + muteAudioPlaying +
                ", videoTrack=" + videoTrack +
                ", isSubScribedAudio=" + isSubScribedAudio +
                ", isSubScribedAllVideo=" + isSubScribedAllVideo +
                ", isSubScribedCamera=" + isSubScribedCamera +
                ", isSubScribedCameraSlave=" + isSubScribedCameraSlave +
                ", isSubScribedScreenSharing=" + isSubScribedScreenSharing +
                ", hasAudio=" + hasAudio +
                ", hasVideo=" + hasVideo +
                ", isLocal=" + isLocal +
                ", screenPreview=" + screenPreview +
                ", cameraPreview=" + cameraPreview +
                ", isNewAddUser=" + isNewAddUser +
                '}';
    }
}
