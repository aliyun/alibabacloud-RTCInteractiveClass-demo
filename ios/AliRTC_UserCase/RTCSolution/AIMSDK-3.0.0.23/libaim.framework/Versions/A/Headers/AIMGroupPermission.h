// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群权限,需要业务方自定义permission_group,用来控制群权限（如是否可以加人，改头像，atall）
 */
@interface AIMGroupPermission : NSObject
- (nonnull instancetype)initWithPermissionGroup:
                            (nonnull NSString *)permissionGroup
                                         status:(int32_t)status;
+ (nonnull instancetype)AIMGroupPermissionWithPermissionGroup:
                            (nonnull NSString *)permissionGroup
                                                       status:(int32_t)status;

/**
 * 权限名
 */
@property(nonatomic, nonnull) NSString *permissionGroup;

/**
 * 0:权限关闭 1:权限开启 2:权限废弃
 */
@property(nonatomic) int32_t status;

@end
