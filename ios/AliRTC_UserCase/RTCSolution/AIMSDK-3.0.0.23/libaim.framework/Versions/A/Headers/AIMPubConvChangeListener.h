// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMConvTypingCommand.h"
#import "AIMConvTypingMessageContent.h"
#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>

/**
 * 会话变更（增量）
 */
@protocol AIMPubConvChangeListener

/**
 * 会话状态变更
 * @param convs 全量的会话结构
 */
- (void)onConvStatusChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话最后一条消息变更
 * @param convs 全量的会话结构
 * 特殊场景:消息撤回时,last_msg中只有recall和mid有效。
 */
- (void)onConvLastMessageChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话未读消息数变更
 * @param convs 全量的会话结构
 */
- (void)onConvUnreadCountChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话extension变更
 * @param convs 全量的会话结构
 */
- (void)onConvExtensionChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话local extension变更
 * @param convs 全量的会话结构
 */
- (void)onConvLocalExtensionChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话user extension变更
 * @param convs 全量的会话结构
 */
- (void)onConvUserExtensionChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话是否通知的状态变更
 * @param convs 全量的会话结构
 */
- (void)onConvNotificationChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话置顶状态变更
 * @param convs 全量的会话结构
 */
- (void)onConvTopChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 会话草稿变更
 * @param convs 全量的会话结构
 */
- (void)onConvDraftChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 接收到正在输入事件
 * @param appCid  	会话id
 * @param command   TypingCommand
 * @param type TypingMessageContent
 */
- (void)onConvTypingEvent:(nonnull NSString *)appCid
                  command:(AIMConvTypingCommand)command
                     type:(AIMConvTypingMessageContent)type;

/**
 * 会话消息被清空
 * @param convs 有效字段appCid
 */
- (void)onConvClearMessage:(nonnull NSArray<AIMPubConversation *> *)convs;

@end
