// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>
@class DPSPubManager;

/**
 * DPSManager 创建监听
 */
@protocol DPSPubManagerCreateListener

/**
 * DPSManager 创建成功
 */
- (void)onSuccess:(nullable DPSPubManager *)manager;

/**
 * DPSManager 创建失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
