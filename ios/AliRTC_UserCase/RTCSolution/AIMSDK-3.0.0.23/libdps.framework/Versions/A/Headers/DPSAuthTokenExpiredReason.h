// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 需要获取token的原因
 */
typedef NS_ENUM(NSInteger, DPSAuthTokenExpiredReason) {
  /**
   * 未知原因
   */
  DPSAuthTokenExpiredReasonUnknown = 0,
  /**
   * 本地无缓存的token，首次登陆或无法解析本地token
   */
  DPSAuthTokenExpiredReasonNoLocalToken = 1,
  /**
   * 本地token超期（30天）
   */
  DPSAuthTokenExpiredReasonLocalTokenExpired = 2,
  /**
   * 服务端判定 uid 和 token 不匹配
   */
  DPSAuthTokenExpiredReasonUidTokenNotMatch = 3,
  /**
   * refreshToken为空，无法刷新accessToken
   */
  DPSAuthTokenExpiredReasonEmptyRefreshToken = 4,
  /**
   * 刷新token失败, 服务端返回刷新失败
   */
  DPSAuthTokenExpiredReasonRefreshTokenFailed = 5,
  /**
   * 刷新token失效，需要更新refreshToken
   */
  DPSAuthTokenExpiredReasonRefreshTokenExpired = 6,
};
