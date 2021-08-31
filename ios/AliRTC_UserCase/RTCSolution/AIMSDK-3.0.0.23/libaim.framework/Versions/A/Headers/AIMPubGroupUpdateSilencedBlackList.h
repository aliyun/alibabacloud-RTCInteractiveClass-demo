// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupUserInfo.h"
#import <Foundation/Foundation.h>

/**
 * 增加/取消黑名单用户
 */
@interface AIMPubGroupUpdateSilencedBlackList : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
           members:(nonnull NSArray<AIMPubGroupUserInfo *> *)members
          duration:(int64_t)duration;
+ (nonnull instancetype)
    AIMPubGroupUpdateSilencedBlackListWithAppCid:(nonnull NSString *)appCid
                                         members:(nonnull NSArray<
                                                     AIMPubGroupUserInfo *> *)
                                                     members
                                        duration:(int64_t)duration;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 操作成员
 */
@property(nonatomic, nonnull) NSArray<AIMPubGroupUserInfo *> *members;

/**
 * 禁言时长 单位ms
 */
@property(nonatomic) int64_t duration;

@end
