// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSRpcDataType.h"
#import <Foundation/Foundation.h>

/**
 * RPC数据结构
 */
DPS_DECL
@interface DPSRpcDataTypeMap : NSObject
- (nonnull instancetype)initWithDataType:(DPSRpcDataType)dataType
                             enableRetry:(BOOL)enableRetry
                               timeoutMs:(int64_t)timeoutMs
                                kvParams:(nonnull NSDictionary<NSString *, NSString *> *)kvParams;
+ (nonnull instancetype)DPSRpcDataTypeMapWithDataType:(DPSRpcDataType)dataType
                                          enableRetry:(BOOL)enableRetry
                                            timeoutMs:(int64_t)timeoutMs
                                             kvParams:(nonnull NSDictionary<NSString *, NSString *> *)kvParams;

/**
 * 数据类型
 */
@property(nonatomic) DPSRpcDataType dataType;

/**
 * 是否允许断线后自动重试
 */
@property(nonatomic) BOOL enableRetry;

/**
 * rpc超时时间，一般设为40s
 */
@property(nonatomic) int64_t timeoutMs;

/**
 * 其他自定义参数，一般为空
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *kvParams;

@end
