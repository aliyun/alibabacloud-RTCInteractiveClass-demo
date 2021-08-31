package com.aliyun.rtc.rtcinteractiveclass.adapter;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;

import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.bean.RemoteUserInfo;

import java.util.ArrayList;
import java.util.List;

public class RemoteUserAdapter extends BaseRecyclerViewAdapter<RemoteUserAdapter.RemoteUserViewHolder> {
    public static final String TAG = RemoteUserAdapter.class.getSimpleName();
    // 远端用户列表数据
    private final List<RemoteUserInfo> mRemoteUserList = new ArrayList<>();

    @NonNull
    @Override
    public RemoteUserViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.alivc_big_interactive_item_student_list, parent, false);
        return new RemoteUserViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull final RemoteUserViewHolder holder, final int position) {
        // 远端用户信息
        RemoteUserInfo userInfo = mRemoteUserList.get(position);
        if (userInfo == null) {
            return;
        }
        // 用户名称
        holder.mTvStudentDisplayName.setText(userInfo.getDisplayName());
        holder.mIvMuteLocalMic.setSelected(userInfo.isHasAudio());
        holder.mIvMuteLocalCamera.setSelected(userInfo.isHasVideo());
        holder.mTvStudentShowName.setVisibility(userInfo.isLocal() ? View.VISIBLE : View.GONE);
        holder.mIvHandUp.setVisibility(userInfo.isHandUp() ? View.VISIBLE : View.GONE);
        holder.mRemoteContainerLayout.setVisibility(userInfo.isHasVideo() ? View.GONE : View.VISIBLE);

        View view;
        if (userInfo.getScreenPreview() != null && userInfo.getCameraPreview() != null) {
            view = userInfo.getScreenPreview();
        } else if (userInfo.getScreenPreview() != null) {
            view = userInfo.getScreenPreview();
        } else {
            view = userInfo.getCameraPreview();
        }
        // 添加远端渲染视图
        if (view != null) {
            //如果老的surfaceView还在之前的viewTree中，需要先移除
            View oldSurface = holder.mRemoteContainerLayout.getChildAt(0);
            ViewParent oldParent = view.getParent();
            if (view != oldSurface) {
                if (oldParent instanceof FrameLayout)
                    ((FrameLayout) oldParent).removeAllViews();
                holder.mRemoteContainerLayout.removeAllViews();
                holder.mRemoteContainerLayout.addView(view, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
            }
        } else {
            holder.mRemoteContainerLayout.removeAllViews();
        }
    }

    @Override
    public int getItemCount() {
        return mRemoteUserList == null ? 0 : mRemoteUserList.size();
    }

    public static class RemoteUserViewHolder extends RecyclerView.ViewHolder {

        private final FrameLayout mRemoteContainerLayout;
        private final TextView mTvStudentDisplayName;
        private final TextView mTvStudentShowName;
        private final ImageView mIvMuteLocalMic;
        private final ImageView mIvMuteLocalCamera;
        private final ImageView mIvHandUp;

        private RemoteUserViewHolder(View view) {
            super(view);
            mIvHandUp = view.findViewById(R.id.alivc_big_interactive_class_iv_student_handUp);
            mRemoteContainerLayout = view.findViewById(R.id.alivc_big_interactive_class_rl_student_preview_container);
            mTvStudentDisplayName = view.findViewById(R.id.alivc_big_interactive_class_tv_student_display_name);
            mTvStudentShowName = view.findViewById(R.id.alivc_big_interactive_class_tv_student_name);
            mIvMuteLocalMic = view.findViewById(R.id.alivc_big_interactive_class_iv_student_mutemic);
            mIvMuteLocalCamera = view.findViewById(R.id.alivc_big_interactive_class_iv_student_mutecamera);
        }
    }

    /**
     * 添加数据
     *
     * @param userInfo
     */
    public synchronized boolean addData(RemoteUserInfo userInfo) {
        if (userInfo == null || mRemoteUserList == null) {
            return false;
        }
        boolean contains = mRemoteUserList.contains(userInfo);
        if (contains) {
            return false;
        }
        boolean isAdd = mRemoteUserList.add(userInfo.setNewAddUser(false));
        if (getItemCount() == 1) {
            notifyDataSetChanged();
        } else {
            notifyItemInserted(getItemCount() - 1);
        }
        Log.i(TAG, "addData 成功  uid: " + userInfo.getUserId() + " " + userInfo.hashCode());

        return isAdd;
    }

    /**
     * 修改数据
     *
     * @param userInfo
     */
    public synchronized void updateData(RemoteUserInfo userInfo) {
        if (userInfo == null) {
            return;
        }
        int position = mRemoteUserList.indexOf(userInfo);
        if (position < 0) {
            addData(userInfo);
        } else {
            notifyItemChanged(position);
        }
        Log.i(TAG, "updateData 成功 " + position + " uid: " + userInfo.getUserId() + " " + userInfo.hashCode());
    }

    /**
     * 移除数据
     *
     * @param userInfo
     */
    public synchronized boolean remoteData(RemoteUserInfo userInfo) {
        int position = mRemoteUserList.indexOf(userInfo);
        if (position == -1) {
            return false;
        }
        boolean isRemove = mRemoteUserList.remove(userInfo);
        if (isRemove) {
            notifyItemRemoved(position);
        }
        Log.i(TAG, "remoteData 成功 " + position + " uid: " + userInfo.getUserId());

        return isRemove;
    }

    /**
     * 交换远端用户和本地预览用户的信息
     * 如果远端用户在本地预览时离会了，需要重置状态
     *
     * @param smallInfo 小屏用户信息
     * @param largeInfo 大屏用户信息
     */
    public synchronized void swapData(RemoteUserInfo smallInfo, RemoteUserInfo largeInfo) {
        int index = mRemoteUserList.indexOf(smallInfo);
        if (index < 0) {
            return;
        }
        mRemoteUserList.set(index, largeInfo);
        notifyItemChanged(index);
    }

    /**
     * 获取数据
     *
     * @param uid 用户id
     * @return
     */
    public synchronized RemoteUserInfo getRemoteUserInfo(String uid) {
        for (int i = 0; i < mRemoteUserList.size(); i++) {
            RemoteUserInfo remoteUserInfo = mRemoteUserList.get(i);
            if (remoteUserInfo != null && remoteUserInfo.getUserId().equals(uid)) {
                return remoteUserInfo;
            }
        }
        return new RemoteUserInfo().setNewAddUser(true).setUserId(uid);
    }

    /**
     * 获取列表
     *
     * @return 列表数据
     */
    public synchronized List<RemoteUserInfo> getRemoteUserList() {
        return mRemoteUserList;
    }

    public OnItemClickListener onItemClickListener;

    public interface OnItemClickListener {
        void onItemClick(RemoteUserAdapter adapter, View view, int position);
    }

    public void setOnItemClickListener(OnItemClickListener onItemClickListener) {

        this.onItemClickListener = onItemClickListener;
    }
}
