package com.aliyun.rtc.rtcinteractiveclass.im;

import com.alibaba.dingpaas.aim.AIMPubGroupMember;
import com.alibaba.dingpaas.aim.AIMPubMessage;
import com.alibaba.dingpaas.aim.AIMPubNewMessage;
import com.alibaba.dingpaas.base.DPSError;

import java.util.ArrayList;

/**
 * AIM相关接口回调
 */
public interface AliImInteractiveListener {

    /**
     * 加入群聊成功
     */
    void joinGroupSuccess(ArrayList<AIMPubGroupMember> arrayList);

    /**
     * 加入群聊失败
     */
    void joinGroupFailure(DPSError dpsError);

    /**
     * 本地登录成功
     */
    void onLocalLogin();

    /**
     * 发送消息成功
     */
    void sendMessageSuccess(AIMPubMessage aimPubMessage);

    /**
     * 发送消息失败
     */
    void sendMessageFailure(DPSError dpsError);

    /**
     * 收到新消息的回调，可通过newMsg.type 区分是自己发送的，或在线/离线状态收到的消息
     */
    void onAddedMessages(final ArrayList<AIMPubNewMessage> arrayList);

    /**
     * 新增群成员
     */
    void onGroupAddedMembers();

    /**
     * 移除群成员
     */
    void onGroupRemovedMembers();

}