package com.aliyun.rtc.rtcinteractiveclass.rtc;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.view.SurfaceView;

import com.alivc.rtc.AliRtcAuthInfo;
import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.AliRtcEngineEventListener;
import com.alivc.rtc.AliRtcEngineNotify;
import com.alivc.rtc.AliRtcRemoteUserInfo;
import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.bean.AliUserInfoResponse;
import com.aliyun.rtc.rtcinteractiveclass.bean.RemoteUserInfo;
import com.aliyun.rtc.rtcinteractiveclass.constant.Constant;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveEngineImpl;
import com.aliyun.rtc.rtcinteractiveclass.network.OkHttpClientManager;
import com.aliyun.rtc.rtcinteractiveclass.network.OkhttpClient;
import com.aliyun.rtc.rtcinteractiveclass.utils.ApplicationContextUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclass.utils.UIHandlerUtil;
import com.aliyun.svideo.common.utils.ThreadUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.alivc.rtc.AliRtcEngine.AliRtcMuteLocalAudioMode.AliRtcMuteAudioModeDefault;
import static com.alivc.rtc.AliRtcEngine.AliRtcPublishState.AliRtcStatsNoPublish;
import static com.alivc.rtc.AliRtcEngine.AliRtcPublishState.AliRtcStatsPublished;
import static com.alivc.rtc.AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera;
import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_ICE_CONNECTION_HEARTBEAT_TIMEOUT;
import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_SDK_INVALID_STATE;
import static org.webrtc.alirtcInterface.ErrorCodeEnum.ERR_SESSION_REMOVED;

public class AliRtcInteractiveEngineImpl extends AliRtcInteractiveEngine {
    private static final String TAG = AliRtcInteractiveEngineImpl.class.getSimpleName();

    public AliRtcEngine mEngine;
    private static boolean hasShowBadNetwork;
    private String mChannelId, mUserName;
    private String mUserId;
    private AliUserInfoResponse.AliUserInfo mRtcAuthInfo;
    private AliRtcInteractiveListener mAliRtcInteractiveListener;
    AliRtcEngine.AliRtcPublishState mAudioPublishState;
    AliRtcEngine.AliRtcPublishState mVideoPublishState;
    private AliRtcEngine.AliRtcVideoCanvas mAliRtcVideoCanvas;
    private static AliRtcInteractiveEngineImpl mInstance;

    private AliRtcInteractiveEngineImpl() {
        init();
    }

    public void init() {
        if (mEngine == null) {
            //对h5页面的支持
            AliRtcEngine.setH5CompatibleMode(1);
            mEngine = AliRtcEngine.getInstance(ApplicationContextUtil.getAppContext());
            //默认开启扬声器
            mEngine.enableSpeakerphone(true);
            //设置频道模式为互动模式
            mEngine.setChannelProfile(AliRtcEngine.AliRTCSdkChannelProfile.AliRTCSdkInteractiveLive);
            //默认进来为观看角色
            mEngine.setClientRole(AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkLive);
            mEngine.enableAudioVolumeIndication(300, 3, 1);

            mEngine.subscribeAllRemoteAudioStreams(true);
            mEngine.subscribeAllRemoteVideoStreams(true);
            mEngine.publishLocalDualStream(true);
            //设置监听
            mEngine.setRtcEngineEventListener(new SimpleRtcEngineEventListener());
            mEngine.setRtcEngineNotify(new SimpleAliRtcEngineNotify());
            mEngine.registerAudioVolumeObserver(volumeObserver);
        }
    }

    @Override
    public AliRtcRemoteUserInfo getRemoteSeatUserInfo(String userId) {
        if (mEngine != null) {
            return mEngine.getUserInfo(userId);
        }
        return null;
    }

    /**
     * 获取单例
     */
    public static synchronized AliRtcInteractiveEngineImpl sharedInstance() {
        if (mInstance == null) {
            synchronized (AliRtcInteractiveEngineImpl.class) {
                if (mInstance == null) {
                    mInstance = new AliRtcInteractiveEngineImpl();
                }
            }
        }
        return mInstance;
    }

    public static void destroyInstance() {
        if (mInstance != null) {
            mInstance.release();
            mInstance = null;
        }
    }

