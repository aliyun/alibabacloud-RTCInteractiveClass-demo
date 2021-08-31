package com.aliyun.rtc.rtcinteractiveclass.rtc;


import android.content.Context;
import android.view.SurfaceView;

import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.AliRtcRemoteUserInfo;
import com.aliyun.rtc.rtcinteractiveclass.bean.RemoteUserInfo;

public abstract class AliRtcInteractiveEngine {


    /**
     * 获取单例
     */
    public static AliRtcInteractiveEngine sharedInstance() {
        return AliRtcInteractiveEngineImpl.sharedInstance();
    }

    /**
     * 销毁实例
     */
    public static void destroy() {
        AliRtcInteractiveEngineImpl.destroyInstance();
    }

    /**
     * 登录
     *
     * @param channelId 房间号
     * @param userName  昵称
     */
    public abstract void login(String channelId, String userName);


    /**
     * 登出
     */
    public abstract void logout();


    /**
     * 上麦
     */
    public abstract void enterSeat();

    /**
     * 下麦
     */
    public abstract void leaveSeat();

    /**
     * 设置本地预览渲染参数
     */
    public abstract void setLocalViewConfig(AliRtcEngine.AliRtcVideoCanvas localAliVideoCanvas, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrackCamera);

    /**
     * 获取本地上麦用户信息
     */
    public abstract RemoteUserInfo getLocalSeatUserInfo();

    /**
     * 获取远端用户信息
     */
    public abstract AliRtcRemoteUserInfo getRemoteSeatUserInfo(String userId);

    /**
     * 获取房间用户列表
     */
    public abstract String[] getRoomUserList();


    /**
     * 停止发布音频
     */
    public abstract int muteLocalMic(boolean isMute);


    /**
     * 停止发布视频
     */
    public abstract int muteLocalCamera(boolean isMute);

    /**
     * 设置远端渲染参数。
     */
    public abstract void setRemoteViewConfig(AliRtcEngine.AliRtcVideoCanvas aliVideoCanvas, String uid, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack);


    /**
     * 设置监听。
     */
    public abstract void setAliRtcInteractiveListener(AliRtcInteractiveListener callback);

    public abstract SurfaceView createRenderView(Context context);

    /**
     * 当前角色
     *
     * @return true:学生 false:连麦学生
     */
    public abstract boolean isActiveStudent();


}

