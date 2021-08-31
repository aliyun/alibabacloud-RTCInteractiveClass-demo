// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgSendMediaProgress.h"
#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>

/**
 * 消息变更监听
 */
@protocol AIMPubMsgChangeListener

/**
 * 消息未读数变更，作为消息的发送者，表示单聊对方或者群聊群内其他成员
 * 没有读取该条消息的人数，如果未读数是0，表示所有人已读
 * @param msgs 发生变化的消息(有效字段appCid/mid/unread_count）
 */
- (void)onMsgUnreadCountChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息未读数变更，作为消息的接收者，多端同步消息已读状态
 * @param msgs 发生变化的消息(有效字段appCid/mid/is_read）
 */
- (void)onMsgReadStatusChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息扩展信息变更
 * @param msgs 发生变化的消息(有效字段appCid/mid/extension)
 */
- (void)onMsgExtensionChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息本地扩展信息变更
 * @param msgs 发生变化的消息(有效字段appCid/localid/local_extension)
 */
- (void)onMsgLocalExtensionChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 业务方自定义消息扩展信息变更
 * @param msgs 发生变化的消息(有效字段appCid/mid/user_extension字段)
 */
- (void)onMsgUserExtensionChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息被撤回
 * @param msgs 发生变化的消息(有效字段appCid/mid/is_recall字段)
 */
- (void)onMsgRecalled:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息状态变更，比如：消息状态从发送中变成了发送失败
 * @param msgs
 * 发生变化的消息(有效字段status/mid/created_at/unread_count/receiver_count/content)
 */
- (void)onMsgStatusChanged:(nonnull NSArray<AIMPubMessage *> *)msgs;

/**
 * 消息发送进度变更
 * @param progress 发送进度
 */
- (void)onMsgSendMediaProgressChanged:
    (nonnull AIMMsgSendMediaProgress *)progress;

@end
