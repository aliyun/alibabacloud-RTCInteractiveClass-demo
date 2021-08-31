// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSConnectionStatus.h"
#import "DPSError.h"
#import "DPSNetType.h"
#import <Foundation/Foundation.h>
@protocol DPSAuthListener;
@protocol DPSKickoutListener;
@protocol DPSLogoutListener;

/**
 * Auth Service
 */
@interface DPSAuthService : NSObject

/**
 * 获取网络是否可用
 */
- (BOOL)isNetworkAvailable;

/**
 * 获取网络连接类型
 */
- (DPSNetType)getNetType;

/**
 * 获取连接状态
 */
- (DPSConnectionStatus)getConnectionStatus;

/**
 * 是否处于本地登录状态（该状态和是否联网无关）
 */
- (BOOL)isLocalLogin;

/**
 * 登录接口, 允许账号连接网络进行登录
 */
- (void)login;

/**
 * 退出登录接口
 * @param listener 监听器
 */
- (void)logout:(nullable id<DPSLogoutListener>)listener;

- (void)logoutWithBlock:(nullable void (^)())onSuccess onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 踢人接口（暂不可用）
 * @param type      被踢下线的设备类型， 0：web，1：app
 * @param message   被踢下线设备收到的消息
 * @param listener 监听器
 */
- (void)kickout:(int32_t)type message:(nonnull NSString *)message listener:(nullable id<DPSKickoutListener>)listener;

- (void)kickoutWithBlock:(int32_t)type
                 message:(nonnull NSString *)message
               onSuccess:(nullable void (^)())onSuccess
               onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 注册监听器
 * @param listener 监听器
 */
- (BOOL)addListener:(nullable id<DPSAuthListener>)listener;

/**
 * 删除监听器
 * @param listener 用户监听器
 */
- (BOOL)removeListener:(nullable id<DPSAuthListener>)listener;

/**
 * 删除所有监听器
 */
- (void)removeAllListeners;

@end
