// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupUserInfo.h"
#import <Foundation/Foundation.h>

/**
 * 群加人参数
 */
@interface AIMPubGroupJoin : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
             users:(nonnull NSArray<AIMPubGroupUserInfo *> *)users;
+ (nonnull instancetype)
    AIMPubGroupJoinWithAppCid:(nonnull NSString *)appCid
                        users:(nonnull NSArray<AIMPubGroupUserInfo *> *)users;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 群成员
 */
@property(nonatomic, nonnull) NSArray<AIMPubGroupUserInfo *> *users;

@end
