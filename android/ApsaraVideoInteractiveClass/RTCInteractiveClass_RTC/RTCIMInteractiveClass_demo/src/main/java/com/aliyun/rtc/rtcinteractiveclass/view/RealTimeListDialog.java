package com.aliyun.rtc.rtcinteractiveclass.view;

import android.content.DialogInterface;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.EditText;

import com.alibaba.dingpaas.aim.AIMPubConversation;
import com.alibaba.dingpaas.aim.AIMPubGroupMember;
import com.alibaba.dingpaas.aim.AIMPubMessage;
import com.alibaba.dingpaas.aim.AIMPubNewMessage;
import com.alibaba.dingpaas.base.DPSError;
import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.adapter.ChatAdapter;
import com.aliyun.rtc.rtcinteractiveclass.bean.ChatBean;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveListener;
import com.aliyun.rtc.rtcinteractiveclass.rtc.AliRtcInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.utils.ScreenUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.SizeUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclass.utils.UIHandlerUtil;
import com.aliyun.svideo.common.utils.ThreadUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import java.util.ArrayList;
import java.util.Map;

/**
 * 实时互动
 */
public class RealTimeListDialog extends DialogFragment {
    public static final String REAL_TIME_TAG = "real_time_tag";
    private View view;
    //聊天列表
    private RecyclerView mChatRecyclerView;
    private ChatAdapter mChatAdapter;
    //输入内容
    private EditText mInputMsgEt;
    private ArrayList<ChatBean> mChatBeanList = new ArrayList<>();

    @Override
    public void onStart() {
        super.onStart();
        Window win = getDialog().getWindow();
        // 一定要设置Background，如果不设置，window属性设置无效
        win.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        WindowManager.LayoutParams params = win.getAttributes();
        params.gravity = Gravity.RIGHT;
        params.windowAnimations = R.style.AnimRight;
        params.width = SizeUtil.dip2px(getContext(), 320);
        params.height = ScreenUtil.getScreenHeight(getContext());
        win.setAttributes(params);
    }

