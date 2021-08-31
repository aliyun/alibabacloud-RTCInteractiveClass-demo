// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 退出群参数
 */
@interface AIMPubGroupLeave : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid;
+ (nonnull instancetype)AIMPubGroupLeaveWithAppCid:(nonnull NSString *)appCid;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

@end
