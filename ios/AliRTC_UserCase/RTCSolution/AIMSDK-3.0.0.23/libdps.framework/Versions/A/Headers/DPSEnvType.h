// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 设置当前环境，
 */
typedef NS_ENUM(NSInteger, DPSEnvType) {
  /**
   * 日常
   */
  DPSEnvTypeEnvTypeDaily = 0,
  /**
   * 预发
   */
  DPSEnvTypeEnvTypePreRelease = 1,
  /**
   * 线上
   */
  DPSEnvTypeEnvTypeOnline = 2,
};
