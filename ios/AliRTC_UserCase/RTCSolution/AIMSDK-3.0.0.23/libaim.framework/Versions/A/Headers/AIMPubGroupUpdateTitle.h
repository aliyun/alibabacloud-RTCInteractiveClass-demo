// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 更新群标题参数
 */
@interface AIMPubGroupUpdateTitle : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                 title:(nonnull NSString *)title;
+ (nonnull instancetype)
    AIMPubGroupUpdateTitleWithAppCid:(nonnull NSString *)appCid
                               title:(nonnull NSString *)title;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 群标题
 */
@property(nonatomic, nonnull) NSString *title;

@end
