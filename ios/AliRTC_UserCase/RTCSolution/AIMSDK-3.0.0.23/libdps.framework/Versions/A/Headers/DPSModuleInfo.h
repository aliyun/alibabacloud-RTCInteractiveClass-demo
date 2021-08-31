// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import <Foundation/Foundation.h>
@class DPSModuleEventHandler;

DPS_DECL
@interface DPSModuleInfo : NSObject

- (nonnull NSString *)getModuleName;

- (nullable DPSModuleEventHandler *)getModuleEventHandler;

@end
