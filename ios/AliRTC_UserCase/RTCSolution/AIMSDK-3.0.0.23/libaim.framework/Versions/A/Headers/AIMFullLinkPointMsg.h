// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMFullLinkPointBase.h"
#import "AIMTraceMsgInfo.h"
#import <Foundation/Foundation.h>

/**
 *消息链路埋点字段
 */
@interface AIMFullLinkPointMsg : NSObject
- (nonnull instancetype)
    initWithBasePoint:(nonnull AIMFullLinkPointBase *)basePoint
             msgInfos:(nonnull NSArray<AIMTraceMsgInfo *> *)msgInfos;
+ (nonnull instancetype)
    AIMFullLinkPointMsgWithBasePoint:(nonnull AIMFullLinkPointBase *)basePoint
                            msgInfos:
                                (nonnull NSArray<AIMTraceMsgInfo *> *)msgInfos;

@property(nonatomic, nonnull) AIMFullLinkPointBase *basePoint;

@property(nonatomic, nonnull) NSArray<AIMTraceMsgInfo *> *msgInfos;

@end
