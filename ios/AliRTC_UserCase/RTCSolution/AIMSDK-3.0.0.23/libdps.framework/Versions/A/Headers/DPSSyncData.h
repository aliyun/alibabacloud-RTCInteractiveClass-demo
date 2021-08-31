// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import <Foundation/Foundation.h>

/**
 * 同步协议数据内容结构
 */
DPS_DECL
@interface DPSSyncData : NSObject
- (nonnull instancetype)initWithObjectType:(int32_t)objectType
                                      data:(nonnull NSString *)data
                                binaryData:(nonnull NSData *)binaryData
                                   bizType:(int32_t)bizType
                                   serveId:(nonnull NSString *)serveId
                                 isOffline:(BOOL)isOffline;
+ (nonnull instancetype)DPSSyncDataWithObjectType:(int32_t)objectType
                                             data:(nonnull NSString *)data
                                       binaryData:(nonnull NSData *)binaryData
                                          bizType:(int32_t)bizType
                                          serveId:(nonnull NSString *)serveId
                                        isOffline:(BOOL)isOffline;

/**
 * 数据类型
 */
@property(nonatomic) int32_t objectType;

/**
 * stirng封装二进制数据
 */
@property(nonatomic, nonnull) NSString *data;

/**
 * 二进制数据
 */
@property(nonatomic, nonnull) NSData *binaryData;

/**
 * 业务类型
 */
@property(nonatomic) int32_t bizType;

/**
 * 数据id
 */
@property(nonatomic, nonnull) NSString *serveId;

/**
 * 是否是离线消息
 */
@property(nonatomic) BOOL isOffline;

@end
