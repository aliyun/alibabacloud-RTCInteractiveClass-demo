// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 多媒体上传状态监听
 */
@protocol AIMDownloadFileListener

/**
 *  创建回调
 */
- (void)onCreate:(nonnull NSString *)taskId;

/**
 * 开始处理回调
 */
- (void)onStart;

/**
 * 处理进度回调
 */
- (void)onProgress:(int64_t)currentSize totalSize:(int64_t)totalSize;

/**
 * 处理成功回调（path：保存路径）
 */
- (void)onSuccess:(nonnull NSString *)path;

/**
 * 处理失败回调
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
