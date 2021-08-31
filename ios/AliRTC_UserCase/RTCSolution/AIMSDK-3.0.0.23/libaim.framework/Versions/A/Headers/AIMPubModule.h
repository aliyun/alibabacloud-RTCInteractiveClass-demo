// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
#import <libdps/DPSModuleInfo.h>
@class AIMMediaService;
@class AIMPubConvService;
@class AIMPubGroupService;
@class AIMPubModule;
@class AIMPubMsgService;
@class AIMPubSearchService;
@class AIMTraceService;

@interface AIMPubModule : NSObject

+ (nullable AIMPubModule *)getModuleInstance:(nonnull NSString *)uid;

+ (nullable DPSModuleInfo *)getModuleInfo;

/**
 * 获取会话相关Service
 */
- (nullable AIMPubConvService *)getConvService;

/**
 * 获取消息相关Service
 */
- (nullable AIMPubMsgService *)getMsgService;

/**
 * 获取群聊相关Service
 */
- (nullable AIMPubGroupService *)getGroupService;

/**
 * 获取多媒体相关Service
 */
- (nullable AIMMediaService *)getMediaService;

/**
 * 获取消息搜索相关Service
 */
- (nullable AIMPubSearchService *)getSearchService;

/**
 * 获取trace相关Service
 */
- (nullable AIMTraceService *)getTraceService;

@end
