package com.aliyun.rtc.rtcinteractiveclassplayer.ui;


import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.SystemClock;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.util.Log;
import android.util.Pair;
import android.view.KeyEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.alivc.rtc.AliRtcEngine;
import com.alivc.rtc.AliRtcRemoteUserInfo;
import com.alivc.rtc.device.utils.StringUtils;
import com.aliyun.rtc.rtcinteractiveclassplayer.R;
import com.aliyun.rtc.rtcinteractiveclassplayer.adapter.AutoItemDecoration;
import com.aliyun.rtc.rtcinteractiveclassplayer.adapter.BottomFunctionAdapter;
import com.aliyun.rtc.rtcinteractiveclassplayer.adapter.StudentListAdapter;
import com.aliyun.rtc.rtcinteractiveclassplayer.bean.AlivcVideoStreamInfo;
import com.aliyun.rtc.rtcinteractiveclassplayer.constant.Constant;
import com.aliyun.rtc.rtcinteractiveclassplayer.rtc.RTCInteractiveClassDelegate;
import com.aliyun.rtc.rtcinteractiveclassplayer.rtc.RTCInteractiveClassImpl;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ClipboardUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ScreenUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.UIHandlerUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.view.AlivcTipDialog;
import com.aliyun.rtc.rtcinteractiveclassplayer.view.TitleBar;
import com.aliyun.svideo.common.utils.ThreadUtils;

