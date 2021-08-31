// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 更新本地消息biz_info监听
 */
@protocol AIMMsgUpdateLocalMsgsBizInfoListener

/**
 * 更新biz_info成功
 */
- (void)onSuccess;

/**
 * 更新失败
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
