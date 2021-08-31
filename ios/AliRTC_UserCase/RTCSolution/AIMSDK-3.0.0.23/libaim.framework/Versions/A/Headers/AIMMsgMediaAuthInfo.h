// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群消息鉴权
 */
@interface AIMMsgMediaAuthInfo : NSObject
- (nonnull instancetype)initWithCid:(nonnull NSString *)cid
                                mid:(nonnull NSString *)mid;
+ (nonnull instancetype)AIMMsgMediaAuthInfoWithCid:(nonnull NSString *)cid
                                               mid:(nonnull NSString *)mid;

@property(nonatomic, nonnull) NSString *cid;

@property(nonatomic, nonnull) NSString *mid;

@end
