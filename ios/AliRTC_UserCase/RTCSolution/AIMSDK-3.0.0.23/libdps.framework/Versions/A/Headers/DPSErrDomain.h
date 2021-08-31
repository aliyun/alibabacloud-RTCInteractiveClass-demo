// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 错误归属域
 */
typedef NS_ENUM(NSInteger, DPSErrDomain) {
  /**
   * 客户端错误
   */
  DPSErrDomainDPSERRDOMAINCLIENT,
  /**
   * 服务端错误
   */
  DPSErrDomainDPSERRDOMAINSERVER,
  /**
   * 外部错误
   */
  DPSErrDomainDPSERREXTERNAL,
};
