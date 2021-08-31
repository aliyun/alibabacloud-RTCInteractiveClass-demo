// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
@protocol DPSAuthListener;

@interface DPSAuthHandler : NSObject

/**
 * 可在此添加 reg 时的 header，无需添加，则返回空
 */
- (nonnull NSDictionary<NSString *, NSString *> *)onGetRegHeader;

/**
 * 监听登陆/连接状态，不感知，可返回空
 */
- (nullable id<DPSAuthListener>)onGetAuthListener;

@end
