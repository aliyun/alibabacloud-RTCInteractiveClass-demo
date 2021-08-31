// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import "AIMPubMessage.h"
#import "AIMSearchHighlightRange.h"
#import <Foundation/Foundation.h>

/**
 * 会话内容搜索返回结果
 */
@interface AIMPubSearchConversationResult : NSObject
- (nonnull instancetype)
    initWithConversation:(nonnull AIMPubConversation *)conversation
            firstMessage:(nonnull AIMPubMessage *)firstMessage
                  ranges:(nonnull NSArray<AIMSearchHighlightRange *> *)ranges;
+ (nonnull instancetype)
    AIMPubSearchConversationResultWithConversation:
        (nonnull AIMPubConversation *)conversation
                                      firstMessage:
                                          (nonnull AIMPubMessage *)firstMessage
                                            ranges:
                                                (nonnull NSArray<
                                                    AIMSearchHighlightRange *>
                                                     *)ranges;

/**
 * 搜索匹配的会话信息
 */
@property(nonatomic, nonnull) AIMPubConversation *conversation;

/**
 * 该会话匹配的第一条消息
 */
@property(nonatomic, nonnull) AIMPubMessage *firstMessage;

/**
 * 消息内容高亮位置
 */
@property(nonatomic, nonnull) NSArray<AIMSearchHighlightRange *> *ranges;

@end