    private void release() {
        if (mEngine != null) {
            mEngine.unRegisterAudioVolumeObserver();
            mEngine.leaveChannel();
            mEngine.destroy();
        }
    }

    /**
     * 登录
     *
     * @param channelId 房间号
     * @param userName  昵称
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
            mEngine.unRegisterAudioVolumeObserver();
            mEngine.leaveChannel();
        }
    }

    /**
     * 上麦
     */
    @Override
    public void enterSeat() {
        if (mEngine != null) {
            mEngine.startPreview();
        }
        setClientRole(AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkInteractive);
    }

    /**
     * 下麦
     */
    @Override
    public void leaveSeat() {
        if (mEngine != null) {
            mEngine.stopPreview();
        }
        setClientRole(AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkLive);
    }

    @Override
    public void setLocalViewConfig(AliRtcEngine.AliRtcVideoCanvas localAliVideoCanvas, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrackCamera) {
        this.mAliRtcVideoCanvas = localAliVideoCanvas;
        if (mEngine != null) {
            mEngine.setLocalViewConfig(localAliVideoCanvas, AliRtcVideoTrackCamera);
        }
    }

    @Override
    public String[] getRoomUserList() {
        if (mEngine != null) {
            return mEngine.getOnlineRemoteUsers();
        }
        return null;
    }

    /**
     * 切换角色
     */
    private void setClientRole(AliRtcEngine.AliRTCSdkClientRole clientRole) {
        if (mEngine != null) {
            mEngine.setClientRole(clientRole);
        }
    }

    @Override
    public RemoteUserInfo getLocalSeatUserInfo() {
        return new RemoteUserInfo().
                setLocal(true)
                .setNewAddUser(true)
                .setUserId(mUserId)
                .setCameraPreview(mAliRtcVideoCanvas == null ? null : mAliRtcVideoCanvas.view)
                .setDisplayName(mUserName);
    }


    /**
     * 设置播放远端视频流
     */
    @Override
    public void setRemoteViewConfig(AliRtcEngine.AliRtcVideoCanvas aliVideoCanvas, String uid, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
        if (mEngine != null) {
            mEngine.setRemoteViewConfig(aliVideoCanvas, uid, aliRtcVideoTrack);
        }
    }

    @Override
    public void setAliRtcInteractiveListener(AliRtcInteractiveListener callback) {
        mAliRtcInteractiveListener = callback;
    }

    @Override
    public SurfaceView createRenderView(Context context) {
        if (mEngine != null) {
            return mEngine.createRenderSurfaceView(context.getApplicationContext());
        }
        return new SurfaceView(context.getApplicationContext());
    }

    @Override
    public boolean isActiveStudent() {
        if (mEngine != null) {
            return mEngine.getCurrentClientRole() == AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkLive;
        }
        return false;
    }

    @Override
    public int muteLocalMic(boolean muteLocalMic) {
        if (mEngine != null) {
            return mEngine.muteLocalMic(muteLocalMic, AliRtcMuteAudioModeDefault);
        }
        return -1;
    }

    @Override
    public int muteLocalCamera(boolean isMute) {
        if (mEngine != null) {
            return mEngine.muteLocalCamera(isMute, AliRtcVideoTrackCamera);
        }
        return -1;
    }

    public class SimpleRtcEngineEventListener extends AliRtcEngineEventListener {

