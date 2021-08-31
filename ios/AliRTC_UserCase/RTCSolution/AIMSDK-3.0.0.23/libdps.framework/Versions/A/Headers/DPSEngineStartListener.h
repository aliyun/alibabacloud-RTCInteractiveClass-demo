// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

/**
 * Engine 启动监听
 */
@protocol DPSEngineStartListener

/**
 * Enigne 启动成功
 */
- (void)onSuccess;

/**
 * Engine 启动失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
