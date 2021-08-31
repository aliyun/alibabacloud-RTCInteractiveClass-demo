// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubConversation.h"
#import "AIMPubSearchChatContentParams.h"
#import "AIMPubSearchChatResult.h"
#import "AIMPubSearchConversationResult.h"
#import "AIMSearchGroupByGroupNickParams.h"
#import "AIMSearchGroupParams.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>
@protocol AIMPubSearchChatContentListener;
@protocol AIMPubSearchConvByContentListener;
@protocol AIMPubSearchGroupByNameListener;

/**
 * AIMSearchService
 */
@interface AIMPubSearchService : NSObject

/**
 * 搜索消息文本
 * @param params 搜索消息参数
 * @param listener 监听器
 * 如何分页:
 * 通过offset, max_num来做分页, total_cout 为返回结果
 * 1. 当offset为0时，total_count返回总的本地搜索匹配个数
 * 2. offset > 0 时, total_count为0，可以忽略
 * 示例，如何使用：
 * 1. 以20条每页进行分页，则
 * 2. offset = 0, max_num = 20, 返回 total_count为110，及第一页的20个消息
 * 3. 根据total_count计算总页码：110 / 20 + 1 = 6
 * 4. 获取第二页：offset = 20, max_num = 20, 返回下一个20条消息，total_count =
 * 0可忽略
 */
- (void)searchChatContent:(nonnull AIMPubSearchChatContentParams *)params
                 listener:
                     (nullable id<AIMPubSearchChatContentListener>)listener;

- (void)
    searchChatContentWithBlock:(nonnull AIMPubSearchChatContentParams *)params
                     onSuccess:
                         (nullable void (^)(
                             NSArray<AIMPubSearchChatResult *> *_Nonnull result,
                             int32_t totalCount))onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 搜索消息文本，按照会话返回，每个会话返回一个消息
 * @param params 搜索参数，offset, maxnum以消息个数作为单位，非会话
 * @param listener 监听器
 * 如何分页:
 * 通过offset, max_num来做分页, total_cout 为返回结果
 * 1. 当offset为0时，total_count返回总的本地搜索匹配个数
 * 2. offset > 0 时，total_count为0，可以忽略
 * 示例，如何使用：
 * 1. 以20条每页进行分页，则
 * 2. offset = 0, max_num = 20, 返回 total_count为110，及第一页的20个消息
 * 3. 根据total_count计算总页码：110 / 20 + 1 = 6
 * 4. 获取第二页：offset = 20, max_num = 20, 返回下一个20条消息，total_count =
 * 0可忽略
 */
- (void)
    searchConversationByContent:(nonnull AIMPubSearchChatContentParams *)params
                       listener:(nullable id<AIMPubSearchConvByContentListener>)
                                    listener;

- (void)
    searchConversationByContentWithBlock:
        (nonnull AIMPubSearchChatContentParams *)params
                               onSuccess:
                                   (nullable void (^)(
                                       NSArray<AIMPubSearchConversationResult *>
                                           *_Nonnull result,
                                       int32_t totalCount))onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 搜索会话名称
 * @param params 群名称搜索参数
 * @param listener 监听器
 * 如何分页:
 * 通过offset, max_num来做分页, total_cout 为返回结果
 * 1. 当offset为0时，total_count返回总的本地搜索匹配个数
 * 2. offset > 0 时，total_count为0，可以忽略
 * 示例，如何使用：
 * 1. 以20条每页进行分页，则
 * 2. offset = 0, max_num = 20, 返回 total_count为110，及第一页的20个消息
 * 3. 根据total_count计算总页码：110 / 20 + 1 = 6
 * 4. 获取第二页：offset = 20, max_num = 20, 返回下一个20条消息，total_count =
 * 0可忽略
 */
- (void)searchGroupByName:(nonnull AIMSearchGroupParams *)params
                 listener:
                     (nullable id<AIMPubSearchGroupByNameListener>)listener;

- (void)searchGroupByNameWithBlock:(nonnull AIMSearchGroupParams *)params
                         onSuccess:
                             (nullable void (^)(
                                 NSArray<AIMPubConversation *> *_Nonnull result,
                                 int32_t totalCount))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 根据群昵称搜索相关群
 * @param params 群昵称搜索参数
 * @param listener 监听器
 * 如何分页:
 * 通过offset, max_num来做分页, total_cout 为返回结果
 * 1. 当offset为0时，total_count返回总的本地搜索匹配个数
 * 2. offset > 0 时，total_count为0，可以忽略
 * 示例，如何使用：
 * 1. 以20条每页进行分页，则
 * 2. offset = 0, max_num = 20, 返回 total_count为110，及第一页的20个消息
 * 3. 根据total_count计算总页码：110 / 20 + 1 = 6
 * 4. 获取第二页：offset = 20, max_num = 20, 返回下一个20条消息，total_count =
 * 0可忽略
 */
- (void)searchGroupByGroupNick:(nonnull AIMSearchGroupByGroupNickParams *)params
                      listener:(nullable id<AIMPubSearchGroupByNameListener>)
                                   listener;

- (void)searchGroupByGroupNickWithBlock:
            (nonnull AIMSearchGroupByGroupNickParams *)params
                              onSuccess:(nullable void (^)(
                                            NSArray<AIMPubConversation *>
                                                *_Nonnull result,
                                            int32_t totalCount))onSuccess
                              onFailure:(nullable void (^)(
                                            DPSError *_Nonnull error))onFailure;

@end
