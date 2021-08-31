// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import "AIMPubGroupAnnouncement.h"
#import "AIMPubGroupCreateGroupConvParam.h"
#import "AIMPubGroupJoin.h"
#import "AIMPubGroupKick.h"
#import "AIMPubGroupLeave.h"
#import "AIMPubGroupMember.h"
#import "AIMPubGroupMemberUpdateNick.h"
#import "AIMPubGroupMemberUpdateRole.h"
#import "AIMPubGroupRoleChangedNotify.h"
#import "AIMPubGroupSetMemberPermission.h"
#import "AIMPubGroupSetOwner.h"
#import "AIMPubGroupSilencedInfo.h"
#import "AIMPubGroupUpdateAnnouncement.h"
#import "AIMPubGroupUpdateIcon.h"
#import "AIMPubGroupUpdateSilenceAll.h"
#import "AIMPubGroupUpdateSilencedBlackList.h"
#import "AIMPubGroupUpdateSilencedWhiteList.h"
#import "AIMPubGroupUpdateTitle.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>
@protocol AIMGroupUpdateListener;
@protocol AIMPubGroupAddMembersListener;
@protocol AIMPubGroupChangeListener;
@protocol AIMPubGroupCreateGroupConvListener;
@protocol AIMPubGroupGetAnnouncementListener;
@protocol AIMPubGroupGetMembersListener;
@protocol AIMPubGroupGetSilencedInfoListener;
@protocol AIMPubGroupListAllMemberListener;
@protocol AIMPubGroupListLocalMemberListener;
@protocol AIMPubGroupMemberChangeListener;
@protocol AIMPubGroupMemberNickUpdateListener;
@protocol AIMPubGroupMemberRoleUpdateListener;
@protocol AIMSuccessListener;

/**
 * 最大时间戳
 */
extern int8_t const AIMPubGroupServiceAimMaxGroupMemberCursor;

@interface AIMPubGroupService : NSObject

/**
 * 创建群聊
 * @param param AIMGroupCreateGroupConvParam 结构
 * @param listener 监听器
 */
- (void)createGroupConversation:(nonnull AIMPubGroupCreateGroupConvParam *)param
                       listener:
                           (nullable id<AIMPubGroupCreateGroupConvListener>)
                               listener;

- (void)createGroupConversationWithBlock:
            (nonnull AIMPubGroupCreateGroupConvParam *)param
                               onSuccess:(nullable void (^)(
                                             AIMPubConversation *_Nonnull conv))
                                             onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 更新群的默认title
 * @param param AIMGroupUpdateTitle 结构
 * @param listener 监听器
 */
- (void)updateDefaultTitle:(nonnull AIMPubGroupUpdateTitle *)param
                  listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)updateDefaultTitleWithBlock:(nonnull AIMPubGroupUpdateTitle *)param
                          onSuccess:(nullable void (^)())onSuccess
                          onFailure:(nullable void (^)(
                                        DPSError *_Nonnull error))onFailure;

/**
 * 更新群的icon
 * @param param AIMGroupUpdateIcon 结构
 * @param listener 监听器
 */
- (void)updateIcon:(nonnull AIMPubGroupUpdateIcon *)param
          listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)updateIconWithBlock:(nonnull AIMPubGroupUpdateIcon *)param
                  onSuccess:(nullable void (^)())onSuccess
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 解散群
 * @param appCid 会话appCid
 * @param listener 监听器
 */
- (void)dismiss:(nonnull NSString *)appCid
       listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)dismissWithBlock:(nonnull NSString *)appCid
               onSuccess:(nullable void (^)())onSuccess
               onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 退出群
 * @param param AIMGroupLeave 结构
 * @param listener 监听器
 */
- (void)leave:(nonnull AIMPubGroupLeave *)param
     listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)leaveWithBlock:(nonnull AIMPubGroupLeave *)param
             onSuccess:(nullable void (^)())onSuccess
             onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 拉取本地群成员
 * @param appCid 会话appCid
 * @param cursor 成员游标
 * @param listener 监听器
 */
- (void)listLocalMembers:(nonnull NSString *)appCid
                  cursor:(int64_t)cursor
                   count:(int64_t)count
                listener:
                    (nullable id<AIMPubGroupListLocalMemberListener>)listener;

- (void)listLocalMembersWithBlock:(nonnull NSString *)appCid
                           cursor:(int64_t)cursor
                            count:(int64_t)count
                        onSuccess:
                            (nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull members))onSuccess
                        onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                      onFailure;

/**
 * 拉取群成员
 * @param appCid 会话appCid
 * @param cur_version 成员版本号
 * @param listener 监听器
 */
