// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgContentType.h"
#import <Foundation/Foundation.h>

/**
 * @brief 搜索消息文本参数
 */
@interface AIMPubSearchChatContentParams : NSObject
- (nonnull instancetype)
    initWithKeyword:(nonnull NSString *)keyword
             offset:(int32_t)offset
             maxNum:(int32_t)maxNum
          startTime:(int64_t)startTime
            endTime:(int64_t)endTime
    isAutoHighlight:(BOOL)isAutoHighlight
              isAsc:(BOOL)isAsc
    supportMsgTypes:(nonnull NSArray<NSNumber *> *)supportMsgTypes
    supportSubTypes:(nonnull NSArray<NSNumber *> *)supportSubTypes
            bizTags:(nonnull NSArray<NSString *> *)bizTags
            appCids:(nonnull NSArray<NSString *> *)appCids
          senderIds:(nonnull NSArray<NSString *> *)senderIds;
+ (nonnull instancetype)
    AIMPubSearchChatContentParamsWithKeyword:(nonnull NSString *)keyword
                                      offset:(int32_t)offset
                                      maxNum:(int32_t)maxNum
                                   startTime:(int64_t)startTime
                                     endTime:(int64_t)endTime
                             isAutoHighlight:(BOOL)isAutoHighlight
                                       isAsc:(BOOL)isAsc
                             supportMsgTypes:
                                 (nonnull NSArray<NSNumber *> *)supportMsgTypes
                             supportSubTypes:
                                 (nonnull NSArray<NSNumber *> *)supportSubTypes
                                     bizTags:
                                         (nonnull NSArray<NSString *> *)bizTags
                                     appCids:
                                         (nonnull NSArray<NSString *> *)appCids
                                   senderIds:
                                       (nonnull NSArray<NSString *> *)senderIds;

/**
 * 搜索关键字
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
 * 查询条件：按消息创建时间开始, (时间标准:time_since_epoch)
 */
@property(nonatomic) int64_t startTime;

/**
 * 查询条件：按消息创建时间结束, 默认为所有消息
 */
@property(nonatomic) int64_t endTime;

/**
 * 是否自动高亮，true 则在onSuccess 内返回需高亮的 Range 信息
 */
@property(nonatomic) BOOL isAutoHighlight;

/**
 * 返回结果是否按消息创建时间从小到大排列，默认为升序
 */
@property(nonatomic) BOOL isAsc;

/**
 *  查询条件：需要查询的消息类型列表，如文本，图片，多媒体，自定义等，为空则仅查询文本类型
 */
@property(nonatomic, nonnull) NSArray<NSNumber *> *supportMsgTypes;

/**
 * 查询条件：消息子类型
 */
@property(nonatomic, nonnull) NSArray<NSNumber *> *supportSubTypes;

/**
 * 查询条件：需要查询的biz_tag列表，为空则查所有 (biz_tag
 * 为调用方回写的biz_info)
 */
@property(nonatomic, nonnull) NSArray<NSString *> *bizTags;

/**
 * 查询条件：需要查询的会话列表，为空则查所有
 */
@property(nonatomic, nonnull) NSArray<NSString *> *appCids;

/**
 * 查询条件：需要查询的发送者列表
 */
@property(nonatomic, nonnull) NSArray<NSString *> *senderIds;

@end
