// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 更新群头像参数
 */
@interface AIMPubGroupUpdateIcon : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                  icon:(nonnull NSString *)icon;
+ (nonnull instancetype)
    AIMPubGroupUpdateIconWithAppCid:(nonnull NSString *)appCid
                               icon:(nonnull NSString *)icon;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 群头像
 */
@property(nonatomic, nonnull) NSString *icon;

@end
