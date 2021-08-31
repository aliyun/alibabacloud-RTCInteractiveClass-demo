// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSSyncData.h"
#import "DPSSyncDataExtend.h"
#import <Foundation/Foundation.h>
@class DPSSyncPlusAck;

@protocol DPSSyncPlusBizEventListener

/**
 * Toolong2事件，数据积压，需要业务拉取补偿
 * @param entend 扩展信息
 * @param ack 业务回调ack对象，完成后需要调用ack->OnSuccess, 失败调用ack->OnFailed
 */
- (void)onTooLong2:(nonnull DPSSyncDataExtend *)entend ack:(nullable DPSSyncPlusAck *)ack;

/**
 * 获取监听标识符，用于记录日志
 * @return 标识符
 */
- (nonnull NSString *)onGetTag;

/**
 * 回调处理重试失败
 * @param data 失败的数据
 * @return 是否丢弃，继续处理下一个数据
 */
- (BOOL)onDispatchRetryFailed:(nonnull NSArray<DPSSyncData *> *)data;

@end
