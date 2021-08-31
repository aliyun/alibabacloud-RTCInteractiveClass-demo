package com.aliyun.rtc.rtcinteractiveclass.im;

import android.util.Log;

import com.alibaba.dingpaas.aim.AIMPubGroupListAllMemberListener;
import com.alibaba.dingpaas.aim.AIMPubGroupMember;
import com.alibaba.dingpaas.aim.AIMPubGroupMemberChangeListener;
import com.alibaba.dingpaas.aim.AIMPubGroupService;
import com.alibaba.dingpaas.aim.AIMPubMessage;
import com.alibaba.dingpaas.aim.AIMPubModule;
import com.alibaba.dingpaas.aim.AIMPubMsgListener;
import com.alibaba.dingpaas.aim.AIMPubMsgService;
import com.alibaba.dingpaas.aim.AIMPubNewMessage;
import com.alibaba.dingpaas.base.DPSAuthListener;
import com.alibaba.dingpaas.base.DPSAuthService;
import com.alibaba.dingpaas.base.DPSAuthToken;
import com.alibaba.dingpaas.base.DPSAuthTokenExpiredReason;
import com.alibaba.dingpaas.base.DPSAuthTokenGotCallback;
import com.alibaba.dingpaas.base.DPSConnectionStatus;
import com.alibaba.dingpaas.base.DPSEngineStartListener;
import com.alibaba.dingpaas.base.DPSError;
import com.alibaba.dingpaas.base.DPSLogoutListener;
import com.alibaba.dingpaas.base.DPSModuleInfo;
import com.alibaba.dingpaas.base.DPSPubAuthTokenCallback;
import com.alibaba.dingpaas.base.DPSPubEngine;
import com.alibaba.dingpaas.base.DPSPubManager;
import com.alibaba.dingpaas.base.DPSPubManagerCreateListener;
import com.alibaba.dingpaas.base.DPSPubSettingService;
import com.alibaba.dingpaas.base.DPSReleaseManagerListener;
import com.aliyun.rtc.rtcinteractiveclass.bean.AIMGetGroupBean;
import com.aliyun.rtc.rtcinteractiveclass.bean.AIMTokenBean;
import com.aliyun.rtc.rtcinteractiveclass.constant.Constant;
import com.aliyun.rtc.rtcinteractiveclass.network.OkHttpClientManager;
import com.aliyun.rtc.rtcinteractiveclass.network.OkhttpClient;
import com.aliyun.rtc.rtcinteractiveclass.utils.ApplicationContextUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.SPUtil;
import com.aliyun.svideo.common.utils.AppUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import org.json.JSONObject;

import java.io.File;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import static com.aliyun.rtc.rtcinteractiveclass.constant.Constant.AIM_APPID;
import static com.aliyun.rtc.rtcinteractiveclass.constant.Constant.AIM_APPKEY;

public class AliImInteractiveEngineImpl extends AliImInteractiveEngine {
    private static final String TAG = AliImInteractiveEngineImpl.class.getSimpleName();
    private String deviceId = "";
    private String mUserId = "";
    private static AliImInteractiveEngineImpl sInstance;
    private DPSAuthService authService = null;
    private DPSPubEngine dpsPubEngine;
    private final List<AliImInteractiveListener> callBacks = new ArrayList<>();
    private volatile boolean isAIMOnline;
    private String mAppCid;

    static {
        // 1. 基座
        // 钉钉定制的sqlite3数据库
        System.loadLibrary("sqlite3");
        // 网络相关动态库
        System.loadLibrary("gaea");
        //ssl
        System.loadLibrary("openssl");
        // 基座动态库
        System.loadLibrary("dps");
        // 2. IM模块
        System.loadLibrary("aim");
    }

    public static synchronized AliImInteractiveEngineImpl sharedInstance() {
        if (sInstance == null) {
            synchronized (AliImInteractiveEngineImpl.class) {
                if (sInstance == null) {
                    sInstance = new AliImInteractiveEngineImpl();
                }
            }
        }
        return sInstance;
    }

    private AliImInteractiveEngineImpl() {
        init();
    }


    public static void destroyInstance() {
        if (sInstance != null) {
            sInstance.releaseDPSManager();
            sInstance = null;
        }
    }

    @Override
    public void listAllMembers(AIMPubGroupListAllMemberListener listener) {
        AIMPubModule imModule = AIMPubModule.getModuleInstance(mUserId);
        if (imModule == null) {
            return;
        }
        AIMPubGroupService groupService = imModule.getGroupService();
        if (listener == null || groupService == null) {
            return;
        }
        groupService.listAllMembers(getPubGroupAppCid(), listener);
    }

