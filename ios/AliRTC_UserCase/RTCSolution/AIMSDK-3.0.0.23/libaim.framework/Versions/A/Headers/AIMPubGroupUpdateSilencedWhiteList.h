// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupUserInfo.h"
#import <Foundation/Foundation.h>

/**
 * 增加/取消白名单用户
 */
@interface AIMPubGroupUpdateSilencedWhiteList : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
           members:(nonnull NSArray<AIMPubGroupUserInfo *> *)members;
+ (nonnull instancetype)
    AIMPubGroupUpdateSilencedWhiteListWithAppCid:(nonnull NSString *)appCid
                                         members:(nonnull NSArray<
                                                     AIMPubGroupUserInfo *> *)
                                                     members;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 操作成员
 */
@property(nonatomic, nonnull) NSArray<AIMPubGroupUserInfo *> *members;

@end
