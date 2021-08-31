// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 删除消息监听
 */
@protocol AIMMsgDeleteMsgListener

/**
 * 成功
 */
- (void)onSuccess;

/**
 * 失败
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
