// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 更新群成员角色回调
 */
@protocol AIMPubGroupMemberRoleUpdateListener

/**
 * 返回成功
 * @param members 成功更新的成员列表
 */
- (void)onSuccess:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 返回错误
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
