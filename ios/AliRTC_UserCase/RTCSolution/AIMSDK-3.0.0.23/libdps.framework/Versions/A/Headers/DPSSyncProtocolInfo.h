// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSSyncProtocolType.h"
#import <Foundation/Foundation.h>

/**
 * Sync协议内容
 */
DPS_DECL
@interface DPSSyncProtocolInfo : NSObject
- (nonnull instancetype)initWithTopic:(nonnull NSString *)topic
                              bizType:(int64_t)bizType
                              bizName:(nonnull NSString *)bizName
                         protocolType:(DPSSyncProtocolType)protocolType;
+ (nonnull instancetype)DPSSyncProtocolInfoWithTopic:(nonnull NSString *)topic
                                             bizType:(int64_t)bizType
                                             bizName:(nonnull NSString *)bizName
                                        protocolType:(DPSSyncProtocolType)protocolType;

/**
 * 通道标识
 */
@property(nonatomic, nonnull) NSString *topic;

/**
 * 业务标示
 */
@property(nonatomic) int64_t bizType;

/**
 * 业务名称
 */
@property(nonatomic, nonnull) NSString *bizName;

/**
 * 协议类型
 */
@property(nonatomic) DPSSyncProtocolType protocolType;

@end
