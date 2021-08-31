// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@interface AIMSearchGroupParams : NSObject
- (nonnull instancetype)initWithKeyword:(nonnull NSString *)keyword
                                 offset:(int32_t)offset
                                 maxNum:(int32_t)maxNum
                              startTime:(int64_t)startTime
                                endTime:(int64_t)endTime
                                  isAsc:(BOOL)isAsc;
+ (nonnull instancetype)AIMSearchGroupParamsWithKeyword:
                            (nonnull NSString *)keyword
                                                 offset:(int32_t)offset
                                                 maxNum:(int32_t)maxNum
                                              startTime:(int64_t)startTime
                                                endTime:(int64_t)endTime
                                                  isAsc:(BOOL)isAsc;

/**
 * 搜索关键字（群名称）
 */
@property(nonatomic, nonnull) NSString *keyword;

/**
 * 返回结果起始位置，用于搜索结果分页，offset >= 0，默认为第一页
 */
@property(nonatomic) int32_t offset;

/**
 * 单次返回结果个数， 0 < max_num <= 1000, 默认为20个
 */
@property(nonatomic) int32_t maxNum;

/**
 * 查询条件：按会话创建时间开始, (时间标准:time_since_epoch)
 */
@property(nonatomic) int64_t startTime;

/**
 * 查询条件：按会啊话创建时间结束, 默认为所有消息
 */
@property(nonatomic) int64_t endTime;

/**
 * 返回结果是否按会话最近更新时间从小到大排列，默认为升序
 */
@property(nonatomic) BOOL isAsc;

@end
