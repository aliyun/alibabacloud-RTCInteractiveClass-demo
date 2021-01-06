package com.aliyun.rtc.rtcinteractiveclassplayer.rtc;

import com.alivc.rtc.AliRtcEngine;

public interface RTCInteractiveClassDelegate {



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
    * @param result 0为成功 反之失败
    */
   void onEnterSeatResult(int result);

   /**
    * 自己下麦结果通知
    */
   void onLeaveSeatResult(int result);

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
    *
    * 订阅结果回调
    * @param userId  用户ID
    * @param videoTrack     订阅成功的视频流
    * @param audioTrack     订阅成功的音频流
    */
   void onSubscribeChangedNotify(String userId, AliRtcEngine.AliRtcAudioTrack audioTrack, AliRtcEngine.AliRtcVideoTrack videoTrack);



    /**
     * 用户muteVideo通知
     */
    void onUserVideoMuted(String userId, boolean mute);

    /**
     * 用户muteAudio通知
     */
    void onUserAudioMuted(String userId, boolean mute);


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
   void onUpdateRoleNotify(AliRtcEngine.AliRTCSDK_Client_Role oldRole, AliRtcEngine.AliRTCSDK_Client_Role newRole);


}
