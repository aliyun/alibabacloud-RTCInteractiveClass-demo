// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSAuthToken.h"
#import <Foundation/Foundation.h>

/**
 * 通知获取到Auth token回调
 */
@interface DPSAuthTokenGotCallback : NSObject

/**
 * 通知DPSEngine token获取成功
 */
- (void)onSuccess:(nonnull DPSAuthToken *)authToken;

/**
 * 通知DPSEngine token获取失败
 */
- (void)onFailure:(int32_t)errorCode errorMsg:(nonnull NSString *)errorMsg;

@end
