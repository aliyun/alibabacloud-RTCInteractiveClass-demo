package com.aliyun.rtc.rtcinteractiveclassplayer.rtc;
import android.text.TextUtils;
import android.util.Log;

import com.alivc.rtc.AliRtcAuthInfo;
import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.AliRtcEngineEventListener;
import com.alivc.rtc.AliRtcEngineNotify;
import com.alivc.rtc.AliRtcRemoteUserInfo;
import com.aliyun.rtc.rtcinteractiveclassplayer.R;
import com.aliyun.rtc.rtcinteractiveclassplayer.bean.AliUserInfoResponse;
import com.aliyun.rtc.rtcinteractiveclassplayer.constant.Constant;
import com.aliyun.rtc.rtcinteractiveclassplayer.network.OkHttpCientManager;
import com.aliyun.rtc.rtcinteractiveclassplayer.network.OkhttpClient;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ApplicationContextUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.MockAliRtcAuthInfo;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.UIHandlerUtil;
import com.aliyun.svideo.common.utils.ThreadUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_ICE_CONNECTION_HEARTBEAT_TIMEOUT;
import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_SDK_INVALID_STATE;
import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_SESSION_REMOVED;

public class RTCInteractiveClassImpl extends BaseRTCInteractiveClass{
    public AliRtcEngine mEngine;
    private static boolean hasShowBadNetwork;
    private String mChannelId,mUserName;
    private String mUserId;
    private AliUserInfoResponse.AliUserInfo mRtcAuthInfo;
    private RTCInteractiveClassDelegate mInteractiveClassDelegate;

    private static final String TAG = RTCInteractiveClassImpl.class.getSimpleName();

    private RTCInteractiveClassImpl() {
        init();
    }
    public void init() {
        if (mEngine == null) {
            //对h5页面的支持
            AliRtcEngine.setH5CompatibleMode(1);
            mEngine = AliRtcEngine.getInstance(ApplicationContextUtil.getAppContext());
            //设置视频固定横屏显示
            mEngine.setDeviceOrientationMode(AliRtcEngine.AliRtcOrientationMode.AliRtcOrientationModeLandscapeLeft);
            ////默认横屏时交换视频宽高
            mEngine.setVideoSwapWidthAndHeight(true, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera);
            //默认开启扬声器
            mEngine.enableSpeakerphone(true);
            //设置频道模式为互动模式
            mEngine.setChannelProfile(AliRtcEngine.AliRTCSDK_Channel_Profile.AliRTCSDK_Interactive_live);
            //默认进来为观看角色
            mEngine.setClientRole(AliRtcEngine.AliRTCSDK_Client_Role.AliRTCSDK_live);
            mEngine.enableHighDefinitionPreview(false);
            //手动发布、手动订阅
            mEngine.setAutoPublishSubscribe(false, false);
            //设置监听
            mEngine.setRtcEngineEventListener(new SimpleRtcEngineEventListener());
            mEngine.setRtcEngineNotify(new SimpleAliRtcEngineNotify());
        }
    }

    public AliRtcRemoteUserInfo getUserInfo(String s) {
        if (mEngine != null) {
            return mEngine.getUserInfo(s);
        }
        return null;
    }

    private static final class RtcManagerInstance {
        private static final RTCInteractiveClassImpl INSTANCE = new RTCInteractiveClassImpl();
    }

    public String getUserId(){
        return mUserId;
    }

    /**
     * 获取单例
     */
    public static RTCInteractiveClassImpl sharedInstance() {
        return RtcManagerInstance.INSTANCE;
    }

    /**
     * 销毁当前实例
     */
    @Override
    public void destorySharedInstance() {
        if (mEngine != null) {
            mEngine.destroy();
            mEngine = null;
        }
    }

    /**
     * 登录
     *
     * @param channelId 房间号
     * @param userName 昵称
     */
    @Override
    public void login(String channelId, String userName) {
        mChannelId = channelId;
        mUserName = userName;
        getTokenByNetAndJoinChannel();
    }


