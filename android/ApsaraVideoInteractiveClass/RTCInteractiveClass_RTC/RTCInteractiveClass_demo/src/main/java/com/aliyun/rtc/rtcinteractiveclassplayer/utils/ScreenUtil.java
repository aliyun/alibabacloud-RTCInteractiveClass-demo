package com.aliyun.rtc.rtcinteractiveclassplayer.utils;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.view.View;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.alivc.rtc.AliRtcEngine;
import com.aliyun.rtc.rtcinteractiveclassplayer.rtc.RTCInteractiveClassImpl;

public class ScreenUtil {

    /*适配水滴屏*/
    public static void autoWaterScreen(View topView) {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            int statusBarHeight = getStatusBarHeight(topView.getContext());
            RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) topView.getLayoutParams();
            layoutParams.setMargins(0, statusBarHeight, 0, 0);
            topView.setLayoutParams(layoutParams);
        }
    }

    /**
     * 获取状态栏高度
     *
     * @return 状态栏高度
     */
    private static int getStatusBarHeight(Context context) {
        try {
            // 获得状态栏高度
            int resourceId = context.getResources().getIdentifier("status_bar_height", "dimen", "android");
            return context.getResources().getDimensionPixelSize(resourceId);
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    //全屏并且隐藏状态栏
    public static void hideStatusBar(Activity activity) {
        WindowManager.LayoutParams attrs = activity.getWindow().getAttributes();
        attrs.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
        activity.getWindow().setAttributes(attrs);
    }

    //全屏并且状态栏透明显示
    public static void showStatusBar(Activity activity) {
        WindowManager.LayoutParams attrs = activity.getWindow().getAttributes();
        attrs.flags &= ~WindowManager.LayoutParams.FLAG_FULLSCREEN;
        activity.getWindow().setAttributes(attrs);
    }

    @SuppressLint("SourceLockedOrientationActivity")
    public static void setLandscapeScreen(Activity activity) {
        int requestedOrientation = activity.getRequestedOrientation();
        if (requestedOrientation != ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
            activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
            RTCInteractiveClassImpl.sharedInstance().setDeviceOrientationMode(AliRtcEngine.AliRtcOrientationMode.AliRtcOrientationModePortrait);
        }
    }

    @SuppressLint("SourceLockedOrientationActivity")
    public static void setPortraitScreen(Activity activity) {
        int requestedOrientation = activity.getRequestedOrientation();
        if (requestedOrientation != ActivityInfo.SCREEN_ORIENTATION_PORTRAIT) {
            activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        }
    }

    public static boolean isLandscapeLayout(Activity activity) {
        return activity.getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
    }
}
