// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgBizInfo.h"
#import "AIMMsgUpdateMode.h"
#import <Foundation/Foundation.h>

/**
 * 本地消息biz信息更新结构
 */
@interface AIMPubMsgBizUpdateInfo : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                               localid:(nonnull NSString *)localid
                            updateMode:(AIMMsgUpdateMode)updateMode
                               bizInfo:(nonnull AIMMsgBizInfo *)bizInfo;
+ (nonnull instancetype)
    AIMPubMsgBizUpdateInfoWithAppCid:(nonnull NSString *)appCid
                             localid:(nonnull NSString *)localid
                          updateMode:(AIMMsgUpdateMode)updateMode
                             bizInfo:(nonnull AIMMsgBizInfo *)bizInfo;

/**
 * 需要更新的消息appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 需要更新的消息localid
 */
@property(nonatomic, nonnull) NSString *localid;

/**
 * 消息更新模式
 */
@property(nonatomic) AIMMsgUpdateMode updateMode;

/**
 * 需更新的消息biz属性
 */
@property(nonatomic, nonnull) AIMMsgBizInfo *bizInfo;

@end
