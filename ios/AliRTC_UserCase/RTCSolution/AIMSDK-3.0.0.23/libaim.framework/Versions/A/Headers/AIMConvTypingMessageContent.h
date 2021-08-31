// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 会话Typing类型
 */
typedef NS_ENUM(NSInteger, AIMConvTypingMessageContent) {
  AIMConvTypingMessageContentConvTypingMessageTypeUnknown = 0,
  AIMConvTypingMessageContentConvTypingMessageTypeText = 1,
  AIMConvTypingMessageContentConvTypingMessageTypeAudio = 2,
};
