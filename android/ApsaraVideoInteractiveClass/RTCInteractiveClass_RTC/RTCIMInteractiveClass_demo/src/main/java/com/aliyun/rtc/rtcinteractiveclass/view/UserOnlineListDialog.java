package com.aliyun.rtc.rtcinteractiveclass.view;

import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

import com.alibaba.dingpaas.aim.AIMPubConversation;
import com.alibaba.dingpaas.aim.AIMPubGroupListAllMemberListener;
import com.alibaba.dingpaas.aim.AIMPubGroupMember;
import com.alibaba.dingpaas.aim.AIMPubMessage;
import com.alibaba.dingpaas.aim.AIMPubNewMessage;
import com.alibaba.dingpaas.base.DPSError;
import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.adapter.BaseRecyclerViewAdapter;
import com.aliyun.rtc.rtcinteractiveclass.bean.OnlineUserInfo;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.im.AliImInteractiveListener;
import com.aliyun.rtc.rtcinteractiveclass.rtc.AliRtcInteractiveEngine;
import com.aliyun.rtc.rtcinteractiveclass.utils.ScreenUtil;
import com.aliyun.rtc.rtcinteractiveclass.utils.SizeUtil;
import com.aliyun.svideo.common.utils.ThreadUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;


public class UserOnlineListDialog extends DialogFragment {
    public static final String TEACHER_NAME = "teacher_name";
    private View view;
    private TextView mOnlineListNumberTv;
    private TextView mMaiShangNumberTv;
    private RecyclerView mOnlineStudentRv;
    private String mTeacherDisplayName;

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

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup
            container, @Nullable Bundle savedInstanceState) {
        getDialog().requestWindowFeature(Window.FEATURE_NO_TITLE);
        getDialog().getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        getDialog().setCanceledOnTouchOutside(true);
        if (view == null) {
            view = inflater.inflate(R.layout.alivc_big_interactive_class_online_list_dialog, container);
        }
        mOnlineListNumberTv = view.findViewById(R.id.alivc_biginteractiveclass_online_number_tv);
        mMaiShangNumberTv = view.findViewById(R.id.alivc_biginteractiveclass_liamai_number_tv);
        mOnlineStudentRv = view.findViewById(R.id.online_list);
        initView();
        iniData();
        return view;
    }

    private void initView() {
        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(getContext());
        linearLayoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        mOnlineStudentRv.setLayoutManager(linearLayoutManager);

    }

    private void iniData() {
        Bundle arguments = getArguments();
        if (arguments != null) {
            mTeacherDisplayName = arguments.getString(TEACHER_NAME);
        }
        getChannelNum();
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

            }

            @Override
            public void sendMessageFailure(DPSError dpsError) {

            }

            @Override
            public void onAddedMessages(ArrayList<AIMPubNewMessage> arrayList) {

            }

            @Override
            public void onGroupAddedMembers() {
                getChannelNum();
            }

            @Override
            public void onGroupRemovedMembers() {
                getChannelNum();
            }
        });
    }

    private void getChannelNum() {
        AliImInteractiveEngine.sharedInstance().listAllMembers(new AIMPubGroupListAllMemberListener() {
            @Override
            public void onLocal(ArrayList<AIMPubGroupMember> arrayList) {

            }

            @Override
            public void onRefresh(final ArrayList<AIMPubGroupMember> arrayList) {
                final List<OnlineUserInfo> onlineLists = new ArrayList<>();
                int onlineRemoteStudentLength = AliRtcInteractiveEngine.sharedInstance().getRoomUserList().length - 1;
                boolean studentRole = AliRtcInteractiveEngine.sharedInstance().isActiveStudent();
                if (!studentRole) {//当前不是观众，连麦学生列表+1
                    onlineRemoteStudentLength += 1;
                }
                for (AIMPubGroupMember aimPubGroupMember : arrayList) {
                    OnlineUserInfo onlineUserInfo = new OnlineUserInfo();
                    onlineUserInfo.setUid(aimPubGroupMember.getUid());
                    if (aimPubGroupMember.groupNick.equals("主持人")) {
                        onlineUserInfo.setTeacher(true);
                        onlineUserInfo.setDisplayName(mTeacherDisplayName);
                    } else {
                        onlineUserInfo.setDisplayName(aimPubGroupMember.getGroupNick());
                    }
                    if (aimPubGroupMember.getUid().contains(AliRtcInteractiveEngine.sharedInstance().getLocalSeatUserInfo().getUserId())) {
                        onlineUserInfo.setLocal(true);
                    }
                    onlineLists.add(onlineUserInfo);
                }
                final int finalOnlineRemoteStudentLength = onlineRemoteStudentLength;
                ThreadUtils.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        String online = String.format(Locale.CHINA, "当前在线人数: %s 人", arrayList.size());
                        if (mOnlineListNumberTv != null) {
                            mOnlineListNumberTv.setText(online);
                        }
                        String format = String.format(Locale.CHINA, "连麦学生: %s 人", Math.max(finalOnlineRemoteStudentLength, 0));
                        if (mMaiShangNumberTv != null) {
                            mMaiShangNumberTv.setText(format);
                        }
                        OnlineAdapter adapter = new OnlineAdapter(onlineLists);
                        if (mOnlineStudentRv != null) {
                            mOnlineStudentRv.setAdapter(adapter);
                        }
                    }
                });

            }

            @Override
            public void onFailure(DPSError dpsError) {

            }
        });
    }

    public static class OnlineAdapter extends BaseRecyclerViewAdapter<OnlineAdapter.OnlineViewHolder> {
        private List<OnlineUserInfo> remoteUserList = new ArrayList<>();

        public OnlineAdapter(List<OnlineUserInfo> onlineLists) {
            this.remoteUserList = onlineLists;
        }

        @Override
        public OnlineViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            return new OnlineViewHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.alivc_big_interactive_online_dialog_item, parent, false));
        }

        @Override
        public void onBindViewHolder(OnlineViewHolder holder, int position) {
            if (remoteUserList != null && remoteUserList.size() > 0) {
                OnlineUserInfo userInfo = remoteUserList.get(position);
                holder.mNameTv.setText(userInfo.getDisplayName());

                if (userInfo.isTeacher()) {
                    holder.mTeacherNameTv.setVisibility(View.VISIBLE);
                }
                if (userInfo.isLocal()) {
                    holder.mStudentNameTv.setVisibility(View.VISIBLE);
                }
            }

        }

        @Override
        public int getItemCount() {
            return remoteUserList == null ? 0 : remoteUserList.size();
        }

        static class OnlineViewHolder extends RecyclerView.ViewHolder {
            public TextView mNameTv;
            public TextView mTeacherNameTv;
            public TextView mStudentNameTv;

            public OnlineViewHolder(View itemView) {
                super(itemView);
                mNameTv = itemView.findViewById(R.id.student_name_tv);
                mTeacherNameTv = itemView.findViewById(R.id.alivc_big_interactive_class_dialog_teacher_name);
                mStudentNameTv = itemView.findViewById(R.id.alivc_big_interactive_class_dialog_student_name);
            }
        }

    }
}
