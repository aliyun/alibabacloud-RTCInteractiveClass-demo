// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 添加群成员
 */
@protocol AIMPubGroupAddMembersListener

/**
 * 返回成功
 * @param members 成功添加的成员列表
 */
- (void)onSuccess:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 返回错误
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
