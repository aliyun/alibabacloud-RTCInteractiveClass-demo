// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息查询高亮位置信息
 */
@interface AIMSearchHighlightRange : NSObject
- (nonnull instancetype)initWithStart:(int64_t)start length:(int64_t)length;
+ (nonnull instancetype)AIMSearchHighlightRangeWithStart:(int64_t)start
                                                  length:(int64_t)length;

/**
 * 高亮开始位置
 */
@property(nonatomic) int64_t start;

/**
 * 高亮文本长度
 */
@property(nonatomic) int64_t length;

@end
