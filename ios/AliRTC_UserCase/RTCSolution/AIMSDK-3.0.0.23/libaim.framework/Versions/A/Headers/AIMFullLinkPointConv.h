// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMFullLinkPointBase.h"
#import "AIMTraceConvInfo.h"
#import <Foundation/Foundation.h>

/**
 *会话链路埋点字段
 */
@interface AIMFullLinkPointConv : NSObject
- (nonnull instancetype)
    initWithBasePoint:(nonnull AIMFullLinkPointBase *)basePoint
            convInfos:(nonnull NSArray<AIMTraceConvInfo *> *)convInfos;
+ (nonnull instancetype)
    AIMFullLinkPointConvWithBasePoint:(nonnull AIMFullLinkPointBase *)basePoint
                            convInfos:(nonnull NSArray<AIMTraceConvInfo *> *)
                                          convInfos;

@property(nonatomic, nonnull) AIMFullLinkPointBase *basePoint;

@property(nonatomic, nonnull) NSArray<AIMTraceConvInfo *> *convInfos;

@end
