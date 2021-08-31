// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 禁言黑名单成员信息
 */
@interface AIMPubGroupSilencedBlackListMemberInfo : NSObject
- (nonnull instancetype)initWithUid:(nonnull NSString *)uid
                            endTime:(int64_t)endTime
                        operateTime:(int64_t)operateTime;
+ (nonnull instancetype)
    AIMPubGroupSilencedBlackListMemberInfoWithUid:(nonnull NSString *)uid
                                          endTime:(int64_t)endTime
                                      operateTime:(int64_t)operateTime;

/**
 * 操作者uid
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 * 禁言截止时间 单位ms
 */
@property(nonatomic) int64_t endTime;

/**
 * 操作时间 单位ms
 */
@property(nonatomic) int64_t operateTime;

@end
