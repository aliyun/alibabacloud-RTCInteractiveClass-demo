// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 会话Typing状态
 */
typedef NS_ENUM(NSInteger, AIMConvTypingCommand) {
  AIMConvTypingCommandConvTypingCommandUnknown = -1,
  AIMConvTypingCommandConvTypingCommandTyping = 0,
  AIMConvTypingCommandConvTypingCommandCancel = 1,
};
