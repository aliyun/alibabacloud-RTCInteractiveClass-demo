// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 *拉取单个群成员
 */
@protocol AIMPubGroupGetMembersListener

/**
 * 返回本地群成员
 * @param member 本地群成员
 */
- (void)onLocal:(nonnull NSArray<AIMPubGroupMember *> *)member;

/**
 * 返回服务端数据
 * @param member 服务端数据
 */
- (void)onRefresh:(nonnull NSArray<AIMPubGroupMember *> *)member;

/**
 * 失败结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
