// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupAnnouncement.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 获取群公告的回调
 */
@protocol AIMPubGroupGetAnnouncementListener

/**
 * 成功回调
 */
- (void)onSuccess:(nonnull AIMPubGroupAnnouncement *)announcement;

/**
 * 失败回调
 * @param error 错误信息
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
