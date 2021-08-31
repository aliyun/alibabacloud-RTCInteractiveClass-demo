// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgReadStatus.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 读取消息已读状态
 */
@protocol AIMPubMsgListMsgsReadStatus

/**
 * 获取成功
 * @param status 消息已读状态
 */
- (void)onSuccess:(nonnull AIMPubMsgReadStatus *)status;

/**
 * 返回错误
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
