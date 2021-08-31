// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupMemberRole.h"
#import <Foundation/Foundation.h>

@interface AIMPubGroupMemberUpdateRole : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                  role:(nonnull AIMGroupMemberRole *)role
                                  uids:(nonnull NSArray<NSString *> *)uids;
+ (nonnull instancetype)
    AIMPubGroupMemberUpdateRoleWithAppCid:(nonnull NSString *)appCid
                                     role:(nonnull AIMGroupMemberRole *)role
                                     uids:(nonnull NSArray<NSString *> *)uids;

/**
 *会话appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 *更新的角色
 */
@property(nonatomic, nonnull) AIMGroupMemberRole *role;

/**
 *用户id
 */
@property(nonatomic, nonnull) NSArray<NSString *> *uids;

@end
