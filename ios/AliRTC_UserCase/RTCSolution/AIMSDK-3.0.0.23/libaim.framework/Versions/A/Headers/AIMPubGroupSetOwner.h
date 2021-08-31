// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupUserInfo.h"
#import <Foundation/Foundation.h>

/**
 * 转让群主参数
 */
@interface AIMPubGroupSetOwner : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                 owner:(nonnull AIMPubGroupUserInfo *)owner;
+ (nonnull instancetype)
    AIMPubGroupSetOwnerWithAppCid:(nonnull NSString *)appCid
                            owner:(nonnull AIMPubGroupUserInfo *)owner;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 操作成员
 */
@property(nonatomic, nonnull) AIMPubGroupUserInfo *owner;

@end