    /**
     * 登出
     */
    @Override
    public void logout() {
        if (mEngine != null) {
            mEngine.stopPreview();
            mEngine.leaveChannel();
        }
    }

    /**
     * 上麦
     */
    @Override
    public void enterSeat() {
        setClientRole(AliRtcEngine.AliRTCSDK_Client_Role.AliRTCSDK_Interactive);
    }

    /**
     * 下麦
     */
    @Override
    public void leavelSeat() {
        stopPublish();
    }



    /**
     * 切换角色
     *
     */
    public void setClientRole(AliRtcEngine.AliRTCSDK_Client_Role clientRole) {
        if (mEngine != null) {
            mEngine.setClientRole(clientRole);
        }
    }




    /**
     * 设置播放远端视频流
     */
    @Override
    public void setRemoteViewConfig(AliRtcEngine.AliVideoCanvas aliVideoCanvas, String uid, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
        Log.i(TAG, "setRemoteViewConfig: ");
        if (mEngine != null) {
            mEngine.setRemoteViewConfig(aliVideoCanvas, uid, aliRtcVideoTrack);
        }
    }

    @Override
    public void setDelegate(RTCInteractiveClassDelegate callback) {
        mInteractiveClassDelegate = callback;
    }


    /**
     * 是否发布本地音频流
     * @return 返回0为切换成功，其他为切换失败
     */
    @Override
    public int muteLocalMic(boolean muteLocalMic) {
        if (mEngine != null) {
            return mEngine.muteLocalMic(muteLocalMic);
        }
        return -1;
    }

    /**
     * 是否发布本地相机流
     * @return 返回0为切换成功，其他为切换失败
     */
    @Override
    public int muteLocalCamera(boolean isMute) {
        if (mEngine != null) {
            return mEngine.muteLocalCamera(isMute, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera);
        }
        return -1;
    }


    /**
     * 设置本地预览渲染参数
     * @param localAliVideoCanvas canvas
     * @param aliRtcVideoTrackCamera 类型
     */
    @Override
    public void setLocalViewConfig(AliRtcEngine.AliVideoCanvas localAliVideoCanvas, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrackCamera) {
        Log.i(TAG, "setLocalViewConfig: ");
        if (mEngine != null) {
            mEngine.setLocalViewConfig(localAliVideoCanvas, aliRtcVideoTrackCamera);
        }
    }

    /**
     * 切换前后摄像头
     * @return 返回0为切换成功，其他为切换失败
     */
    public int switchCamera() {
        if (mEngine != null) {
            return mEngine.switchCamera();
        }
        return -1;
    }


    /**
     * 开始预览
     */
    @Override
    public void startPreview() {
        if (mEngine != null) {
            mEngine.startPreview();
        }
    }


    @Override
    public void stopPreview() {
        if (mEngine != null) {
            mEngine.stopPreview();
        }
    }

    public void setDeviceOrientationMode(AliRtcEngine.AliRtcOrientationMode aliRtcOrientationMode) {
        if (mEngine != null) {
            mEngine.setDeviceOrientationMode(aliRtcOrientationMode);
        }
    }

    public void startPublish() {
        if (mEngine != null) {
            mEngine.configLocalCameraPublish(true);
            mEngine.configLocalAudioPublish(true);
            //移动端不涉及屏幕分享
//            mEngine.configLocalScreenPublish(true);
            mEngine.publish();
        }
    }

    public void stopPublish() {
        if (mEngine != null) {
            mEngine.configLocalCameraPublish(false);
            mEngine.configLocalAudioPublish(false);
            //移动端不涉及屏幕分享
//            mEngine.configLocalScreenPublish(false);
            mEngine.publish();
        }
    }

