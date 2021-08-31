// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群头像鉴权
 */
@interface AIMGroupAvatorMediaAuthInfo : NSObject
- (nonnull instancetype)initWithCid:(nonnull NSString *)cid;
+ (nonnull instancetype)AIMGroupAvatorMediaAuthInfoWithCid:
    (nonnull NSString *)cid;

@property(nonatomic, nonnull) NSString *cid;

@end