        @Override
        public void onUpdateRoleNotify(final AliRtcEngine.AliRTCSdkClientRole oldRole, final AliRtcEngine.AliRTCSdkClientRole newRole) {
            super.onUpdateRoleNotify(oldRole, newRole);
            Log.i(TAG, "onUpdateRoleNotify: result --> " + newRole);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onUpdateRoleNotify(oldRole, newRole);
                    }
                }
            });

        }

        @Override
        public void onJoinChannelResult(final int result, String channel, int elapsed) {
            super.onJoinChannelResult(result, channel, elapsed);
            Log.i(TAG, "onJoinChannelResult: result --> " + result);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onJoinChannelResult(result);
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
        public void onLeaveChannelResult(final int result, AliRtcEngine.AliRtcStats stats) {
            super.onLeaveChannelResult(result, stats);
            Log.i(TAG, "onLeaveChannelResult: result --> " + result);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onLeaveChannelResult(result);
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
            synchronized (AliRtcInteractiveEngineImpl.class) {
                if (aliRtcNetworkQuality1.getValue() >= AliRtcEngine.AliRtcNetworkQuality.AliRtcNetworkBad.getValue() && aliRtcNetworkQuality1.getValue() <= AliRtcEngine.AliRtcNetworkQuality.AliRtcNetworkVeryBad.getValue() && !hasShowBadNetwork) {//网络质量差
                    hasShowBadNetwork = true;
                    if (TextUtils.isEmpty(s)) {
                        showToast(R.string.alivc_biginteractiveclass_string_network_bad);
                    } else {
                        showToast(R.string.alivc_biginteractiveclass_string_remote_user_network_bad);
                    }
                } else if (TextUtils.isEmpty(s) && aliRtcNetworkQuality1.getValue() <= AliRtcEngine.AliRtcNetworkQuality.AliRtcNetworkGood.getValue()) {
                    hasShowBadNetwork = false;
                }
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (mAliRtcInteractiveListener != null) {
                            mAliRtcInteractiveListener.onNetworkQualityChanged(s, aliRtcNetworkQuality, aliRtcNetworkQuality1);
                        }
                    }
                });
            }
        }

        /**
         * 出现警告的回调
         *
         * @param warn 错误码
         */
        @Override
        public void onOccurWarning(final int warn, String message) {
            super.onOccurWarning(warn, message);
            Log.i(TAG, "onOccurWarning: i --> " + warn);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onOccurWarning(warn);
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
        public void onOccurError(final int error, String message) {
            super.onOccurError(error, message);
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
                            if (mAliRtcInteractiveListener != null) {
                                mAliRtcInteractiveListener.onSDKError(error);
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
                            if (mAliRtcInteractiveListener != null) {
                                mAliRtcInteractiveListener.onOccurError(error);
                            }
                        }
                    });
                    break;
            }
        }

        /**
         * 音频推流变更回调
         *
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         */
        @Override
        public void onAudioPublishStateChanged(AliRtcEngine.AliRtcPublishState oldState, final AliRtcEngine.AliRtcPublishState newState, int elapseSinceLastState, String channel) {
            super.onAudioPublishStateChanged(oldState, newState, elapseSinceLastState, channel);
            Log.d(TAG, "onAudioPublishStateChanged: oldState:" + oldState + " newState：" + newState);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        if (mVideoPublishState == AliRtcStatsNoPublish && newState == AliRtcStatsNoPublish) {
                            //下麦回调
                            mAliRtcInteractiveListener.onLeaveSeatResult();
                        } else if (mVideoPublishState == AliRtcStatsPublished && newState == AliRtcStatsPublished) {
                            //上麦回调
                            mAliRtcInteractiveListener.onEnterSeatResult();
                        }

                    }
                }
            });
        }

        /**
         * 视频推流变更回调
         *
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         */
        @Override
        public void onVideoPublishStateChanged(AliRtcEngine.AliRtcPublishState oldState, final AliRtcEngine.AliRtcPublishState newState, int elapseSinceLastState, String channel) {
            super.onVideoPublishStateChanged(oldState, newState, elapseSinceLastState, channel);
            Log.d(TAG, "onVideoPublishStateChanged: oldState:" + oldState + " newState：" + newState);
        }

        /**
         * 次要流推流变更回调
         *
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         */
        @Override
        public void onDualStreamPublishStateChanged(AliRtcEngine.AliRtcPublishState oldState, AliRtcEngine.AliRtcPublishState newState, int elapseSinceLastState, String channel) {
            super.onDualStreamPublishStateChanged(oldState, newState, elapseSinceLastState, channel);
            Log.d(TAG, "onDualStreamPublishStateChanged: oldState:" + oldState.getValue() + " newState：" + newState.getValue());
        }

        /**
         * 屏幕分享推流变更回调
         *
         * @param oldState 之前的推流状态
         * @param newState 当前的推流状态
         */
        @Override
        public void onScreenSharePublishStateChanged(AliRtcEngine.AliRtcPublishState oldState, AliRtcEngine.AliRtcPublishState newState, int elapseSinceLastState, String channel) {
            super.onScreenSharePublishStateChanged(oldState, newState, elapseSinceLastState, channel);
            Log.d(TAG, "onScreenSharePublishStateChanged: oldState:" + oldState + " newState：" + newState);
        }

        /**
         * 音频订阅情况变更回调
         *
         * @param uid      用户Id
         * @param oldState 之前的订阅状态
         * @param newState 当前的订阅状态
         */
        @Override
        public void onAudioSubscribeStateChanged(final String uid, final AliRtcEngine.AliRtcSubscribeState oldState, final AliRtcEngine.AliRtcSubscribeState newState, final int elapseSinceLastState, final String channel) {
            super.onAudioSubscribeStateChanged(uid, oldState, newState, elapseSinceLastState, channel);
            Log.d(TAG, "onAudioSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onAudioSubscribeStateChanged(uid, oldState, newState, elapseSinceLastState, channel);
                    }
                }
            });
        }


        /**
         * 相机流订阅情况变更回调
         *
         * @param uid      用户Id
         * @param oldState 之前的订阅状态
         * @param newState 当前的订阅状态
         */
        @Override
        public void onVideoSubscribeStateChanged(final String uid,
                                                 final AliRtcEngine.AliRtcSubscribeState oldState,
                                                 final AliRtcEngine.AliRtcSubscribeState newState,
                                                 final int elapseSinceLastState, final String channel) {
            Log.d(TAG, "onVideoSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onVideoSubscribeStateChanged(uid, oldState, newState, elapseSinceLastState, channel);
                    }
                }
            });
        }


        /**
         * 大小流订阅情况变更回调
         *
         * @param uid           用户Id
         * @param oldStreamType 之前的订阅状态
         * @param newStreamType 当前的订阅状态
         */
        @Override
        public void onSubscribeStreamTypeChanged(final String uid,
                                                 final AliRtcEngine.AliRtcVideoStreamType oldStreamType,
                                                 final AliRtcEngine.AliRtcVideoStreamType newStreamType,
                                                 final int elapseSinceLastState, final String channel) {
            Log.d(TAG, "onSubscribeStreamTypeChanged: uid: " + uid + " oldState" + oldStreamType + " newState: " + newStreamType);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onSubscribeStreamTypeChanged(uid, oldStreamType, newStreamType, elapseSinceLastState, channel);
                    }
                }
            });
        }

        /**
         * 屏幕分享流订阅情况变更回调
         *
         * @param uid      用户Id
         * @param oldState 之前的订阅状态
         * @param newState 当前的订阅状态
         */
        @Override
        public void onScreenShareSubscribeStateChanged(final String uid,
                                                       final AliRtcEngine.AliRtcSubscribeState oldState,
                                                       final AliRtcEngine.AliRtcSubscribeState newState,
                                                       final int elapseSinceLastState, final String channel) {
            Log.d(TAG, "onScreenShareSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onScreenShareSubscribeStateChanged(uid, oldState, newState, elapseSinceLastState, channel);
                    }
                }
            });
        }

    }

    /**
     * SDK事件通知(回调接口都在子线程)
     */
    public class SimpleAliRtcEngineNotify extends AliRtcEngineNotify {

        /**
         * 远端用户上线通知
         *
         * @param uid userid
         */
        @Override
        public void onRemoteUserOnLineNotify(final String uid, int elapsed) {
            super.onRemoteUserOnLineNotify(uid, elapsed);
            Log.i(TAG, "onRemoteUserOnLineNotify: uid --> " + uid);
            if (mEngine != null) {
                AliRtcRemoteUserInfo remoteUserInfo = mEngine.getUserInfo(uid);
                if (remoteUserInfo != null && !remoteUserInfo.getDisplayName().contains("_老师")) {
                    mEngine.setRemoteVideoStreamType(uid, AliRtcEngine.AliRtcVideoStreamType.AliRtcVideoStreamTypeLow);
                }
            }
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onRemoteUserOnLineNotify(uid);
                    }
                }
            });
        }

        /**
         * 远端用户下线通知
         *
         * @param uid userid
         */
        @Override
        public void onRemoteUserOffLineNotify(final String uid, AliRtcEngine.
                AliRtcUserOfflineReason reason) {
            super.onRemoteUserOffLineNotify(uid, reason);
            Log.i(TAG, "onRemoteUserOffLineNotify: s --> " + uid);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onRemoteUserOffLineNotify(uid);
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
        public void onRemoteTrackAvailableNotify(final String s,
                                                 final AliRtcEngine.AliRtcAudioTrack aliRtcAudioTrack,
                                                 final AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
            Log.i(TAG, "onRemoteTrackAvailableNotify: s --> " + s + ", aliRtcVideoTrack --> " + aliRtcVideoTrack);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onRemoteTrackAvailableNotify(s, aliRtcAudioTrack, aliRtcVideoTrack);
                    }
                }
            });
        }


        /**
         * 被服务器踢出或者频道关闭时回调
         */
        @Override
        public void onBye(final int result) {
            Log.i(TAG, "onBye: result" + result);
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onRoomDestroy(result);
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
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onUserAudioMuted(uid, isMute);
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
                    if (mAliRtcInteractiveListener != null) {
                        mAliRtcInteractiveListener.onUserVideoMuted(uid, isMute);
                    }
                }
            });
        }

        @Override
        public void onRtcRemoteVideoStats(AliRtcEngine.AliRtcRemoteVideoStats aliRtcStats) {
            super.onRtcRemoteVideoStats(aliRtcStats);
            Log.i(TAG, "onRtcRemoteVideoStats: aliRtcStats " + aliRtcStats.toString());
        }
    }

    private final StringBuilder mSpeakers = new StringBuilder();
    private final AliRtcEngine.AliRtcAudioVolumeObserver volumeObserver = new AliRtcEngine.AliRtcAudioVolumeObserver() {
        @Override
        public void onAudioVolume(final List<AliRtcEngine.AliRtcAudioVolume> speakers, int totalVolume) {
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    StringBuilder builder = new StringBuilder();
                    mSpeakers.delete(0, mSpeakers.length());
                    if (speakers != null && mEngine != null) {
                        for (AliRtcEngine.AliRtcAudioVolume speaker : speakers) {
                            if (!speaker.mUserId.equals("0") && speaker.mVolume > 0 && speaker.mSpeechstate == 1) {
                                AliRtcRemoteUserInfo userInfo = mEngine.getUserInfo(speaker.mUserId);
                                if (userInfo != null && !userInfo.getDisplayName().contains("_老师")) {
                                    builder.append(userInfo.getDisplayName());
                                    builder.append("、");
                                }
                            }
                        }
                        if (!TextUtils.isEmpty(builder.toString())) {
                            mSpeakers.append(builder.toString())
                                    .append("正在发言");
                        }
                        if (mAliRtcInteractiveListener != null) {
                            mAliRtcInteractiveListener.onActiveSpeaker(mSpeakers.toString());
                        }
                    }
                }
            });
        }
    };


    /**
     * 获取auth信息，并加入房间
     */
    private void getTokenByNetAndJoinChannel() {
        String url = Constant.getUserLoginUrl();
        Map<String, String> params = createTokenParams();
        OkHttpClientManager.getInstance().doGet(url, params, new OkhttpClient.HttpCallBack() {
            @Override
            public void onSuccess(final String result) {
                try {
                    ThreadUtils.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            AliUserInfoResponse aliUserInfoResponse = new Gson().fromJson(result, AliUserInfoResponse.class);
                            if (aliUserInfoResponse != null) {
                                mRtcAuthInfo = aliUserInfoResponse.getData();
                                mUserId = mRtcAuthInfo.getUserid();
                                AliRtcAuthInfo authInfo = createAliRtcAuthInfo(mChannelId);
                                //创建AIM用户并登录
                                AliImInteractiveEngineImpl.sharedInstance().createUserManager(mUserId);
                                if (mEngine != null) {
                                    mEngine.joinChannel(authInfo, mUserName);
                                }
                            }
                        }
                    });
                } catch (JsonSyntaxException e) {
                    e.printStackTrace();
                    showToast(R.string.alivc_biginteractiveclass_string_userinfo_empty);
                }
            }

            @Override
            public void onFailed(String errorMsg) {
                showToast(R.string.alivc_biginteractiveclass_string_userinfo_empty);
            }
        });
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
        userInfo.setChannelId(channel);
        String appid = mRtcAuthInfo.getAppid();
        /* 应用ID */
        userInfo.setAppId(appid);
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
