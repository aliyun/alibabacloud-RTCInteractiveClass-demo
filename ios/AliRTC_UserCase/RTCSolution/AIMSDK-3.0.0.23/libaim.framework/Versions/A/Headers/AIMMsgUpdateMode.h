// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 本地消息更新模式
 */
typedef NS_ENUM(NSInteger, AIMMsgUpdateMode) {
  /**
   * 仅更新biz_tag
   */
  AIMMsgUpdateModeUpdateBizTag = 0,
  /**
   * 仅更新biz_text
   */
  AIMMsgUpdateModeUpdateBizText = 1,
  /**
   * 全部更新
   */
  AIMMsgUpdateModeUpdateAll = 2,
};
