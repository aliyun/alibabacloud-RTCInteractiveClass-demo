// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupSilencedInfo.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 拉取禁言列表监听
 */
@protocol AIMPubGroupGetSilencedInfoListener

/**
 * 返回成功
 * @param silencedInfo 禁言列表
 */
- (void)onSuccess:(nonnull AIMPubGroupSilencedInfo *)silencedInfo;

/**
 * 返回统一失败结果
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
