// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
@class DPSPushAckStatus;

/**
 * RPC push监听
 */
@protocol DPSPushListener

/**
 * @brief 推送处理
 * @param body   消息体内容
 * @param ack    本次推送回复服务端处理状态（服务端依赖此回复进行下次推送）
 */
- (void)onPush:(nonnull NSData *)body ack:(nullable DPSPushAckStatus *)ack;

@end
