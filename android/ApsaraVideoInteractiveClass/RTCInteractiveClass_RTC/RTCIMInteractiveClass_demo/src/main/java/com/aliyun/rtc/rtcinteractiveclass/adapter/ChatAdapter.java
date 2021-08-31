package com.aliyun.rtc.rtcinteractiveclass.adapter;

import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.bean.ChatBean;

import java.util.ArrayList;
import java.util.List;

public class ChatAdapter extends BaseRecyclerViewAdapter<ChatAdapter.ChatViewHolder> {
    public static final String TAG = ChatAdapter.class.getSimpleName();

    private final List<ChatBean> mChatUserList = new ArrayList<>();

    @Override
    public ChatViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new ChatViewHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.alivc_big_interactive_chat_item, parent, false));
    }

    @Override
    public void onBindViewHolder(ChatViewHolder holder, int position) {
        if (mChatUserList == null) {
            return;
        }
        ChatBean bean = mChatUserList.get(position);
        if (bean.isLocal()) {
            holder.mChatRemoteMsgTv.setVisibility(View.INVISIBLE);
            holder.mChatRemoteNameTv.setVisibility(View.INVISIBLE);
            holder.mChatRemoteTagTv.setVisibility(View.INVISIBLE);

            holder.mLocalNameTv.setVisibility(View.VISIBLE);
            holder.mLocalTagTv.setVisibility(View.VISIBLE);
            holder.mLocalMsgTv.setVisibility(View.VISIBLE);

            holder.mLocalNameTv.setText(bean.getDisplayName());
            holder.mLocalMsgTv.setText(bean.getMsg());
        } else {
            holder.mLocalNameTv.setVisibility(View.INVISIBLE);
            holder.mLocalTagTv.setVisibility(View.INVISIBLE);
            holder.mLocalMsgTv.setVisibility(View.INVISIBLE);

            holder.mChatRemoteMsgTv.setVisibility(View.VISIBLE);
            holder.mChatRemoteNameTv.setVisibility(View.VISIBLE);

            if (bean.getDisplayName().contains("_老师")) {
                holder.mChatRemoteTagTv.setVisibility(View.VISIBLE);
            }

            holder.mChatRemoteNameTv.setText(bean.getDisplayName());
            holder.mChatRemoteMsgTv.setText(bean.getMsg());
        }
    }

    @Override
    public int getItemCount() {
        return mChatUserList == null ? 0 : mChatUserList.size();
    }

    public static class ChatViewHolder extends RecyclerView.ViewHolder {


        private final TextView mLocalNameTv;
        private final TextView mLocalTagTv;
        private final TextView mLocalMsgTv;

        private final TextView mChatRemoteMsgTv;
        private final TextView mChatRemoteNameTv;
        private final TextView mChatRemoteTagTv;

        public ChatViewHolder(View itemView) {
            super(itemView);
            mLocalNameTv = itemView.findViewById(R.id.local_name_tv);
            mLocalTagTv = itemView.findViewById(R.id.alivc_big_interactive_class_tv_student_name);
            mLocalMsgTv = itemView.findViewById(R.id.chat_local_msg_tv);

            mChatRemoteMsgTv = itemView.findViewById(R.id.chat_student_msg_tv);
            mChatRemoteNameTv = itemView.findViewById(R.id.student_name_tv);
            mChatRemoteTagTv = itemView.findViewById(R.id.alivc_big_interactive_class_dialog_teacher_name);

        }
    }


    /**
     * 添加数据
     *
     * @param chatBean
     */
    public synchronized boolean addData(ChatBean chatBean) {
        if (chatBean == null || mChatUserList == null) {
            return false;
        }
//        boolean contains = mChatUserList.contains(chatBean);
//        if (contains) {
//            return false;
//        }
        boolean isAdd = mChatUserList.add(chatBean);
        if (getItemCount() == 1) {
            notifyDataSetChanged();
        } else {
            notifyItemInserted(getItemCount() - 1);
        }
        Log.i(TAG, "addData 成功  uid: " + chatBean.getUid() + " " + chatBean.hashCode());

        return isAdd;
    }

    public synchronized void addAllData(List<ChatBean> chatBeans) {
        if (chatBeans == null) {
            return;
        }
        mChatUserList.addAll(chatBeans);
        notifyDataSetChanged();
    }

    /**
     * 修改数据
     *
     * @param chatBean
     */
    public synchronized void updateChatData(ChatBean chatBean) {
        if (chatBean == null) {
            return;
        }
        int position = mChatUserList.indexOf(chatBean);
        if (position < 0) {
            addData(chatBean);
        } else {
            notifyItemChanged(position);
        }
        Log.i(TAG, "updateData 成功 " + position + " uid: " + chatBean.getUid() + " " + chatBean.hashCode());
    }

    /**
     * 移除数据
     *
     * @param chatBean
     */
    public synchronized boolean remoteData(ChatBean chatBean) {
        int position = mChatUserList.indexOf(chatBean);
        if (position == -1) {
            return false;
        }
        boolean isRemove = mChatUserList.remove(chatBean);
        if (isRemove) {
            notifyItemRemoved(position);
        }
        Log.i(TAG, "remoteData 成功 " + position + " uid: " + chatBean.getUid());

        return isRemove;
    }

//    /**
//     * 获取数据
//     *
//     * @param uid 用户id
//     * @return
//     */
//    public synchronized ChatBean getChatUserInfo(String uid) {
//        for (int i = 0; i < mChatUserList.size(); i++) {
//            ChatBean chatBean = mChatUserList.get(i);
//            if (chatBean != null && chatBean.getUid().equals(uid)) {
//                return chatBean;
//            }
//        }
//        return new ChatBean().setUid(uid);
//    }

    /**
     * 获取列表
     *
     * @return 列表数据
     */
    public synchronized List<ChatBean> getRemoteUserList() {
        return mChatUserList;
    }

}
