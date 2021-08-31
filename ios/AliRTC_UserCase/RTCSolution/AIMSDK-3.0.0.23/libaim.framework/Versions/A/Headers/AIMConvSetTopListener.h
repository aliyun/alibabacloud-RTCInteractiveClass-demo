// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 会话置顶监听
 */
@protocol AIMConvSetTopListener

/**
 * 置顶成功
 */
- (void)onSuccess:(int64_t)topRank;

/**
 * 置顶失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
