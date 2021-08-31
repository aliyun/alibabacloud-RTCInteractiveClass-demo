// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgContentFilter.h"
#import <Foundation/Foundation.h>

/**
 * 消息过滤条件
 */
@interface AIMMsgFilter : NSObject
- (nonnull instancetype)initWithContent:
                            (nonnull NSArray<AIMMsgContentFilter *> *)content
                           filterRecall:(BOOL)filterRecall
                             orderInAsc:(BOOL)orderInAsc;
+ (nonnull instancetype)AIMMsgFilterWithContent:
                            (nonnull NSArray<AIMMsgContentFilter *> *)content
                                   filterRecall:(BOOL)filterRecall
                                     orderInAsc:(BOOL)orderInAsc;

/**
 * 消息类型选项（可选）
 */
@property(nonatomic, nonnull) NSArray<AIMMsgContentFilter *> *content;

/**
 * 是否过滤撤回消息（可选）
 */
@property(nonatomic) BOOL filterRecall;

/**
 * 是否按照时间升序排列（可选）
 */
@property(nonatomic) BOOL orderInAsc;

@end
