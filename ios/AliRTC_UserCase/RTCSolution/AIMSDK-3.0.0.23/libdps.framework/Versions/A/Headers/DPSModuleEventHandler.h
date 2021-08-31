// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSError.h"
#import "DPSSyncProtocolInfo.h"
#import "DPSUserId.h"
#import <Foundation/Foundation.h>
@class DPSAuthHandler;
@class DPSServiceProvider;
@protocol DPSModuleEventHandlerCallback;

DPS_DECL
@interface DPSModuleEventHandler : NSObject

/**
 * 引擎启动前的回调，可进行用户无关的初始化设置
 * @param appID 应用的AppID
 */
- (void)onBeforeEngineStart:(nonnull NSString *)appID;

/**
 * 引擎启动完成通知
 */
- (void)onEngineStarted;

/**
 * 用户相关Manager开始创建，用于创建该module内相应用户实例
 * @param uid 用户ID
 */
- (void)onBeforeManagerCreate:(nonnull DPSUserId *)uid;

/**
 * 初始化用户实例回调, 可异步初始化，完成后需调用成功或失败回调，否则将影响DPS的初始化
 * @param uid 用户ID
 * @param callback 初始化成功或失败回调，必须调用
 * @param serviceProvider DPSBase 提供的基础服务
 */
- (void)onInitModuleForUser:(nonnull DPSUserId *)uid
                   callback:(nullable id<DPSModuleEventHandlerCallback>)callback
            serviceProvider:(nullable DPSServiceProvider *)serviceProvider;

- (void)onInitModuleForUserWithBlock:(nonnull DPSUserId *)uid
                           onSuccess:(nullable void (^)())onSuccess
                           onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure
                     serviceProvider:(nullable DPSServiceProvider *)serviceProvider;

/**
 * 用户相关Manager创建完成，可获取其他service
 * @param uid 用户ID
 * @param error 错误信息
 */
- (void)onManagerCreateFinished:(nonnull DPSUserId *)uid error:(nonnull DPSError *)error;

/**
 * 释放该uid的manager
 * @param uid 用户ID
 */
- (void)onReleaseManager:(nonnull DPSUserId *)uid;

/**
 * App 切到后台
 */
- (void)onAppDidEnterBackground;

/**
 * App 切回前台
 */
- (void)onAppWillEnterForeground;

/**
 * Engine 被释放
 */
- (void)onEngineReleased;

/**
 * 获取登陆相关监听，如需要设置reg header或获取监听，需返回 DPSAuthHandler 实例
 * @param uid 用户ID
 */
- (nullable DPSAuthHandler *)onGetAuthHandler:(nonnull DPSUserId *)uid;

/**
 * 返回同步协议设置
 */
- (nonnull NSArray<DPSSyncProtocolInfo *> *)onGetSyncProtocolInfo;

@end
