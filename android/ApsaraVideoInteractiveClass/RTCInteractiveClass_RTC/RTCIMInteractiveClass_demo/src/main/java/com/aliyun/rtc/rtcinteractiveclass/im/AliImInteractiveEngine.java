package com.aliyun.rtc.rtcinteractiveclass.im;

import com.alibaba.dingpaas.aim.AIMPubGroupListAllMemberListener;
public abstract class AliImInteractiveEngine {

    /**
     * 获取单例
     */
    public static AliImInteractiveEngine sharedInstance() {
        return AliImInteractiveEngineImpl.sharedInstance();
    }

    /**
     * 销毁实例
     */
    public static void destroy() {
        AliImInteractiveEngineImpl.destroyInstance();
    }

    /**
     * 创建用户实例并登录
     *
     * @param userId 用户ID
     */
    public abstract void createUserManager(String userId);

    /**
     * 加入群聊
     *
     * @param userId   用户ID
     * @param nickName 昵称
     */
    public abstract void addMembers(String userId, String channelId, String nickName);

    /**
     * 发送消息
     *
     * @param userId 用户ID
     * @param msg    消息内容
     */
    public abstract void sendMessage(String userId, String msg, String displayName);

    /**
     * 举手
     *
     * @param userId 用户ID
     */
    public abstract void handUp(String userId, String displayName);

    /**
     * 设置回调
     */
    public abstract void setAliImInteractiveListener(AliImInteractiveListener callback);

    /**
     * 拉取所有群成员
     */
    public abstract void listAllMembers(AIMPubGroupListAllMemberListener listener);


}