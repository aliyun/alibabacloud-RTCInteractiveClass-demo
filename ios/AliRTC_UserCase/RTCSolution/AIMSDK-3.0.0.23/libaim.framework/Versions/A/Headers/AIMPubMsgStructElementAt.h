// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 结构化消息At元素
 */
@interface AIMPubMsgStructElementAt : NSObject
- (nonnull instancetype)initWithIsAtAll:(BOOL)isAtAll
                                    uid:(nonnull NSString *)uid
                            defaultNick:(nonnull NSString *)defaultNick;
+ (nonnull instancetype)
    AIMPubMsgStructElementAtWithIsAtAll:(BOOL)isAtAll
                                    uid:(nonnull NSString *)uid
                            defaultNick:(nonnull NSString *)defaultNick;

@property(nonatomic) BOOL isAtAll;

@property(nonatomic, nonnull) NSString *uid;

@property(nonatomic, nonnull) NSString *defaultNick;

@end
