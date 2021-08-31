// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 链接状态
 */
typedef NS_ENUM(NSInteger, DPSConnectionStatus) {
  /**
   * 未连接
   */
  DPSConnectionStatusCsUnconnected = 0,
  /**
   * 正在连接
   */
  DPSConnectionStatusCsConnecting = 1,
  /**
   * 已连接
   */
  DPSConnectionStatusCsConnected = 2,
  /**
   * 正在登录
   */
  DPSConnectionStatusCsAuthing = 3,
  /**
   * 登录成功
   */
  DPSConnectionStatusCsAuthed = 4,
};
