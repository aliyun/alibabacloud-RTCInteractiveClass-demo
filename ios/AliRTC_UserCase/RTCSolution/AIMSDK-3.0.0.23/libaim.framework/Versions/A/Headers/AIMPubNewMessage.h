// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgSourceType.h"
#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>

/**
 * 添加的消息
 */
@interface AIMPubNewMessage : NSObject
- (nonnull instancetype)initWithMsg:(nonnull AIMPubMessage *)msg
                               type:(AIMMsgSourceType)type;
+ (nonnull instancetype)AIMPubNewMessageWithMsg:(nonnull AIMPubMessage *)msg
                                           type:(AIMMsgSourceType)type;

@property(nonatomic, nonnull) AIMPubMessage *msg;

@property(nonatomic) AIMMsgSourceType type;

@end
