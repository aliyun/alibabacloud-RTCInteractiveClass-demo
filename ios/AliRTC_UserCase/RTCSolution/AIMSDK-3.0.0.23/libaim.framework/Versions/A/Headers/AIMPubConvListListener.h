// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>

/**
 * 全量变更的监听器
 */
@protocol AIMPubConvListListener

/**
 * 新增会话
 * @param convs 新增的会话集合
 */
- (void)onAddedConversations:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 删除会话
 * @param appCids 删除的会话appCid集合
 */
- (void)onRemovedConversations:(nonnull NSArray<NSString *> *)appCids;

/**
 * 所有会话被更新替换
 * @param convs 更新后的会话集合
 */
- (void)onRefreshedConversations:(nonnull NSArray<AIMPubConversation *> *)convs;

@end
