// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 禁言白名单成员信息
 */
@interface AIMPubGroupSilencedWhiteListMemberInfo : NSObject
- (nonnull instancetype)initWithUid:(nonnull NSString *)uid
                        operateTime:(int64_t)operateTime;
+ (nonnull instancetype)
    AIMPubGroupSilencedWhiteListMemberInfoWithUid:(nonnull NSString *)uid
                                      operateTime:(int64_t)operateTime;

/**
 * 操作者uid
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 * 操作时间 单位ms
 */
@property(nonatomic) int64_t operateTime;

@end
