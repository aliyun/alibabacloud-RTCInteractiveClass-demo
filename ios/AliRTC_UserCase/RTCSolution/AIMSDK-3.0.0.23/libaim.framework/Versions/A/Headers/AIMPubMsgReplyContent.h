// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgInnerReplyContent.h"
#import "AIMPubMsgReference.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgReplyContent : NSObject
- (nonnull instancetype)
    initWithReferenceMsg:(nonnull AIMPubMsgReference *)referenceMsg
            replyContent:(nonnull AIMPubMsgInnerReplyContent *)replyContent;
+ (nonnull instancetype)
    AIMPubMsgReplyContentWithReferenceMsg:
        (nonnull AIMPubMsgReference *)referenceMsg
                             replyContent:(nonnull AIMPubMsgInnerReplyContent *)
                                              replyContent;

@property(nonatomic, nonnull) AIMPubMsgReference *referenceMsg;

@property(nonatomic, nonnull) AIMPubMsgInnerReplyContent *replyContent;

@end
