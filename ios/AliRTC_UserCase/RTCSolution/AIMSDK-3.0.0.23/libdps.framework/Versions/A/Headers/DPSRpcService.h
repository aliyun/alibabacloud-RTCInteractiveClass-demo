// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import "DPSRpcRequestHeader.h"
#import <Foundation/Foundation.h>
@class DPSPushAckStatus;
@protocol DPSPushListener;
@protocol DPSRpcRequestListener;

/**
 * DPSRpcService
 */
@interface DPSRpcService : NSObject

/**
 * @brief 发送rpc请求
 * @param name rpc名称
 * @param body 包体内容，格式由header中的data_type指定
 * @param header 包头
 * @param listener 返回监听器
 */
- (void)request:(nonnull NSString *)name
           body:(nonnull NSData *)body
         header:(nonnull DPSRpcRequestHeader *)header
       listener:(nullable id<DPSRpcRequestListener>)listener;

- (void)requestWithBlock:(nonnull NSString *)name
                    body:(nonnull NSData *)body
                  header:(nonnull DPSRpcRequestHeader *)header
               onSuccess:(nullable void (^)(NSDictionary<NSString *, NSString *> *_Nonnull kvParams,
                                            NSData *_Nonnull responseBody))onSuccess
               onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * @brief 通道名称
 * @param name 通道名称
 * @param lisenter 通道消息监听器
 */
- (void)subscribe:(nonnull NSString *)name lisenter:(nullable id<DPSPushListener>)lisenter;

@end
