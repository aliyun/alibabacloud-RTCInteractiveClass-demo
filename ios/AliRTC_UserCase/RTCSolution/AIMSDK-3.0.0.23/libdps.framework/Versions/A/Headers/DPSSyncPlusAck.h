// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@interface DPSSyncPlusAck : NSObject

/**
 * 业务回调掉成功
 */
- (void)onSuccess;

/**
 * 业务回调掉失败
 * @param msg 失败原因，可以为空
 */
- (void)onFailed:(nonnull NSString *)msg;

@end
