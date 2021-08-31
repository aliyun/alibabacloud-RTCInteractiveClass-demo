// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupMemberRole.h"
#import <Foundation/Foundation.h>

/**
 * 群成员角色变更
 */
@interface AIMPubGroupRoleChangedNotify : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                  role:(nonnull AIMGroupMemberRole *)role
                                  uids:(nonnull NSArray<NSString *> *)uids;
+ (nonnull instancetype)
    AIMPubGroupRoleChangedNotifyWithAppCid:(nonnull NSString *)appCid
                                      role:(nonnull AIMGroupMemberRole *)role
                                      uids:(nonnull NSArray<NSString *> *)uids;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 角色
 */
@property(nonatomic, nonnull) AIMGroupMemberRole *role;

/**
 * 变更成员的uid
 */
@property(nonatomic, nonnull) NSArray<NSString *> *uids;

@end
