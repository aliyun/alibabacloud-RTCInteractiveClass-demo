// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgStructElement.h"
#import <Foundation/Foundation.h>

/**
 * 结构化消息内容
 */
@interface AIMPubMsgStructContent : NSObject
- (nonnull instancetype)initWithElements:
    (nonnull NSArray<AIMPubMsgStructElement *> *)elements;
+ (nonnull instancetype)AIMPubMsgStructContentWithElements:
    (nonnull NSArray<AIMPubMsgStructElement *> *)elements;

@property(nonatomic, nonnull) NSArray<AIMPubMsgStructElement *> *elements;

@end
