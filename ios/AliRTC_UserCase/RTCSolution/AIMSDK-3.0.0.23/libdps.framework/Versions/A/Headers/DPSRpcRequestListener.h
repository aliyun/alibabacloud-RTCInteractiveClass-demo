// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

/**
 * RPC 请求监听
 */
@protocol DPSRpcRequestListener

- (void)onSuccess:(nonnull NSDictionary<NSString *, NSString *> *)kvParams responseBody:(nonnull NSData *)responseBody;

- (void)onFailure:(nonnull DPSError *)error;

@end
