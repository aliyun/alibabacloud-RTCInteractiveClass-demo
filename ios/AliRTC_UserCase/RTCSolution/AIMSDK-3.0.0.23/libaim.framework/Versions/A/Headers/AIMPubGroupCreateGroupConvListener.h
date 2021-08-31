// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 创建群聊监听
 */
@protocol AIMPubGroupCreateGroupConvListener

/**
 * 返回成功
 * @param conv 创建的conversation
 */
- (void)onSuccess:(nonnull AIMPubConversation *)conv;

/**
 * 返回统一失败结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
