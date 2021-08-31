// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgRecallType.h"
#import <Foundation/Foundation.h>

/**
 * 消息撤回信息
 */
@interface AIMPubMsgRecallFeature : NSObject
- (nonnull instancetype)
    initWithOperatorType:(AIMMsgRecallType)operatorType
                    code:(nonnull NSString *)code
             operatorUid:(nonnull NSString *)operatorUid
               extension:
                   (nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMPubMsgRecallFeatureWithOperatorType:(AIMMsgRecallType)operatorType
                                      code:(nonnull NSString *)code
                               operatorUid:(nonnull NSString *)operatorUid
                                 extension:(nonnull NSDictionary<NSString *,
                                                                 NSString *> *)
                                               extension;

/**
 * 操作类型
 */
@property(nonatomic) AIMMsgRecallType operatorType;

/**
 * 业务方自定义code
 */
@property(nonatomic, nonnull) NSString *code;

/**
 * 撤回者UID
 */
@property(nonatomic, nonnull) NSString *operatorUid;

/**
 * 撤回扩展字段
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
