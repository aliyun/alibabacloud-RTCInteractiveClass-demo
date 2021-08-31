// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 添加的消息的类型
 */
typedef NS_ENUM(NSInteger, AIMMsgSourceType) {
  /**
   * 未知
   */
  AIMMsgSourceTypeSourceTypeUnknown = -1,
  /**
   * 发送消息
   */
  AIMMsgSourceTypeSourceTypeSend = 0,
  /**
   * 拉取消息
   */
  AIMMsgSourceTypeSourceTypePullOnline = 1,
  /**
   * 接收在线消息
   */
  AIMMsgSourceTypeSourceTypeRecvOnline = 2,
  /**
   * 接收离线消息
   */
  AIMMsgSourceTypeSourceTypeRecvOffline = 3,
};
