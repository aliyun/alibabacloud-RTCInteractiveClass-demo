// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import <Foundation/Foundation.h>

/**
 * DPSUserID
 */
DPS_DECL
@interface DPSUserId : NSObject
- (nonnull instancetype)initWithUid:(nonnull NSString *)uid domain:(nonnull NSString *)domain;
+ (nonnull instancetype)DPSUserIdWithUid:(nonnull NSString *)uid domain:(nonnull NSString *)domain;

/**
 * 最大32 byte
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 * 最大16 byte
 */
@property(nonatomic, nonnull) NSString *domain;

@end
