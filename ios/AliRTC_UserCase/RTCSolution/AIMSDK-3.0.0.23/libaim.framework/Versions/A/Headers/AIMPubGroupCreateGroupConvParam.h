// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupUserInfo.h"
#import <Foundation/Foundation.h>

/**
 * 创建群参数
 */
@interface AIMPubGroupCreateGroupConvParam : NSObject
- (nonnull instancetype)
    initWithUserInfos:(nonnull NSArray<AIMPubGroupUserInfo *> *)userInfos
                title:(nonnull NSString *)title
                 icon:(nonnull NSString *)icon
              bizType:(nonnull NSString *)bizType
                  ext:(nonnull NSDictionary<NSString *, NSString *> *)ext
                  ctx:(nonnull NSDictionary<NSString *, NSString *> *)ctx
    operatorExtension:
        (nonnull NSDictionary<NSString *, NSString *> *)operatorExtension;
+ (nonnull instancetype)
    AIMPubGroupCreateGroupConvParamWithUserInfos:
        (nonnull NSArray<AIMPubGroupUserInfo *> *)userInfos
                                           title:(nonnull NSString *)title
                                            icon:(nonnull NSString *)icon
                                         bizType:(nonnull NSString *)bizType
                                             ext:(nonnull NSDictionary<
                                                     NSString *, NSString *> *)
                                                     ext
                                             ctx:(nonnull NSDictionary<
                                                     NSString *, NSString *> *)
                                                     ctx
                               operatorExtension:
                                   (nonnull NSDictionary<NSString *, NSString *>
                                        *)operatorExtension;

/**
 * 群成员信息列表，里面的uid必填
 */
@property(nonatomic, nonnull) NSArray<AIMPubGroupUserInfo *> *userInfos;

@property(nonatomic, nonnull) NSString *title;

@property(nonatomic, nonnull) NSString *icon;

@property(nonatomic, nonnull) NSString *bizType;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *ext;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *ctx;

@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *operatorExtension;

@end
