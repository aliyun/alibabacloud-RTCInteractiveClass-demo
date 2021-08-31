// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSMediaHostType.h"
#import <Foundation/Foundation.h>

/**
 * 多媒体服务端配置
 */
DPS_DECL
@interface DPSMediaHost : NSObject
- (nonnull instancetype)initWithType:(DPSMediaHostType)type host:(nonnull NSString *)host;
+ (nonnull instancetype)DPSMediaHostWithType:(DPSMediaHostType)type host:(nonnull NSString *)host;

/**
 * 类型
 */
@property(nonatomic) DPSMediaHostType type;

/**
 * 地址
 */
@property(nonatomic, nonnull) NSString *host;

@end
