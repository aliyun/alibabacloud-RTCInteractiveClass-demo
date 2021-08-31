// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * RPC数据类型
 */
typedef NS_ENUM(NSInteger, DPSRpcDataType) {
  /**
   * msgpack格式
   */
  DPSRpcDataTypeDtMsgpack = 0,
  /**
   * json格式
   */
  DPSRpcDataTypeDtJson = 1,
};
