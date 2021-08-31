// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

/**
 * 设置事件监听器
 */
@protocol DPSPubEngineListener

/**
 * DB错误回调, 在数据库无法继续工作时发生此回调
 * @param uid 用户id
 * @param error 错误类型
 * error.code类型:
 * DB_FULL: 磁盘满，需提示用户进行磁盘清理操作，否则功能异常
 * DB_MAILFORMED:
 * 数据库异常，需在下次启动前调用engine.ResetUserData接口进行数据清理重置
 * DB_NO_MEMORY: 内存不足
 */
- (void)onDBError:(nonnull NSString *)uid error:(nonnull DPSError *)error;

@end
