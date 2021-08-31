// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 拉取本地群成员列表监听
 */
@protocol AIMPubGroupListLocalMemberListener

/**
 * 返回成功
 * @param members 本地群成员列表
 */
- (void)onSuccess:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 拉取失败
 * 返回统一失败结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
