package com.aliyun.rtc.rtcinteractiveclass.utils;

import android.text.TextUtils;

import com.aliyun.rtc.rtcinteractiveclass.bean.LoginUserInfoResponse;
import com.aliyun.rtc.rtcinteractiveclass.constant.Constant;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import java.util.HashMap;
import java.util.Map;

public class LoginUserManager {

    private LoginUserManager() {
    }

    private static LoginUserManager instance;

    private LoginUserInfoResponse.LoginUserInfo userInfo;

    public static LoginUserManager getInstance() {
        if (instance == null) {
            synchronized (LoginUserManager.class) {
                if (instance == null) {
                    instance = new LoginUserManager();
                }
            }
        }
        return instance;
    }

    public void obtainUserInfo(UserInfoResultListener listener) {

        if (!checkUserInfoHasData(userInfo)) {
            loadUserInfoBySp(listener);
        }

        if (!checkUserInfoHasData(userInfo)) {
//            loadUserInfoByNetwork(listener);
        }

        if (checkUserInfoHasData(userInfo)) {
            if (listener != null) {
                listener.onSuccess(userInfo);
            }
        }
    }

    private void loadUserInfoByNetwork(final UserInfoResultListener listener) {
        Map<String, String> params = new HashMap<>();
        params.put(Constant.NEW_GUEST_PARAMS_KEY_PACKAGE, ApplicationContextUtil.getAppContext().getPackageName());
//        OkHttpCientManager.sharedInstance().doGet(Constant.getUrlNewGuest(), null, new OkhttpClient.HttpCallBack() {
//            @Override
//            public void onSuccess(String result) {
//                if (!TextUtils.isEmpty(result)) {
//                    LoginUserInfoResponse loginUserInfoResponse = new Gson().fromJson(result, LoginUserInfoResponse.class);
//                    saveUserInfo(loginUserInfoResponse.getLoginUserInfo());
//                    if (listener != null) {
//                        listener.onSuccess(loginUserInfoResponse.getLoginUserInfo());
//                    }
//                }
//            }
//
//            @Override
//            public void onFaild(String errorMsg) {
//                if (listener != null) {
//                    listener.onFaild(errorMsg);
//                }
//            }
//        });
    }

    private void loadUserInfoBySp(UserInfoResultListener listener) {
        String userInfoString = SPUtil.getInstance().getString(Constant.ALIVC_VOICE_CALL_SP_KEY_USER_INFO, "");
        if (!TextUtils.isEmpty(userInfoString)) {
            try {
                userInfo = new Gson().fromJson(userInfoString, LoginUserInfoResponse.LoginUserInfo.class);
            } catch (JsonSyntaxException e) {
                e.printStackTrace();
            }

            if (listener != null && !checkUserInfoHasData(userInfo)) {
                listener.onSuccess(userInfo);
            }
        }
    }

    public interface UserInfoResultListener {
        void onSuccess(LoginUserInfoResponse.LoginUserInfo userInfo);

        void onFaild(String errorMsg);
    }

    private void saveUserInfo(LoginUserInfoResponse.LoginUserInfo userInfo) {
        if (userInfo != null) {
            this.userInfo = userInfo;
            String userInfoString = new Gson().toJson(this.userInfo, LoginUserInfoResponse.LoginUserInfo.class);
            SPUtil.getInstance().putString(Constant.ALIVC_VOICE_CALL_SP_KEY_USER_INFO, userInfoString);
        }
    }

    private boolean checkUserInfoHasData(LoginUserInfoResponse.LoginUserInfo userInfo) {
        return userInfo != null && !TextUtils.isEmpty(userInfo.getUserId());
    }
}
