// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSError.h"
#import <Foundation/Foundation.h>

@protocol DPSModuleEventHandlerCallback

- (void)onSuccess;

- (void)onFailure:(nonnull DPSError *)error;

@end
