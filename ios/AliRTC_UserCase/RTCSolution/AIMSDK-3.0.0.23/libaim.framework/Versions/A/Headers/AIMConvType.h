// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 会话类型
 */
typedef NS_ENUM(NSInteger, AIMConvType) {
  /**
   * 未知类型
   */
  AIMConvTypeConvTypeUnknow = -1,
  /**
   * 单聊
   */
  AIMConvTypeConvTypeSingle = 1,
  /**
   * 群聊
   */
  AIMConvTypeConvTypeGroup = 2,
};
