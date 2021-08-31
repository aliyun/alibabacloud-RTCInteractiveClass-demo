// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 网络类型
 */
typedef NS_ENUM(NSInteger, DPSNetType) {
  /**
   * 无网络
   */
  DPSNetTypeNtNotReachable = 0,
  /**
   * WIFI
   */
  DPSNetTypeNtWifi = 1,
  /**
   * 有线网络
   */
  DPSNetTypeNtWire = 2,
  /**
   * 2G
   */
  DPSNetTypeNt2g = 3,
  /**
   * 3G
   */
  DPSNetTypeNt3g = 4,
  /**
   * 4G
   */
  DPSNetTypeNt4g = 5,
  /**
   * 5G
   */
  DPSNetTypeNt5g = 6,
  /**
   * 其他
   */
  DPSNetTypeNtOther = 100,
};
