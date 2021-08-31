// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMConvStatus.h"
#import "AIMConvType.h"
#import "AIMGroupPermission.h"
#import "AIMGroupSilencedStatus.h"
#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>

/**
 * 会话信息
 */
@interface AIMPubConversation : NSObject
- (nonnull instancetype)
         initWithAppCid:(nonnull NSString *)appCid
                   type:(AIMConvType)type
                 status:(AIMConvStatus)status
                userids:(nonnull NSArray<NSString *> *)userids
              createdAt:(int64_t)createdAt
             modifyTime:(int64_t)modifyTime
               redPoint:(int32_t)redPoint
                  draft:(nonnull NSString *)draft
       muteNotification:(BOOL)muteNotification
                topRank:(int64_t)topRank
              extension:
                  (nonnull NSDictionary<NSString *, NSString *> *)extension
          userExtension:
              (nonnull NSDictionary<NSString *, NSString *> *)userExtension
         localExtension:
             (nonnull NSDictionary<NSString *, NSString *> *)localExtension
             hasLastMsg:(BOOL)hasLastMsg
                lastMsg:(nonnull AIMPubMessage *)lastMsg
               joinTime:(int64_t)joinTime
               ownerUid:(nonnull NSString *)ownerUid
                  title:(nonnull NSString *)title
                   icon:(nonnull NSString *)icon
            memberCount:(int32_t)memberCount
             silenceAll:(BOOL)silenceAll
         silencedStatus:(AIMGroupSilencedStatus)silencedStatus
        silencedEndtime:(int64_t)silencedEndtime
      memberPermissions:
          (nonnull NSArray<AIMGroupPermission *> *)memberPermissions
    readReceiptsEnabled:(BOOL)readReceiptsEnabled;
+ (nonnull instancetype)
    AIMPubConversationWithAppCid:(nonnull NSString *)appCid
                            type:(AIMConvType)type
                          status:(AIMConvStatus)status
                         userids:(nonnull NSArray<NSString *> *)userids
                       createdAt:(int64_t)createdAt
                      modifyTime:(int64_t)modifyTime
                        redPoint:(int32_t)redPoint
                           draft:(nonnull NSString *)draft
                muteNotification:(BOOL)muteNotification
                         topRank:(int64_t)topRank
                       extension:
                           (nonnull NSDictionary<NSString *, NSString *> *)
                               extension
                   userExtension:
                       (nonnull NSDictionary<NSString *, NSString *> *)
                           userExtension
                  localExtension:
                      (nonnull NSDictionary<NSString *, NSString *> *)
                          localExtension
                      hasLastMsg:(BOOL)hasLastMsg
                         lastMsg:(nonnull AIMPubMessage *)lastMsg
                        joinTime:(int64_t)joinTime
                        ownerUid:(nonnull NSString *)ownerUid
                           title:(nonnull NSString *)title
                            icon:(nonnull NSString *)icon
                     memberCount:(int32_t)memberCount
                      silenceAll:(BOOL)silenceAll
                  silencedStatus:(AIMGroupSilencedStatus)silencedStatus
                 silencedEndtime:(int64_t)silencedEndtime
               memberPermissions:
                   (nonnull NSArray<AIMGroupPermission *> *)memberPermissions
             readReceiptsEnabled:(BOOL)readReceiptsEnabled;

@property(nonatomic, nonnull) NSString *appCid;

/**
 * type=1单聊
 */
@property(nonatomic) AIMConvType type;

/**
 * 会话状态，比如是否可见
 */
@property(nonatomic) AIMConvStatus status;

/**
 * 单聊双方的uid（群聊的uid由单独接口提供）
 */
@property(nonatomic, nonnull) NSArray<NSString *> *userids;

/**
 * 创建时间
 */
@property(nonatomic) int64_t createdAt;

/**
 * 修改时间（可用于会话列表排序，目前会变更modify_time的是lastmsg变更和置顶）
 */
@property(nonatomic) int64_t modifyTime;

/**
 * 未读消息数
 */
@property(nonatomic) int32_t redPoint;

/**
 * 草稿
 */
@property(nonatomic, nonnull) NSString *draft;

/**
 * 是否免打扰
 */
@property(nonatomic) BOOL muteNotification;

/**
 * 置顶 （>0表示置顶，越大越靠前）
 */
@property(nonatomic) int64_t topRank;

/**
 * 扩展信息
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

/**
 * user扩展信息
 */
@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *userExtension;

/**
 * 本地扩展信息
 */
@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *localExtension;

/**
 * 会话是否有最后一条消息
 */
@property(nonatomic) BOOL hasLastMsg;

/**
 * 会话最后一条消息（如果其中mid为空，则没有最后一条消息）
 */
@property(nonatomic, nonnull) AIMPubMessage *lastMsg;

/**
 * 会话加入时间
 */
@property(nonatomic) int64_t joinTime;

/**
 * 群主uid
 */
@property(nonatomic, nonnull) NSString *ownerUid;

/**
 * 群标题
 */
@property(nonatomic, nonnull) NSString *title;

/**
 * 群头像
 */
@property(nonatomic, nonnull) NSString *icon;

/**
 * 群人数
 */
@property(nonatomic) int32_t memberCount;

/**
 * 群禁言
 */
@property(nonatomic) BOOL silenceAll;

/**
 * 禁言状态
 */
@property(nonatomic) AIMGroupSilencedStatus silencedStatus;

/**
 * 禁言截止时间（ms）
 */
@property(nonatomic) int64_t silencedEndtime;

/**
 * 群权限群成员权限
 */
@property(nonatomic, nonnull) NSArray<AIMGroupPermission *> *memberPermissions;

/**
 * 是否支持已读回执
 */
@property(nonatomic) BOOL readReceiptsEnabled;

@end
