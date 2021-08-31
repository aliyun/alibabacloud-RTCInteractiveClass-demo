// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSLogLevel.h"
#import <Foundation/Foundation.h>

/**
 * Log 监听
 */
@protocol DPSLogHandler

- (void)onLog:(DPSLogLevel)logLevel logContent:(nonnull NSString *)logContent;

@end
