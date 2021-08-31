// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import <Foundation/Foundation.h>

/**
 * 同步协议扩展信息
 */
DPS_DECL
@interface DPSSyncDataExtend : NSObject
- (nonnull instancetype)initWithMinCreateTime:(int64_t)minCreateTime isFailover:(BOOL)isFailover;
+ (nonnull instancetype)DPSSyncDataExtendWithMinCreateTime:(int64_t)minCreateTime isFailover:(BOOL)isFailover;

/**
 * toolong2之前最后一个收到的消息时间
 */
@property(nonatomic) int64_t minCreateTime;

/**
 * 双推数据
 */
@property(nonatomic) BOOL isFailover;

@end
