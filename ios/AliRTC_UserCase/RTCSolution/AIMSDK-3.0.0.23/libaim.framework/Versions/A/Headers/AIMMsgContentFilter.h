// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息内容过滤条件
 */
@interface AIMMsgContentFilter : NSObject
- (nonnull instancetype)initWithContentType:(int32_t)contentType
                          customContentType:
                              (nonnull NSString *)customContentType;
+ (nonnull instancetype)
    AIMMsgContentFilterWithContentType:(int32_t)contentType
                     customContentType:(nonnull NSString *)customContentType;

/**
 * 消息类型（必填）
 */
@property(nonatomic) int32_t contentType;

/**
 * 自定义消息子类型（可选，内容类型int32_t, 如果不选择为空）
 */
@property(nonatomic, nonnull) NSString *customContentType;

@end
