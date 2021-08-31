// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupPermission.h"
#import <Foundation/Foundation.h>

/**
 * 群权限,需要业务方自定义permission_group,用来控制群权限（如是否可以加人，改头像，atall）
 */
@interface AIMPubGroupSetMemberPermission : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                      memberPermission:
                          (nonnull AIMGroupPermission *)memberPermission;
+ (nonnull instancetype)
    AIMPubGroupSetMemberPermissionWithAppCid:(nonnull NSString *)appCid
                            memberPermission:
                                (nonnull AIMGroupPermission *)memberPermission;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 权限名
 */
@property(nonatomic, nonnull) AIMGroupPermission *memberPermission;

@end
