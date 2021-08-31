// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMGroupAvatorMediaAuthInfo.h"
#import "AIMMediaAuthScene.h"
#import "AIMMsgMediaAuthInfo.h"
#import <Foundation/Foundation.h>

/**
 * 鉴权信息
 */
@interface AIMMediaAuthInfo : NSObject
- (nonnull instancetype)initWithScene:(AIMMediaAuthScene)scene
                              bizType:(nonnull NSString *)bizType
                      groupAvatorAuth:
                          (nonnull AIMGroupAvatorMediaAuthInfo *)groupAvatorAuth
                              msgAuth:(nonnull AIMMsgMediaAuthInfo *)msgAuth;
+ (nonnull instancetype)
    AIMMediaAuthInfoWithScene:(AIMMediaAuthScene)scene
                      bizType:(nonnull NSString *)bizType
              groupAvatorAuth:
                  (nonnull AIMGroupAvatorMediaAuthInfo *)groupAvatorAuth
                      msgAuth:(nonnull AIMMsgMediaAuthInfo *)msgAuth;

@property(nonatomic) AIMMediaAuthScene scene;

@property(nonatomic, nonnull) NSString *bizType;

@property(nonatomic, nonnull) AIMGroupAvatorMediaAuthInfo *groupAvatorAuth;

@property(nonatomic, nonnull) AIMMsgMediaAuthInfo *msgAuth;

@end
