// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 发送多媒体信息进度
 */
@interface AIMMsgSendMediaProgress : NSObject
- (nonnull instancetype)initWithCid:(nonnull NSString *)cid
                            localid:(nonnull NSString *)localid
                           progress:(double)progress;
+ (nonnull instancetype)AIMMsgSendMediaProgressWithCid:(nonnull NSString *)cid
                                               localid:
                                                   (nonnull NSString *)localid
                                              progress:(double)progress;

@property(nonatomic, nonnull) NSString *cid;

@property(nonatomic, nonnull) NSString *localid;

@property(nonatomic) double progress;

@end
