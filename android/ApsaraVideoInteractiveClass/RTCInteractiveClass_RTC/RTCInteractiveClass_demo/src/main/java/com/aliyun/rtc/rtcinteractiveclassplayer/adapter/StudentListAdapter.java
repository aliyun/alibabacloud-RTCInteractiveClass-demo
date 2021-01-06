package com.aliyun.rtc.rtcinteractiveclassplayer.adapter;

import android.content.Context;
import android.graphics.PixelFormat;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.alivc.rtc.AliRtcEngine;
import com.aliyun.rtc.rtcinteractiveclassplayer.R;
import com.aliyun.rtc.rtcinteractiveclassplayer.bean.AlivcVideoStreamInfo;
import com.aliyun.rtc.rtcinteractiveclassplayer.rtc.RTCInteractiveClassImpl;

import org.webrtc.sdk.SophonSurfaceView;

import java.util.List;

public class StudentListAdapter extends RecyclerView.Adapter {

    private Context mContext;
    private List<AlivcVideoStreamInfo> mAlivcVideoStreamInfos;
    private ItemClickListener mItemClickListener;

    public void setItemClickListener(ItemClickListener itemClickListener) {
        mItemClickListener = itemClickListener;
    }

    public StudentListAdapter(Context context, List<AlivcVideoStreamInfo> alivcVideoStreamInfos) {
        mContext = context;
        mAlivcVideoStreamInfos = alivcVideoStreamInfos;
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.alivc_big_interactive_item_student_list, parent, false);
        return new StudentListHolder(view);
    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder holder, int position) {
    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder holder, int position, List payloads) {
        super.onBindViewHolder(holder, position, payloads);
        ((StudentListHolder) holder).bindView(position,payloads);
    }

    @Override
    public int getItemCount() {
        return mAlivcVideoStreamInfos == null ? 0 : mAlivcVideoStreamInfos.size();
    }

    /**
     * 移除item的时候先把soponsurfaceview从父view上移除，防止切换大小屏的时候提示view的添加异常
     * @param info 流信息
     */
    public void detachedPreview(AlivcVideoStreamInfo info) {
        if (info != null && info.isLocalStream()) {
            SophonSurfaceView view = info.getAliVideoCanvas().view;
            if (view != null) {
                if (view.getParent() != null) {
                    ((ViewGroup) view.getParent()).removeAllViews();
                }
            }
        }
    }

    private class StudentListHolder extends RecyclerView.ViewHolder {

        private final FrameLayout mRlContainer;
        private final TextView mTvStudentName;
        private final ImageView mIvMuteLocalMic;
        private final LinearLayout mCameraCloseView;

        private StudentListHolder(View view) {
            super(view);
            mRlContainer = view.findViewById(R.id.alivc_big_interactive_class_rl_student_preview_container);
            mTvStudentName = view.findViewById(R.id.alivc_big_interactive_class_tv_student_name);
            mIvMuteLocalMic = view.findViewById(R.id.alivc_big_interactive_class_iv_student_mutelocalmic);
            mCameraCloseView = view.findViewById(R.id.rtc_biginteractive_class_camera_close);
        }

        private void bindView(final int position,final List payloads) {
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    mRlContainer.removeAllViews();
                    if (mItemClickListener != null) {
                        mItemClickListener.onItemClicked(position);
                    }
                }
            });
            //复用，防止重复添加
            AlivcVideoStreamInfo alivcVideoStreamInfo = null;
            if (position < mAlivcVideoStreamInfos.size()) {
                alivcVideoStreamInfo = mAlivcVideoStreamInfos.get(position);
            }
            if (alivcVideoStreamInfo == null) {
                return;
            }
            if(payloads.isEmpty()){
                mTvStudentName.setText(TextUtils.isEmpty(alivcVideoStreamInfo.getUserName()) ? "":alivcVideoStreamInfo.getUserName());
                mIvMuteLocalMic.setImageResource(alivcVideoStreamInfo.isMuteMic() ? R.drawable.alivc_biginteractiveclass_item_mute_mic : R.drawable.alivc_biginteractiveclass_item_unmute_mic);
                mCameraCloseView.setVisibility(alivcVideoStreamInfo.isMuteCamera() ? View.VISIBLE : View.GONE );
                SophonSurfaceView sophonSurfaceView = alivcVideoStreamInfo.getAliVideoCanvas().view;
                if (sophonSurfaceView == null) {
                    sophonSurfaceView = new SophonSurfaceView(itemView.getContext());
                    sophonSurfaceView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
                    // true 在最顶层，会遮挡一切view
                    sophonSurfaceView.setZOrderOnTop(false);
                    //true 如已绘制SurfaceView则在surfaceView上一层绘制。
                    sophonSurfaceView.setZOrderMediaOverlay(true);
                    alivcVideoStreamInfo.getAliVideoCanvas().view = sophonSurfaceView;
                    //设置渲染模式,一共有四种
                    alivcVideoStreamInfo.getAliVideoCanvas().renderMode = AliRtcEngine.AliRtcRenderMode.AliRtcRenderModeFill;
                    mRlContainer.removeAllViews();
                    mRlContainer.addView(sophonSurfaceView, FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT);
                    if (alivcVideoStreamInfo.isLocalStream()) {
                        // preview
                        startPreview(alivcVideoStreamInfo);
                    } else {
                        displayStream(alivcVideoStreamInfo);
                    }
                } else {
                    mTvStudentName.setText(TextUtils.isEmpty(alivcVideoStreamInfo.getUserName()) ? "":alivcVideoStreamInfo.getUserName());
                    mIvMuteLocalMic.setImageResource(alivcVideoStreamInfo.isMuteMic() ? R.drawable.alivc_biginteractiveclass_item_mute_mic : R.drawable.alivc_biginteractiveclass_item_unmute_mic);
                    mCameraCloseView.setVisibility(alivcVideoStreamInfo.isMuteCamera() ? View.VISIBLE : View.GONE );
                    //已经添加并开始预览就只切换展示的spoonsurfaceview
                    if (sophonSurfaceView.getParent() != null) {
                        ((ViewGroup) sophonSurfaceView.getParent()).removeView(sophonSurfaceView);
                    }
                    // true 在最顶层，会遮挡一切view
                    sophonSurfaceView.setZOrderOnTop(false);
                    //true 如已绘制SurfaceView则在surfaceView上一层绘制。
                    sophonSurfaceView.setZOrderMediaOverlay(true);
                    mRlContainer.removeAllViews();
                    mRlContainer.addView(sophonSurfaceView, FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT);
                    if (!alivcVideoStreamInfo.isLocalStream()) {
                        return;
                    }
                    //点击关闭摄像头需要掉rtc sdk的停止预览展示黑背景
                    if (alivcVideoStreamInfo.isMuteLocalCamera()) {
                        RTCInteractiveClassImpl.sharedInstance().stopPreview();
                    } else {
                        RTCInteractiveClassImpl.sharedInstance().startPreview();
                    }
                }
            } else {
                //这里可以刷新item的局部view，防止画面预览view出现黑屏抖动
                int type= (int) payloads.get(0);
                if(type == 1){
                    mTvStudentName.setText(TextUtils.isEmpty(alivcVideoStreamInfo.getUserName()) ? "":alivcVideoStreamInfo.getUserName());
                    mIvMuteLocalMic.setImageResource(alivcVideoStreamInfo.isMuteMic() ? R.drawable.alivc_biginteractiveclass_item_mute_mic : R.drawable.alivc_biginteractiveclass_item_unmute_mic);
                    mCameraCloseView.setVisibility(alivcVideoStreamInfo.isMuteCamera() ? View.VISIBLE : View.GONE );
                }

            }
        }
    }

    /**
     * 展示远端流
     */
    private void displayStream(AlivcVideoStreamInfo alivcVideoStreamInfo) {

        AliRtcEngine.AliVideoCanvas aliVideoCanvas = alivcVideoStreamInfo.getAliVideoCanvas();
        if (aliVideoCanvas != null) {
            AliRtcEngine.AliRtcVideoTrack aliRtcVideoTrack = alivcVideoStreamInfo.getAliRtcVideoTrack() == AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackBoth ? AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackScreen : alivcVideoStreamInfo.getAliRtcVideoTrack();
            if(alivcVideoStreamInfo.isTeacher()){
                aliRtcVideoTrack = AliRtcEngine.AliRtcVideoTrack.AliRtcVideoTrackCamera;
            }
            RTCInteractiveClassImpl.sharedInstance().setRemoteViewConfig(aliVideoCanvas, alivcVideoStreamInfo.getUserId(), aliRtcVideoTrack);
        }
    }

    /**
     * 展示本地流
     */
    private void startPreview(AlivcVideoStreamInfo alivcVideoStreamInfo) {

        AliRtcEngine.AliVideoCanvas aliVideoCanvas = alivcVideoStreamInfo.getAliVideoCanvas();
        if (aliVideoCanvas != null) {
            RTCInteractiveClassImpl.sharedInstance().setLocalViewConfig(aliVideoCanvas, alivcVideoStreamInfo.getAliRtcVideoTrack());
        }
        if (!alivcVideoStreamInfo.isMuteLocalCamera()) {
            RTCInteractiveClassImpl.sharedInstance().startPreview();
        } else {
            RTCInteractiveClassImpl.sharedInstance().stopPreview();

        }
    }

    public interface ItemClickListener {
        void onItemClicked(int position);
    }
}
