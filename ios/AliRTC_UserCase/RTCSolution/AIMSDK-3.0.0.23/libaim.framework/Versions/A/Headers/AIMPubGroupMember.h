// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupMemberRole.h"
#import <Foundation/Foundation.h>

/**
 * 群成员信息
 */
@interface AIMPubGroupMember : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
               uid:(nonnull NSString *)uid
              role:(nonnull AIMGroupMemberRole *)role
         createdAt:(int64_t)createdAt
         groupNick:(nonnull NSString *)groupNick
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMPubGroupMemberWithAppCid:(nonnull NSString *)appCid
                            uid:(nonnull NSString *)uid
                           role:(nonnull AIMGroupMemberRole *)role
                      createdAt:(int64_t)createdAt
                      groupNick:(nonnull NSString *)groupNick
                      extension:(nonnull NSDictionary<NSString *, NSString *> *)
                                    extension;

/**
 * 群id
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 用户id
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 * 用户角色
 */
@property(nonatomic, nonnull) AIMGroupMemberRole *role;

/**
 * 创建时间
 */
@property(nonatomic) int64_t createdAt;

/**
 * 群昵称
 */
@property(nonatomic, nonnull) NSString *groupNick;

/**
 *扩展信息
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