    public static RealTimeListDialog getInstance(ArrayList<ChatBean> list) {
        RealTimeListDialog dialog = new RealTimeListDialog();
        Bundle bundle = new Bundle();
        bundle.putParcelableArrayList(REAL_TIME_TAG, list);
        dialog.setArguments(bundle);
        return dialog;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getData();
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        view = super.onCreateView(inflater, container, savedInstanceState);
        getDialog().requestWindowFeature(Window.FEATURE_NO_TITLE);
        getDialog().getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        getDialog().setCanceledOnTouchOutside(true);
        if (view == null) {
            view = inflater.inflate(R.layout.alivc_big_interactive_class_real_time_dialog, container);
            mChatRecyclerView = view.findViewById(R.id.realtime_chat_recyclerView);
            mInputMsgEt = view.findViewById(R.id.alivc_send_msg_et);
        }
        getData();
        initView();
        this.getDialog().setOnKeyListener(new DialogInterface.OnKeyListener() {
            @Override
            public boolean onKey(DialogInterface dialogInterface, int i, KeyEvent keyEvent) {
                if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_ENTER && keyEvent.getAction() != KeyEvent.ACTION_UP) {

                    String userId = AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo().getUserId();
                    String displayName = AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo().getDisplayName();
                    if (!TextUtils.isEmpty(getSendMessage())) {
                        AliImInteractiveEngine.sharedInstance().sendMessage(userId, getSendMessage(), displayName);
                    }
                }
                return false;
            }
        });
        return view;
    }

    private void getData() {
        Bundle arguments = getArguments();
        if (arguments != null) {
            if (arguments.getParcelableArrayList(REAL_TIME_TAG) != null) {
                mChatBeanList = arguments.getParcelableArrayList(REAL_TIME_TAG);
            }
        }
    }

    private void initView() {
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(getContext());
        linearLayoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        mChatRecyclerView.setLayoutManager(linearLayoutManager);
        if (mChatAdapter == null) {
            mChatAdapter = new ChatAdapter();
            mChatAdapter.addAllData(mChatBeanList);
            setAIMDelegate();
        }
        mChatRecyclerView.setAdapter(mChatAdapter);
        mChatRecyclerView.scrollToPosition(mChatAdapter.getItemCount() - 1);

    }

    /**
     * 设置AIM回调
     */
    private void setAIMDelegate() {
        AliImInteractiveEngine.sharedInstance().setAliImInteractiveListener(new AliImInteractiveListener() {

            @Override
            public void joinGroupSuccess(ArrayList<AIMPubGroupMember> arrayList) {

            }

            @Override
            public void joinGroupFailure(DPSError dpsError) {
            }

            @Override
            public void onLocalLogin() {
            }

            @Override
            public void sendMessageSuccess(AIMPubMessage aimPubMessage) {
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (mInputMsgEt != null) {
                            String trim = mInputMsgEt.getText().toString().trim();
                            if (!TextUtils.isEmpty(trim)) {
                                mInputMsgEt.setText("");
                            }
                        }
                    }
                });
            }

            @Override
            public void sendMessageFailure(DPSError dpsError) {
                showToastInCenter(dpsError.reason);
            }


            @Override
            public void onAddedMessages(ArrayList<AIMPubNewMessage> arrayList) {
                Log.i("scar", "onAddedMessages: " + arrayList.size());
                //判断消息类型
                for (AIMPubNewMessage aimPubNewMessage : arrayList) {
                    if (aimPubNewMessage == null) {
                        return;
                    }
                    AIMPubMessage messageMsg = aimPubNewMessage.getMsg();
                    if (messageMsg == null || messageMsg.content == null) {
                        return;
                    }
                    String jsonContent = messageMsg.content.textContent.getText();
                    parseMsgJson2Map(messageMsg, jsonContent);
                }
            }

            @Override
            public void onGroupAddedMembers() {

            }

            @Override
            public void onGroupRemovedMembers() {

            }
        });
    }

    private void parseMsgJson2Map(AIMPubMessage messageMsg, String jsonContent) {
        if (!TextUtils.isEmpty(jsonContent)) {
            Map resultMap = null;
            double type = 0;
            try {
                resultMap = new Gson().fromJson(jsonContent, Map.class);
                type = -1;
                if (resultMap.containsKey("type")) {
                    type = (double) resultMap.get("type");
                }
                //收到消息
                if (type == 0) {
                    processReceivesMsg(messageMsg, resultMap);
                }
            } catch (JsonSyntaxException | NumberFormatException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 处理im收到的普通消息
     *
     * @param messageMsg
     * @param resultMap
     */
    private void processReceivesMsg(AIMPubMessage messageMsg, Map resultMap) {
        String displayName = null;
        String message = null;
        if (resultMap.get("displayName") != null) {
            displayName = (String) resultMap.get("displayName");
        }
        if (resultMap.get("message") != null) {
            message = (String) resultMap.get("message");
        }
        //消息体不为空，存在消息，添加到聊天列表
        boolean equals = AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo().getUserId().equals(messageMsg.getSender());
        ChatBean chatBean = new ChatBean()
                .setUid(messageMsg.getSender())
                .setLocal(equals)
                .setMsg(message)
                .setDisplayName(displayName);
        addChatUser(chatBean);

    }

    /**
     * 聊天列表添加用户
     */
    private void addChatUser(final ChatBean chatBean) {
        ThreadUtils.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mChatAdapter != null) {
                    mChatAdapter.addData(chatBean);
                    if (mChatRecyclerView != null && mChatAdapter != null) {
                        mChatRecyclerView.smoothScrollToPosition(mChatAdapter.getItemCount() - 1);
                    }
                }
            }
        });
    }

    private String getSendMessage() {
        return mInputMsgEt == null ? "" : mInputMsgEt.getText().toString().trim();
    }

    private DialogInterface.OnDismissListener mOnClickListener;

    public void setOnDismissListener(DialogInterface.OnDismissListener listener) {
        this.mOnClickListener = listener;
    }

    @Override
    public void onDismiss(DialogInterface dialog) {
        super.onDismiss(dialog);
        if (mOnClickListener != null) {
            mOnClickListener.onDismiss(dialog);
        }
    }

    private void showToastInCenter(final String msg) {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            ToastUtils.showInCenter(getContext(), msg);
        } else {
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    ToastUtils.showInCenter(getContext(), msg);
                }
            });
        }
    }
}
