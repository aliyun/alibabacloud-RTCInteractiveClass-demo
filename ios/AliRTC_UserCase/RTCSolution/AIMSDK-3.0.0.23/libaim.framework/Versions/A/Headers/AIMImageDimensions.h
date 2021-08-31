// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 图片尺寸
 */
@interface AIMImageDimensions : NSObject
- (nonnull instancetype)initWithWidth:(int32_t)width height:(int32_t)height;
+ (nonnull instancetype)AIMImageDimensionsWithWidth:(int32_t)width
                                             height:(int32_t)height;

@property(nonatomic) int32_t width;

@property(nonatomic) int32_t height;

@end