    private void init() {
        // 创建引擎，仅需创建一次
        if (dpsPubEngine == null) {
            dpsPubEngine = DPSPubEngine.createDPSEngine();
            // 获取DingPaaS设置
            DPSPubSettingService setting = dpsPubEngine.getSettingService();
            // 设置必要信息，appKey和appID从控制台的 直播互动>功能配置 页面获取
            setting.setAppKey(AIM_APPKEY);
            setting.setAppID(AIM_APPID);
            // 设置本地数据库或数据存储路径, 该路径必须存在，并可有可写权限
            String dataPath = ApplicationContextUtil.getAppContext().getExternalCacheDir().getPath() + "/AliImInteractiveEngine";
            File file = new File(dataPath);
            if (!file.exists()) {
                file.mkdir();
            }
            setting.setDataPath(dataPath);
            // 设备唯一ID
            deviceId = SPUtil.getInstance().getString("deviceId", "0");
            if (deviceId.equals("0")) {
                deviceId = UUID.randomUUID().toString();
                SPUtil.getInstance().putString("deviceId", deviceId);
                setting.setDeviceId(deviceId);
            } else {
                setting.setDeviceId(deviceId);
            }
            Log.d(TAG, deviceId);

            setting.setAppName(AppUtils.getAppName(ApplicationContextUtil.getAppContext()));
            setting.setAppVersion(AppUtils.getAppVersionName(ApplicationContextUtil.getAppContext()));
            setting.setOSName(AppUtils.getOsName());
            setting.setOSVersion(AppUtils.getOsVersion());
            setting.setDeviceName(AppUtils.getSystemDevice());
            setting.setDeviceType("Android");
            setting.setDeviceLocale(AppUtils.getSystemLanguage());
            setting.setAuthTokenCallback(dPSPubAuthTokenCallback);

            // 注册IM模块
            DPSModuleInfo imInfo = AIMPubModule.getModuleInfo();
            if (imInfo != null) {
                dpsPubEngine.registerModule(imInfo);
            }
            // 启动引擎，为异步，成功后，将回调listener.onSuccess()
            dpsPubEngine.start(dPSEngineStartListener);
        }
    }

    //登录token获取回调
    private final DPSPubAuthTokenCallback dPSPubAuthTokenCallback = new DPSPubAuthTokenCallback() {
        @Override
        public void onCallback(String uid, final DPSAuthTokenGotCallback dpsAuthTokenGotCallback, DPSAuthTokenExpiredReason dpsAuthTokenExpiredReason) {
            Log.i(TAG, " DPSPubAuthTokenCallback onCallback: " + uid + " dpsAuthTokenExpiredReason " + dpsAuthTokenExpiredReason);
            getAimToken(uid, dpsAuthTokenGotCallback);
        }
    };

