// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSError.h"
#import "DPSLogLevel.h"
#import <Foundation/Foundation.h>
@class DPSModuleInfo;
@class DPSPubEngine;
@class DPSPubManager;
@class DPSPubSettingService;
@protocol DPSEngineStartListener;
@protocol DPSLogHandler;
@protocol DPSPubEngineListener;
@protocol DPSPubManagerCreateListener;
@protocol DPSReleaseManagerListener;
@protocol DPSResetUserDataListener;

DPS_DECL extern int32_t const DPSPubEngineMAXMANAGERNUM;

/**
 * DPS Engine
 */
DPS_DECL
@interface DPSPubEngine : NSObject

/**
 * 注册service
 */
- (nonnull DPSError *)registerModule:(nullable DPSModuleInfo *)serviceInfo;

/**
 * App切到后台后通知SDK
 */
- (void)onAppDidEnterBackground;

/**
 * App切到前台前通知SDK
 */
- (void)onAppWillEnterForeground;

/**
 * 获取设置服务
 */
- (nullable DPSPubSettingService *)getSettingService;

/**
 * 获取引擎是否启动
 */
- (BOOL)isStarted;

/**
 * 启动
 * @param listener Engine Start回调
 */
- (void)start:(nullable id<DPSEngineStartListener>)listener;

- (void)startWithBlock:(nullable void (^)())onSuccess onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 设置事件监听器
 * @param listener 监听器
 */
- (void)setListener:(nullable id<DPSPubEngineListener>)listener;

/**
 * 获取所有当前存在的DPSUserId
 */
- (nonnull NSArray<NSString *> *)getUserIds;

/**
 * 创建Manager,注意只允许同时存在MAX_MANAGER_NUM以下的Manager实例
 * @param userId 登录帐号
 * @param listener 监听器
 */
- (void)createDPSManager:(nonnull NSString *)userId listener:(nullable id<DPSPubManagerCreateListener>)listener;

- (void)createDPSManagerWithBlock:(nonnull NSString *)userId
                        onSuccess:(nullable void (^)(DPSPubManager *_Nullable manager))onSuccess
                        onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 获取DPSManager
 * @param userId 登录帐号
 */
- (nullable DPSPubManager *)getDPSManager:(nonnull NSString *)userId;

/**
 * 释放DPSManager
 * @param userId 登录帐号
 */
- (void)releaseDPSManager:(nonnull NSString *)userId listener:(nullable id<DPSReleaseManagerListener>)listener;

- (void)releaseDPSManagerWithBlock:(nonnull NSString *)userId
                         onSuccess:(nullable void (^)())onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 创建DPSEngine,如果已经有实例存在,会返回已创建的DPSEngine
 */
+ (nullable DPSPubEngine *)createDPSEngine;

/**
 * 获取DPSEngine
 */
+ (nullable DPSPubEngine *)getDPSEngine;

/**
 * 设置log处理函数,处理函数可能会在多个线程调用,处理函数不能长时间阻塞
 * @param minLogLevel 需要输出的最低日志级别（日志级别大于等于这个值才会输出）
 * @param handler 日志处理函数
 */
+ (void)setLogHandler:(DPSLogLevel)minLogLevel handler:(nullable id<DPSLogHandler>)handler;

/**
 * 释放DPSEngine
 */
+ (void)releaseDPSEngine;

/**
 * 清理用户数据接口，可通过该接口清理用户数据，本地存储的消息/会话等数据将被清空
 * @param dataPath 数据存储路径，与之前设置到DPSSettingService内的DataPath一致
 * @param userId 需清理的账号
 * @param appId 账号关联的appID
 * @param onSuccess 重置成功
 * @param onFailure 重置失败，部分文件无法删除
 * 注意事项：
 * 1. 需在user_id 对应DPSManager启动之前进行该操作
 * 2. 部分文件由于io错误，或被其他应用使用，可能导致无法删除
 */
+ (void)resetUserData:(nonnull NSString *)dataPath
               userId:(nonnull NSString *)userId
                appId:(nonnull NSString *)appId
             listener:(nullable id<DPSResetUserDataListener>)listener;

+ (void)resetUserDataWithBlock:(nonnull NSString *)dataPath
                        userId:(nonnull NSString *)userId
                         appId:(nonnull NSString *)appId
                     onSuccess:(nullable void (^)())onSuccess
                     onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 获取服务端时钟
 * @return 单位毫秒，如果获取失败，返回-1
 */
- (int64_t)getServerTimeClock;

@end
