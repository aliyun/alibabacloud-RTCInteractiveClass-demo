// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSConnectionStatus.h"
#import <Foundation/Foundation.h>

/**
 * 登录监听
 */
@protocol DPSAuthListener

/**
 * 连接状态事件
 * @param status      网络状态
 */
- (void)onConnectionStatusChanged:(DPSConnectionStatus)status;

/**
 * 登录token获取失败事件
 * @param errorCode  获取登录token失败错误值
 * @param errorMsg   获取登录token失败错误信息
 */
- (void)onGetAuthCodeFailed:(int32_t)errorCode errorMsg:(nonnull NSString *)errorMsg;

/**
 * 本地登录事件
 * 如果本地已有登录信息，调用Login接口后会立即回调；反之会等待网络登录成功之后回调
 */
- (void)onLocalLogin;

/**
 * 被踢事件
 * @param message     被踢下线时附带的消息
 */
- (void)onKickout:(nonnull NSString *)message;

/**
 * 其他端设备在（离）线情况
 * @param type        事件类型（1：事件通知，包括上下线，2：状态通知，在线状态）
 * @param deviceType 设备类型
 * （0:default,1:web,2:Android,3:iOS,4:Mac,5:Windows,6:iPad）
 * @param status      设备状态（1：上线或在线，2：下线或离线）
 * @param time        时间（上线或下线时间）
 */
- (void)onDeviceStatus:(int32_t)type deviceType:(int32_t)deviceType status:(int32_t)status time:(int64_t)time;

/**
 * 下载资源cookie变更事件
 * @param cookie      新cookie
 */
- (void)onMainServerCookieRefresh:(nonnull NSString *)cookie;

@end
