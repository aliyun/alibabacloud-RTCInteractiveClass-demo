// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSRpcDataType.h"
#import <Foundation/Foundation.h>

/**
 * RPC请求header
 */
DPS_DECL
@interface DPSRpcRequestHeader : NSObject
- (nonnull instancetype)initWithDataType:(DPSRpcDataType)dataType
                             enableRetry:(BOOL)enableRetry
                               timeoutMs:(int64_t)timeoutMs
                              noNeedAuth:(BOOL)noNeedAuth
                                kvParams:(nonnull NSDictionary<NSString *, NSString *> *)kvParams;
+ (nonnull instancetype)DPSRpcRequestHeaderWithDataType:(DPSRpcDataType)dataType
                                            enableRetry:(BOOL)enableRetry
                                              timeoutMs:(int64_t)timeoutMs
                                             noNeedAuth:(BOOL)noNeedAuth
                                               kvParams:(nonnull NSDictionary<NSString *, NSString *> *)kvParams;

@property(nonatomic) DPSRpcDataType dataType;

/**
 * 是否运行自动重试（需要确认服务端此RPC是否支持去重）
 */
@property(nonatomic) BOOL enableRetry;

/**
 * 本次RPC超时时间
 */
@property(nonatomic) int64_t timeoutMs;

/**
 * 此RPC是否不需要认证(仅用于特殊场景，如登录前需要扫码认证)
 */
@property(nonatomic) BOOL noNeedAuth;

/**
 * 其他自定义参数，一般为空
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *kvParams;

@end
