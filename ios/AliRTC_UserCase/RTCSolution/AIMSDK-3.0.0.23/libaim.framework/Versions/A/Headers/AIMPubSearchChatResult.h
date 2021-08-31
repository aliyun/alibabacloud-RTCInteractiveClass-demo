// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import "AIMSearchHighlightRange.h"
#import <Foundation/Foundation.h>

/**
 * 消息内容搜索返回结果
 */
@interface AIMPubSearchChatResult : NSObject
- (nonnull instancetype)
    initWithMessage:(nonnull AIMPubMessage *)message
             ranges:(nonnull NSArray<AIMSearchHighlightRange *> *)ranges;
+ (nonnull instancetype)
    AIMPubSearchChatResultWithMessage:(nonnull AIMPubMessage *)message
                               ranges:
                                   (nonnull NSArray<AIMSearchHighlightRange *>
                                        *)ranges;

/**
 * 消息体
 */
@property(nonatomic, nonnull) AIMPubMessage *message;

/**
 * 高亮信息
 */
@property(nonatomic, nonnull) NSArray<AIMSearchHighlightRange *> *ranges;

@end
