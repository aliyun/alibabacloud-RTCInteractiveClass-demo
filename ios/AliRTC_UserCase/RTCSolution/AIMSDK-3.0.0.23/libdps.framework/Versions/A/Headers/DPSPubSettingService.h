// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSAuthTokenExpiredReason.h"
#import "DPSEnvType.h"
#import "DPSMediaHost.h"
#import "DPSSyncProtocolInfo.h"
#import <Foundation/Foundation.h>
@class DPSAuthTokenGotCallback;
@protocol DPSPubAuthTokenCallback;

/**
 * DPSSettingService
 */
@interface DPSPubSettingService : NSObject

/**
 * 设置多媒体Media Host, 若不设置则采用内置默认Host
 */
- (void)setMediaHost:(nonnull NSArray<DPSMediaHost *> *)mediaHost;

/**
 * 设置应用appid
 * @param appId DingPaaS分配给应用的appID
 */
- (void)setAppID:(nonnull NSString *)appId;

/**
 * 设置应用key
 * @param appKey IM_PAAS分配给应用的key
 */
- (void)setAppKey:(nonnull NSString *)appKey;

/**
 * 设置数据存储路径
 * @param dataPath
 * 数据存取路径(utf-8),app需提前创建好此目录并对此目录有读写权限
 */
- (void)setDataPath:(nonnull NSString *)dataPath;

/**
 * 设置应用名称
 * @param appName 应用名称
 */
- (void)setAppName:(nonnull NSString *)appName;

/**
 * 设置应用版本
 * @param app_version 应用版本号
 */
- (void)setAppVersion:(nonnull NSString *)version;

/**
 * 设置App语言区域
 * @param app_locale 语言区域（默认zh_CN）
 */
- (void)setAppLocale:(nonnull NSString *)appLocal;

/**
 * 设置操作系统名称
 * @param osName 操作系统名称，如Win、macOS、iOS、Android等
 */
- (void)setOSName:(nonnull NSString *)osName;

/**
 * 设置操作系统版本
 * @param osVersion 操作系统版本
 */
- (void)setOSVersion:(nonnull NSString *)osVersion;

/**
 * 设置设备名称
 * @param deviceName 设备名称
 */
- (void)setDeviceName:(nonnull NSString *)deviceName;

/**
 * 设置设备型号
 * @param deviceType 设备型号
 */
- (void)setDeviceType:(nonnull NSString *)deviceType;

/**
 * 设置设备语言
 * @param deviceLocal 设备语言（默认zh_CN）
 */
- (void)setDeviceLocale:(nonnull NSString *)deviceLocal;

/**
 * 设置设备唯一id
 * @param deviceId 设备唯一id
 *  device_id生成算法不合适（容易冲突）可能会影响正常使用
 */
- (void)setDeviceId:(nonnull NSString *)deviceId;

/**
 * 设置时区
 * @param timeZone 时区（默认Asia/Shanghai）
 */
- (void)setTimeZone:(nonnull NSString *)timeZone;

/**
 * 设置长链接地址, 若不设置则采用内置默认地址
 * @param url 长链接地址
 */
- (void)setLonglinkServerAddress:(nonnull NSString *)url;

/**
 * 文件上传服务器地址, 若不设置则采用内置默认地址
 * @param url 服务器地址
 */
- (void)setFileUploadServerAddress:(nonnull NSString *)url;

/**
 * 设置获取登录token的回调函数
 * @param onCallback 获取登录token的回调函数（注意需要做成异步操作，不能有阻塞）
 */
- (void)setAuthTokenCallback:(nullable id<DPSPubAuthTokenCallback>)onCallback;

- (void)setAuthTokenCallbackWithBlock:(nullable void (^)(NSString *_Nonnull userId,
                                                         DPSAuthTokenGotCallback *_Nullable onGot,
                                                         DPSAuthTokenExpiredReason reason))onCallback;

/**
 * 设置Sync协议相关设置
 * @param info Sync协议设置
 */
- (void)addSyncProtocolSetting:(nonnull NSArray<DPSSyncProtocolInfo *> *)info;

/**
 * 设置自定义UserAgent：可选配置，如不设定，则自动生成UserAgent，设置则使用该UA
 */
- (void)setCustomUserAgent:(nonnull NSString *)ua;

/**
 * 设置是否开启ipv6(默认不开启)
 */
- (void)setEnableIpv6:(BOOL)enable;

/**
 * 设置关闭ssl校验(默认不关闭，日常环境请设置为true)
 */
- (void)setDisableSslVerify:(BOOL)disable;

/**
 * 设置当前连接的服务端环境(日常，预发或线上)
 * 需要与长连接地址匹配，不然无法登陆成功
 */
- (void)setEnvType:(DPSEnvType)type;

@end
