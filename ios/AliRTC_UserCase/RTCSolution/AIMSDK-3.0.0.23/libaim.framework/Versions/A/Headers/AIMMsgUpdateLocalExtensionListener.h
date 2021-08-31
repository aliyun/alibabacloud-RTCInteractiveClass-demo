// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 更新本地消息extension监听
 */
@protocol AIMMsgUpdateLocalExtensionListener

/**
 * 更新成功
 */
- (void)onSuccess;

/**
 * 更新失败
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
