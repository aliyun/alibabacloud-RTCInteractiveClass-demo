// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSSyncData.h"
#import "DPSSyncDataExtend.h"
#import <Foundation/Foundation.h>
@class DPSSyncPlusAck;

@protocol DPSSyncPlusPackageDataHandler

/**
 * 支持的数据类型
 * @return object type 列表
 */
- (nonnull NSArray<NSNumber *> *)onSupportTypes;

/**
 * 获取监听标识符，用于记录日志
 * @return 标识符
 */
- (nonnull NSString *)onGetTag;

/**
 * 接收到数据推送
 * @param data 数据
 * @param entend 扩展信息
 * @param ack 业务回调ack对象，完成后需要调用ack->OnSuccess, 失败调用ack->OnFailed
 */
- (void)onReceived:(nonnull NSArray<DPSSyncData *> *)data
            entend:(nonnull DPSSyncDataExtend *)entend
               ack:(nullable DPSSyncPlusAck *)ack;

@end
