// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 *鉴权场景
 */
typedef NS_ENUM(NSInteger, AIMMediaAuthScene) {
  /**
   * 未知类型
   */
  AIMMediaAuthSceneMacUnknown = 0,
  /**
   *会话头像
   */
  AIMMediaAuthSceneMacGroupAvator = 1,
  /**
   *会话消息
   */
  AIMMediaAuthSceneMacMsg = 2,
};
