// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupMemberRoleType.h"
#import <Foundation/Foundation.h>

/**
 * 群成员角色
 */
@interface AIMGroupMemberRole : NSObject
- (nonnull instancetype)initWithRole:(AIMGroupMemberRoleType)role
                          customRole:(int32_t)customRole;
+ (nonnull instancetype)AIMGroupMemberRoleWithRole:(AIMGroupMemberRoleType)role
                                        customRole:(int32_t)customRole;

/**
 * 角色类型
 */
@property(nonatomic) AIMGroupMemberRoleType role;

/**
 * 当 role 为业务自定义类型时，使用该字段获取
 */
@property(nonatomic) int32_t customRole;

@end
