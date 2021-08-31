// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import "AIMPubGroupAnnouncement.h"
#import "AIMPubGroupRoleChangedNotify.h"
#import <Foundation/Foundation.h>

/**
 * 群变更（增量）
 */
@protocol AIMPubGroupChangeListener

/**
 * title变更
 * @param convs 全量的会话结构
 */
- (void)onGroupTitleChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * icon变更
 * @param convs 全量的会话结构
 */
- (void)onGroupIconChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群成员数变更
 * @param convs 全量的会话结构
 */
- (void)onGroupMemberCountChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群主变更
 * @param convs 全量的会话结构
 */
- (void)onGroupOwnerChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群禁言状态变更
 * @param convs 全量的会话结构
 */
- (void)onGroupSilenceAllChanged:(nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群禁言黑白名单状态变更
 * @param convs 全量的会话结构
 */
- (void)onGroupSilencedStatusChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群禁言截止时间变更
 * @param convs 全量的会话结构
 */
- (void)onGroupSilencedEndtimeChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群成员角色变更
 * @param convs 全量的会话结构
 */
- (void)onGroupMemberRoleChanged:(nonnull AIMPubGroupRoleChangedNotify *)param;

/**
 * 群成员权限变更
 * @param convs 全量的会话结构
 */
- (void)onGroupMemberPermissionsChanged:
    (nonnull NSArray<AIMPubConversation *> *)convs;

/**
 * 群解散
 * @param appCids  解散的会话appCid集合
 */
- (void)onGroupDismissed:(nonnull NSArray<NSString *> *)appCids;

/**
 * 被移除
 * @param appCids  解散的会话appCid集合
 */
- (void)onGroupKicked:(nonnull NSArray<NSString *> *)appCids;

/**
 * 群公告变更
 * @param cid 群公告变更的cid
 * @param announcement 公告变更内容
 */
- (void)onGroupAnnouncementChanged:(nonnull NSString *)appCid
                      announcement:
                          (nonnull AIMPubGroupAnnouncement *)announcement;

@end
