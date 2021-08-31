// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 网络连接通道类型
 */
typedef NS_ENUM(NSInteger, DPSConnectionType) {
  /**
   * 使用ACCS作为网络连接通道，仅可作为主连接通道
   */
  DPSConnectionTypeConnectionTypeAccs = 0,
  /**
   * 使用Bifrost作为网络连接通道，可作为主连接及文件上传通道
   */
  DPSConnectionTypeConnectionTypeBifrost = 1,
  /**
   * 使用DingTalk文件上传下载通道，仅可作为文件相关通道
   */
  DPSConnectionTypeConnectionTypeDingtalkFile = 2,
};
