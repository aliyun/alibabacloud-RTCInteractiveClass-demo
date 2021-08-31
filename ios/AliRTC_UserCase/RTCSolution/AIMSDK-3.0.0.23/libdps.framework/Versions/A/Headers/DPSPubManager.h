// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
@class DPSAuthService;
@class DPSRpcService;
@class DPSSyncService;
@class DPSUtService;

@interface DPSPubManager : NSObject

/**
 * 获取该DPSManager对应的DPSUserID
 */
- (nonnull NSString *)getUserId;

/**
 * 获取登录授权Service
 */
- (nullable DPSAuthService *)getAuthService;

/**
 * 获取同步协议相关Service
 */
- (nullable DPSSyncService *)getSyncService;

/**
 * 获取Rpc相关Service
 */
- (nullable DPSRpcService *)getRpcService;

/**
 * 获取打点相关Service
 */
- (nullable DPSUtService *)getUtService;

@end
