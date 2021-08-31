// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSSyncData.h"
#import "DPSSyncDataExtend.h"
#import <Foundation/Foundation.h>
@class DPSSyncPlusAck;
@protocol DPSSyncPlusBizEventListener;
@protocol DPSSyncPlusPackageDataHandler;
@protocol DPSSyncPlusTopicEventListener;

/**
 * DPSSyncServer
 */
@interface DPSSyncService : NSObject

/**
 * 添加通道事件监听
 * @param topic 通道名
 * @param listener 回调对象
 */
- (BOOL)addSyncTopicEventListener:(nonnull NSString *)topic
                         listener:(nullable id<DPSSyncPlusTopicEventListener>)listener;

/**
 * 删除通道事件监听
 * @param topic 通道名
 * @param listener 回调对象
 */
- (BOOL)removeSyncTopicEventListener:(nonnull NSString *)topic
                            listener:(nullable id<DPSSyncPlusTopicEventListener>)listener;

/**
 * 添加业务事件监听
 * @param bizType 业务类型
 * @param listener 回调对象
 */
- (BOOL)addSyncBizEventListener:(int32_t)bizType listener:(nullable id<DPSSyncPlusBizEventListener>)listener;

/**
 * 删除业务事件监听
 * @param bizType 业务类型
 * @param listener 回调对象
 */
- (BOOL)removeSyncBizEventListener:(int32_t)bizType listener:(nullable id<DPSSyncPlusBizEventListener>)listener;

/**
 * 添加业务数据监听
 * @param bizType 业务类型
 * @param handler 回调对象
 */
- (BOOL)addSyncDataHandler:(int32_t)bizType handler:(nullable id<DPSSyncPlusPackageDataHandler>)handler;

/**
 * 删除业务数据监听
 * @param bizType 业务类型
 * @param handler 回调对象
 */
- (BOOL)removeSyncDataHandler:(int32_t)bizType handler:(nullable id<DPSSyncPlusPackageDataHandler>)handler;

@end
