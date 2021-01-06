package com.aliyun.rtc.rtcinteractiveclassplayer.adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.aliyun.rtc.rtcinteractiveclassplayer.R;

import java.util.ArrayList;
import java.util.List;

public class BottomFunctionAdapter extends RecyclerView.Adapter {

    private Context mContext;
    private ArrayList<Pair<String, Integer>> mFunctions;
    private FunctionCheckedListener mListener;
    private List<Integer> mSelectedViews = new ArrayList<>();
    private List<Integer> mEnableViews = new ArrayList<>();
    private boolean initBtnStatus;
    public BottomFunctionAdapter(Context context, ArrayList<Pair<String, Integer>> functions) {
        mContext = context;
        mFunctions = functions;
        mEnableViews.add(0);
        mEnableViews.add(1);
        mEnableViews.add(3);
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View inflate = LayoutInflater.from(mContext).inflate(R.layout.alivc_big_interactive_item_bottom_functions, parent, false);
        return new BottomFunctionHolder(inflate);
    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder holder, int position) {
        ((BottomFunctionHolder) holder).bindView(position);
    }

    @Override
    public int getItemCount() {
        return mFunctions != null ? mFunctions.size() : 0;
    }

    public void setListener(FunctionCheckedListener listener) {
        mListener = listener;
    }

    public void initBtnStatus() {
        initBtnStatus = true;
    }

    private class BottomFunctionHolder extends RecyclerView.ViewHolder {

        private final ImageView mFunctionIcon;
        private final TextView mFunctionName;

        public BottomFunctionHolder(View inflate) {
            super(inflate);
            mFunctionIcon = inflate.findViewById(R.id.alivc_big_interactive_class_iv_bottom_function_icon);
            mFunctionName = inflate.findViewById(R.id.alivc_big_interactive_class_tv_bottom_function_name);
        }

        public void bindView(final int position) {
            String str = null;
            int bgResId = -1;
            boolean contains = mSelectedViews.contains(position);
            if (position == 0) {
                str = mContext.getString(contains ? R.string.alivc_biginteractiveclass_string_resume : R.string.alivc_biginteractiveclass_string_mute_mic);
                bgResId = R.drawable.alivc_biginteractiveclass_mute_mic_selector;
            } else if (position == 1) {
                str = mContext.getString(contains ? R.string.alivc_biginteractiveclass_string_open_camera : R.string.alivc_biginteractiveclass_string_camera);
                bgResId = R.drawable.alivc_biginteractiveclass_mute_camera_selector;
            } else if (position == 2) {
                str = mContext.getString(contains ? R.string.alivc_biginteractiveclass_string_unconn_mic : R.string.alivc_biginteractiveclass_string_conn_mic);
                bgResId = R.drawable.alivc_biginteractiveclass_conn_mic_selector;
            } else if (position == 3) {
                str = mFunctions.get(position).first;
                bgResId = R.drawable.alivc_biginteractiveclass_rotate_camera_selector;
            } else {
                str = mFunctions.get(position).first;
                bgResId = mFunctions.get(position).second;
            }
            mFunctionName.setText(str);
            mFunctionIcon.setBackgroundResource(bgResId);
            if (contains) {
                mFunctionIcon.setSelected(true);
            } else {
                mFunctionIcon.setSelected(false);
            }
            if (mEnableViews.contains(position)) {
                //                mFunctionIcon.setEnabled(true);
                mFunctionIcon.setAlpha(0.5f);
                mFunctionName.setAlpha(0.5f);
            } else {
                mFunctionIcon.setAlpha(1f);
                mFunctionName.setAlpha(1f);
                //                mFunctionIcon.setEnabled(false);
            }
            ((ViewGroup) mFunctionIcon.getParent()).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    boolean b = true;
                    if (mListener != null) {
                        b = mListener.onFunctionChecked(position);
                    }
                    if (!b) {
                        return;
                    }

                    if (initBtnStatus) {
                        initAllBtnStatus();
                    } else {
                        if (mSelectedViews.contains(position)) {
                            mSelectedViews.remove(Integer.valueOf(position));
                        } else {
                            mSelectedViews.add(position);
                        }
                        mEnableViews.clear();
                        notifyDataSetChanged();
                    }

                }
            });
        }
    }

    public void initAllBtnStatus() {
        mEnableViews.add(0);
        mEnableViews.add(1);
        mEnableViews.add(3);
        mSelectedViews.clear();
        notifyDataSetChanged();
        initBtnStatus = false;
    }

    public interface FunctionCheckedListener {
        boolean onFunctionChecked(int position);
    }
}
