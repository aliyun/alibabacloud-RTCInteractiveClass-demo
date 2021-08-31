// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSAuthTokenExpiredReason.h"
#import <Foundation/Foundation.h>
@class DPSAuthTokenGotCallback;

/**
 * 请求获取Token回调
 */
@protocol DPSPubAuthTokenCallback

- (void)onCallback:(nonnull NSString *)userId
             onGot:(nullable DPSAuthTokenGotCallback *)onGot
            reason:(DPSAuthTokenExpiredReason)reason;

@end