- (void)listAllMembers:(nonnull NSString *)appCid
              listener:(nullable id<AIMPubGroupListAllMemberListener>)listener;

- (void)
    listAllMembersWithBlock:(nonnull NSString *)appCid
                    onLocal:(nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull members))onLocal
                  onRefresh:(nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull members))onRefresh
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 获取群成员
 * @param appCid 会话appCid
 * @param uids 群成员uid列表
 * @param listener 监听器
 */
- (void)getMembers:(nonnull NSString *)appCid
              uids:(nonnull NSArray<NSString *> *)uids
          listener:(nullable id<AIMPubGroupGetMembersListener>)listener;

- (void)getMembersWithBlock:(nonnull NSString *)appCid
                       uids:(nonnull NSArray<NSString *> *)uids
                    onLocal:(nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull member))onLocal
                  onRefresh:(nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull member))onRefresh
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 添加群成员
 * @param param AIMGroupJoin 结构
 * @param listener 监听器
 */
- (void)addMembers:(nonnull AIMPubGroupJoin *)param
          listener:(nullable id<AIMPubGroupAddMembersListener>)listener;

- (void)addMembersWithBlock:(nonnull AIMPubGroupJoin *)param
                  onSuccess:(nullable void (^)(NSArray<AIMPubGroupMember *>
                                                   *_Nonnull members))onSuccess
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 删除群成员
 * @param param AIMGroupKick 结构
 * @param listener 监听器
 */
- (void)removeMembers:(nonnull AIMPubGroupKick *)param
             listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)removeMembersWithBlock:(nonnull AIMPubGroupKick *)param
                     onSuccess:(nullable void (^)())onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 更新群成员昵称
 * @param param AIMGroupNickChange 结构
 * @param listener 监听器
 */
- (void)updateGroupMemberNick:(nonnull AIMPubGroupMemberUpdateNick *)param
                     listener:(nullable id<AIMPubGroupMemberNickUpdateListener>)
                                  listener;

- (void)
    updateGroupMemberNickWithBlock:(nonnull AIMPubGroupMemberUpdateNick *)param
                         onSuccess:
                             (nullable void (^)(
                                 AIMPubGroupMember *_Nonnull members))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 设置全员禁言
 * 调用权限：群主或群管理员
 * 禁言后仅群主和管理员可发言
 * @param param AIMGroupUpdateSilenceAll 结构
 * @param listener 监听器
 */
- (void)silenceAll:(nonnull AIMPubGroupUpdateSilenceAll *)param
          listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)silenceAllWithBlock:(nonnull AIMPubGroupUpdateSilenceAll *)param
                  onSuccess:(nullable void (^)())onSuccess
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 取消全员禁言
 * 调用权限：群主或群管理员
 * @param param AIMGroupUpdateSilenceAll 结构
 * @param listener 监听器
 */
- (void)cancelSilenceAll:(nonnull AIMPubGroupUpdateSilenceAll *)param
                listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)cancelSilenceAllWithBlock:(nonnull AIMPubGroupUpdateSilenceAll *)param
                        onSuccess:(nullable void (^)())onSuccess
                        onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                      onFailure;

/**
 * 增加白名单用户(在设置全员禁言后，可以设置白名单，白名单中的用户可以发言)
 * 调用权限：群主或群管理员,
 * @param param AIMGroupUpdateSilencedWhiteList 结构
 * @param listener 监听器
 */
- (void)addSilencedWhitelist:(nonnull AIMPubGroupUpdateSilencedWhiteList *)param
                    listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)addSilencedWhitelistWithBlock:
            (nonnull AIMPubGroupUpdateSilencedWhiteList *)param
                            onSuccess:(nullable void (^)())onSuccess
                            onFailure:(nullable void (^)(
                                          DPSError *_Nonnull error))onFailure;

/**
 * 删除白名单用户
 * 调用权限：群主或群管理员
 * @param param AIMGroupUpdateSilencedWhiteList 结构
 * @param listener 监听器
 */
- (void)removeSilencedWhitelist:
            (nonnull AIMPubGroupUpdateSilencedWhiteList *)param
                       listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)removeSilencedWhitelistWithBlock:
            (nonnull AIMPubGroupUpdateSilencedWhiteList *)param
                               onSuccess:(nullable void (^)())onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 增加禁言用户
 * 调用权限：群主或群管理员
 * @param param AIMGroupUpdateSilencedBlackList 结构
 * @param listener 监听器
 */
- (void)addSilencedBlacklist:(nonnull AIMPubGroupUpdateSilencedBlackList *)param
                    listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)addSilencedBlacklistWithBlock:
            (nonnull AIMPubGroupUpdateSilencedBlackList *)param
                            onSuccess:(nullable void (^)())onSuccess
                            onFailure:(nullable void (^)(
                                          DPSError *_Nonnull error))onFailure;

