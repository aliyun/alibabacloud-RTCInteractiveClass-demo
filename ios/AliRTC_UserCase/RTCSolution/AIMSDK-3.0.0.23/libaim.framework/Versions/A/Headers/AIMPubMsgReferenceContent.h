// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgContentType.h"
#import "AIMPubMsgSimpleContent.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgReferenceContent : NSObject
- (nonnull instancetype)initWithContentType:(AIMMsgContentType)contentType
                                    content:(nonnull AIMPubMsgSimpleContent *)
                                                content;
+ (nonnull instancetype)
    AIMPubMsgReferenceContentWithContentType:(AIMMsgContentType)contentType
                                     content:(nonnull AIMPubMsgSimpleContent *)
                                                 content;

@property(nonatomic) AIMMsgContentType contentType;

@property(nonatomic, nonnull) AIMPubMsgSimpleContent *content;

@end