import org.webrtc.sdk.SophonSurfaceView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class AlivcClassRoomActivity extends AppCompatActivity implements RTCInteractiveClassDelegate, TitleBar.BackBtnListener, TitleBar.MenuBtnListener, BottomFunctionAdapter.FunctionCheckedListener, View.OnClickListener, StudentListAdapter.ItemClickListener {


    private static final String TAG = AlivcClassRoomActivity.class.getSimpleName();
    //横屏时隐藏页面上的view的倒计时时间
    private static final int HIDE_VIEW_TIME = 15;
    private String mChannelId;
    private FrameLayout mContainerView;
    //private AliUserInfoResponse.AliUserInfo mRtcAuthInfo;
    private RecyclerView mRcyFunctionViews;
    private ArrayList<Pair<String, Integer>> mFunctions;
    private boolean mMuteLocalMic, mMuteLocalCamera;
    private String mStudentName;
    protected String mRemoteUid = "";
    protected String mTeacherUid = "";
    private RecyclerView mRcyStudentList;
    private ArrayList<AlivcVideoStreamInfo> mAlivcVideoStreamInfos;
    private StudentListAdapter mStudentListAdapter;
    private ImageButton mIbBack;
    private TextView mTvChannelName;
    private CountDownRunnable mCountDownRunnable;
    private AlivcVideoStreamInfo mDisplayVideoStreamInfo, mRemoteVideoStreamInfo;
    private BottomFunctionAdapter mAdapter;
    private ImageView mIvClassNotBegin;
    private SurfaceView mPlaySurfaceview;
    private boolean isStudentRole = true;
    private ImageButton mIbShare;
    private AudioManager mAudioManager;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (ScreenUtil.isLandscapeLayout(this)) {
            ScreenUtil.hideStatusBar(this);
        }
        setContentView(R.layout.alivc_big_interactive_class_activity_rtc_chat);
        getDataForIntent();
        initView();
        newStudentLogin();

        mAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
    }


    /**
     * 学生身份登录
     */
    public void newStudentLogin() {
        mIvClassNotBegin.setVisibility(View.GONE);
        isStudentRole = true;
        RTCInteractiveClassImpl.sharedInstance().init();
        RTCInteractiveClassImpl.sharedInstance().setDelegate(this);
        RTCInteractiveClassImpl.sharedInstance().login(mChannelId, mStudentName);
    }



    /**
     * 将本地或远端预览信息添加到学生列表，并刷新显示
     * @param s
     * @param aliRtcVideoTrack
     * @param isLocalStream
     * @param isTeacherCamera  是否是老师的相机流
     */
    private void addVideoStreamInfo(String s, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack, boolean isLocalStream,boolean isTeacherCamera) {
        final AlivcVideoStreamInfo alivcVideoStreamInfo = createAlivcVideoStreamInfo(s, aliRtcVideoTrack, isLocalStream,isTeacherCamera);
        //如果当前学生列表已经存在添加的数据，那就是流的类型变了，刷新预览
        if (!mAlivcVideoStreamInfos.contains(alivcVideoStreamInfo)) {
            mAlivcVideoStreamInfos.add(isLocalStream ? 0 : mAlivcVideoStreamInfos.size(), alivcVideoStreamInfo);
        } else {
            if(isTeacherCamera){
                //单独添加老师的相机流
                mAlivcVideoStreamInfos.add(isLocalStream ? 0 : mAlivcVideoStreamInfos.size(), alivcVideoStreamInfo);
            } else {
                mAlivcVideoStreamInfos.set(mAlivcVideoStreamInfos.indexOf(alivcVideoStreamInfo), alivcVideoStreamInfo);
            }
        }
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                mStudentListAdapter.notifyDataSetChanged();
            }
        });
    }

    /**，本地预览才需要mmuteLocalCamera数据
     * @param s 用户id
     * @param aliRtcVideoTrack 视频流类型
     * @param isLocalStream 是否为本地预览
     * @param isTeacherCamera 是否为老师的相机流
     * @return 封装的视频流信息
     */
    private AlivcVideoStreamInfo createAlivcVideoStreamInfo(String s, AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack, boolean isLocalStream,boolean isTeacherCamera) {
        AliRtcRemoteUserInfo userInfo = RTCInteractiveClassImpl.sharedInstance().getUserInfo(s);
        AlivcVideoStreamInfo streamInfo = new AlivcVideoStreamInfo.Builder()
                .setUserId(s)
                .setAliRtcVideoTrack(aliRtcVideoTrack)
                .setUserName(userInfo != null ? userInfo.getDisplayName() : "")
                .setLocalStream(isLocalStream)
                .setTeacher(isTeacherCamera)
                .setMuteLocalCamera(mMuteLocalCamera)
                .setMuteLocalMic(mMuteLocalMic)
                .setAliVideoCanvas(new AliRtcEngine.AliVideoCanvas())
                .build();
        if(isLocalStream){
            streamInfo.setUserName("我");
        }
        return streamInfo;

    }

    private void initView() {
        mContainerView = findViewById(R.id.alivc_big_interactive_class_fl_Container);
        mRcyFunctionViews = findViewById(R.id.alivc_big_interactive_class_rcy_function_views);
        mRcyStudentList = findViewById(R.id.alivc_big_interactive_class_rcy_student_list);
        mIbBack = findViewById(R.id.alivc_big_interactive_class_landscape_ib_back);
        mIbShare = findViewById(R.id.alivc_big_interactive_class_landscape_ib_share);
        mTvChannelName = findViewById(R.id.alivc_big_interactive_class_tv_landscape_channel_name);
        mIvClassNotBegin = findViewById(R.id.alivc_big_interactive_class_iv_icon_class_not_begin);
        mPlaySurfaceview = findViewById(R.id.alivc_big_interactive_class_surface_play);
        RelativeLayout rlContent = findViewById(R.id.alivc_big_interactive_class_rl_content_class_room);
        //隐藏播放器的页面
        mContainerView.setVisibility(View.VISIBLE);
        mPlaySurfaceview.setVisibility(View.GONE);

        initFunctionViews();
        initStudentList();

        if (mIbBack != null) {
            mIbBack.setOnClickListener(this);
        }

        if (mTvChannelName != null) {
            mTvChannelName.setText(String.format(getString(R.string.alivc_biginteractiveclass_string_title_channel_id), mChannelId));
        }

        if (mIbShare != null) {
            mIbShare.setVisibility(View.GONE);
            //mIbShare.setOnClickListener(this);
        }
        rlContent.setOnClickListener(this);
        mStudentListAdapter.setItemClickListener(this);
    }

    @Override
    protected void onStart() {
        super.onStart();
        //开启计时线程，一段时间未操作屏幕就隐藏按钮
        if (mCountDownRunnable == null) {
            mCountDownRunnable = new CountDownRunnable();
            ThreadUtils.runOnSubThread(mCountDownRunnable);
        }
        //RTCInteractiveClassImpl.sharedInstance().startPublish();
    }


    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    /**
     * 初始化学生列表
     */
    private void initStudentList() {
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        linearLayoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        mRcyStudentList.setItemViewCacheSize(20);
        mRcyStudentList.setLayoutManager(linearLayoutManager);
        if (mAlivcVideoStreamInfos == null) {
            mAlivcVideoStreamInfos = new ArrayList<>();
        }
        mStudentListAdapter = new StudentListAdapter(this, mAlivcVideoStreamInfos);
        mRcyStudentList.setAdapter(mStudentListAdapter);
    }

    /**
     * 初始化底部功能view
     */
    private void initFunctionViews() {
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        linearLayoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        mRcyFunctionViews.setLayoutManager(linearLayoutManager);
        mFunctions = getFunctions();
        mAdapter = new BottomFunctionAdapter(this, mFunctions);
        mAdapter.setListener(this);
        mRcyFunctionViews.addItemDecoration(new AutoItemDecoration(mFunctions.size()));
        mRcyFunctionViews.setAdapter(mAdapter);
    }

    /**
     * 从资源文件中获取底部功能按钮列表
     * @return 图片资源文件和名称集合
     */
    private ArrayList<Pair<String, Integer>> getFunctions() {
        String[] names;
        if (!ScreenUtil.isLandscapeLayout(this)) {
            names = getResources().getStringArray(R.array.functions_portrait);
        } else {
            names = getResources().getStringArray(R.array.functions_landscape);
        }
        ArrayList<Pair<String, Integer>> bottomBtns = new ArrayList<>();
        for (int i = 0; i < names.length; i++) {
            bottomBtns.add(new Pair<>(names[i], getBottombtnResId(i)));
        }
        return bottomBtns;
    }

    private Integer getBottombtnResId(int i) {
        int resId = -1;
        switch (i) {
        case 0:
            resId = R.drawable.alivc_biginteractiveclass_mute_mic;
            break;
        case 1:
            resId = R.drawable.alivc_biginteractiveclass_mute_camera;
            break;
        case 2:
            resId = R.drawable.alivc_biginteractiveclass_conn_mic;
            break;
        case 3:
            resId = R.drawable.alivc_biginteractiveclass_rotate_camera;
            break;
        case 4:
            if (getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
                resId = R.drawable.alivc_biginteractiveclass_leavel_channel;
            } else {
                resId = R.drawable.alivc_biginteractiveclass_user_list;
            }
            break;
        default:
        }
        return resId;
    }

    /**
     * 获取intent传过来的用户信息
     */
    private void getDataForIntent() {
        Intent intent = getIntent();
        if (intent != null) {
            Bundle b = intent.getExtras();
            if (b != null) {
                //频道号
                mChannelId = b.getString("channel");
                //用户信息
                //mRtcAuthInfo = (AliUserInfoResponse.AliUserInfo) b.getSerializable("rtcAuthInfo");
                //学生姓名
                mStudentName = b.getString("studentName");
            }
        }
    }

    /**
     * 开始主屏预览，复用sophonsurfaceview，不需要重复创建
     */
    private void startPreview() {
        if (mRemoteVideoStreamInfo == null) {
            return;
        }
        AliRtcEngine.AliVideoCanvas aliVideoCanvas = mRemoteVideoStreamInfo.getAliVideoCanvas();
        if (aliVideoCanvas.view == null) {
            SophonSurfaceView sophonSurfaceView = new SophonSurfaceView(this);
            sophonSurfaceView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
            // true 在最顶层，会遮挡一切view
            sophonSurfaceView.setZOrderOnTop(false);
            //true 如已绘制SurfaceView则在surfaceView上一层绘制。
            sophonSurfaceView.setZOrderMediaOverlay(false);
            aliVideoCanvas.view = sophonSurfaceView;
            //设置渲染模式,一共有四种
            aliVideoCanvas.renderMode = AliRtcEngine.AliRtcRenderMode.AliRtcRenderModeFill;
        }
        //添加LocalView
        mContainerView.removeAllViews();
        mContainerView.addView(aliVideoCanvas.view);
        AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack = mRemoteVideoStreamInfo.getAliRtcVideoTrack();
        aliRtcVideoTrack = aliRtcVideoTrack == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackBoth ? AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackScreen : aliRtcVideoTrack;
        RTCInteractiveClassImpl.sharedInstance().setRemoteViewConfig(aliVideoCanvas, mRemoteUid, aliRtcVideoTrack);
    }

    @Override
    public void onBackBtnClicked() {
        onBackPressed();
    }

    /**
     * 展示退出dialog
     */
    private void showExitDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
        .setTitle(getString(R.string.alivc_biginteractiveclass_string_leave_channel))
        .setDes(getString(R.string.alivc_biginteractiveclass_string_hint_leave_channel))
        .setButtonType(AlivcTipDialog.TWO_BUTTON)
        .setCancelStr(getString(R.string.alivc_biginteractiveclass_string_confirm_leave_channel))
        .setConfirmStr(getString(R.string.alivc_biginteractiveclass_string_continue_to_experience))
        .setTwoButtonClickListener(new AlivcTipDialog.TwoButtonClickListener() {
            @Override
            public void onCancel() {
                //1.参照主播流程停⽌拉流
                RTCInteractiveClassImpl.sharedInstance().logout();
                finish();
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
        RTCInteractiveClassImpl.sharedInstance().logout();
        RTCInteractiveClassImpl.sharedInstance().destorySharedInstance();
        mCountDownRunnable.quick();
        Log.i(TAG, "onDestroy: ");
    }

    /**
     * 底部功能按钮点击事件回调
     */
    @Override
    public boolean onFunctionChecked(int position) {
        boolean b = true;
        switch (position) {
        //静音
        case 0:
            if (!isStudentRole) {
                mMuteLocalMic = !mMuteLocalMic;
                RTCInteractiveClassImpl.sharedInstance().muteLocalMic(mMuteLocalMic);
                //刷新列表的静音图标
                for(AlivcVideoStreamInfo info:mAlivcVideoStreamInfos){
                    if(info.getUserId().equals(RTCInteractiveClassImpl.sharedInstance().getUserId())){
                        info.setMuteMic(mMuteLocalMic);
                        mStudentListAdapter.notifyItemChanged(mAlivcVideoStreamInfos.indexOf(info),1);
                        break;
                    }
                }
            } else {
                b = false;
                ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(R.string.alivc_biginteractiveclass_string_need_set_teacher_role));
            }

            break;
        //摄像头
        case 1:
            if (!isStudentRole) {
                mMuteLocalCamera = !mMuteLocalCamera;
                RTCInteractiveClassImpl.sharedInstance().muteLocalCamera(mMuteLocalCamera);
                //刷新UI
                if (mAlivcVideoStreamInfos == null || mAlivcVideoStreamInfos.size() == 0) {
                    break;
                }
                AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                .setUserId(RTCInteractiveClassImpl.sharedInstance().getUserId())
                .build();
                int index = mAlivcVideoStreamInfos.indexOf(build);
                if (index != -1) {
                    mAlivcVideoStreamInfos.get(index).setMuteLocalCamera(mMuteLocalCamera);
                    mAlivcVideoStreamInfos.get(index).setMuteCamera(mMuteLocalCamera);
                    mStudentListAdapter.notifyItemChanged(index);
                } else if (StringUtils.equals(mDisplayVideoStreamInfo.getUserId(), RTCInteractiveClassImpl.sharedInstance().getUserId())) {
                    //刷新大屏
                    if (!mMuteLocalCamera) {
                        RTCInteractiveClassImpl.sharedInstance().startPreview();
                    } else {
                        RTCInteractiveClassImpl.sharedInstance().stopPreview();
                    }
                    boolean isExist = mContainerView.getChildCount() > 0 && mContainerView.getChildAt(0) instanceof SurfaceView;
                    if (isExist) {
                        mContainerView.getChildAt(0).setBackgroundColor(!mMuteLocalCamera ? Color.TRANSPARENT : Color.BLACK);
                    }
                }
            } else {
                b = false;
                ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(R.string.alivc_biginteractiveclass_string_need_set_teacher_role));
            }
            break;
        //连麦
        case 2:
            toogleClientRole();
            break;
        //翻转
        case 3:
            if (!isStudentRole) {
                RTCInteractiveClassImpl.sharedInstance().switchCamera();
            } else {
                b = false;
                ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(R.string.alivc_biginteractiveclass_string_need_set_teacher_role));
            }
            break;
        //成员列表
        case 4:
            //全屏模式为退出课程
            if (getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
                showExitDialog();
            }
            break;
        default:
        }
        return b;
    }

    //清除本地视频流的摄像头、静音属性
    private void clearLocalVideoStreamInfo() {
        mMuteLocalMic = mMuteLocalCamera = false;
        //刷新底部按钮
        mAdapter.initBtnStatus();
    }

    /**
     * 切换学生下上麦状态
     */
    private void toogleClientRole() {
        if (!isStudentRole) {

            //清除底部按钮状态
            clearLocalVideoStreamInfo();
            isStudentRole = true;
            //下麦第一步：停止推流
            RTCInteractiveClassImpl.sharedInstance().leavelSeat();
        } else {
            //  连麦
            isStudentRole = false;
            //连麦第一步：切换为互动角色
            RTCInteractiveClassImpl.sharedInstance().enterSeat();
        }
    }


    private void removeStudentList(final int index) {
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                AlivcVideoStreamInfo remove = mAlivcVideoStreamInfos.remove(index);
                if (remove != null) {
                    mStudentListAdapter.detachedPreview(remove);
                    mStudentListAdapter.notifyItemRemoved(index);
                    mStudentListAdapter.notifyItemRangeChanged(index,mAlivcVideoStreamInfos.size());
                }
            }
        });
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        if (id == R.id.alivc_big_interactive_class_landscape_ib_back) {
            showExitDialog();
        } else if (id == R.id.alivc_big_interactive_class_rl_content_class_room) {
            if (mCountDownRunnable.mCountdown >= 15) {
                showLandscapeLayoutView();
                mCountDownRunnable.resetCount();
            } else {
                hideLandscapeLayoutView();
                mCountDownRunnable.setCount(HIDE_VIEW_TIME);
            }
        } else if (id == R.id.alivc_big_interactive_class_landscape_ib_share) {
            boolean copy = ClipboardUtil.copy(AlivcClassRoomActivity.this, Constant.getWebPlayUrl(mChannelId));
            ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(copy ? R.string.alivc_biginteractiveclass_string_copy_success : R.string.alivc_biginteractiveclass_string_copy_faild));
        }
    }

    /**
     * 控制横屏时，底部功能按钮和上方的title
     */
    private void showLandscapeLayoutView() {
        if (mIbBack != null) {
            mIbBack.setVisibility(View.VISIBLE);
        }
        if (mTvChannelName != null) {
            mTvChannelName.setVisibility(View.VISIBLE);
        }
        //if (mIbShare != null) {
        //    mIbShare.setVisibility(View.VISIBLE);
        //}
        mRcyFunctionViews.setVisibility(View.VISIBLE);
    }

    /**
     * 学生列表的点击事件
     */
    @Override
    public void onItemClicked(final int position) {
        if (position >= mAlivcVideoStreamInfos.size() || position < 0) {
            return;
        }
        AlivcVideoStreamInfo alivcVideoStreamInfo = mAlivcVideoStreamInfos.get(position);
        //将正在显示的id设置给小屏
        if (mDisplayVideoStreamInfo != null) {
            mAlivcVideoStreamInfos.set(position, mDisplayVideoStreamInfo);
            //小屏切换到小流
            ThreadUtils.runOnSubThread(new Runnable() {
                @Override
                public void run() {
                    RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(mAlivcVideoStreamInfos.get(position).getUserId(), false, true);
                }
            });
            mDisplayVideoStreamInfo = alivcVideoStreamInfo;
            mStudentListAdapter.notifyItemChanged(position);
        } else {
            mAlivcVideoStreamInfos.remove(position);
            mDisplayVideoStreamInfo = alivcVideoStreamInfo;
            mStudentListAdapter.notifyItemRemoved(position);
            mStudentListAdapter.notifyItemRangeChanged(position,mAlivcVideoStreamInfos.size());
        }
        //刷新大屏
        reflushContainerView(alivcVideoStreamInfo);

    }

    /**
     * 刷新主屏，切换两个流展示的spoonsurface即可，不需要重复预览
     * @param alivcVideoStreamInfo 流信息
     */
    private void reflushContainerView(final AlivcVideoStreamInfo alivcVideoStreamInfo) {
        mDisplayVideoStreamInfo = alivcVideoStreamInfo;
        mRemoteUid = mDisplayVideoStreamInfo.getUserId();
        if(alivcVideoStreamInfo != null){
            //主屏切换到大流
            ThreadUtils.runOnSubThread(new Runnable() {
                @Override
                public void run() {
                    RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(alivcVideoStreamInfo.getUserId(), true, true);
                }
            });
            AliRtcEngine.AliVideoCanvas aliVideoCanvas = alivcVideoStreamInfo.getAliVideoCanvas();
            if (aliVideoCanvas != null && aliVideoCanvas.view != null) {
                // true 在最顶层，会遮挡一切view
                aliVideoCanvas.view.setZOrderOnTop(false);
                //true 如已绘制SurfaceView则在surfaceView上一层绘制。
                aliVideoCanvas.view.setZOrderMediaOverlay(false);
                mContainerView.removeAllViews();
                if(aliVideoCanvas.view != null && ((ViewGroup) aliVideoCanvas.view.getParent()) != null){
                    ((ViewGroup) aliVideoCanvas.view.getParent()).removeAllViews();
                }
                mContainerView.addView(aliVideoCanvas.view);
            }
        } else {
            mContainerView.removeAllViews();
        }
    }

    /**
     * 用户上麦结果通知
     * @param result 0为成功 反之失败
     */
    @Override
    public void onEnterSeatResult(int result) {
        if(result == 0){
            //推流成功，将本地画面添加到小屏
            addVideoStreamInfo(RTCInteractiveClassImpl.sharedInstance().getUserId(), AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera, true,false);
        }
    }

    /**
     * 用户下麦结果通知
     * @param result 0为成功 反之失败
     */
    @Override
    public void onLeaveSeatResult(int result) {
        if(result == 0){
            //下麦第二步：停止推流后切换为观众角色
            RTCInteractiveClassImpl.sharedInstance().setClientRole(AliRtcEngine.AliRTCSDK_Client_Role.AliRTCSDK_live);
            //删除本地的预览画面
            if(mDisplayVideoStreamInfo != null && StringUtils.equals(mDisplayVideoStreamInfo.getUserId(),RTCInteractiveClassImpl.sharedInstance().getUserId())){
                if(!mAlivcVideoStreamInfos.isEmpty() && mAlivcVideoStreamInfos.size() > 1){
                    onItemClicked(0);
                } else {
                    reflushContainerView(null);
                }
            }
            AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                    .setUserId(RTCInteractiveClassImpl.sharedInstance().getUserId())
                    .build();
            int index = mAlivcVideoStreamInfos.indexOf(build);
            if(index != -1){
                removeStudentList(index);
            }
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
    public void onRoomDestroy(int i) {
        Log.i(TAG, "onBye: " + i);
        //频道关闭，体验时间结束
        if (i == 2) {
            UIHandlerUtil.getInstance().postRunnable(new ShowTimeOutDialogRunnable());
        } else {
            finish();
        }
    }

    /**
     *  当提示下列三个错误时需要重新创建实例
     * @param error 错误码
     */
    @Override
    public void onSDKError( int error) {
        showRtcErrorDialog(error);
    }

    /**
     *
     * @param result 加入房间的结果码，0为成功，反之失败
     */
    @Override
    public void onJoinChannelResult(int result) {
        if (result != 0) {
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    mAdapter.initAllBtnStatus();
                    ToastUtils.showInCenter(AlivcClassRoomActivity.this, getString(R.string.alivc_biginteractiveclass_string_hint_join_room_faild));
                }
            });
        }
    }


    /**
     * 远端用户上线通知
     *
     * @param userId  userid
     */
    @Override
    public void onRemoteUserOnLineNotify( String userId) {

    }

    /**
     * 远端用户下线通知
     * @param userId  userid
     */
    @Override
    public void onRemoteUserOffLineNotify(String userId) {
        if(StringUtils.equals(mTeacherUid,userId)){
            ToastUtils.showInCenter(AlivcClassRoomActivity.this,getString(R.string.alivc_biginteractiveclass_string_teacher_is_leavel_room));
        }
        if (mAlivcVideoStreamInfos == null) {
            return;
        }
        //主屏的用户退出了
        if (mDisplayVideoStreamInfo != null && StringUtils.equals(userId, mDisplayVideoStreamInfo.getUserId())) {
            AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                    .setUserId(RTCInteractiveClassImpl.sharedInstance().getUserId())
                    .build();
            int index = mAlivcVideoStreamInfos.indexOf(build);
            if (index == -1) {
                UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                    @Override
                    public void run() {
                        reflushContainerView(null);
                    }
                });
                return;
            }
            //大屏显示小屏第一个用户
            final AlivcVideoStreamInfo alivcVideoStreamInfo = mAlivcVideoStreamInfos.get(index);
            //小屏删除第一个试图
            //移除成功刷新页面
            removeStudentList(index);
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    reflushContainerView(alivcVideoStreamInfo);
                }
            });
            return;
        }

        AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                .setUserId(userId)
                .build();
        int index = mAlivcVideoStreamInfos.indexOf(build);
        //移除成功刷新页面
        if (index != -1) {
            removeStudentList(index);
        }


    }


    @Override
    public void onLeaveChannelResult(int result) {

    }


    /**
     * 远端用户发布音视频流变化通知
     *
     * @param uid                userid
     * @param aliRtcAudioTrack 音频流
     * @param aliRtcVideoTrack 相机流
     */
    @Override
    public void onRemoteTrackAvailableNotify(final String uid, AliRtcEngine.AliRtcAudioTrack aliRtcAudioTrack, final AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack) {
        //无流的时候不需要处理
        if (aliRtcVideoTrack == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackNo || aliRtcAudioTrack == AliRtcEngine.AliRtcAudioTrack.AliRtcAudioTrackNo) {
            return;
        }
        AliRtcRemoteUserInfo info = RTCInteractiveClassImpl.sharedInstance().getUserInfo(uid);
        if(info != null && info.getDisplayName().contains("_老师")){
            mTeacherUid = uid;
        }
        if (((TextUtils.isEmpty(mRemoteUid) || mDisplayVideoStreamInfo == null) && StringUtils.equals(uid, mTeacherUid)) || (mRemoteUid.equals(uid) && StringUtils.equals(uid, mDisplayVideoStreamInfo.getUserId()))) {
            mRemoteUid = uid;
            RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(uid, true, true);
            mRemoteVideoStreamInfo = mDisplayVideoStreamInfo = createAlivcVideoStreamInfo(uid, aliRtcVideoTrack, false,false);
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    startPreview();
                }
            });
        } else if (!StringUtils.equals(mRemoteUid, uid) && !info.getDisplayName().contains("_老师")) {
            //列表添加学生
            RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(uid, false, true);
            addVideoStreamInfo(uid, aliRtcVideoTrack, false,false);
        }
        //老师推送屏幕流
        if(info.getDisplayName().contains("_老师") && aliRtcVideoTrack == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackBoth){
            //如果主屏幕不是老师，将老师添加的主屏幕，并删除列表中的老师画面
            if(!StringUtils.equals(mRemoteUid,uid)){
                AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                        .setUserId(mTeacherUid)
                        .build();
                if(mAlivcVideoStreamInfos.contains(build)){
                    mAlivcVideoStreamInfos.remove(build);
                }
                addVideoStreamInfo(mRemoteUid,mDisplayVideoStreamInfo.getAliRtcVideoTrack(),false,false);
                mRemoteUid = uid;
                RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(uid, true, true);
                mRemoteVideoStreamInfo = mDisplayVideoStreamInfo = createAlivcVideoStreamInfo(uid, aliRtcVideoTrack, false,false);
                UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                    @Override
                    public void run() {
                        startPreview();
                    }
                });
            }
            // 列表添加老师的相机流
            addVideoStreamInfo(uid, aliRtcVideoTrack, false,true);
        } else if(info.getDisplayName().contains("_老师") && aliRtcVideoTrack != AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackBoth){
            //老师关闭屏幕流
            //删除列表中的老师，把主屏的学生添加到列表中，然后在主屏添加老师画面
            AlivcVideoStreamInfo build = new AlivcVideoStreamInfo.Builder()
                    .setUserId(mTeacherUid)
                    .build();
            if(mAlivcVideoStreamInfos.contains(build)){
                mAlivcVideoStreamInfos.remove(build);
                mStudentListAdapter.notifyDataSetChanged();
            }
            if(mAlivcVideoStreamInfos.contains(build)){
                mAlivcVideoStreamInfos.remove(build);
                mStudentListAdapter.notifyDataSetChanged();
            }

            if(!StringUtils.equals(mRemoteUid,mTeacherUid)){
                addVideoStreamInfo(mRemoteUid,mDisplayVideoStreamInfo.getAliRtcVideoTrack(),false,false);
            }
            mRemoteUid = uid;
            RTCInteractiveClassImpl.sharedInstance().configRemoteCameraTrack(uid, true, true);
            mRemoteVideoStreamInfo = mDisplayVideoStreamInfo = createAlivcVideoStreamInfo(uid, aliRtcVideoTrack, false,false);
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    startPreview();
                }
            });
        }

    }


    /**
     *  流变化监听
     * @param userId 用户id
     * @param audioTrack 音频流
     * @param videoTrack 视频流
     */
    @Override
    public void onSubscribeChangedNotify(String userId, AliRtcEngine.AliRtcAudioTrack audioTrack, AliRtcEngine.AliRtcVideoTrack videoTrack) {
        Log.i(TAG, "onSubscribeChangedNotify: uid --> " + userId);
    }

    @Override
    public void onUserVideoMuted(String userId, boolean mute) {
        for(AlivcVideoStreamInfo info:mAlivcVideoStreamInfos){
            if(info.getUserId().equals(userId)){
                info.setMuteCamera(mute);
                mStudentListAdapter.notifyItemChanged(mAlivcVideoStreamInfos.indexOf(info),1);
                break;
            }
        }
    }

    @Override
    public void onUserAudioMuted(String userId, boolean mute) {
        for(AlivcVideoStreamInfo info:mAlivcVideoStreamInfos){
            if(info.getUserId().equals(userId)){
                info.setMuteMic(mute);
                mStudentListAdapter.notifyItemChanged(mAlivcVideoStreamInfos.indexOf(info),1);
                break;
            }
        }
    }

    /**
     * 网络状态回调
     *
     * @param aliRtcNetworkQuality1 下行网络质量
     * @param aliRtcNetworkQuality  上行网络质量
     * @param userId                String  用户ID
     */
    @Override
    public void onNetworkQualityChanged(String userId, AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality, AliRtcEngine.AliRtcNetworkQuality aliRtcNetworkQuality1) {

    }

    /**
     * 用户角色发生改变时回调
     * @param oldRole
     * @param newRole
     */
    @Override
    public void onUpdateRoleNotify(AliRtcEngine.AliRTCSDK_Client_Role oldRole, AliRtcEngine.AliRTCSDK_Client_Role newRole) {
        //从观众角色切换到互动角色
        if(newRole == AliRtcEngine.AliRTCSDK_Client_Role.AliRTCSDK_Interactive){
            //连麦第二步：切换成互动角色后开始推流
            RTCInteractiveClassImpl.sharedInstance().startPublish();
        }
    }

    /**
     * 计时线程，控制页面按钮的显示隐藏
     */
    private class CountDownRunnable implements Runnable {
        private int mCountdown = 0;
        private boolean startLoop = true;

        @Override
        public void run() {

            while (startLoop) {
                if (HIDE_VIEW_TIME - mCountdown == 0) {
                    hideLandscapeLayoutView();
                }
                SystemClock.sleep(1000);
                mCountdown++;
            }
        }

        private void resetCount() {
            mCountdown = 0;
        }

        private void quick() {
            startLoop = false;
        }

        public void setCount(int i) {
            mCountdown = i;
        }
    }

    private void hideLandscapeLayoutView() {
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                if (mIbBack != null) {
                    mIbBack.setVisibility(View.GONE);
                }
                if (mTvChannelName != null) {
                    mTvChannelName.setVisibility(View.GONE);
                }
                //if (mIbShare != null) {
                //    mIbShare.setVisibility(View.GONE);
                //}
                mRcyFunctionViews.setVisibility(View.GONE);
            }
        });
    }


    private class ShowTimeOutDialogRunnable implements Runnable {
        @Override
        public void run() {
            showTimeoutDialog();
        }
    }

    /**
     * 体验时间结束
     */
    private void showTimeoutDialog() {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
        .setTitle(getString(R.string.alivc_biginteractiveclass_string_experience_time_out))
        .setDes(getString(R.string.alivc_biginteractiveclass_string_experience_time_out_please_try_angin))
        .setButtonType(AlivcTipDialog.ONE_BUTTON)
        .setOneBtnStr(getString(R.string.alivc_biginteractiveclass_string_know))
        .setOneButtonClickListener(new AlivcTipDialog.OneButtonClickListener() {

            @Override
            public void onClicked() {
                finish();
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
     * 当rtc sdk报错时弹出
     *
     * @param error 错误码
     */
    private void showRtcErrorDialog(int error) {
        AlivcTipDialog alivcTipDialog = new AlivcTipDialog.Builder(AlivcClassRoomActivity.this)
        .setTitle(getString(R.string.alivc_biginteractiveclass_string_title_dialog_tip))
        .setDes(getString(R.string.alivc_biginteractiveclass_string_error_rtc_normal))
        .setButtonType(AlivcTipDialog.ONE_BUTTON)
        .setOneBtnStr(getString(R.string.alivc_biginteractiveclass_string_confrim_btn))
        .setOneButtonClickListener(new AlivcTipDialog.OneButtonClickListener() {

            @Override
            public void onClicked() {
                finish();
            }
        })
        .create();
        alivcTipDialog.setCanceledOnTouchOutside(false);
        alivcTipDialog.setCancelable(false);
        if (!alivcTipDialog.isShowing()) {
            alivcTipDialog.show();
        }
    }



    @Override
    protected void onStop() {
        super.onStop();
        Log.i(TAG, "onStop: ");
        RTCInteractiveClassImpl.sharedInstance().stopPublish();
    }

    private Map<String, String> createChannelNumParams() {
        Map<String, String> params = new HashMap<>();
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_CHANNELID, mChannelId);
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_PLATFORM, Constant.NEW_TOKEN_PARAMS_VALUE_PLATFORM);
        return params;
    }

    /**
     * 适配部分机型点击音量按键控制的时通话音量
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode) {
        case KeyEvent.KEYCODE_VOLUME_UP:
            if (mAudioManager != null) {
                mAudioManager.adjustStreamVolume(isStudentRole ? AudioManager.STREAM_MUSIC : AudioManager.STREAM_VOICE_CALL, AudioManager.ADJUST_RAISE, AudioManager.FLAG_SHOW_UI);
            }
            break;
        case KeyEvent.KEYCODE_VOLUME_DOWN:
            if (mAudioManager != null) {
                mAudioManager.adjustStreamVolume(isStudentRole ? AudioManager.STREAM_MUSIC : AudioManager.STREAM_VOICE_CALL, AudioManager.ADJUST_LOWER, AudioManager.FLAG_SHOW_UI);
            }
            break;
        default:
        }
        return super.onKeyDown(keyCode, event);
    }
}
