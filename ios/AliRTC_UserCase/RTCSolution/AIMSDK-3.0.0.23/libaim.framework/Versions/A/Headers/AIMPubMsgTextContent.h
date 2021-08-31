// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 文本消息内容
 */
@interface AIMPubMsgTextContent : NSObject
- (nonnull instancetype)initWithText:(nonnull NSString *)text;
+ (nonnull instancetype)AIMPubMsgTextContentWithText:(nonnull NSString *)text;

/**
 * 内容
 */
@property(nonatomic, nonnull) NSString *text;

@end
