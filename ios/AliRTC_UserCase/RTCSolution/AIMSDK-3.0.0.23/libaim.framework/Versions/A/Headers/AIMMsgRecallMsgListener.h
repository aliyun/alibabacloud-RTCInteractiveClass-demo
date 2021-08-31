// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 撤回消息监听
 */
@protocol AIMMsgRecallMsgListener

/**
 * 撤回成功
 */
- (void)onSuccess;

/**
 * 撤回失败
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
