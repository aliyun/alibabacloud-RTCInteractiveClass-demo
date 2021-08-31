// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 会话状态
 */
typedef NS_ENUM(NSInteger, AIMConvStatus) {
  /**
   * 未知类型
   */
  AIMConvStatusConvStatusUnknow = -1,
  /**
   * 隐藏
   */
  AIMConvStatusConvStatusHide = 0,
  /**
   * 正常状态，一般会话都在该状态
   */
  AIMConvStatusConvStatusNormal = 1,
  /**
   * 会话处于离线状态，未同步入云端
   */
  AIMConvStatusConvStatusOffline = 2,
  /**
   * 群会话被踢
   */
  AIMConvStatusConvStatusKicked = 3,
  /**
   * 群会话被解散
   */
  AIMConvStatusConvStatusDismissed = 4,
};
