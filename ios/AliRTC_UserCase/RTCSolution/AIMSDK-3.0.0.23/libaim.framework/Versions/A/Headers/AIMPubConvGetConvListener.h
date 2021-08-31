// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 获取会话列表监听
 */
@protocol AIMPubConvGetConvListener

/**
 * 获取成功
 */
- (void)onSuccess:(nonnull NSArray<AIMPubConversation *> *)result;

/**
 * 获取失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
