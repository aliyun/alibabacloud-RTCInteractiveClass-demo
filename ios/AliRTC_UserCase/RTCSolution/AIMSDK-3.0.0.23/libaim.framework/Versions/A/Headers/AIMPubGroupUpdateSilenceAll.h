// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群禁言/取消群禁言参数
 */
@interface AIMPubGroupUpdateSilenceAll : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid;
+ (nonnull instancetype)AIMPubGroupUpdateSilenceAllWithAppCid:
    (nonnull NSString *)appCid;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

@end
