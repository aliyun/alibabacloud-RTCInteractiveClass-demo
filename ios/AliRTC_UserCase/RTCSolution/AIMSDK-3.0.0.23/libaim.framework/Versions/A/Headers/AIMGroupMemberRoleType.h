// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群成员角色类型
 */
typedef NS_ENUM(NSInteger, AIMGroupMemberRoleType) {
  /**
   * 未知类型
   */
  AIMGroupMemberRoleTypeGroupMemberRoleTypeUnknow = 0,
  /**
   * 群主
   */
  AIMGroupMemberRoleTypeGroupMemberRoleTypeOwner = 1,
  /**
   * 管理员
   */
  AIMGroupMemberRoleTypeGroupMemberRoleTypeAdmin = 2,
  /**
   * 普通
   */
  AIMGroupMemberRoleTypeGroupMemberRoleTypeNormal = 3,
  /**
   * 自定义角色
   */
  AIMGroupMemberRoleTypeGroupMemberRoleTypeCustom = 100,
};
