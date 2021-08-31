// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMFullLinkPointBase.h"
#import "AIMFullLinkPointConv.h"
#import "AIMFullLinkPointMsg.h"
#import <Foundation/Foundation.h>
@protocol AIMTraceListener;

@interface AIMTraceService : NSObject

- (void)registerTraceListener:(nullable id<AIMTraceListener>)listener;

@end
