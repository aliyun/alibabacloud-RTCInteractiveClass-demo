// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@interface AIMSearchGroupByGroupNickParams : NSObject
- (nonnull instancetype)initWithKeyword:(nonnull NSString *)keyword
                                 offset:(int32_t)offset
                                 maxNum:(int32_t)maxNum
                                  isAsc:(BOOL)isAsc;
+ (nonnull instancetype)
    AIMSearchGroupByGroupNickParamsWithKeyword:(nonnull NSString *)keyword
                                        offset:(int32_t)offset
                                        maxNum:(int32_t)maxNum
                                         isAsc:(BOOL)isAsc;

/**
 * 搜索关键字（群昵称）
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
 * 返回结果是否按昵称创建时间从小到大排列，默认为升序
 */
@property(nonatomic) BOOL isAsc;

@end
