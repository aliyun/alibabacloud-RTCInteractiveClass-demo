// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息发送状态
 */
typedef NS_ENUM(NSInteger, AIMMsgSendStatus) {
  /**
   * 未知
   */
  AIMMsgSendStatusSendStatusUnknown = -1,
  /**
   * 消息发送成功
   */
  AIMMsgSendStatusSendStatusSentSuccess = 0,
  /**
   * 消息发送中
   */
  AIMMsgSendStatusSendStatusSending = 1,
  /**
   * 消息发送失败
   */
  AIMMsgSendStatusSendStatusSendFail = 2,
};
