// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

/**
 * 被踢出监听
 */
@protocol DPSKickoutListener

/**
 * 成功
 */
- (void)onSuccess;

/**
 * 失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
