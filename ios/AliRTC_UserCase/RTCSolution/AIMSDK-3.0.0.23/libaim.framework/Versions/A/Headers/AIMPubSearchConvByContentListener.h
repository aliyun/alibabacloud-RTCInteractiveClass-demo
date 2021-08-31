// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubSearchConversationResult.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * SearchConversationByContent监听
 */
@protocol AIMPubSearchConvByContentListener

- (void)onSuccess:(nonnull NSArray<AIMPubSearchConversationResult *> *)result
       totalCount:(int32_t)totalCount;

- (void)onFailure:(nonnull DPSError *)error;

@end
