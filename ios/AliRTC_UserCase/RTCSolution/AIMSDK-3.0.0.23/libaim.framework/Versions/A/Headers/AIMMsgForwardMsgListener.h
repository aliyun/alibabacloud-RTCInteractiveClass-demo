// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 转发发送消息监听
 */
@protocol AIMMsgForwardMsgListener

/**
 * 处理成功
 */
- (void)onSuccess;

/**
 * 处理失败，返回失败原因
 * @param error 失败信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