    /**
     * 设置是否订阅远端相机流。默认为订阅大流，手动订阅时，需要调用subscribe才能生效。
     * @param userId userid
     * @param master true为优先订阅大流，false为订阅次小流。
     * @param enable true为订阅远端相机流，false为停止订阅远端相机流。
     */
    @Override
    public void configRemoteCameraTrack(String userId, boolean master, boolean enable) {
        if (mEngine != null) {
            mEngine.configRemoteCameraTrack(userId, master, enable);
            // 订阅远端音频流。
            mEngine.configRemoteAudio(userId, true);
            // 订阅远端屏幕流。
            mEngine.configRemoteScreenTrack(userId, true);
            subscribe(userId);
        }
    }

    /**
     * 设置是否订阅远端相机流。默认为订阅大流，手动订阅时，需要调用subscribe才能生效。
     * @param userId userid
     * @param master true为优先订阅大流，false为订阅次小流。
     * @param enable true为订阅远端相机流，false为停止订阅远端相机流。
     */
    public void configRemoteCameraTrack(String userId, boolean master, boolean enable,boolean screenTrack) {
        if(mEngine != null){
            mEngine.configRemoteCameraTrack(userId, master, enable);
            // 订阅远端音频流。
            mEngine.configRemoteAudio(userId, true);
            // 订阅远端屏幕流。
            mEngine.configRemoteScreenTrack(userId, screenTrack);
            mEngine.subscribe(userId);
        }
    }

    @Override
    public void subscribe(String userId) {
        if (mEngine != null) {
            mEngine.subscribe(userId);
        }
    }


    public class SimpleRtcEngineEventListener extends AliRtcEngineEventListener {

