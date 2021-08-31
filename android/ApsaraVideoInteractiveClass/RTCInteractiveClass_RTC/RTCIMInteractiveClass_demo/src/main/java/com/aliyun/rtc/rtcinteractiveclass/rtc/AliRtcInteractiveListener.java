package com.aliyun.rtc.rtcinteractiveclass.rtc;

import com.alivc.rtc.AliRtcEngine;

public interface AliRtcInteractiveListener {

   /**
    * 用户上线通知
    *
    * @param userId 用户id
    */
   void onRemoteUserOnLineNotify(String userId);

   /**
    * 用户下线通知
    * @param userId 用户id
    */
   void onRemoteUserOffLineNotify(String userId);


   /**
    * 自己上麦结果通知
    */
   void onEnterSeatResult();

   /**
    * 自己下麦结果通知
    */
   void onLeaveSeatResult();

   /**
    * sdk报错
    *
    */
   void onOccurError(int error);

   /**
    * sdk警告
    *
    */
   void onOccurWarning( int error);

   /**
    * 房间被销毁的回调
    */
   void onRoomDestroy(int i);

   /**
    * sdk报错,需要销毁实例
    */
   void onSDKError( int error);


    /**
     * 加入房间通知
     * @param result 0为成功 反之失败
     */
    void onJoinChannelResult(int result);

    /**
     * 离开房间通知
     */
    void onLeaveChannelResult(int result);


   /**
    *
    * 当订阅情况发生变化时，返回这个消息 onSubscribeChangedNotify
    * @param userId  用户ID
    * @param videoTrack     订阅成功的视频流
    * @param audioTrack     订阅成功的音频流
    */
   void onRemoteTrackAvailableNotify(String userId, AliRtcEngine.AliRtcAudioTrack audioTrack, AliRtcEngine.AliRtcVideoTrack videoTrack);


    /**
     * 音频订阅情况变更回调
     * @param uid 用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    void onAudioSubscribeStateChanged(String uid, AliRtcEngine.AliRtcSubscribeState oldState, AliRtcEngine.AliRtcSubscribeState newState, int elapseSinceLastState, String channel);

    /**
     * 相机流订阅情况变更回调
     * @param uid 用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    void onVideoSubscribeStateChanged(String uid, AliRtcEngine.AliRtcSubscribeState oldState, AliRtcEngine.AliRtcSubscribeState newState, int elapseSinceLastState, String channel);


    /**
     * 大小流订阅情况变更回调
     * @param uid 用户Id
     * @param oldStreamType 之前的订阅状态
     * @param newStreamType 当前的订阅状态
     */
    void onSubscribeStreamTypeChanged(String uid, AliRtcEngine.AliRtcVideoStreamType oldStreamType, AliRtcEngine.AliRtcVideoStreamType newStreamType, int elapseSinceLastState, String channel);

    /**
     * 屏幕分享流订阅情况变更回调
     * @param uid 用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    void onScreenShareSubscribeStateChanged(String uid, AliRtcEngine.AliRtcSubscribeState oldState, AliRtcEngine.AliRtcSubscribeState newState, int elapseSinceLastState, String channel);

    /**
     * 用户muteVideo通知
     */
    void onUserVideoMuted(String userId, boolean mute);

    /**
     * 用户muteAudio通知
     */
    void onUserAudioMuted(String userId, boolean mute);

     void onActiveSpeaker(String speakers);
    /**
     * 网络状态回调
     *
     * @param aliRtcNetworkQuality1 下行网络质量
     * @param aliRtcNetworkQuality  上行网络质量
     * @param userId                     String  用户ID
     */
   void onNetworkQualityChanged( String userId, AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality, AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality1);

   /**
    *
    * 角色切换成功通知
    */
   void onUpdateRoleNotify(AliRtcEngine.AliRTCSdkClientRole oldRole, AliRtcEngine.AliRTCSdkClientRole newRole);


}
