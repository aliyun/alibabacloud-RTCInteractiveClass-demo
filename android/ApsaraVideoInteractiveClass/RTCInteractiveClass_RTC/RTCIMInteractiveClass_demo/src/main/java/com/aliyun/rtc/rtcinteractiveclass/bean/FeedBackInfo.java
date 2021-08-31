package com.aliyun.rtc.rtcinteractiveclass.bean;

import android.os.Parcel;
import android.os.Parcelable;

public class FeedBackInfo implements Parcelable {

    private String mTeacherDisplayName;
    private long mStartTime;
    private long mEndTime;
    private int mOnlineNum;
    private int mSeatNum;

    public FeedBackInfo() {

    }

    protected FeedBackInfo(Parcel in) {
        mTeacherDisplayName = in.readString();
        mStartTime = in.readLong();
        mEndTime = in.readLong();
        mOnlineNum = in.readInt();
        mSeatNum = in.readInt();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(mTeacherDisplayName);
        dest.writeLong(mStartTime);
        dest.writeLong(mEndTime);
        dest.writeInt(mOnlineNum);
        dest.writeInt(mSeatNum);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<FeedBackInfo> CREATOR = new Creator<FeedBackInfo>() {
        @Override
        public FeedBackInfo createFromParcel(Parcel in) {
            return new FeedBackInfo(in);
        }

        @Override
        public FeedBackInfo[] newArray(int size) {
            return new FeedBackInfo[size];
        }
    };

    public String getTeacherDisplayName() {
        return mTeacherDisplayName;
    }

    public void setTeacherDisplayName(String mTeacherDisplayName) {
        this.mTeacherDisplayName = mTeacherDisplayName;
    }

    public long getStartTime() {
        return mStartTime;
    }

    public void setStartTime(long mStartTime) {
        this.mStartTime = mStartTime;
    }

    public long getEndTime() {
        return mEndTime;
    }

    public void setEndTime(long mTotalTime) {
        this.mEndTime = mTotalTime;
    }

    public int getOnlineNum() {
        return mOnlineNum;
    }

    public void setOnlineNum(int mOnlineNum) {
        this.mOnlineNum = mOnlineNum;
    }

    public int getSeatNum() {
        return mSeatNum;
    }

    public void setSeatNum(int mSeatNum) {
        this.mSeatNum = mSeatNum;
    }

    @Override
    public String toString() {
        return "FeedBackInfo{" +
                "mTeacherDisplayName='" + mTeacherDisplayName + '\'' +
                ", mStartTime=" + mStartTime +
                ", mTotalTime=" + mEndTime +
                ", mOnlineNum=" + mOnlineNum +
                ", mSeatNum=" + mSeatNum +
                '}';
    }
}
