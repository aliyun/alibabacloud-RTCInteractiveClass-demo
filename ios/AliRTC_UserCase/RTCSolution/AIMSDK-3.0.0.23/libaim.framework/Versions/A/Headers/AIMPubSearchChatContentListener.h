// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubSearchChatResult.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * SearchChatContent 监听
 */
@protocol AIMPubSearchChatContentListener

- (void)onSuccess:(nonnull NSArray<AIMPubSearchChatResult *> *)result
       totalCount:(int32_t)totalCount;

- (void)onFailure:(nonnull DPSError *)error;

@end
