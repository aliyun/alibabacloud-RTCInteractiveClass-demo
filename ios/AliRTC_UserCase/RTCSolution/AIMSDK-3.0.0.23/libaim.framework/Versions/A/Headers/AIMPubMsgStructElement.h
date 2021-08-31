// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgStructElementType.h"
#import "AIMPubMsgStructElementAt.h"
#import "AIMPubMsgStructElementUid.h"
#import "AIMPubMsgTextContent.h"
#import <Foundation/Foundation.h>

/**
 * 结构化消息元素
 */
@interface AIMPubMsgStructElement : NSObject
- (nonnull instancetype)
    initWithElementType:(AIMMsgStructElementType)elementType
            textContent:(nonnull AIMPubMsgTextContent *)textContent
             uidElement:(nonnull AIMPubMsgStructElementUid *)uidElement
              atElement:(nonnull AIMPubMsgStructElementAt *)atElement;
+ (nonnull instancetype)
    AIMPubMsgStructElementWithElementType:(AIMMsgStructElementType)elementType
                              textContent:
                                  (nonnull AIMPubMsgTextContent *)textContent
                               uidElement:(nonnull AIMPubMsgStructElementUid *)
                                              uidElement
                                atElement:(nonnull AIMPubMsgStructElementAt *)
                                              atElement;

@property(nonatomic) AIMMsgStructElementType elementType;

@property(nonatomic, nonnull) AIMPubMsgTextContent *textContent;

@property(nonatomic, nonnull) AIMPubMsgStructElementUid *uidElement;

@property(nonatomic, nonnull) AIMPubMsgStructElementAt *atElement;

@end
