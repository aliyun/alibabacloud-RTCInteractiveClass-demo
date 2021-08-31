// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

/**
 * ResetUserData 用户目录重置监听
 */
@protocol DPSResetUserDataListener

/**
 * 重置成功
 */
- (void)onSuccess;

/**
 * 重置失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
