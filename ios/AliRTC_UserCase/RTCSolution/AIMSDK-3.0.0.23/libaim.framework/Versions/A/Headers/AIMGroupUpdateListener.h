// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 群信息更新监听
 */
@protocol AIMGroupUpdateListener

/**
 * 返回成功
 */
- (void)onSuccess;

/**
 * 返回统一错误结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
