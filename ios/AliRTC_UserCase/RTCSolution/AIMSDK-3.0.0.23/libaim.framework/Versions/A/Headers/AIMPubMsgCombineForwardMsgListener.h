// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 合并转发发送消息监听
 */
@protocol AIMPubMsgCombineForwardMsgListener

/**
 * 处理成功
 */
- (void)onSuccess:(nonnull AIMPubMessage *)msg;

/**
 * 处理失败，返回失败原因
 * @param error 失败信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
