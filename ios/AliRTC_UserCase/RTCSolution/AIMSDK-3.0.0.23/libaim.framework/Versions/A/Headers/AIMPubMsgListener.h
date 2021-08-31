// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import "AIMPubNewMessage.h"
#import <Foundation/Foundation.h>

/**
 * 消息变更监听
 */
@protocol AIMPubMsgListener

/**
 * 消息新增
 * 发送消息或收到推送消息时，触发该回调
 * 当从服务端拉取历史消息时，不会触发该回调
 * @param msgs 新增消息
 */
- (void)onAddedMessages:(nonnull NSArray<AIMPubNewMessage *> *)msgs;

/**
 * 消息删除
 * @param msgs 变更消息
 */
- (void)onRemovedMessages:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 当消息数据库内有消息添加时，触发该回调
 * 包括发送，推送及拉取历史消息
 * 注意：
 * 1. 不保证传入消息 msgs 的顺序
 * 2. onStored 回调的顺序也不保证消息组间的顺序
 * @param msgs 变更消息
 */
- (void)onStoredMessages:(nonnull NSArray<AIMPubMessage *> *)msgs;

@end