/**
 * 删除禁言用户
 * 调用权限：群主或群管理员
 * @param param AIMGroupUpdateSilencedBlackList 结构
 * @param listener 监听器
 */
- (void)removeSilencedBlacklist:
            (nonnull AIMPubGroupUpdateSilencedBlackList *)param
                       listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)removeSilencedBlacklistWithBlock:
            (nonnull AIMPubGroupUpdateSilencedBlackList *)param
                               onSuccess:(nullable void (^)())onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 拉取禁言列表
 * 调用权限：群主或群管理员
 * @param appCid 群appCid
 * @param listener 监听器
 */
- (void)getSilencedInfo:(nonnull NSString *)appCid
               listener:
                   (nullable id<AIMPubGroupGetSilencedInfoListener>)listener;

- (void)getSilencedInfoWithBlock:(nonnull NSString *)appCid
                       onSuccess:
                           (nullable void (^)(
                               AIMPubGroupSilencedInfo *_Nonnull silencedInfo))
                               onSuccess
                       onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                     onFailure;

/**
 * 转让群主
 * 调用权限：群主或群管理员
 * @param param AIMGroupSetOwner结构
 * @param listener 监听器
 */
- (void)setOwner:(nonnull AIMPubGroupSetOwner *)param
        listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)setOwnerWithBlock:(nonnull AIMPubGroupSetOwner *)param
                onSuccess:(nullable void (^)())onSuccess
                onFailure:
                    (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 设置群权限
 * 调用权限：群主或群管理员
 * @param param AIMGroupSetMemberPermission
 * @param listener 监听器
 */
- (void)setMemberPermission:(nonnull AIMPubGroupSetMemberPermission *)param
                   listener:(nullable id<AIMGroupUpdateListener>)listener;

- (void)
    setMemberPermissionWithBlock:(nonnull AIMPubGroupSetMemberPermission *)param
                       onSuccess:(nullable void (^)())onSuccess
                       onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                     onFailure;

/**
 * 增加群变更的监听器
 * @param listener 监听器
 */
- (void)addGroupChangeListener:(nullable id<AIMPubGroupChangeListener>)listener;

/**
 * 删除群变更的监听器
 * @param listener 监听器
 */
- (void)removeGroupChangeListener:
    (nullable id<AIMPubGroupChangeListener>)listener;

/**
 * 删除所有会话的监听器
 */
- (void)removeAllGroupChangeListener;

/**
 * 注册会话成员增量变更的监听器
 * @param listener 监听器
 */
- (void)addGroupMemberChangeListener:
    (nullable id<AIMPubGroupMemberChangeListener>)listener;

/**
 * 删除会话成员增量变更的监听器
 * @param listener 监听器
 */
- (void)removeGroupMemberChangeListener:
    (nullable id<AIMPubGroupMemberChangeListener>)listener;

/**
 * 删除所有会话成员的监听器
 */
- (void)removeAllGroupMemberChangeListener;

/**
 * 更新群成员角色
 * @param param AIMGroupMemberUpdateRole 结构
 * @param listener 监听器
 */
- (void)updateGroupMemberRole:(nonnull AIMPubGroupMemberUpdateRole *)param
                     listener:(nullable id<AIMPubGroupMemberRoleUpdateListener>)
                                  listener;

- (void)
    updateGroupMemberRoleWithBlock:(nonnull AIMPubGroupMemberUpdateRole *)param
                         onSuccess:
                             (nullable void (^)(NSArray<AIMPubGroupMember *>
                                                    *_Nonnull members))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 更新群公告
 * @param param AIMGroupUpdateAnnouncement 结构
 */
- (void)updateAnnouncement:(nonnull AIMPubGroupUpdateAnnouncement *)param
                  listener:(nullable id<AIMSuccessListener>)listener;

- (void)
    updateAnnouncementWithBlock:(nonnull AIMPubGroupUpdateAnnouncement *)param
                      onSuccess:(nullable void (^)())onSuccess
                      onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                    onFailure;

/**
 * 获取群公告
 * @param cid 需要获取群公告的cid
 * @param listener 获取群公告的回调
 */
- (void)getAnnouncement:(nonnull NSString *)cid
               listener:
                   (nullable id<AIMPubGroupGetAnnouncementListener>)listener;

- (void)getAnnouncementWithBlock:(nonnull NSString *)cid
                       onSuccess:
                           (nullable void (^)(
                               AIMPubGroupAnnouncement *_Nonnull announcement))
                               onSuccess
                       onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                     onFailure;

@end
