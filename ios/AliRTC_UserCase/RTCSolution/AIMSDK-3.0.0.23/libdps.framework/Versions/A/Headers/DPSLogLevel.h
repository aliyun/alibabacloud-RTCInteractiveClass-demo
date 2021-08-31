// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 日志级别
 */
typedef NS_ENUM(NSInteger, DPSLogLevel) {
  DPSLogLevelDPSLOGLEVELDEBUG = 0,
  DPSLogLevelDPSLOGLEVELINFO = 1,
  DPSLogLevelDPSLOGLEVELWARNING = 2,
  DPSLogLevelDPSLOGLEVELERROR = 3,
  DPSLogLevelDPSLOGLEVELFATAL = 4,
};
