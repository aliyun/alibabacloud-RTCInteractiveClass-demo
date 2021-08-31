// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 创建单聊会话监听
 */
@protocol AIMPubConvCreateSingleConvListener

/**
 * 创建成功
 */
- (void)onSuccess:(nonnull AIMPubConversation *)conv;

/**
 * 创建失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