    /**
     * 获取token，并传递给AIM
     */
    private void getAimToken(String uid, final DPSAuthTokenGotCallback dpsAuthTokenGotCallback) {
        Map<String, String> params = new HashMap<>();
        params.put("appKey", AIM_APPKEY);
        params.put("appId", AIM_APPID);
        params.put("deviceId", deviceId);
        params.put("appUid", uid);

        OkHttpClientManager.getInstance().doGet(Constant.getAIMTokenLoginUrl(), params, new OkhttpClient.HttpCallBack() {
            @Override
            public void onSuccess(String result) {
                try {
                    AIMTokenBean aimTokenBean = new Gson().fromJson(result, AIMTokenBean.class);
                    if (aimTokenBean != null && dpsAuthTokenGotCallback != null) {
                        DPSAuthToken dpsAuthToken = new DPSAuthToken();
                        dpsAuthToken.accessToken = aimTokenBean.getData().getAccessToken();
                        dpsAuthToken.refreshToken = aimTokenBean.getData().getRefreshToken();
                        dpsAuthTokenGotCallback.onSuccess(dpsAuthToken);
                    }

                } catch (JsonSyntaxException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(String errorMsg) {
                if (dpsAuthTokenGotCallback != null) {
                    dpsAuthTokenGotCallback.onFailure(0, errorMsg);
                }
            }
        });
    }

    /**
     * 获取加入群聊需要的频道id
     *
     * @param ChannelId
     * @param nickName
     */
    private void getAimChannelId(final String userId, final String ChannelId, final String nickName) {
        Map<String, String> params = new HashMap<>();
        params.put("appId", AIM_APPID);
        params.put("room", ChannelId);

        OkHttpClientManager.getInstance().doGet(Constant.getAIMChannelIdUrl(), params, new OkhttpClient.HttpCallBack() {
            @Override
            public void onSuccess(String result) {
                try {
                    AIMGetGroupBean aimGetGroupBean = new Gson().fromJson(result, AIMGetGroupBean.class);
                    if (aimGetGroupBean != null) {
                        Log.d(TAG, "aimGetGroupBean code: " + aimGetGroupBean.getCode() + " appcid: " + aimGetGroupBean.getData());
                        internalAddMembers(userId, nickName, ChannelId, aimGetGroupBean.getData());
                        mAppCid = aimGetGroupBean.getData();

                    }
                } catch (JsonSyntaxException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(String errorMsg) {

            }
        });
    }

    //引擎启动回调,引擎启动成功再进行下一步
    private final DPSEngineStartListener dPSEngineStartListener = new DPSEngineStartListener() {
        @Override
        public void onSuccess() {
            Log.i(TAG, " DPSEngineStartListener onSuccess: ");
        }

        @Override
        public void onFailure(DPSError dpsError) {
            Log.i(TAG, " DPSEngineStartListener onFailure: ");

        }
    };


    //通过listener监听是否创建完成（内部会进行数据库初始化等操作）
    private final DPSPubManagerCreateListener dPSPubManagerCreateListener = new DPSPubManagerCreateListener() {

        @Override
        public void onSuccess(DPSPubManager dpsPubManager) {
            Log.d(TAG, "DPSPubManagerCreateListener onSuccess " + dpsPubManager.getUserId());
            authService = dpsPubManager.getAuthService();
            if (authService == null) {
                return;
            }
            authService.addListener(dPSAuthListener);
            authService.login();
        }

        @Override
        public void onFailure(DPSError dpsError) {
            Log.d(TAG, "DPSPubManagerCreateListener onFailure " + dpsError.getReason());

        }
    };

    private final DPSAuthListener dPSAuthListener = new DPSAuthListener() {

        // 连接状态通知
        @Override
        public void onConnectionStatusChanged(DPSConnectionStatus dpsConnectionStatus) {
            Log.d(TAG, "onConnectionStatusChanged dpsConnectionStatus " + dpsConnectionStatus.name());
        }

        // 登录失败回调
        @Override
        public void onGetAuthCodeFailed(int errorCode, String uid) {
            Log.d(TAG, "onGetAuthCodeFailed errorCode " + errorCode + " uid " + uid);
            isAIMOnline = false;
        }

        // 本地登录成功，可进入IM或其他业务UI
        @Override
        public void onLocalLogin() {
            Log.d(TAG, "onLocalLogin");
            isAIMOnline = true;
            for (AliImInteractiveListener callBack : callBacks) {
                callBack.onLocalLogin();
            }

        }

        // 被踢事件回调，message为被踢下线附带的信息
        @Override
        public void onKickout(String s) {
            Log.d(TAG, "onKickout uid:" + s);

        }

        /**
         * 其他端设备在（离）线情况
         * @param type 事件类型（1：事件通知，包括上下线，2：状态通知，在线状态）
         * @param deviceType 设备类型
         * （0:default,1:web,2:Android,3:iOS,4:Mac,5:Windows,6:iPad）
         * @param status      设备状态（1：上线或在线，2：下线或离线）
         * @param time        时间（上线或下线时间）
         */
        @Override
        public void onDeviceStatus(int type, int deviceType, int status, long time) {
            Log.d(TAG, "onDeviceStatus type:" + type + " deviceType:" + deviceType + " status:" + status + " time:" + time);

        }

        /**
         * 下载资源cookie变更事件，仅当需要http下载资源时需要
         * @param cookie      新cookie
         */
        @Override
        public void onMainServerCookieRefresh(String cookie) {

        }
    };

    /**
     * 接受消息回调
     */
    private final AIMPubMsgListener aIMPubMsgListener = new AIMPubMsgListener() {

        @Override
        public void onAddedMessages(ArrayList<AIMPubNewMessage> arrayList) {
            Log.d(TAG, "AIMPubMsgListener onAddedMessages:" + arrayList.size());
            for (AliImInteractiveListener callBack : callBacks) {
                callBack.onAddedMessages(arrayList);
            }
        }

        @Override
        public void onRemovedMessages(ArrayList<AIMPubMessage> arrayList) {

        }

        @Override
        public void onStoredMessages(ArrayList<AIMPubMessage> arrayList) {

        }
    };

    private final DPSReleaseManagerListener dPSReleaseManagerListener = new DPSReleaseManagerListener() {

        @Override
        public void onSuccess() {
            Log.d(TAG, "DPSReleaseManagerListener onSuccess ");

        }

        @Override
        public void onFailure(DPSError dpsError) {
            Log.d(TAG, "DPSReleaseManagerListener onFailure " + dpsError.getReason());

        }
    };

    /**
     * 创建用户实例并登录
     *
     * @param userId
     */
    @Override
    public void createUserManager(String userId) {
        Log.d(TAG, "createUserManager " + userId);
        // 创建 userId 用户实例，异步，通过listener监听是否创建完成（内部会进行数据库初始化等操作）
        mUserId = userId;
        if (dpsPubEngine != null) {
            dpsPubEngine.createDPSManager(userId, dPSPubManagerCreateListener);
        }

    }

    /**
     * 加入群聊
     */
    @Override
    public void addMembers(String userId, String channelId, String nickName) {
        if (isIMNotOnline()) {
            Log.e(TAG, "当前用户AIM未在线");
            return;
        }
        getAimChannelId(userId, channelId, nickName);
    }

    private void internalAddMembers(String userId, String nickName, final String mChannelId, String appCid) {
        AIMPubModule imModule = AIMPubModule.getModuleInstance(userId);
        // 获取 MsgService
        if (imModule == null) {
            return;
        }
        AIMPubMsgService msgService = imModule.getMsgService();
        if (msgService == null) {
            return;
        }
        AIMPubGroupService groupService = imModule.getGroupService();
        if (groupService == null) {
            return;
        }
        groupService.addGroupMemberChangeListener(new AIMPubGroupMemberChangeListener() {
            @Override
            public void onAddedMembers(ArrayList<AIMPubGroupMember> arrayList) {
                for (AliImInteractiveListener callBack : callBacks) {
                    callBack.onGroupAddedMembers();
                }
            }

            @Override
            public void onRemovedMembers(ArrayList<AIMPubGroupMember> arrayList) {
                for (AliImInteractiveListener callBack : callBacks) {
                    callBack.onGroupRemovedMembers();
                }
            }

            @Override
            public void onUpdatedMembers(ArrayList<AIMPubGroupMember> arrayList) {
                for (AIMPubGroupMember aimPubGroupMember : arrayList) {
                    Log.i(TAG, "onUpdatedMembers: " + aimPubGroupMember.getGroupNick());
                }
            }
        });

        msgService.addMsgListener(aIMPubMsgListener);
        internalJoinChannel(appCid, userId, nickName, mChannelId);
    }

    /**
     * 加入IM频道
     */
    private void internalJoinChannel(String appCid, String appUid, String nickName, String mChannelId) {
        Map<String, String> params = new HashMap<>();
        params.put("appId", AIM_APPID);
        params.put("appCid", appCid);
        params.put("appUid", appUid);
        params.put("role", "3");
        params.put("room", mChannelId);
        params.put("nickName", nickName);

        OkHttpClientManager.getInstance().doGet(Constant.getAIMJoinChannelUrl(), params, new OkhttpClient.HttpCallBack() {
            @Override
            public void onSuccess(String result) {
                try {
                    Log.i(TAG, "aim internalJoinChannel: " + result);
                    AIMGetGroupBean aimJoinChannelBean = new Gson().fromJson(result, AIMGetGroupBean.class);
                    if (aimJoinChannelBean != null && aimJoinChannelBean.isSuccessful()) {
                        for (AliImInteractiveListener callBack : callBacks) {
                            callBack.joinGroupSuccess(new ArrayList<AIMPubGroupMember>());
                        }
                    }

                } catch (JsonSyntaxException e) {
                    DPSError dpsError = new DPSError();
                    dpsError.reason = e.getMessage();
                    for (AliImInteractiveListener callBack : callBacks) {
                        callBack.joinGroupFailure(dpsError);
                    }
                }
            }

            @Override
            public void onFailed(String errorMsg) {
                DPSError dpsError = new DPSError();
                dpsError.reason = errorMsg;
                for (AliImInteractiveListener callBack : callBacks) {
                    callBack.joinGroupFailure(dpsError);
                }
            }
        });
    }

    /**
     * 发送消息
     * tip:目前使用服务端发送消息
     *
     * @param userId
     * @param msg
     */
    @Override
    public void sendMessage(String userId, String msg, String displayName) {
        if (isIMNotOnline()) {
            Log.e(TAG, "当前用户AIM未在线");
            return;
        }
        if (getPubGroupAppCid() == null) {
            Log.e(TAG, "当前用户AIM未加入群聊");
            return;
        }
        // 获取 MsgService
        AIMPubModule imModule = AIMPubModule.getModuleInstance(userId);
        if (imModule == null) {
            return;
        }
        AIMPubMsgService msgService = imModule.getMsgService();
        if (msgService == null) {
            return;
        }

        Log.i(TAG, "Send message begin");
        HashMap<String, Object> extension = new HashMap<>();
        extension.put("type", 0);
        extension.put("isTeacher", false);
        extension.put("displayName", displayName);
        extension.put("message", msg);

        //转化为json格式
        JSONObject extensionJson = new JSONObject(extension);
        internalSendMessage(getPubGroupAppCid(), userId, extensionJson.toString());

    }

    private void internalSendMessage(String appCid, String sendUid, String content) {
        Map<String, String> params = new HashMap<>();
        params.put("appId", AIM_APPID);
        params.put("appCid", appCid);
        params.put("sendUid", sendUid);
        params.put("content", URLEncoder.encode(content));

        OkHttpClientManager.getInstance().doGet(Constant.sendMessageUrl(), params, new OkhttpClient.HttpCallBack() {
            @Override
            public void onSuccess(String result) {
                try {
                    AIMGetGroupBean aimSendMessageBean = new Gson().fromJson(result, AIMGetGroupBean.class);
                    if (aimSendMessageBean != null) {
                        if (aimSendMessageBean.isSuccessful()) {
                            for (AliImInteractiveListener callBack : callBacks) {
                                callBack.sendMessageSuccess(new AIMPubMessage());
                            }
                            Log.i(TAG, "aimSendMessageBean: " + aimSendMessageBean.getData());
                        } else {
                            for (AliImInteractiveListener callBack : callBacks) {
                                DPSError dpsError = new DPSError();
                                dpsError.reason = aimSendMessageBean.getData();
                                callBack.sendMessageFailure(dpsError);
                            }
                        }
                    }
                } catch (JsonSyntaxException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(String errorMsg) {
                Log.e(TAG, "aimSendMessageBean: onFailed" + errorMsg);
                for (AliImInteractiveListener callBack : callBacks) {
                    DPSError dpsError = new DPSError();
                    dpsError.reason = errorMsg;
                    callBack.sendMessageFailure(dpsError);
                }
            }
        });
    }

    /**
     * 举手
     */
    @Override
    public void handUp(String userId, String displayName) {
        if (isIMNotOnline()) {
            Log.e(TAG, "当前用户AIM未在线");
            return;
        }
        if (getPubGroupAppCid() == null) {
            Log.e(TAG, "当前用户AIM未加入群聊");
            return;
        }
        // 获取 MsgService
        AIMPubModule imModule = AIMPubModule.getModuleInstance(userId);
        if (imModule == null) {
            return;
        }
        AIMPubMsgService msgService = imModule.getMsgService();
        if (msgService == null) {
            return;
        }

        Log.i(TAG, "Send handUp begin");
        HashMap<String, Object> extension = new HashMap<>();
        extension.put("type", 1);
        extension.put("isTeacher", false);
        extension.put("displayName", displayName);
        extension.put("handUp", true);
        extension.put("message", "");

        //转化为json格式
        JSONObject extensionJson = new JSONObject(extension);
        internalSendMessage(getPubGroupAppCid(), userId, extensionJson.toString());
    }

    @Override
    public void setAliImInteractiveListener(AliImInteractiveListener callback) {
        callBacks.add(callback);
    }

    public void unRegister(AliImInteractiveListener callBack) {
        callBacks.remove(callBack);
    }

    private boolean isIMNotOnline() {
        return !isAIMOnline;
    }

    private String getPubGroupAppCid() {
        return mAppCid;
    }

    private void releaseDPSManager() {
        if (authService != null) {
            authService.logout(new DPSLogoutListener() {
                @Override
                public void onSuccess() {
                    if (dpsPubEngine != null) {
                        dpsPubEngine.releaseDPSManager(mUserId, dPSReleaseManagerListener);
                    }
                    Log.i(TAG, " logout onSuccess: ");
                }

                @Override
                public void onFailure(DPSError dpsError) {
                    Log.i(TAG, " logout onFailure: ");
                }
            });
        }
    }
}
