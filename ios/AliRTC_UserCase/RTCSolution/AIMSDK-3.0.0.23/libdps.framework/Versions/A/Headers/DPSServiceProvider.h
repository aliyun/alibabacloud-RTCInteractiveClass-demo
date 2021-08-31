// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
@class DPSRpcService;
@class DPSSyncService;

@interface DPSServiceProvider : NSObject

- (nullable DPSRpcService *)getRpcService;

- (nullable DPSSyncService *)getSyncService;

@end
