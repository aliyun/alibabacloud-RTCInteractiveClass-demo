package com.aliyun.rtc.rtcinteractiveclassplayer.view;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.IntDef;
import android.support.annotation.NonNull;
import android.text.TextUtils;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;


import com.aliyun.rtc.rtcinteractiveclassplayer.R;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public class AlivcTipDialog extends Dialog implements View.OnClickListener {

    private TextView mTvTitle;
    private TextView mTvDes;
    private LinearLayout mLlTwoBtnLayout;
    private Button mBtnCancel;
    private Button mBtnComfin;
    private Button mBtnOne;

    private OneButtonClickListener mOneButtonClickListener;
    private TwoButtonClickListener mTwoButtonClickListener;

    private Builder mBuilder;

    @IntDef({
        ONE_BUTTON,
        TWO_BUTTON
    })
    @Retention(RetentionPolicy.SOURCE)
    public @interface BUTTONTYPE {
    }

    public static final int ONE_BUTTON = 1;

    public static final int TWO_BUTTON = 2;

    public AlivcTipDialog(@NonNull Context context) {
        this(context, R.style.CustomDialogStyle);
    }

    private AlivcTipDialog(@NonNull Context context, int themeResId) {
        super(context, themeResId);
    }

    private AlivcTipDialog(AlivcTipDialog.Builder builder, Context context) {
        super(context);
        mBuilder = builder;
    }

    private void setData() {
        if (mBuilder.mButtonType > 0) {
            setType(mBuilder.mButtonType);
        }

        if (!TextUtils.isEmpty(mBuilder.mTitle)) {
            mTvTitle.setText(mBuilder.mTitle);
        }

        if (!TextUtils.isEmpty(mBuilder.mDes)) {
            mTvDes.setText(mBuilder.mDes);
        }

        if (!TextUtils.isEmpty(mBuilder.mCancelStr)) {
            mBtnCancel.setText(mBuilder.mCancelStr);
        }

        if (!TextUtils.isEmpty(mBuilder.mConfirmStr)) {
            mBtnComfin.setText(mBuilder.mConfirmStr);
        }

        if (!TextUtils.isEmpty(mBuilder.mOneBtnStr)) {
            mBtnOne.setText(mBuilder.mOneBtnStr);
        }

        mOneButtonClickListener = mBuilder.mOneButtonClickListener;
        mTwoButtonClickListener = mBuilder.mTwoButtonClickListener;
    }

    private void setType(@BUTTONTYPE int buttonType) {
        mLlTwoBtnLayout.setVisibility(buttonType == TWO_BUTTON ? View.VISIBLE : View.GONE);
        mBtnOne.setVisibility(buttonType == ONE_BUTTON ? View.VISIBLE : View.GONE);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.alivc_big_interactive_class_layout_tip_dialog);
        initView();
        setData();
    }

    private void initView() {
        mTvTitle = findViewById(R.id.alivc_voicecall_tv_tip_dialog_title);
        mTvDes = findViewById(R.id.alivc_voicecall_tv_tip_dialog_des);
        mLlTwoBtnLayout = findViewById(R.id.alivc_voicecall_ll_two_btn_layout);
        mBtnCancel = findViewById(R.id.alivc_voicecall_btn_tip_dialog_cancel);
        mBtnComfin = findViewById(R.id.alivc_voicecall_btn_tip_dialog_confirm);
        mBtnOne = findViewById(R.id.alivc_common_dialog_tip_dialog_one_btn);

        mBtnCancel.setOnClickListener(this);
        mBtnComfin.setOnClickListener(this);
        mBtnOne.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        if (id == R.id.alivc_voicecall_btn_tip_dialog_cancel) {
            if (mTwoButtonClickListener != null) {
                mTwoButtonClickListener.onCancel();
            }
        } else if (id == R.id.alivc_voicecall_btn_tip_dialog_confirm) {
            if (mTwoButtonClickListener != null) {
                mTwoButtonClickListener.onConfirm();
            }
        } else if (id == R.id.alivc_common_dialog_tip_dialog_one_btn) {
            if (mOneButtonClickListener != null) {
                mOneButtonClickListener.onClicked();
            }
        }
        dismiss();
    }

    public interface OneButtonClickListener {
        void onClicked();
    }

    public interface TwoButtonClickListener {
        void onCancel();

        void onConfirm();
    }

    public static class Builder {

        private Context mContext;
        private int mButtonType;
        private String mTitle, mDes, mCancelStr, mConfirmStr, mOneBtnStr;
        private OneButtonClickListener mOneButtonClickListener;
        private TwoButtonClickListener mTwoButtonClickListener;

        public Builder(Context context) {
            mContext = context;
        }

        public Builder setButtonType(@BUTTONTYPE int buttonType) {
            mButtonType = buttonType;
            return this;
        }

        public Builder setTitle(String title) {
            mTitle = title;
            return this;
        }

        public Builder setDes(String des) {
            mDes = des;
            return this;
        }

        public Builder setCancelStr(String cancelStr) {
            mCancelStr = cancelStr;
            return this;
        }

        public Builder setConfirmStr(String confirmStr) {
            mConfirmStr = confirmStr;
            return this;
        }

        public Builder setOneBtnStr(String oneBtnStr) {
            mOneBtnStr = oneBtnStr;
            return this;
        }

        public Builder setOneButtonClickListener(OneButtonClickListener oneButtonClickListener) {
            mOneButtonClickListener = oneButtonClickListener;
            return this;
        }

        public Builder setTwoButtonClickListener(TwoButtonClickListener twoButtonClickListener) {
            mTwoButtonClickListener = twoButtonClickListener;
            return this;
        }

        public AlivcTipDialog create() {
            return new AlivcTipDialog(this, mContext);
        }
    }
}
