// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMFullLinkPointBase.h"
#import "AIMFullLinkPointConv.h"
#import "AIMFullLinkPointMsg.h"
#import <Foundation/Foundation.h>

@protocol AIMTraceListener

/**
 * 上报消息链路埋点
 */
- (void)onCommitMsgPoint:(nonnull AIMFullLinkPointMsg *)point;

/**
 * 上报会话链路埋点
 */
- (void)onCommitConvPoint:(nonnull AIMFullLinkPointConv *)point;

/**
 * 上报基础链路埋点
 */
- (void)onCommitBasePoint:(nonnull AIMFullLinkPointBase *)point;

@end
