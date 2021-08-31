// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 禁言类型
 */
typedef NS_ENUM(NSInteger, AIMGroupSilencedStatus) {
  /**
   * 既不在白名单也不在黑名单
   */
  AIMGroupSilencedStatusGroupSilenceStatusNormal = 0,
  /**
   * 白名单
   */
  AIMGroupSilencedStatusGroupSilenceStatusInWhitelist = 1,
  /**
   * 黑名单
   */
  AIMGroupSilencedStatusGroupSilenceStatusInBlacklist = 2,
};
