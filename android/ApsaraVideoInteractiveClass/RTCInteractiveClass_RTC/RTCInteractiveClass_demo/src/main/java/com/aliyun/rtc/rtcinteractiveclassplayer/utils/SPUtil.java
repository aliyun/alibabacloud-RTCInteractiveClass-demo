package com.aliyun.rtc.rtcinteractiveclassplayer.utils;

import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;

public class SPUtil {

    private static final String SP_NAME = "VOICE_CALL_SP";
    private SharedPreferences sp;

    private SPUtil() {
        sp = ApplicationContextUtil.getAppContext().getSharedPreferences(SP_NAME, Context.MODE_PRIVATE);
    }

    public static SPUtil getInstance() {
        return SPUtilInstance.INSTANCE;
    }

    private static class SPUtilInstance {
        private static final SPUtil INSTANCE = new SPUtil();
    }

    public void putString(String key, String value) {
        if (TextUtils.isEmpty(key) || TextUtils.isEmpty(value)) {
            return;
        }
        if (sp != null) {
            SharedPreferences.Editor edit = sp.edit();
            edit.putString(key, value);
            edit.apply();
        }
    }

    public String getString(String key, String defaultValue) {
        if (TextUtils.isEmpty(key)) {
            return null;
        }
        String string = null;
        if (sp != null) {
            string = sp.getString(key, defaultValue);
        }
        return string;
    }

    public void putBoolean(String key, boolean value) {
        if (TextUtils.isEmpty(key)) {
            return;
        }
        if (sp != null) {
            SharedPreferences.Editor edit = sp.edit();
            edit.putBoolean(key, value);
            edit.apply();
        }
    }

    public boolean getBoolean(String key, boolean defaultValue) {
        boolean b = false;

        if (sp != null && !TextUtils.isEmpty(key)) {
            b = sp.getBoolean(key, defaultValue);
        }
        return b;
    }
}
