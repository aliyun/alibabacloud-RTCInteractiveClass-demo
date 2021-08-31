// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import <Foundation/Foundation.h>

/**
 * Auth token信息
 */
DPS_DECL
@interface DPSAuthToken : NSObject
- (nonnull instancetype)initWithAccessToken:(nonnull NSString *)accessToken
                               refreshToken:(nonnull NSString *)refreshToken;
+ (nonnull instancetype)DPSAuthTokenWithAccessToken:(nonnull NSString *)accessToken
                                       refreshToken:(nonnull NSString *)refreshToken;

@property(nonatomic, nonnull) NSString *accessToken;

@property(nonatomic, nonnull) NSString *refreshToken;

@end
