package com.aliyun.rtc.rtcinteractiveclassplayer.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.support.annotation.Nullable;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.aliyun.rtc.rtcinteractiveclassplayer.R;


public class TitleBar extends RelativeLayout implements View.OnClickListener {

    private ImageButton mIbBack;
    private TextView mTvTitle;
    private BackBtnListener backBtnListener;
    private MenuBtnListener menuBtnListener;
    private LinearLayout mLlMenu;
    private ImageView mIvIconMenu;
    private TextView mTvMenuName;
    private RelativeLayout mRlContent;

    public TitleBar(Context context) {
        this(context, null);
    }

    public TitleBar(Context context, @Nullable AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public TitleBar(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        LayoutInflater.from(context).inflate(R.layout.alivc_big_interactive_class_layout_title_bar, this);
        initView();

        initEvent();
    }

    private void initEvent() {
        if (mIbBack != null) {
            mIbBack.setOnClickListener(this);
        }

        if (mLlMenu != null) {
            mLlMenu.setOnClickListener(this);
        }
    }

    private void initView() {
        mIbBack = findViewById(R.id.alivc_big_interactive_class_title_bar_ib_back);
        mTvTitle = findViewById(R.id.alivc_big_interactive_class_title_bar_tv_title);
        mLlMenu = findViewById(R.id.alivc_big_interactive_class_ll_menu);
        mIvIconMenu = findViewById(R.id.alivc_big_interactive_class_iv_icon_menu);
        mTvMenuName = findViewById(R.id.alivc_big_interactive_class_tv_menu_name);
        mRlContent = findViewById(R.id.alivc_big_interactive_class_rl_content);

        //初始化view的状态
        mTvTitle.setText(R.string.app_name);
        mIbBack.setVisibility(GONE);
        mLlMenu.setVisibility(GONE);
        //        rcy_menu.setVisibility(GONE);
    }

    public void setTitle(CharSequence title) {
        if (TextUtils.isEmpty(title) || mTvTitle == null) {
            return;
        }
        mTvTitle.setText(title);
    }

    public void setBackBtnEnable(boolean enable) {
        if (mIbBack != null) {
            mIbBack.setVisibility(enable ? View.VISIBLE : View.GONE);
        }
    }

    public void setMenuBtnEnable(boolean enable) {
        if (mLlMenu != null) {
            mLlMenu.setVisibility(enable ? View.VISIBLE : View.GONE);
        }
    }

    public void setBackBtnListener(BackBtnListener listener) {
        if (mIbBack.getVisibility() != View.VISIBLE) {
            setBackBtnEnable(true);
        }
        this.backBtnListener = listener;
    }

    public void setMenuBtnListener(MenuBtnListener listener) {
        if (mLlMenu.getVisibility() != View.VISIBLE) {
            setMenuBtnEnable(true);
        }
        this.menuBtnListener = listener;
    }
    @Override
    public void onClick(View v) {
        int id = v.getId();
        if (id == R.id.alivc_big_interactive_class_title_bar_ib_back) {
            if (backBtnListener != null) {
                backBtnListener.onBackBtnClicked();
            }
        } else if (id == R.id.alivc_big_interactive_class_ll_menu) {
            if (menuBtnListener != null) {
                menuBtnListener.onMenuBtnClicked(v.getTag() == null ? -1 : (Integer) v.getTag());
            }
        }

    }

    public void setTitle(int resId) {
        if (resId <= 0 || mTvTitle == null) {
            return;
        }
        mTvTitle.setText(resId);
    }

    public void setMenuBtnText(CharSequence s) {
        if (TextUtils.isEmpty(s) || mTvMenuName == null) {
            return;
        }

        mTvMenuName.setVisibility(VISIBLE);
        mTvMenuName.setText(s);
    }

    public void setMenuIcon(Bitmap bitmap) {
        if (null == bitmap || mIvIconMenu == null) {
            return;
        }
        mIvIconMenu.setVisibility(VISIBLE);
        mIvIconMenu.setImageBitmap(bitmap);
    }

    public void setMenuBtnText(int resId) {
        if (resId <= 0 || mTvMenuName == null) {
            return;
        }
        setMenuBtnEnable(true);
        mTvMenuName.setVisibility(VISIBLE);
        mTvMenuName.setText(resId);
    }

    public void setMenuIcon(int resId) {
        if (resId <= 0 || mIvIconMenu == null) {
            return;
        }
        setMenuBtnEnable(true);
        mIvIconMenu.setVisibility(VISIBLE);
        mIvIconMenu.setImageResource(resId);
    }

    public void setMenuBackground(int resId) {
        if (resId <= 0 || mRlContent == null) {
            return;
        }
        mLlMenu.setBackgroundResource(resId);
    }

    public void setBackground(int resId) {
        if (resId <= 0 || mRlContent == null) {
            return;
        }
        mRlContent.setBackgroundResource(resId);
    }

    public void setBackground(Drawable drawable) {
        if (drawable == null || mRlContent == null) {
            return;
        }
        mRlContent.setBackground(drawable);
    }

    public void setTitleTextColor(int color) {
        if (mTvTitle != null) {
            mTvTitle.setTextColor(color);
        }
    }

    public void setMenuBtnId(int id) {
        if (mLlMenu != null) {
            mLlMenu.setTag(id);
        }
    }
    public interface BackBtnListener {
        void onBackBtnClicked();
    }

    public interface MenuBtnListener {
        void onMenuBtnClicked(int id);
    }
}
