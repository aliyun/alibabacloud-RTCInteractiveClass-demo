// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 多媒体上传状态监听
 */
@protocol AIMUploadFileListener

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
 * 处理成功回调（mediaId：多媒体id）
 */
- (void)onSuccess:(nonnull NSString *)mediaId;

/**
 * 处理失败回调
 */
- (void)onFailure:(nonnull DPSError *)error;

@end
