// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>

/**
 * 会话成员增量变更的监听器
 */
@protocol AIMPubGroupMemberChangeListener

/**
 * 新增成员
 * @param members 成员
 */
- (void)onAddedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 删除成员
 * @param members 成员
 */
- (void)onRemovedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 成员变更
 * @param members 成员
 */
- (void)onUpdatedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members;

@end
