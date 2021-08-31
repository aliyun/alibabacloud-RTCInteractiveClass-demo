// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 异步操作是否成功的回调
 */
@protocol AIMSuccessListener

/**
 * 异步操作成功
 */
- (void)onSuccess;

/**
 * 异步操作失败
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
