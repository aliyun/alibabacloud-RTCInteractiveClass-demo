// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupMember.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 拉取群成员
 */
@protocol AIMPubGroupListAllMemberListener

/**
 * 返回本地群成员
 * @param members 本地群成员列表
 */
- (void)onLocal:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 返回服务端数据
 * @param members 服务端数据
 */
- (void)onRefresh:(nonnull NSArray<AIMPubGroupMember *> *)members;

/**
 * 失败结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
