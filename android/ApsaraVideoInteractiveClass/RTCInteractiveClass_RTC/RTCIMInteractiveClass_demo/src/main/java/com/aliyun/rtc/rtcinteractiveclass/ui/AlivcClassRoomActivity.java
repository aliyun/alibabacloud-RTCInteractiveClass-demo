package com.aliyun.rtc.rtcinteractiveclass.ui;


import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.constraint.ConstraintLayout;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.DividerItemDecoration;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewParent;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.alibaba.dingpaas.aim.AIMPubGroupListAllMemberListener;
import com.alibaba.dingpaas.aim.AIMPubGroupMember;
import com.alibaba.dingpaas.aim.AIMPubMessage;
import com.alibaba.dingpaas.aim.AIMPubNewMessage;
import com.alibaba.dingpaas.base.DPSError;
import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.AliRtcRemoteUserInfo;
import com.alivc.rtc.device.utils.StringUtils;
import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.adapter.RemoteUserAdapter;
import com.aliyun.rtc.rtcinteractiveclass.bean.ChatBean;
import com.aliyun.rtc.rtcinteractiveclass.bean.FeedBackInfo;
import com.aliyun.rtc.rtcinteractiveclass.bean.RemoteUserInfo;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveListener;
import com.aliyun.rtc.rtcinteractiveclass.rtc.AliRtcInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.rtc.AliRtcInteractiveListener;
import com.aliyun.rtc.rtcinteractiveclass.utils.ScreenUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclass.utils.UIHandlerUtil;
import com.aliyun.rtc.rtcinteractiveclass.view.AlivcTipDialog;
import com.aliyun.rtc.rtcinteractiveclass.view.RealTimeListDialog;
import com.aliyun.rtc.rtcinteractiveclass.view.TitleBar;
import com.aliyun.rtc.rtcinteractiveclass.view.UserOnlineListDialog;
import com.aliyun.svideo.common.utils.ClipboardUtil;
import com.aliyun.svideo.common.utils.ThreadUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import java.util.ArrayList;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

public class AlivcClassRoomActivity extends AppCompatActivity implements AliRtcInteractiveListener, TitleBar.BackBtnListener, TitleBar.MenuBtnListener, View.OnClickListener {


    private static final String TAG = AlivcClassRoomActivity.class.getSimpleName();
    //横屏时隐藏页面上的view的倒计时时间
    private static final int HIDE_VIEW_TIME = 15;
    //允许最大上麦学生数量
    private static final int MAX_STUDENTS_NUMBER = 10;
    private String mChannelId;
    private boolean mMuteLocalMic, mMuteLocalCamera;
    private String mStudentName;
    protected String mTeacherUid = "";
    private RecyclerView mRcyStudentList;
    private RemoteUserAdapter mStudentListAdapter;
    private TextView mTvChannelName;

    private ImageView mIbShare;
    private LinearLayout mLayoutMuteMic;
    private LinearLayout mLayoutMuteCamera;
    private ImageView mIvMuteMic;
    private ImageView mIvMuteCamera;

    private AudioManager mAudioManager;

    //老师屏幕流
    private FrameLayout mScreenContainer;
    //老师相机流
    private FrameLayout mCameraContainer;
    //老师昵称
    private TextView mTeacherDisplayName;
    //老师麦克风控制
    private ImageView mTeacherMicIv;
    //老师相机流控制
    private ImageView mTeacherCameraIv;
    //正在发言用户
    private TextView mSpeakerUsersTv;
    //教师昵称
    private TextView mTeacherDisplayNameNotify;
    //在线列表
    private LinearLayout mOnlineLayout;
    //申请连麦
    private LinearLayout mApplyCallLayout;
    private ImageView mIvApplyCall;
    private TextView mTvApplyCall;
    //实时互动
    private LinearLayout mRealTimeLayout;
    private ImageView mIvRealTime;
    private final Gson gson = new Gson();
    //记录入会时间
    private long mJoinChannelTime = 0L;

    private final ArrayList<ChatBean> mChatBeanList = new ArrayList<>();
    private RealTimeListDialog mRealTimeListDialog;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        if (ScreenUtil.isLandscapeLayout(this)) {
            ScreenUtil.hideStatusBar(this);
        }
        setContentView(R.layout.alivc_im_big_interactive_class_activity_rtc_chat);
        getDataForIntent();
        initView();
        newStudentLogin();
        setAIMDelegate();

        mAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
    }


    /**
     * 学生身份登录
     */
    public void newStudentLogin() {
        AliRtcEngine.AliRtcVideoCanvas videoCanvas = new AliRtcEngine.AliRtcVideoCanvas();
        videoCanvas.view = AliRtcInteractiveEngine.sharedInstance().createRenderView(this);
        AliRtcInteractiveEngine.sharedInstance().setLocalViewConfig(videoCanvas, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera);
        AliRtcInteractiveEngine.sharedInstance().login(mChannelId, mStudentName);
        AliRtcInteractiveEngine.sharedInstance().setAliRtcInteractiveListener(this);

    }

    /**
     * 设置AIM回调
     */
    private void setAIMDelegate() {
        AliImInteractiveEngine.sharedInstance().setAliImInteractiveListener(new AliImInteractiveListener() {

            @Override
            public void joinGroupSuccess(ArrayList<AIMPubGroupMember> arrayList) {
                Log.i(TAG, "joinGroupSuccess:  size " + arrayList.size());

            }

            @Override
            public void joinGroupFailure(DPSError dpsError) {
                showToastInCenter("加入群聊失败: " + dpsError.getReason());

            }

            @Override
            public void onLocalLogin() {
                Log.i(TAG, "onLocalLogin: ");
                AliImInteractiveEngine.sharedInstance().addMembers(getLocalUserId(), mChannelId, mStudentName);


            }

            @Override
            public void sendMessageSuccess(AIMPubMessage aimPubMessage) {
                Log.i(TAG, "sendMessageSuccess: aimPubMessage " + aimPubMessage.content);

            }

            @Override
            public void sendMessageFailure(DPSError dpsError) {
                showToastInCenter("消息发送失败");
            }

            @Override
            public void onAddedMessages(ArrayList<AIMPubNewMessage> arrayList) {
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


    /**
     * 将json消息解析成map
     *
     * @param messageMsg
     * @param jsonContent
     */
    private void parseMsgJson2Map(AIMPubMessage messageMsg, String jsonContent) {
        if (!TextUtils.isEmpty(jsonContent)) {
            Map resultMap = null;
            double type = 0;
            try {
                resultMap = gson.fromJson(jsonContent, Map.class);
                Log.e(TAG, jsonContent);
                type = -1;
                if (resultMap.containsKey("type")) {
                    type = (double) resultMap.get("type");
                }
                //收到消息
                if (type == 0) {
                    processReceivesMsg(messageMsg, resultMap);
                } else if (type == 1) {//信令模式
                    processSignal(resultMap);
                }
            } catch (JsonSyntaxException | NumberFormatException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 处理信令消息
     *
     * @param resultMap
     */
    private void processSignal(Map resultMap) {

        boolean isTeacher = false;
        if (resultMap.containsKey("isTeacher")) {
            isTeacher = (boolean) resultMap.get("isTeacher");
        }
        String uid = null;
        if (resultMap.containsKey("uid")) {
            uid = (String) resultMap.get("uid");
        }
        //全部静音
        if (isTeacher) {
            if (resultMap.containsKey("muteAllMic")) {
                signalMuteMic((boolean) resultMap.get("muteAllMic"));
            }
        }
        //当前用户跟被关闭相机用户uid一致，则进行关闭操作，否则不处理
        if (isTeacher && !TextUtils.isEmpty(uid) && getLocalUserId().equals(uid)) {
            if (resultMap.containsKey("muteCamera")) {
                signalMuteCamera((boolean) resultMap.get("muteCamera"));
            }
        }
        //收到教师举手反馈
        if (isTeacher && !TextUtils.isEmpty(uid) && getLocalUserId().equals(uid)) {
            if (resultMap.containsKey("backHandUp"))
                signalMuteHandUp((Boolean) resultMap.get("backHandUp"));
        }

        // 当前用户跟被静音用户uid一致，则进行静音操作，否则不处理
        if (isTeacher && !TextUtils.isEmpty(uid) && getLocalUserId().equals(uid)) {
            if (resultMap.containsKey("muteMic")) {
                signalMuteMic((boolean) resultMap.get("muteMic"));
            }
        }
    }

    /**
     * 处理im收到的普通消息
     *
     * @param resultMap
     */
    private void processReceivesMsg(final AIMPubMessage messageMsg, final Map resultMap) {
        if (resultMap.get("message") != null && resultMap.get("displayName") != null) {
            ThreadUtils.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    String displayName = (String) resultMap.get("displayName");
                    String message = (String) resultMap.get("message");
                    if (!TextUtils.isEmpty(message) && !mIvRealTime.isSelected()) {
                        mIvRealTime.setBackground(ContextCompat.getDrawable(AlivcClassRoomActivity.this, R.drawable.alivc_biginteractiveclass_real_time_selected));
                        boolean equals = getLocalUserId().equals(messageMsg.getSender());
                        ChatBean chatBean = new ChatBean()
                                .setUid(messageMsg.getSender())
                                .setLocal(equals)
                                .setMsg(message)
                                .setDisplayName(displayName);
                        mChatBeanList.add(chatBean);
                    }
                }
            });
        }

    }

    /**
     * 教师端下发的打开/关闭麦克风操作
     */
    private synchronized void signalMuteMic(final boolean mute) {
        Log.i(TAG, "signalMuteMic " + mute);
        ThreadUtils.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mIvMuteMic != null) {
                    mIvMuteMic.setSelected(mute);
                }
                muteLocalMic(mute);
            }
        });
    }

    /**
     * 教师端下发的关闭/打开相机流操作
     */
    private synchronized void signalMuteCamera(final boolean mute) {
        Log.i(TAG, "signalMuteCamera" + mute);
        ThreadUtils.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mIvMuteCamera != null) {
                    mIvMuteCamera.setSelected(mute);
                }
                muteLocalCamera(mute);
            }
        });
    }

    /**
     * 教师端下发举手反馈操作
     */
    private synchronized void signalMuteHandUp(final boolean mute) {
        Log.i(TAG, "signalMuteHandUp" + mute);
        ThreadUtils.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                showToastInCenter(mute ? "老师已同意连麦" : "老师已拒绝连麦");
                if (mute) {
                    //连麦第二步：收到教师端信令，学生上麦
                    mIvApplyCall.setBackground(ContextCompat.getDrawable(AlivcClassRoomActivity.this, R.drawable.alivc_biginteractiveclass_self_apply_call_selected));
                    AliRtcInteractiveEngine.sharedInstance().enterSeat();
                }
            }
        });
    }

    /**
     * 举手
     */
    private void sendHandUp() {
        AliImInteractiveEngine.sharedInstance().handUp(getLocalUserId(), mStudentName);
    }

    private void initView() {
        mScreenContainer = findViewById(R.id.alivc_big_interactive_class_fl_Container);
        mRcyStudentList = findViewById(R.id.alivc_big_interactive_class_rcy_student_list);
        mIbShare = findViewById(R.id.alivc_big_interactive_class_landscape_ib_share);
        mTvChannelName = findViewById(R.id.alivc_big_interactive_class_tv_landscape_channel_name);
        mSpeakerUsersTv = findViewById(R.id.alivc_big_interactive_class_tv_speaker);
        //right
        mCameraContainer = findViewById(R.id.alivc_big_interactive_class_camera_container);
        mTeacherDisplayName = findViewById(R.id.alivc_big_interactive_class_tv_teacher_display_name);
        mTeacherDisplayNameNotify = findViewById(R.id.alivc_big_interactive_class_tv_teacher_display_name_notify);
        mTeacherMicIv = findViewById(R.id.alivc_big_interactive_class_iv_teacher_mutemic);
        mTeacherCameraIv = findViewById(R.id.alivc_big_interactive_class_iv_teacher_mutecamera);
        mOnlineLayout = findViewById(R.id.online_item_layout);
        mApplyCallLayout = findViewById(R.id.apply_call_item_layout);
        mRealTimeLayout = findViewById(R.id.real_time_item_layout);
        mIvApplyCall = findViewById(R.id.apply_call_item_iv);
        mTvApplyCall = findViewById(R.id.apply_call_item_tv);
        mIvRealTime = findViewById(R.id.real_time_item_iv);
        ConstraintLayout constraintLayout = findViewById(R.id.alivc_big_interactive_class_rl_content_class_room);
        mIvMuteMic = findViewById(R.id.alivc_big_interactive_class_iv_student_mutemic);
        mIvMuteCamera = findViewById(R.id.alivc_big_interactive_class_iv_student_mutecamera);
        mLayoutMuteMic = findViewById(R.id.alivc_big_interactive_class_layout_student_mutemic);
        mLayoutMuteCamera = findViewById(R.id.alivc_big_interactive_class_layout_student_mutecamera);

        mOnlineLayout.setOnClickListener(this);
        mApplyCallLayout.setOnClickListener(this);
        mRealTimeLayout.setOnClickListener(this);
        mTeacherCameraIv.setOnClickListener(this);
        mTeacherMicIv.setOnClickListener(this);
        mTvChannelName.setOnClickListener(this);
        constraintLayout.setOnClickListener(this);
        mLayoutMuteMic.setOnClickListener(this);
        mLayoutMuteCamera.setOnClickListener(this);

        initStudentList();
        if (mTvChannelName != null) {
            mTvChannelName.setText(String.format(getString(R.string.alivc_biginteractiveclass_string_title_channel_id), mChannelId));
        }
        if (mIbShare != null) {
            mIbShare.setOnClickListener(this);
        }
    }

    /**
     * 初始化学生列表
     */
    private void initStudentList() {
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        linearLayoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        mRcyStudentList.setLayoutManager(linearLayoutManager);
        DividerItemDecoration divider = new DividerItemDecoration(this, DividerItemDecoration.VERTICAL);
        divider.setDrawable(getResources().getDrawable(R.drawable.alivc_biginteractiveclass_divider_vertical_userlist));
        mRcyStudentList.addItemDecoration(divider);
        DefaultItemAnimator anim = new DefaultItemAnimator();
        anim.setSupportsChangeAnimations(false);
        mRcyStudentList.setItemAnimator(anim);
        mRcyStudentList.setHasFixedSize(true);
        mStudentListAdapter = new RemoteUserAdapter();
        mRcyStudentList.setAdapter(mStudentListAdapter);
    }

    /**
     * 获取intent传过来的用户信息
     */
    private void getDataForIntent() {
        Intent intent = getIntent();
        if (intent != null) {
            Bundle bundle = intent.getExtras();
            if (bundle != null) {
                //频道号
                mChannelId = bundle.getString("channel");
                //学生姓名
                mStudentName = bundle.getString("studentName");
            }
        }
    }


    @Override
    public void onBackBtnClicked() {
        onBackPressed();
    }

    /**
     * 退出教室
     */
    private void showExitDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
                .setDes(getString(R.string.alivc_biginteractiveclass_string_hint_leave_channel))
                .setDrawableTip(R.drawable.alivc_biginteractiveclass_important_warn)
                .setButtonType(AlivcTipDialog.TWO_BUTTON)
                .setCancelStr(getString(R.string.alivc_biginteractiveclass_string_confirm))
                .setConfirmStr(getString(R.string.alivc_biginteractiveclass_string_continue))
                .setTwoButtonClickListener(new AlivcTipDialog.TwoButtonClickListener() {
                    @Override
                    public void onCancel() {
                        getChannelNum(new OnGroupMemberCallBack() {
                            @Override
                            public void onSuccess(int size) {
                                startToFeedback(size);
                            }
                        });
                    }

                    @Override
                    public void onConfirm() {
                    }
                })
                .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        alivcTipDialog.show();
    }

    /**
     * 申请连麦
     */
    private void showApplyCallDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
                .setDes(getString(R.string.alivc_biginteractiveclass_string_hint_apply_call))
                .setButtonType(AlivcTipDialog.TWO_BUTTON)
                .setCancelStr(getString(R.string.alivc_biginteractiveclass_string_continue))
                .setConfirmStr(getString(R.string.alivc_biginteractiveclass_string_confirm))
                .setDrawableTip(R.drawable.alivc_biginteractiveclass_warn)
                .setTwoButtonClickListener(new AlivcTipDialog.TwoButtonClickListener() {
                    @Override
                    public void onCancel() {
                    }

                    @Override
                    public void onConfirm() {
                        sendHandUp();
                    }
                })
                .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        alivcTipDialog.show();
    }

    @Override
    public void onMenuBtnClicked(int id) {
        onBackPressed();
    }

    @Override
    public void onBackPressed() {
        showExitDialog();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //在destroy中释放播放器和rtc资源
        AliRtcInteractiveEngine.sharedInstance().logout();
        AliRtcInteractiveEngine.destroy();
        AliImInteractiveEngine.destroy();
        Log.e(TAG, "onDestroy: ");
    }

    private void muteLocalCamera(boolean mute) {
        if (!AliRtcInteractiveEngine.sharedInstance().isActiveStudent()) {
            int localCamera = AliRtcInteractiveEngine.sharedInstance().muteLocalCamera(mute);
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(getLocalUserId());
            if (localCamera != -1 && remoteUserInfo != null && remoteUserInfo.isLocal()) {
                mMuteLocalCamera = mute;
                remoteUserInfo.setHasVideo(mute);
                mStudentListAdapter.updateData(remoteUserInfo);
            }
        }
    }

    private void muteLocalMic(boolean mute) {
        if (!AliRtcInteractiveEngine.sharedInstance().isActiveStudent()) {
            int localMic = AliRtcInteractiveEngine.sharedInstance().muteLocalMic(mute);
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(getLocalUserId());
            if (localMic != -1 && remoteUserInfo != null && remoteUserInfo.isLocal()) {
                mMuteLocalMic = mute;
                remoteUserInfo.setHasAudio(mute);
                mStudentListAdapter.updateData(remoteUserInfo);
            }
        }
    }

    /**
     * 展示远端列表
     */
    private void showOnlineDialog() {
        UserOnlineListDialog listDialog = new UserOnlineListDialog();
        Bundle bundle = new Bundle();
        bundle.putString(UserOnlineListDialog.TEACHER_NAME, mTeacherDisplayName.getText().toString());
        listDialog.setArguments(bundle);
        listDialog.show(getSupportFragmentManager(), "listDialog");
    }

    /**
     * 切换学生下上麦状态
     */
    private void toggleClientRole() {
        if (!AliRtcInteractiveEngine.sharedInstance().isActiveStudent()) {
            showLeaveSeatDialog();
        } else {
            //判断当前麦上用户数量,超过10则不进行连麦
            if (mStudentListAdapter.getItemCount() >= MAX_STUDENTS_NUMBER) {
                showToastInCenter("连麦学生数量已满，请等待其它同学下麦后再次申请");
                return;
            }
            //连麦第一步：发送举手信令请求上麦
            showApplyCallDialog();
        }
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        if (id == R.id.alivc_big_interactive_class_rl_content_class_room) {

        } else if (id == R.id.alivc_big_interactive_class_landscape_ib_share) {
            showExitDialog();
        } else if (id == R.id.alivc_big_interactive_class_tv_landscape_channel_name) {
            boolean copy = ClipboardUtil.copy(AlivcClassRoomActivity.this, mChannelId);
            String msg = getString(copy ? R.string.alirtc_audioliveroom_string_copy_success : R.string.alirtc_audioliverooms_string_copy_faild);
            showToastInCenter(msg);
        } else if (id == R.id.online_item_layout) {
            showOnlineDialog();
        } else if (id == R.id.apply_call_item_layout) {
            toggleClientRole();
        } else if (id == R.id.real_time_item_layout) {
            showRealTimeDialog();
        } else if (id == R.id.alivc_big_interactive_class_layout_student_mutemic) {
            v.setSelected(!v.isSelected());
            muteLocalMic(v.isSelected());
        } else if (id == R.id.alivc_big_interactive_class_layout_student_mutecamera) {
            v.setSelected(!v.isSelected());
            muteLocalCamera(v.isSelected());
        }
    }

    private void showRealTimeDialog() {
        if (mRealTimeListDialog == null) {
            mRealTimeListDialog = RealTimeListDialog.getInstance(mChatBeanList);
            mRealTimeListDialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
                @Override
                public void onDismiss(DialogInterface dialogInterface) {
                    mIvRealTime.setSelected(false);
                }
            });
        }
        if (!mRealTimeListDialog.isResumed()) {
            mIvRealTime.setSelected(true);
            mIvRealTime.setBackground(ContextCompat.getDrawable(AlivcClassRoomActivity.this, R.drawable.alivc_biginteractiveclass_real_time_normal));
            mRealTimeListDialog.show(getSupportFragmentManager(), "mRealTimeListDialog");
        }
    }

    /**
     * 用户上麦结果通知
     */
    @Override
    public void onEnterSeatResult() {

    }

    /**
     * 用户下麦结果通知
     */
    @Override
    public void onLeaveSeatResult() {
        //下麦移除自己远端画面
        RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(getLocalUserId());
        if (remoteUserInfo != null) {
            mStudentListAdapter.remoteData(remoteUserInfo);
        }
    }


    @Override
    public void onOccurError(int error) {

    }

    @Override
    public void onOccurWarning(int error) {

    }

    /**
     * 被服务器踢出或者频道关闭时回调
     * * @param i 状态码
     */
    @Override
    public void onRoomDestroy(int result) {
        Log.i(TAG, "onBye: " + result);
        //频道关闭，体验时间结束
        if (result == 2) {
            showTimeoutDialog();
        } else {
            finish();
        }
    }

    /**
     * 当提示下列三个错误时需要重新创建实例
     *
     * @param error 错误码
     */
    @Override
    public void onSDKError(int error) {
        showRtcErrorDialog();
    }

    /**
     * @param result 加入房间的结果码，0为成功，反之失败
     */
    @Override
    public void onJoinChannelResult(int result) {
        if (result != 0) {
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(R.string.alivc_biginteractiveclass_string_hint_join_room_faild));
                }
            });
        } else {
            mJoinChannelTime = System.currentTimeMillis();
        }
    }


    /**
     * 远端用户上线通知
     *
     * @param userId userid
     */
    @Override
    public void onRemoteUserOnLineNotify(String userId) {
        Log.d(TAG, "onRemoteUserOnLineNotify" + userId);
        addRemoteUser(userId);

    }

    /**
     * 远端用户下线通知
     *
     * @param userId userId
     */
    @Override
    public void onRemoteUserOffLineNotify(final String userId) {
        //移除老师相关的画面
        if (StringUtils.equals(mTeacherUid, userId)) {
            if (!isTipDialogShow) {
                getChannelNum(new OnGroupMemberCallBack() {
                    @Override
                    public void onSuccess(int size) {
                        startToFeedback(size);
                    }
                });
            }
        } else {
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(userId);
            if (remoteUserInfo != null) {
                mStudentListAdapter.remoteData(remoteUserInfo);
            }

        }
    }


    @Override
    public void onLeaveChannelResult(int result) {

    }


    /**
     * 远端用户发布音视频流变化通知
     *
     * @param uid              userid
     * @param aliRtcAudioTrack 音频流
     * @param aliRtcVideoTrack 相机流
     */
    @Override
    public void onRemoteTrackAvailableNotify(final String uid, AliRtcEngine.
            AliRtcAudioTrack aliRtcAudioTrack, final AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
        updateRemoteDisplay(uid, aliRtcAudioTrack, aliRtcVideoTrack);
    }


    /**
     * 音频订阅情况变更回调
     *
     * @param uid      用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    @Override
    public void onAudioSubscribeStateChanged(String uid, AliRtcEngine.AliRtcSubscribeState
            oldState, AliRtcEngine.AliRtcSubscribeState newState, int elapseSinceLastState, String
                                                     channel) {
        Log.d(TAG, "onAudioSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
    }


    /**
     * 相机流订阅情况变更回调
     *
     * @param uid      用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    @Override
    public void onVideoSubscribeStateChanged(String uid,
                                             AliRtcEngine.AliRtcSubscribeState oldState,
                                             AliRtcEngine.AliRtcSubscribeState newState,
                                             int elapseSinceLastState, String channel) {
        Log.d(TAG, "onVideoSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
    }


    /**
     * 大小流订阅情况变更回调
     *
     * @param uid           用户Id
     * @param oldStreamType 之前的订阅状态
     * @param newStreamType 当前的订阅状态
     */
    @Override
    public void onSubscribeStreamTypeChanged(String uid,
                                             AliRtcEngine.AliRtcVideoStreamType oldStreamType,
                                             AliRtcEngine.AliRtcVideoStreamType newStreamType,
                                             int elapseSinceLastState, String channel) {
        Log.d(TAG, "onSubscribeStreamTypeChanged: uid: " + uid + " oldState" + oldStreamType + " newState: " + newStreamType);
    }

    /**
     * 屏幕分享流订阅情况变更回调
     *
     * @param uid      用户Id
     * @param oldState 之前的订阅状态
     * @param newState 当前的订阅状态
     */
    @Override
    public void onScreenShareSubscribeStateChanged(String uid,
                                                   AliRtcEngine.AliRtcSubscribeState oldState,
                                                   AliRtcEngine.AliRtcSubscribeState newState,
                                                   int elapseSinceLastState, String channel) {
        Log.d(TAG, "onScreenShareSubscribeStateChanged: uid: " + uid + " oldState" + oldState + " newState: " + newState);
    }

    @Override
    public void onUserVideoMuted(final String userId, final boolean mute) {
        Log.d(TAG, "onUserVideoMuted: uid: " + userId + " mute" + mute);
        AliRtcRemoteUserInfo userInfo = AliRtcInteractiveEngine.sharedInstance().getRemoteSeatUserInfo(userId);
        if (userInfo != null && userInfo.getDisplayName().contains("_老师")) {
            mTeacherCameraIv.setSelected(mute);
            mCameraContainer.setVisibility(mute ? View.GONE : View.VISIBLE);

        } else {
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(userId);
            if (remoteUserInfo != null) {
                remoteUserInfo.setHasVideo(mute);
                mStudentListAdapter.updateData(remoteUserInfo);
            }
        }
    }

    @Override
    public void onUserAudioMuted(final String userId, final boolean mute) {
        Log.d(TAG, "onUserAudioMuted: uid: " + userId + " mute" + mute);
        AliRtcRemoteUserInfo userInfo = AliRtcInteractiveEngine.sharedInstance().getRemoteSeatUserInfo(userId);
        if (userInfo != null && userInfo.getDisplayName().contains("_老师")) {
            mTeacherMicIv.setSelected(mute);
        } else {
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(userId);
            if (remoteUserInfo != null) {
                remoteUserInfo.setHasAudio(mute);
                mStudentListAdapter.updateData(remoteUserInfo);
            }
        }
    }

    @Override
    public void onActiveSpeaker(String speakers) {
        mSpeakerUsersTv.setVisibility(TextUtils.isEmpty(speakers) ? View.GONE : View.VISIBLE);
        mSpeakerUsersTv.setText(speakers);
    }

    /**
     * 网络状态回调
     *
     * @param aliRtcNetworkQuality1 下行网络质量
     * @param aliRtcNetworkQuality  上行网络质量
     * @param userId                String  用户ID
     */
    @Override
    public void onNetworkQualityChanged(String userId, AliRtcEngine.AliRtcNetworkQuality
            aliRtcNetworkQuality, AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality1) {

    }

    /**
     * 用户角色发生改变时回调
     *
     * @param oldRole
     * @param newRole
     */
    @Override
    public void onUpdateRoleNotify(AliRtcEngine.AliRTCSdkClientRole
                                           oldRole, AliRtcEngine.AliRTCSdkClientRole newRole) {
        //从观众角色切换到互动角色
        if (newRole == AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkInteractive && oldRole == AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkLive) {
            //连麦第二步：更新本地预览到远端用户列表
            localGroupVisible(View.VISIBLE, true);
            RemoteUserInfo localRemoteUserInfo = AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo();
            localRemoteUserInfo.setHasVideo(mMuteLocalCamera)
                    .setHandUp(true)
                    .setHasAudio(mMuteLocalMic);
            mStudentListAdapter.addData(localRemoteUserInfo);

        } else if (newRole == AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkLive && oldRole == AliRtcEngine.AliRTCSdkClientRole.AliRTCSdkInteractive) {
            //下麦第二步：移除远端用户列表的本地预览
            localGroupVisible(View.GONE, false);
            mIvApplyCall.setBackground(ContextCompat.getDrawable(AlivcClassRoomActivity.this, R.drawable.alivc_biginteractiveclass_self_apply_call_normal));
            RemoteUserInfo remoteUserInfo = mStudentListAdapter.getRemoteUserInfo(getLocalUserId());
            if (remoteUserInfo != null) {
                mStudentListAdapter.remoteData(remoteUserInfo);
            }
        }
    }

    private void localGroupVisible(int visible, boolean online) {
        if (mLayoutMuteCamera != null && mLayoutMuteMic != null) {
            mLayoutMuteCamera.setVisibility(visible);
            mLayoutMuteMic.setVisibility(visible);
        }
        if (mTvApplyCall != null) {
            mTvApplyCall.setText(online ? getResources().getString(R.string.alivc_biginteractive_end_seat_str) :
                    getResources().getString(R.string.alivc_biginteractive_apply_seat_str));
        }
    }

    private String getLocalUserId() {
        return AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo().getUserId();
    }

    private void updateRemoteDisplay(final String uid, final AliRtcEngine.AliRtcAudioTrack at,
                                     final AliRtcEngine.AliRtcVideoTrack vt) {
        Log.i(TAG, " updateRemoteDisplay AliRtcAudioTrack " + at + " AliRtcVideoTrack " + vt);
        AliRtcRemoteUserInfo aliRtcRemoteUserInfo = AliRtcInteractiveEngine.sharedInstance().getRemoteSeatUserInfo(uid);
        if (aliRtcRemoteUserInfo != null) {
            //change
            AliRtcEngine.AliRtcVideoCanvas cameraCanvas = aliRtcRemoteUserInfo.getCameraCanvas();
            AliRtcEngine.AliRtcVideoCanvas screenCanvas = aliRtcRemoteUserInfo.getScreenCanvas();
            //视频情况
            if (vt == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackNo) {
                //没有视频流
                return;
            } else if (vt == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera) {
                //相机流
                screenCanvas = null;
                cameraCanvas = createCanvasIfNull(cameraCanvas);
                AliRtcInteractiveEngine.sharedInstance().setRemoteViewConfig(cameraCanvas, uid, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera);
            } else if (vt == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackScreen) {
                //屏幕流
                cameraCanvas = null;
                screenCanvas = createCanvasIfNull(screenCanvas);
                AliRtcInteractiveEngine.sharedInstance().setRemoteViewConfig(screenCanvas, uid, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackScreen);
            } else if (vt == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackBoth) {
                //多流
                cameraCanvas = createCanvasIfNull(cameraCanvas);
                AliRtcInteractiveEngine.sharedInstance().setRemoteViewConfig(cameraCanvas, uid, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera);
                screenCanvas = createCanvasIfNull(screenCanvas);
                AliRtcInteractiveEngine.sharedInstance().setRemoteViewConfig(screenCanvas, uid, AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackScreen);

            }
            //音频流
            if (at == AliRtcEngine.AliRtcAudioTrack.AliRtcAudioTrackNo) {

            }
            RemoteUserInfo remoteUserInfo = convert2RemoteUserInfo(aliRtcRemoteUserInfo, screenCanvas, cameraCanvas);
            remoteUserInfo.setVideoTrack(vt);
            if (remoteUserInfo.getDisplayName().contains("_老师")) {
                //更新老师流显示
                updateTeacherBigViewDisplay(remoteUserInfo);
            } else {
                //更新学生列表
                mStudentListAdapter.updateData(remoteUserInfo);
            }
        } else {
            // remote user exit room
            Log.e(TAG, "updateRemoteDisplay remoteUserInfo = null, uid = " + uid);
        }
    }

    /**
     * 添加用户数据
     *
     * @param uid 用户id
     */
    private void addRemoteUser(final String uid) {
        AliRtcRemoteUserInfo remoteUserInfo = AliRtcInteractiveEngine.sharedInstance().getRemoteSeatUserInfo(uid);
        if (remoteUserInfo != null && !remoteUserInfo.getDisplayName().contains("_老师")) {
            mStudentListAdapter.addData(convert2RemoteUserInfo(remoteUserInfo, null, null));
        } else {
            Log.e(TAG, "addRemoteUser remoteUserInfo = null, uid = " + uid);
        }

    }

    private void updateTeacherBigViewDisplay(RemoteUserInfo remoteUserInfo) {
        if (remoteUserInfo == null) {
            return;
        }
        mTeacherUid = remoteUserInfo.getUserId();
        //处理屏幕流
        if (remoteUserInfo.getScreenPreview() != null && remoteUserInfo.getCameraPreview() != null) {
            //如果老的surfaceView还在之前的viewTree中，需要先移除
            ViewParent oldScreenParent = remoteUserInfo.getScreenPreview().getParent();
            if (oldScreenParent instanceof FrameLayout)
                ((FrameLayout) oldScreenParent).removeAllViews();
            if (remoteUserInfo.getScreenPreview() instanceof SurfaceView) {
                mScreenContainer.removeAllViews();
                mScreenContainer.addView(remoteUserInfo.getScreenPreview(), new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
            }

            ViewParent oldCameraParent = remoteUserInfo.getCameraPreview().getParent();
            if (oldCameraParent instanceof FrameLayout)
                ((FrameLayout) oldCameraParent).removeAllViews();
            if (remoteUserInfo.getCameraPreview() instanceof SurfaceView) {
                mCameraContainer.removeAllViews();
                mCameraContainer.addView(remoteUserInfo.getCameraPreview());
            }
        } else if (remoteUserInfo.getScreenPreview() != null && remoteUserInfo.getCameraPreview() == null) {
            ViewParent oldParent = remoteUserInfo.getScreenPreview().getParent();
            if (oldParent instanceof FrameLayout)
                ((FrameLayout) oldParent).removeAllViews();
            if (remoteUserInfo.getScreenPreview() instanceof SurfaceView) {
                mScreenContainer.removeAllViews();
                mScreenContainer.addView(remoteUserInfo.getScreenPreview());
            }
            mCameraContainer.removeAllViews();

        } else if (remoteUserInfo.getScreenPreview() == null && remoteUserInfo.getCameraPreview() != null) {
            ViewParent oldParent = remoteUserInfo.getCameraPreview().getParent();
            if (oldParent instanceof FrameLayout)
                ((FrameLayout) oldParent).removeAllViews();
            if (remoteUserInfo.getCameraPreview() instanceof SurfaceView) {
                mScreenContainer.removeAllViews();
                mScreenContainer.addView(remoteUserInfo.getCameraPreview());
            }
            mCameraContainer.removeAllViews();
        } else if (remoteUserInfo.getScreenPreview() == null && remoteUserInfo.getCameraPreview() == null) {
            mCameraContainer.removeAllViews();
            mScreenContainer.removeAllViews();
        }
        mTeacherDisplayName.setText(remoteUserInfo.getDisplayName());
        mTeacherDisplayNameNotify.setText(String.format("%s%s", remoteUserInfo.getDisplayName(), " (教师)"));
    }

    private AliRtcEngine.AliRtcVideoCanvas createCanvasIfNull(AliRtcEngine.AliRtcVideoCanvas canvas) {
        if (canvas == null || canvas.view == null) {
            canvas = new AliRtcEngine.AliRtcVideoCanvas();
            SurfaceView view = AliRtcInteractiveEngine.sharedInstance().createRenderView(this);
            if (view != null) {
                canvas.view = view;
            }
        }
        return canvas;
    }

    private RemoteUserInfo convert2RemoteUserInfo(AliRtcRemoteUserInfo
                                                          remoteUserInfo, AliRtcEngine.AliRtcVideoCanvas screenCanvas, AliRtcEngine.AliRtcVideoCanvas
                                                          cameraCanvas) {
        RemoteUserInfo userInfo = mStudentListAdapter.getRemoteUserInfo(remoteUserInfo.getUserID());
        if (userInfo.isNewAddUser()) {
            // 新加入的远端用户：默认设置初始化配置的订阅
            userInfo.setSubScribedAudio(remoteUserInfo.isSubscribedAudio())
                    .setSubScribedAllVideo(remoteUserInfo.isSubscribedCameraMaster() & remoteUserInfo.isSubscribedCameraSlave() & remoteUserInfo.isSubscribedScreenSharing())
                    .setSubScribedCamera(remoteUserInfo.isSubscribedCameraMaster())
                    .setSubScribedCameraSlave(remoteUserInfo.isSubscribedCameraSlave())
                    .setSubScribedScreenSharing(remoteUserInfo.isSubscribedScreenSharing());
        }
        return userInfo.setUserId(remoteUserInfo.getUserID())
                .setDisplayName(remoteUserInfo.getDisplayName())
                .setMuteAudioPlaying(remoteUserInfo.isMuteAudioPlaying())
                .setLocal(false)
                .setScreenPreview(screenCanvas == null ? null : screenCanvas.view)
                .setCameraPreview(cameraCanvas == null ? null : cameraCanvas.view);
    }

    private boolean isTipDialogShow;

    /**
     * 体验时间结束
     */
    private void showTimeoutDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
                .setDes(getString(R.string.alivc_biginteractiveclass_string_experience_time_out_please_try_angin))
                .setButtonType(AlivcTipDialog.ONE_BUTTON)
                .setOneBtnStr(getString(R.string.alivc_biginteractiveclass_string_know))
                .setOneButtonClickListener(new AlivcTipDialog.OneButtonClickListener() {

                    @Override
                    public void onClicked() {
                        getChannelNum(new OnGroupMemberCallBack() {
                            @Override
                            public void onSuccess(int size) {
                                startToFeedback(size);
                            }
                        });
                    }
                })
                .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        isTipDialogShow = alivcTipDialog.isShowing();
        if (!isTipDialogShow) {
            alivcTipDialog.show();
        }
    }

    /**
     * 当rtc sdk报错时弹出
     */
    private void showRtcErrorDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
                .setTitle(getString(R.string.alivc_biginteractiveclass_string_title_dialog_tip))
                .setDes(getString(R.string.alivc_biginteractiveclass_string_error_rtc_normal))
                .setButtonType(AlivcTipDialog.ONE_BUTTON)
                .setOneBtnStr(getString(R.string.alivc_biginteractiveclass_string_confrim_btn))
                .setOneButtonClickListener(new AlivcTipDialog.OneButtonClickListener() {

                    @Override
                    public void onClicked() {
                        getChannelNum(new OnGroupMemberCallBack() {
                            @Override
                            public void onSuccess(int size) {
                                startToFeedback(size);
                            }
                        });
                    }
                })
                .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        if (!alivcTipDialog.isShowing()) {
            alivcTipDialog.show();
        }
    }

    /**
     * 二次确认是否下麦
     */
    private void showLeaveSeatDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
                .setDrawableTip(R.drawable.alivc_biginteractiveclass_important_warn)
                .setDes(getString(R.string.alivc_biginteractiveclass_string_hint_change_live))
                .setButtonType(AlivcTipDialog.TWO_BUTTON)
                .setCancelStr("取消")
                .setConfirmStr("确定")
                .setTwoButtonClickListener(new AlivcTipDialog.TwoButtonClickListener() {
                    @Override
                    public void onCancel() {

                    }

                    @Override
                    public void onConfirm() {
                        //下麦第一步：切换观众角色
                        AliRtcInteractiveEngine.sharedInstance().leaveSeat();
                    }
                })
                .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        alivcTipDialog.show();
    }

    /**
     * 适配部分机型点击音量按键控制的时通话音量
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_VOLUME_UP:
                if (mAudioManager != null) {
                    mAudioManager.adjustStreamVolume(AliRtcInteractiveEngine.sharedInstance().isActiveStudent() ? AudioManager.STREAM_MUSIC : AudioManager.STREAM_VOICE_CALL, AudioManager.ADJUST_RAISE, AudioManager.FLAG_SHOW_UI);
                }
                break;
            case KeyEvent.KEYCODE_VOLUME_DOWN:
                if (mAudioManager != null) {
                    mAudioManager.adjustStreamVolume(AliRtcInteractiveEngine.sharedInstance().isActiveStudent() ? AudioManager.STREAM_MUSIC : AudioManager.STREAM_VOICE_CALL, AudioManager.ADJUST_LOWER, AudioManager.FLAG_SHOW_UI);
                }
                break;
            default:
        }
        return super.onKeyDown(keyCode, event);
    }

    private void showToastInCenter(final String msg) {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            ToastUtils.showInCenter(AlivcClassRoomActivity.this, msg);
        } else {
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    ToastUtils.showInCenter(AlivcClassRoomActivity.this, msg);
                }
            });
        }
    }

    /**
     * @note 当老师离开教师时候，查询用户会少一人，手动加1
     */
    private void getChannelNum(final OnGroupMemberCallBack onGroupMemberCallBack) {
        final AtomicBoolean first = new AtomicBoolean(true);
        AliImInteractiveEngine.sharedInstance().listAllMembers(new AIMPubGroupListAllMemberListener() {
            @Override
            public void onLocal(ArrayList<AIMPubGroupMember> arrayList) {

            }

            @Override
            public void onRefresh(ArrayList<AIMPubGroupMember> arrayList) {
                if (first.get() & onGroupMemberCallBack != null) {
                    first.set(false);
                    onGroupMemberCallBack.onSuccess(arrayList.size());
                }
            }

            @Override
            public void onFailure(DPSError dpsError) {
            }
        });

    }

    private interface OnGroupMemberCallBack {
        void onSuccess(int size);
    }

    private void startToFeedback(int size) {
        try {
            FeedBackInfo feedBackInfo = new FeedBackInfo();
            if (mTeacherDisplayName != null) {
                feedBackInfo.setTeacherDisplayName(mTeacherDisplayName.getText().toString());
            }
            feedBackInfo.setStartTime(mJoinChannelTime);
            feedBackInfo.setEndTime(System.currentTimeMillis());
            feedBackInfo.setSeatNum(getMaxStudentsNumber());
            feedBackInfo.setOnlineNum(size);
            AlivcFeedbackActivity.start(AlivcClassRoomActivity.this, feedBackInfo);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            finish();
        }
        finish();
    }

    private int getMaxStudentsNumber() {
        if (mStudentListAdapter != null) {
            return mStudentListAdapter.getItemCount();
        }
        return 0;
    }
}
