package com.aliyun.rtc.rtcinteractiveclass.constant;

public class Constant {

    /**
     * 设置必要信息，appKey和appID从AIM控制台的 直播互动>功能配置 页面获取
     * 实际开发中不建议将appKey和appId写在本地，容易被盗取信息造成流量的损失
     * 参考链接 https://help.aliyun.com/document_detail/272591.html?spm=a2c4g.11174283.6.546.4b004c07jhqsGe
     */
    public static final String AIM_APPKEY = ;

    /**
     * 设置必要信息，appKey和appID从AIM控制台的 直播互动>功能配置 页面获取
     * 实际开发中不建议将appKey和appId写在本地，容易被盗取信息造成流量的损失
     * 参考链接 https://help.aliyun.com/document_detail/272591.html?spm=a2c4g.11174283.6.546.4b004c07jhqsGe
     */

    public static final String AIM_APPID = ;

    public static final String NEW_TOKEN_PARAMS_KEY_USERID = "userName";
    public static final String NEW_TOKEN_PARAMS_KEY_PLATFORM = "platform";
    public static final String NEW_TOKEN_PARAMS_VALUE_PLATFORM = "android";
    public static final String NEW_GUEST_PARAMS_KEY_PACKAGE = "PACKAGE_NAME";
    public static final String NEW_TOKEN_PARAMS_KEY_CHANNELID = "channelId";
    public static final String ALIVC_VOICE_CALL_SP_KEY_USER_INFO = "user_info";

    /**
     * server端的请求域名，需要用户自己替换成自己server端的域名
     */
    private static final String BASE_URL = ;

    /**
     * 获取鉴权信息
     */
    private static final String URL_NEW_TOKEN = BASE_URL + "/interactive-live-class/getRtcAuth";


    /**
     * IM获取授权信息
     */
    private static final String AIM_LOGIN_TOKEN_PRE_URL = BASE_URL + "/interactive-live-class/im/login";

    /**
     * 获取群聊频道ID
     */
    private static final String AIM_LOGIN_CHANNEL_ID_URL = BASE_URL + "/interactive-live-class/im/getGroup";

    /**
     * 加入群聊AIM
     */
    private static final String AIM_LOGIN_JOIN_CHANNEL = BASE_URL + "/interactive-live-class/im/joinChannel";

    /**
     * 发送消息
     */
    private static final String AIM_LOGIN_SEND_MESSAGE = BASE_URL + "/interactive-live-class/im/sendMsg";

    public static String getUserLoginUrl() {
        return URL_NEW_TOKEN;
    }

    public static String getAIMTokenLoginUrl() {
        return AIM_LOGIN_TOKEN_PRE_URL;
    }

    public static String getAIMChannelIdUrl() {
        return AIM_LOGIN_CHANNEL_ID_URL;
    }

    public static String getAIMJoinChannelUrl() {
        return AIM_LOGIN_JOIN_CHANNEL;
    }

    public static String sendMessageUrl() {
        return AIM_LOGIN_SEND_MESSAGE;
    }



}
