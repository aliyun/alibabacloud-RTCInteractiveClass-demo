// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 导入会话列表监听
 */
@protocol AIMConvServiceCompleteListener

/**
 * 导入成功
 */
- (void)onSuccess;

/**
 * 导入失败
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
