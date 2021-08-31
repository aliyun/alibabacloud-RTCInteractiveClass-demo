// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 自定义消息内容
 */
@interface AIMMsgCustomContent : NSObject
- (nonnull instancetype)initWithType:(int32_t)type
                          binaryData:(nonnull NSData *)binaryData
                               title:(nonnull NSString *)title
                             summary:(nonnull NSString *)summary
                             degrade:(nonnull NSString *)degrade;
+ (nonnull instancetype)AIMMsgCustomContentWithType:(int32_t)type
                                         binaryData:(nonnull NSData *)binaryData
                                              title:(nonnull NSString *)title
                                            summary:(nonnull NSString *)summary
                                            degrade:(nonnull NSString *)degrade;

@property(nonatomic) int32_t type;

@property(nonatomic, nonnull) NSData *binaryData;

@property(nonatomic, nonnull) NSString *title;

@property(nonatomic, nonnull) NSString *summary;

@property(nonatomic, nonnull) NSString *degrade;

@end
