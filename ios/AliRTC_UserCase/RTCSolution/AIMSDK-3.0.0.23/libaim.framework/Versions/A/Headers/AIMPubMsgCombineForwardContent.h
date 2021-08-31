// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgCombineForward.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgCombineForwardContent : NSObject
- (nonnull instancetype)initWithCombineForward:
    (nonnull NSArray<AIMPubMsgCombineForward *> *)combineForward;
+ (nonnull instancetype)AIMPubMsgCombineForwardContentWithCombineForward:
    (nonnull NSArray<AIMPubMsgCombineForward *> *)combineForward;

@property(nonatomic, nonnull)
    NSArray<AIMPubMsgCombineForward *> *combineForward;

@end
