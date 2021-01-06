package com.aliyun.rtc.rtcinteractiveclassplayer.ui;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Looper;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.View;
import android.view.Window;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.aliyun.rtc.alivcrtcviewcommon.view.ChannelEditView;
import com.aliyun.rtc.rtcinteractiveclassplayer.R;
import com.aliyun.rtc.rtcinteractiveclassplayer.bean.AliUserInfoResponse;
import com.aliyun.rtc.rtcinteractiveclassplayer.constant.Constant;
import com.aliyun.rtc.rtcinteractiveclassplayer.network.OkHttpCientManager;
import com.aliyun.rtc.rtcinteractiveclassplayer.network.OkhttpClient;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.DoubleClickUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.PermissionUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.ToastUtils;
import com.aliyun.rtc.rtcinteractiveclassplayer.utils.UIHandlerUtil;
import com.aliyun.rtc.rtcinteractiveclassplayer.view.LoadingDrawable;
import com.aliyun.svideo.common.utils.NetUtils;
import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;


import java.util.HashMap;
import java.util.Map;


public class AlivcJoinChannelActivity extends AppCompatActivity implements View.OnClickListener, PermissionUtil.PermissionGrantedListener, OkhttpClient.HttpCallBack {

    private ChannelEditView mEtChannelId;
    private String[] permissions = new String[] {
        PermissionUtil.PERMISSION_CAMERA,
        PermissionUtil.PERMISSION_WRITE_EXTERNAL_STORAGE,
        PermissionUtil.PERMISSION_RECORD_AUDIO,
        PermissionUtil.PERMISSION_READ_EXTERNAL_STORAGE
    };
    //private AliUserInfoResponse.AliUserInfo rtcAuthInfo;
    private TextView mTvConfirm;
    private EditText mEtStudentName;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setStatusBarLightMode(this, false);
        setContentView(R.layout.alivc_big_interactive_class_activity_join_channel);
        //请求权限
        PermissionUtil.requestPermissions(AlivcJoinChannelActivity.this, permissions, PermissionUtil.PERMISSION_REQUEST_CODE, AlivcJoinChannelActivity.this);
        initView();
    }

    /**
     *  设置statusBar的字体颜色
     * @param isLightMode true 浅色 false 深色
     */
    public void setStatusBarLightMode(Activity activity, boolean isLightMode) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            Window window = activity.getWindow();
            int option = window.getDecorView().getSystemUiVisibility();
            if (!isLightMode) {
                option |= View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR;
            } else {
                option &= ~View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR;
            }
            window.getDecorView().setSystemUiVisibility(option);
        }
    }

    @Override
    protected void onStart() {
        super.onStart();
        clearAllEdit();
    }

    private void clearAllEdit() {
        if (mEtChannelId != null) {
            mEtChannelId.setText("");
        }

        if (mEtStudentName != null) {
            mEtStudentName.setText("");
        }
    }

    private void initView() {
        mEtChannelId = findViewById(R.id.alivc_biginteractiveclass_edittext_channelid);
        mTvConfirm = findViewById(R.id.alivc_voicecall_tv_begin_speak);
        mEtStudentName = findViewById(R.id.alivc_biginteractiveclassl_edittext_student_name);
        ImageView ivBack = findViewById(R.id.alivc_big_interactive_class_iv_back);
        RelativeLayout rlContent = findViewById(R.id.alivc_voicecall_rl_login_layout_content);

        rlContent.setOnClickListener(this);
        mTvConfirm.setOnClickListener(this);
        ivBack.setOnClickListener(this);
        mTvConfirm.setEnabled(false);
        mEtChannelId.addTextChangedListener(new ChannelIdTextWatcher());
        mEtStudentName.addTextChangedListener(new ChannelIdTextWatcher());
        mEtChannelId.setOnClickListener(this);
        //mEtStudentName.setText("测试");
        //mEtChannelId.setText("11111");
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        if (id == R.id.alivc_voicecall_tv_begin_speak) {
            if (DoubleClickUtil.isDoubleClick(v, 500)) {
                ToastUtils.showInCenter(AlivcJoinChannelActivity.this, getString(R.string.alivc_biginteractiveclass_string_hint_double_click));
                return;
            }

            if (TextUtils.isEmpty(getStudentName())) {
                ToastUtils.showInCenter(AlivcJoinChannelActivity.this, getString(R.string.alivc_biginteractiveclass_string_error_student_name_empty));
                return;
            }

            if (!NetUtils.isNetworkConnected(AlivcJoinChannelActivity.this)) {
                ToastUtils.showInCenter(AlivcJoinChannelActivity.this, getString(R.string.alivc_biginteractiveclass_string_network_conn_error));
                return;
            }
            //getTokenByNet();
            toChatActivity();
        } else if (id == R.id.alivc_voicecall_rl_login_layout_content) {
            hideSoftInput();
        }else if(id == R.id.alivc_big_interactive_class_iv_back){
            finish();
        }
    }

    private void hideSoftInput() {
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm != null) {
            imm.hideSoftInputFromWindow(getWindow().getDecorView().getWindowToken(), 0);
        }
    }

    /**
     * 获取rtc服务器的token信息
     */
    private void getTokenByNet() {
        showLoadingView();
        String url = Constant.getUserLoginUrl();
        Map<String, String> params = createTokenParams();
        OkHttpCientManager.getInstance().doGet(url, params, this);
    }



    /**
     * 开始通话按钮显示loading画面
     */
    private void showLoadingView() {
        mTvConfirm.setText(R.string.alivc_biginteractiveclass_string_loading_join_channel);
        LoadingDrawable loadingDrawable = new LoadingDrawable();
        int width = mTvConfirm.getWidth();
        int height = mTvConfirm.getHeight();
        int left = width / 2 - height;
        int right = width / 2;
        loadingDrawable.setBounds(left, 0, right, height);
        mTvConfirm.setCompoundDrawables(loadingDrawable, null, null, null);
    }

    private void hideLoadingView() {
        UIHandlerUtil.getInstance().postRunnable(new Runnable() {
            @Override
            public void run() {
                mTvConfirm.setText(R.string.alivc_biginteractiveclass_string_btn_start_voice_call);
                mTvConfirm.setCompoundDrawables(null, null, null, null);
            }
        });
    }

    /*String token, String channelId*/
    private Map<String, String> createTokenParams() {
        Map<String, String> params = new HashMap<>();
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_CHANNELID, getChannelId());
        params.put(Constant.NEW_TOKEN_PARAMS_KEY_USERID, getStudentName());
        return params;
    }

    /**
     * 获取房间号
     *
     * @return 房间号
     */
    private String getChannelId() {
        return mEtChannelId == null ? "" : mEtChannelId.getText().toString().trim();
    }

    private String getStudentName() {
        return mEtStudentName == null ? "" : mEtStudentName.getText().toString().trim();
    }

    /**
     * 权限申请成功
     */
    @Override
    public void onPermissionGranted() {

    }

    /**
     * 权限申请失败
     */
    @Override
    public void onPermissionCancel() {
        ToastUtils.showInCenter(AlivcJoinChannelActivity.this, getString(R.string.alirtc_permission));
        finish();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode == PermissionUtil.PERMISSION_REQUEST_CODE) {
            PermissionUtil.requestPermissionsResult(AlivcJoinChannelActivity.this, PermissionUtil.PERMISSION_REQUEST_CODE, permissions, grantResults, AlivcJoinChannelActivity.this);
        } else {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    public void toChatActivity() {
        Intent intent = new Intent(AlivcJoinChannelActivity.this, AlivcClassRoomActivity.class);
        Bundle b = new Bundle();
        //频道号
        String channel = getChannelId();
        b.putString("channel", channel);
        b.putString("studentName", getStudentName());
        //b.putSerializable("rtcAuthInfo", rtcAuthInfo);
        intent.putExtras(b);
        startActivity(intent);
    }

    /**
     * 获取RTC服务器TOKEN成功
     */
    @Override
    public void onSuccess(String result) {
        try {
            AliUserInfoResponse aliUserInfoResponse = new Gson().fromJson(result, AliUserInfoResponse.class);
            if (aliUserInfoResponse != null) {
                //rtcAuthInfo = aliUserInfoResponse.getData();
                toChatActivity();
                //getChannelNum();
            }

        } catch (JsonSyntaxException e) {
            e.printStackTrace();
        }
    }

    /**
     * 获取用户数据失败
     *
     * @param errorMsg 失败信息
     */
    @Override
    public void onFaild(String errorMsg) {
        showToastInCenter(String.format(getString(R.string.alivc_biginteractiveclass_string_join_channel_error), errorMsg));
        hideLoadingView();
    }

    /**
     * 房间号输入框的文字监听器
     */
    private class ChannelIdTextWatcher implements TextWatcher {
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {

        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            if (TextUtils.isEmpty(getChannelId()) || getChannelId().length() < 6 || TextUtils.isEmpty(getStudentName())) {
                if (mTvConfirm.isEnabled()) {
                    mTvConfirm.setEnabled(false);
                }
            } else
                //改变开始通话按钮状态
                if (!mTvConfirm.isEnabled()) {
                    mTvConfirm.setEnabled(true);
                }
        }

        @Override
        public void afterTextChanged(Editable s) {

        }
    }

    public void showToastInCenter(final String msg) {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            ToastUtils.showInCenter(AlivcJoinChannelActivity.this, msg);
        } else {
            UIHandlerUtil.getInstance().postRunnable(new Runnable() {
                @Override
                public void run() {
                    ToastUtils.showInCenter(AlivcJoinChannelActivity.this, msg);
                }
            });
        }
    }
}
