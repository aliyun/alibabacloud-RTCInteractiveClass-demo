// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 结构化消息uid元素
 */
@interface AIMPubMsgStructElementUid : NSObject
- (nonnull instancetype)initWithUid:(nonnull NSString *)uid
                        defaultNick:(nonnull NSString *)defaultNick
                             prefix:(nonnull NSString *)prefix;
+ (nonnull instancetype)
    AIMPubMsgStructElementUidWithUid:(nonnull NSString *)uid
                         defaultNick:(nonnull NSString *)defaultNick
                              prefix:(nonnull NSString *)prefix;

@property(nonatomic, nonnull) NSString *uid;

@property(nonatomic, nonnull) NSString *defaultNick;

@property(nonatomic, nonnull) NSString *prefix;

@end
