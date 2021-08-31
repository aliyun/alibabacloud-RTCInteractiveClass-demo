// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 *会话信息字段
 */
@interface AIMTraceConvInfo : NSObject
- (nonnull instancetype)initWithCid:(nonnull NSString *)cid
                            bizType:(nonnull NSString *)bizType
                          targetUid:(nonnull NSString *)targetUid;
+ (nonnull instancetype)AIMTraceConvInfoWithCid:(nonnull NSString *)cid
                                        bizType:(nonnull NSString *)bizType
                                      targetUid:(nonnull NSString *)targetUid;

@property(nonatomic, nonnull) NSString *cid;

@property(nonatomic, nonnull) NSString *bizType;

@property(nonatomic, nonnull) NSString *targetUid;

@end
