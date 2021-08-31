package com.aliyun.rtc.rtcinteractiveclass.ui;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;
import android.widget.TextView;

import com.aliyun.rtc.rtcinteractiveclass.R;
import com.aliyun.rtc.rtcinteractiveclass.bean.FeedBackInfo;
import com.aliyun.svideo.common.utils.DateTimeUtils;

/**
 * 结束反馈
 */
public class AlivcFeedbackActivity extends AppCompatActivity {

    public static final String FEED_BACK = "feed_back";
    //教师昵称
    private TextView mTvTeacherName;
    //开始时间
    private TextView mTvClassStartTime;
    //课程时长
    private TextView mTvClassTotalTime;
    //在线人数
    private TextView mTvOnlineNum;
    //连麦人数
    private TextView mTvSeatNum;

    private String mStartTime;

    private String mEndTime;

    private String mTeacherDisplayName;

    private String mSeatNum;

    private String mOnlineNum;

    public static void start(Context context, FeedBackInfo feedBackInfo) {
        Intent intent = new Intent(context, AlivcFeedbackActivity.class);
        intent.putExtra(FEED_BACK, feedBackInfo);
        context.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setStatusBarLightMode(this, false);
        setContentView(R.layout.alivc_big_interactive_class_feedback);
        getData();
        initialize();
        initData();
    }

    private void initData() {
        mTvTeacherName.setText(String.format("教师: %s", mTeacherDisplayName));
        mTvClassStartTime.setText(mStartTime);
        mTvClassTotalTime.setText(mEndTime);
        mTvSeatNum.setText(mSeatNum);
        mTvOnlineNum.setText(mOnlineNum);
    }

    private void initialize() {
        mTvTeacherName = findViewById(R.id.feedback_teacher_name_tv);
        mTvClassStartTime = findViewById(R.id.feedback_class_start_time_tv);
        mTvClassTotalTime = findViewById(R.id.feedback_class_time_tv);
        mTvOnlineNum = findViewById(R.id.feedback_online_num_tv);
        mTvSeatNum = findViewById(R.id.feedback_seat_num_tv);
    }

    private void getData() {
        FeedBackInfo feedBackInfo = getIntent().getParcelableExtra(FEED_BACK);
        if (feedBackInfo != null) {
            mTeacherDisplayName = feedBackInfo.getTeacherDisplayName();
            mSeatNum = String.valueOf(feedBackInfo.getSeatNum());
            mOnlineNum = String.valueOf(feedBackInfo.getOnlineNum());
            mStartTime = DateTimeUtils.getDateTimeFromMD(feedBackInfo.getStartTime());
            long timeCost = feedBackInfo.getEndTime() - feedBackInfo.getStartTime();
            mEndTime = DateTimeUtils.formatMs(timeCost);
        }
    }

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

    public void endFeedBackOnclick(View view) {
        finish();
    }
}