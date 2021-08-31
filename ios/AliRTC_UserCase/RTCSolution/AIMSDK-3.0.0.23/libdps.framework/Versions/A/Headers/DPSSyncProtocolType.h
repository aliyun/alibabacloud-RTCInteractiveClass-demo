// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Sync 协议类型
 */
typedef NS_ENUM(NSInteger, DPSSyncProtocolType) {
  /**
   * 可靠推送
   */
  DPSSyncProtocolTypeReliable,
  /**
   * 不可靠推送
   */
  DPSSyncProtocolTypeUnreliable,
};