        @Override
        public void onUpdateRoleNotify(final AliRtcEngine.AliRTCSDK_Client_Role oldRole, final AliRtcEngine.AliRTCSDK_Client_Role newRole) {
            super.onUpdateRoleNotify(oldRole, newRole);
            Log.i(TAG, "onUpdateRoleNotify: result --> " + newRole);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onUpdateRoleNotify(oldRole,newRole);
                    }
                }
            });

        }

        @Override
        public void onJoinChannelResult(final int result) {
            Log.i(TAG, "onJoinChannelResult: result --> " + result);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onJoinChannelResult(result);
                    }
                }
            });
        }

        /**
         * 离开房间的回调
         *
         * @param result 结果码
         */
        @Override
        public void onLeaveChannelResult(final int result) {
            Log.i(TAG, "onLeaveChannelResult: result --> " + result);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onLeaveChannelResult(result);
                    }
                }
            });
        }

        /**
         * 网络状态变化的回调
         *
         * @param aliRtcNetworkQuality1 下行网络质量
         * @param aliRtcNetworkQuality  上行网络质量
         * @param s                     String  用户ID
         */
        @Override
        public void onNetworkQualityChanged(final String s, final AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality, final AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality1) {
            synchronized (RTCInteractiveClassImpl.class) {
                if (aliRtcNetworkQuality1.getValue() >= AliRtcEngine.AliRtcNetworkQuality.Network_Bad.getValue() && aliRtcNetworkQuality1.getValue() <= AliRtcEngine.AliRtcNetworkQuality.Network_VeryBad.getValue() && !hasShowBadNetwork) {//网络质量差
                    hasShowBadNetwork = true;
                    if (TextUtils.isEmpty(s)) {
                        showToast(R.string.alivc_biginteractiveclass_string_network_bad);
                    } else {
                        showToast(R.string.alivc_biginteractiveclass_string_remote_user_network_bad);
                    }
                } else if (TextUtils.isEmpty(s) && aliRtcNetworkQuality1.getValue() <= AliRtcEngine.AliRtcNetworkQuality.Network_Good.getValue()) {
                    hasShowBadNetwork = false;
                }
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if(mInteractiveClassDelegate != null){
                            mInteractiveClassDelegate.onNetworkQualityChanged(s,aliRtcNetworkQuality,aliRtcNetworkQuality1);
                        }
                    }
                });
            }
        }

        /**
         * 出现警告的回调
         *
         * @param i 错误码
         */
        @Override
        public void onOccurWarning(final int i) {
            Log.i(TAG, "onOccurWarning: i --> " + i);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onOccurWarning(i);
                    }
                }
            });
        }

        /**
         * 出现错误的回调
         *
         * @param error 错误码
         */
        @Override
        public void onOccurError(final int error) {
            Log.i(TAG, "onOccurError: error --> " + error);
            //出现这几个错误码需要销毁sdk，否则无法再次观看
            switch (error) {
            case ERR_SDK_INVALID_STATE:
            case ERR_ICE_CONNECTION_HEARTBEAT_TIMEOUT:
            case ERR_SESSION_REMOVED:
                //先销毁在创建
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if(mInteractiveClassDelegate != null){
                            mInteractiveClassDelegate.onSDKError(error);
                        }
                    }
                });
                break;
            //local network disconnect
            case 259:
                showToast(R.string.alivc_biginteractiveclass_string_rtc_network_conn_error);
                break;
            default:
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if(mInteractiveClassDelegate != null){
                            mInteractiveClassDelegate.onOccurError(error);
                        }
                    }
                });
                break;
            }
        }


        /**
         * 推流结果回调
         * @param result
         * @param isPublished
         */
        @Override
        public void onPublishChangedNotify(final int result, final boolean isPublished) {
            //推流失败
            if (result != 0) {
                showToast(R.string.alivc_biginteractiveclass_string_publish_error);
            }
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        if(!isPublished){
                            //下麦回调
                            mInteractiveClassDelegate.onLeaveSeatResult(result);
                        } else if(isPublished){
                            //上麦回调
                            mInteractiveClassDelegate.onEnterSeatResult(result);
                        }

                    }
                }
            });
        }

        /**
         *  流变化监听
         * @param uid 用户id
         * @param audioTrack 音频流
         * @param videoTrack 视频流
         */
        @Override
        public void onSubscribeChangedNotify(final String uid, final AliRtcEngine.AliRtcAudioTrack audioTrack, final AliRtcEngine.AliRtcVideoTrack videoTrack) {
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onSubscribeChangedNotify(uid,audioTrack,videoTrack);
                    }
                }
            });
        }

    }

    /**
     * SDK事件通知(回调接口都在子线程)
     */
    public  class SimpleAliRtcEngineNotify extends AliRtcEngineNotify {

        /**
         * 远端用户上线通知
         *
         * @param s userid
         */
        @Override
        public void onRemoteUserOnLineNotify(final String s) {
            Log.i(TAG, "onRemoteUserOnLineNotify: s --> " + s);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onRemoteUserOnLineNotify(s);
                    }
                }
            });
        }

        /**
         * 远端用户下线通知
         *
         * @param s userid
         */
        @Override
        public void onRemoteUserOffLineNotify(final String s) {
            Log.i(TAG, "onRemoteUserOffLineNotify: s --> " + s);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onRemoteUserOffLineNotify(s);
                    }
                }
            });
        }

        /**
         * 远端用户发布音视频流变化通知
         *
         * @param s                userid
         * @param aliRtcAudioTrack 音频流
         * @param aliRtcVideoTrack 相机流
         */
        @Override
        public void onRemoteTrackAvailableNotify(final String s, final AliRtcEngine.AliRtcAudioTrack aliRtcAudioTrack,
                                                 final AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
            Log.i(TAG, "onRemoteTrackAvailableNotify: s --> " + s + ", aliRtcVideoTrack --> " + aliRtcVideoTrack);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onRemoteTrackAvailableNotify(s,aliRtcAudioTrack,aliRtcVideoTrack);
                    }
                }
            });
        }


        /**
         * 被服务器踢出或者频道关闭时回调
         *
         */
        @Override
        public void onBye(final int i) {
            Log.i(TAG, "onBye: ");
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onRoomDestroy(i);
                    }
                }
            });
        }

        @Override
        public void onUserAudioMuted(final String uid, final boolean isMute) {
            super.onUserAudioMuted(uid, isMute);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onUserAudioMuted(uid,isMute);
                    }
                }
            });
        }

        @Override
        public void onUserVideoMuted(final String uid, final boolean isMute) {
            super.onUserVideoMuted(uid, isMute);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(mInteractiveClassDelegate != null){
                        mInteractiveClassDelegate.onUserVideoMuted(uid,isMute);
                    }
                }
            });
        }
    }



    /**
     * 获取auth信息，并加入房间
     */
    private void getTokenByNetAndJoinChannel() {
        //网络获取auth
        //String url = Constant.getUserLoginUrl();
        //Map<String, String> params = createTokenParams();
        //OkHttpCientManager.getInstance().doGet(url, params, new OkhttpClient.HttpCallBack() {
        //    @Override
        //    public void onSuccess(final String result) {
        //        try {
        //            ThreadUtils.runOnUiThread(new Runnable() {
        //                @Override
        //                public void run() {
        //                    AliUserInfoResponse aliUserInfoResponse = new Gson().fromJson(result, AliUserInfoResponse.class);
        //                    if (aliUserInfoResponse != null) {
        //                        mRtcAuthInfo = aliUserInfoResponse.getData();
        //                        mUserId = mRtcAuthInfo.getUserid();
        //                        AliRtcAuthInfo authInfo = createAliRtcAuthInfo(mChannelId);
        //                        if (mEngine != null) {
        //                            mEngine.joinChannel(authInfo, mUserName);
        //                        }
        //                    }
        //                }
        //            });
        //        } catch (JsonSyntaxException e) {
        //            e.printStackTrace();
        //        }
        //    }
        //
        //    @Override
        //    public void onFaild(String errorMsg) {
        //
        //    }
        //});

        //本地获取auth
        try {
            String userId = MockAliRtcAuthInfo.createUserId(mChannelId,mUserName);
            AliRtcAuthInfo aliRtcAuthInfo = MockAliRtcAuthInfo.mockAuthInfo(mChannelId,userId);
            mUserId = aliRtcAuthInfo.getUserId();
            if (mEngine != null) {
                mEngine.joinChannel(aliRtcAuthInfo, mUserName);
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }


    }
    private Map<String, String> createTokenParams() {
        Map<String, String> params = new HashMap<>();
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_CHANNELID, mChannelId);
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_USERID, mUserName);
        return params;
    }

    private AliRtcAuthInfo createAliRtcAuthInfo(String channel) {
        List<String> gslb = mRtcAuthInfo.getGslb();
        AliRtcAuthInfo userInfo = new AliRtcAuthInfo();
        //频道ID
        userInfo.setConferenceId(channel);
        String appid = mRtcAuthInfo.getAppid();
        /* 应用ID */
        userInfo.setAppid(appid);
        /* 随机码 */
        userInfo.setNonce(mRtcAuthInfo.getNonce());
        /* 时间戳*/
        userInfo.setTimestamp(mRtcAuthInfo.getTimestamp());
        String userid = mRtcAuthInfo != null ? mRtcAuthInfo.getUserid() : "";
        /* 用户ID */
        userInfo.setUserId(userid);
        /* GSLB地址*/
        userInfo.setGslb(gslb.toArray(new String[0]));
        /*鉴权令牌Token*/
        userInfo.setToken(mRtcAuthInfo.getToken());
        return userInfo;
    }

    private static void showToast(final String s) {
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                ToastUtils.showInCenter(ApplicationContextUtil.getAppContext(), s);
            }
        });
    }

    private static void showToast(final int resId) {
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                String string = ApplicationContextUtil.getAppContext().getString(resId);
                ToastUtils.showInCenter(ApplicationContextUtil.getAppContext(), string);
            }
        });
    }
}
