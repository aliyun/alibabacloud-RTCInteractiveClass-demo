// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 通过mid获取消息,本地不存在到服务端拉取监听
 */
@protocol AIMPubMsgGetMsgListener

/**
 * 处理成功，返回连续的消息对象
 * @param msg 发送成功的消息
 */
- (void)onSuccess:(nonnull AIMPubMessage *)msg;

/**
 * 发送错误
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
