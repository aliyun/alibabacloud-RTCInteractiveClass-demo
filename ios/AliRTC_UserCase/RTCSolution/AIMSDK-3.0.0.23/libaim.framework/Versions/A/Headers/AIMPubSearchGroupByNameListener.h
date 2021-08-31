// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * SearchConversationByContent监听
 */
@protocol AIMPubSearchGroupByNameListener

- (void)onSuccess:(nonnull NSArray<AIMPubConversation *> *)result
       totalCount:(int32_t)totalCount;

- (void)onFailure:(nonnull DPSError *)error;

@end
