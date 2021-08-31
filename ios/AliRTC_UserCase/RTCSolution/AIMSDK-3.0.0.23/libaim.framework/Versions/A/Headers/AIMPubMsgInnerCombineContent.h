// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgContentType.h"
#import "AIMPubMsgReplyContent.h"
#import "AIMPubMsgSimpleContent.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgInnerCombineContent : NSObject
- (nonnull instancetype)
    initWithContentType:(AIMMsgContentType)contentType
          simpleContent:(nonnull AIMPubMsgSimpleContent *)simpleContent
           replyContent:(nonnull AIMPubMsgReplyContent *)replyContent;
+ (nonnull instancetype)
    AIMPubMsgInnerCombineContentWithContentType:(AIMMsgContentType)contentType
                                  simpleContent:
                                      (nonnull AIMPubMsgSimpleContent *)
                                          simpleContent
                                   replyContent:
                                       (nonnull AIMPubMsgReplyContent *)
                                           replyContent;

@property(nonatomic) AIMMsgContentType contentType;

@property(nonatomic, nonnull) AIMPubMsgSimpleContent *simpleContent;

@property(nonatomic, nonnull) AIMPubMsgReplyContent *replyContent;

@end
