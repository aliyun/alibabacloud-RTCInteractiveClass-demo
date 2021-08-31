// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 消息重发回调
 */
@protocol AIMPubMsgReSendMsgListener

/**
 * 发送进度（图片、视频、文件）progress: 0.0~1.0
 * @param progress 进度 0.0~1.0
 */
- (void)onProgress:(double)progress;

/**
 * 处理成功
 * @param msg 发送成功的消息
 */
- (void)onSuccess:(nonnull AIMPubMessage *)msg;

/**
 * 处理失败，返回失败原因
 * @param error 失败信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
