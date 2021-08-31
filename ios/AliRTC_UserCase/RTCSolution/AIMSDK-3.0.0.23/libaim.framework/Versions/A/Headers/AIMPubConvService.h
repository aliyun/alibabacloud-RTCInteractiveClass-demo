// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMConvTypingCommand.h"
#import "AIMConvTypingMessageContent.h"
#import "AIMPubConvCreateSingleConvParam.h"
#import "AIMPubConversation.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>
@protocol AIMConvServiceCompleteListener;
@protocol AIMConvSetTopListener;
@protocol AIMPubConvChangeListener;
@protocol AIMPubConvCreateSingleConvListener;
@protocol AIMPubConvGetConvListener;
@protocol AIMPubConvGetSingleConvListener;
@protocol AIMPubConvListListener;

@interface AIMPubConvService : NSObject

/**
 * 创建单聊会话。
 * @param param  CreateConversationParams结构
 * @param listener 监听器
 */
- (void)
    createSingleConversation:(nonnull AIMPubConvCreateSingleConvParam *)param
                    listener:(nullable id<AIMPubConvCreateSingleConvListener>)
                                 listener;

- (void)
    createSingleConversationWithBlock:
        (nonnull AIMPubConvCreateSingleConvParam *)param
                            onSuccess:
                                (nullable void (^)(
                                    AIMPubConversation *_Nonnull conv))onSuccess
                            onFailure:(nullable void (^)(
                                          DPSError *_Nonnull error))onFailure;

/**
 * 获取会话列表，隐藏的会话不会返回（拉取会话不需要rpc请求,sdk内部有同步会话机制）
 * @param offset 从offset开始拉取（排序index，根据置顶及最后更新时间进行排序）
 * @param count     需要的Conversation个数
 * @param listener 监听器
 */
- (void)listLocalConversationsWithOffset:(int32_t)offset
                                   count:(int32_t)count
                                listener:
                                    (nullable id<AIMPubConvGetConvListener>)
                                        listener;

- (void)listLocalConversationsWithOffsetWithBlock:(int32_t)offset
                                            count:(int32_t)count
                                        onSuccess:
                                            (nullable void (^)(
                                                NSArray<AIMPubConversation *>
                                                    *_Nonnull result))onSuccess
                                        onFailure:(nullable void (^)(
                                                      DPSError *_Nonnull error))
                                                      onFailure;

/**
 * 获取本地会话列表，隐藏的会话不会返回（本地，不会有rpc请求）。
 * @param appCid
 * 从指定appCid开始拉取(当appCid为空时，表示拉首屏，会从第0个会话拉取)
 * @param count     需要的Conversation个数
 * @param listener 监听器
 */
- (void)listLocalConversationsWithCid:(nonnull NSString *)appCid
                                count:(int32_t)count
                             listener:(nullable id<AIMPubConvGetConvListener>)
                                          listener;

- (void)
    listLocalConversationsWithCidWithBlock:(nonnull NSString *)appCid
                                     count:(int32_t)count
                                 onSuccess:(nullable void (^)(
                                               NSArray<AIMPubConversation *>
                                                   *_Nonnull result))onSuccess
                                 onFailure:
                                     (nullable void (^)(
                                         DPSError *_Nonnull error))onFailure;

/**
 * 获取本地会话列表，包括所有状态的会话（也会返回隐藏的）。
 * @param offset 从offset开始拉取（排序index，根据置顶及最后更新时间进行排序）
 * @param count     需要拉取的Conversation个数
 * @param listener 监听器
 */
- (void)listAllStatusLocalConvs:(int32_t)offset
                          count:(int32_t)count
                       listener:
                           (nullable id<AIMPubConvGetConvListener>)listener;

- (void)listAllStatusLocalConvsWithBlock:(int32_t)offset
                                   count:(int32_t)count
                               onSuccess:(nullable void (^)(
                                             NSArray<AIMPubConversation *>
                                                 *_Nonnull result))onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 获取会话Id对应的会话。
 * @param appCid    会话id
 * @param listener 监听器
 */
- (void)getConversation:(nonnull NSString *)appCid
               listener:(nullable id<AIMPubConvGetSingleConvListener>)listener;

- (void)
    getConversationWithBlock:(nonnull NSString *)appCid
                   onSuccess:(nullable void (^)(
                                 AIMPubConversation *_Nonnull conv))onSuccess
                   onFailure:
                       (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 获取会话appCid集合对应的会话列表。
 * @param appCids    会话集合id
 * @param listener 监听器
 */
- (void)getConversations:(nonnull NSArray<NSString *> *)appCids
                listener:(nullable id<AIMPubConvGetConvListener>)listener;

- (void)
    getConversationsWithBlock:(nonnull NSArray<NSString *> *)appCids
                    onSuccess:(nullable void (^)(NSArray<AIMPubConversation *>
                                                     *_Nonnull result))onSuccess
                    onFailure:
                        (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 批量获取会话Id对应的本地会话（如果本地不存在则不会发送rpc）。
 * @param appCids    会话id
 * @param listener 监听器
 */
- (void)getLocalConversations:(nonnull NSArray<NSString *> *)appCids
                     listener:(nullable id<AIMPubConvGetConvListener>)listener;

- (void)
    getLocalConversationsWithBlock:(nonnull NSArray<NSString *> *)appCids
                         onSuccess:
                             (nullable void (^)(NSArray<AIMPubConversation *>
                                                    *_Nonnull result))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 根据user_id获取对应的会话列表集合。
 * @param userId    用户id
 * @param listener 监听器
 */
- (void)getSingleConversations:(nonnull NSString *)userId
                      listener:(nullable id<AIMPubConvGetConvListener>)listener;

- (void)getSingleConversationsWithBlock:(nonnull NSString *)userId
                              onSuccess:(nullable void (^)(
                                            NSArray<AIMPubConversation *>
                                                *_Nonnull result))onSuccess
                              onFailure:(nullable void (^)(
                                            DPSError *_Nonnull error))onFailure;

/**
 * 批量根据user_ids获取对应的会话列表集合。
 * @param userIds    用户id集合
 * @param listener 监听器
 */
- (void)getSingleConversationsWithUserIds:(nonnull NSArray<NSString *> *)userIds
                                 listener:
                                     (nullable id<AIMPubConvGetConvListener>)
                                         listener;

- (void)getSingleConversationsWithUserIdsWithBlock:
            (nonnull NSArray<NSString *> *)userIds
                                         onSuccess:
                                             (nullable void (^)(
                                                 NSArray<AIMPubConversation *>
                                                     *_Nonnull result))onSuccess
                                         onFailure:
                                             (nullable void (^)(
                                                 DPSError *_Nonnull error))
                                                 onFailure;

/**
 * 从本地DB物理删除会话，并且会同步删除会话的所有本地消息(再次拉取到会话消息会再次同步)，群会删除本地群成员，没有rpc发送
 * @param appCid    会话id
 * @param listener 监听器
 */
- (void)removeLocalConversation:(nonnull NSString *)appCid
                       listener:(nullable id<AIMConvServiceCompleteListener>)
                                    listener;

- (void)removeLocalConversationWithBlock:(nonnull NSString *)appCid
                               onSuccess:(nullable void (^)())onSuccess
                               onFailure:
                                   (nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 发送正在输入消息事件给接收方，接收者需要精确receiverid，只对单聊会话有效。发送typing事件建议5s为间隔。
 * @param appCid   会话id
 * @param receiverid   接受者id
 * @param command   TypingCommand
 * @param type TypingMessageContent
 * @param listener 监听器
 */
- (void)updateTypingStatus:(nonnull NSString *)appCid
                receiverId:(nonnull NSString *)receiverId
                   command:(AIMConvTypingCommand)command
                      type:(AIMConvTypingMessageContent)type
                  listener:
                      (nullable id<AIMConvServiceCompleteListener>)listener;

- (void)updateTypingStatusWithBlock:(nonnull NSString *)appCid
                         receiverId:(nonnull NSString *)receiverId
                            command:(AIMConvTypingCommand)command
                               type:(AIMConvTypingMessageContent)type
                          onSuccess:(nullable void (^)())onSuccess
                          onFailure:(nullable void (^)(
                                        DPSError *_Nonnull error))onFailure;

/**
 * 更新草稿，草稿只在本地存储。
 * @param appCid   会话id
 * @param draft   草稿内容
 * @param listener 监听器
 */
- (void)updateDraftMessage:(nonnull NSString *)appCid
                     draft:(nonnull NSString *)draft
                  listener:
                      (nullable id<AIMConvServiceCompleteListener>)listener;

- (void)updateDraftMessageWithBlock:(nonnull NSString *)appCid
                              draft:(nonnull NSString *)draft
                          onSuccess:(nullable void (^)())onSuccess
                          onFailure:(nullable void (^)(
                                        DPSError *_Nonnull error))onFailure;

/**
 * 全量更新本地extension数据，只在本地存储。
 * @param appCid   会话id
 * @param localExt 扩展信息
 * @param listener 监听器
 */
- (void)updateLocalExtension:(nonnull NSString *)appCid
                    localExt:
                        (nonnull NSDictionary<NSString *, NSString *> *)localExt
                    listener:
                        (nullable id<AIMConvServiceCompleteListener>)listener;

- (void)
    updateLocalExtensionWithBlock:(nonnull NSString *)appCid
                         localExt:
                             (nonnull NSDictionary<NSString *, NSString *> *)
                                 localExt
                        onSuccess:(nullable void (^)())onSuccess
                        onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                      onFailure;

/**
 * 增量更新数据(add or update),不影响其他key
 * @param appCid   会话id
 * @param localExt 扩展信息
 * @param listener 监听器
 */
- (void)updateLocalExtensionByKeys:(nonnull NSString *)appCid
                          localExt:
                              (nonnull NSDictionary<NSString *, NSString *> *)
                                  localExt
                          listener:(nullable id<AIMConvServiceCompleteListener>)
                                       listener;

- (void)
    updateLocalExtensionByKeysWithBlock:(nonnull NSString *)appCid
                               localExt:
                                   (nonnull NSDictionary<NSString *, NSString *>
                                        *)localExt
                              onSuccess:(nullable void (^)())onSuccess
                              onFailure:(nullable void (^)(
                                            DPSError *_Nonnull error))onFailure;

/**
 * 批量增量更新数据(add or update),不影响其他key
 * @param appCid2ext appCid to localext的map
 * @param listener 监听器
 */
- (void)bulkUpdateLocalExtensionByKeys:
            (nonnull NSDictionary<
                NSString *, NSDictionary<NSString *, NSString *> *> *)appCid2ext
                              listener:
                                  (nullable id<AIMConvServiceCompleteListener>)
                                      listener;

- (void)bulkUpdateLocalExtensionByKeysWithBlock:
            (nonnull NSDictionary<
                NSString *, NSDictionary<NSString *, NSString *> *> *)appCid2ext
                                      onSuccess:(nullable void (^)())onSuccess
                                      onFailure:(nullable void (^)(
                                                    DPSError *_Nonnull error))
                                                    onFailure;

/**
 * 隐藏会话，会话将处于不可见状态，当会话状态变化时，例如会话收到消息，会话内数据变化时，将变为可见状态。
 * @param appCid   会话id
 * @param listener 监听器
 */
- (void)hide:(nonnull NSString *)appCid
    listener:(nullable id<AIMConvServiceCompleteListener>)listener;

- (void)hideWithBlock:(nonnull NSString *)appCid
            onSuccess:(nullable void (^)())onSuccess
            onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 更新会话是否免打扰
 * 这里只是更新会话状态的标示，会话变更和消息新增等还是会广播出来，是否通知用户由开发者决定
 * @param appCid   会话id
 * @param mute  是否免打扰
 * @param listener 监听器
 */
- (void)mute:(nonnull NSString *)appCid
        mute:(BOOL)mute
    listener:(nullable id<AIMConvServiceCompleteListener>)listener;

- (void)muteWithBlock:(nonnull NSString *)appCid
                 mute:(BOOL)mute
            onSuccess:(nullable void (^)())onSuccess
            onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 会话置顶(返回值为会话置顶服务端时间戳，会同时更新会话的modify_time和top_rank字段)
 * @param appCid   会话id
 * @param top   置顶
 * @param listener 监听器
 */
- (void)setTop:(nonnull NSString *)appCid
           top:(BOOL)top
      listener:(nullable id<AIMConvSetTopListener>)listener;

- (void)setTopWithBlock:(nonnull NSString *)appCid
                    top:(BOOL)top
              onSuccess:(nullable void (^)(int64_t topRank))onSuccess
              onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 会话置顶带时间戳，kv的时间戳会存放在local_ext中
 * @param appCid   会话id
 * @param top   置顶
 * @param timeStamp   置顶时间戳字段的kv
 * @param listener 监听器
 */
- (void)setTopWithTimeStamp:(nonnull NSString *)appCid
                        top:(BOOL)top
                  timeStamp:
                      (nonnull NSDictionary<NSString *, NSString *> *)timeStamp
                   listener:(nullable id<AIMConvSetTopListener>)listener;

- (void)
    setTopWithTimeStampWithBlock:(nonnull NSString *)appCid
                             top:(BOOL)top
                       timeStamp:
                           (nonnull NSDictionary<NSString *, NSString *> *)
                               timeStamp
                       onSuccess:(nullable void (^)(int64_t topRank))onSuccess
                       onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                     onFailure;

/**
 * 清空会话未读消息
 * @param appCid 会话id
 * @param mid 会话最后一条消息的id
 * @param listener 监听器
 */
- (void)clearRedPoint:(nonnull NSString *)appCid
                  mid:(nonnull NSString *)mid
             listener:(nullable id<AIMConvServiceCompleteListener>)listener;

- (void)clearRedPointWithBlock:(nonnull NSString *)appCid
                           mid:(nonnull NSString *)mid
                     onSuccess:(nullable void (^)())onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 批量清空所有缓存会话的红点，上层显示或者有过操作的会话都会在缓存中（无notify推送）
 * @param listener 监听器
 */
- (void)clearAllConvsRedPoint:
    (nullable id<AIMConvServiceCompleteListener>)listener;

- (void)clearAllConvsRedPointWithBlock:(nullable void (^)())onSuccess
                             onFailure:(nullable void (^)(
                                           DPSError *_Nonnull error))onFailure;

/**
 * 清空会话所有消息
 * @param appCid   会话id
 * @param listener 监听器
 */
- (void)clear:(nonnull NSString *)appCid
     listener:(nullable id<AIMConvServiceCompleteListener>)listener;

- (void)clearWithBlock:(nonnull NSString *)appCid
             onSuccess:(nullable void (^)())onSuccess
             onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 激活会话，选择会话后需要调用，激活后的会话不会计算红点；如果不再选择会话，需要传入appCid为空字符串
 * 一些特殊情况，比如没有从服务端同步到群的解散和被移除，会补偿解散和移除事件
 * @param appCid    会话id
 */
- (void)setActiveCid:(nonnull NSString *)appCid;

/**
 * 注册会话全量变更的监听器
 * @param listener 监听器
 */
- (void)addConvListListener:(nullable id<AIMPubConvListListener>)listener;

/**
 * 删除全量变更的监听器
 * @param listener 监听器
 */
- (void)removeConvListListener:(nullable id<AIMPubConvListListener>)listener;

/**
 * 注册会话增量变更的监听器
 * @param listener 监听器
 */
- (void)addConvChangeListener:(nullable id<AIMPubConvChangeListener>)listener;

/**
 * 删除会话增量变更的监听器
 * @param listener 监听器
 */
- (void)removeConvChangeListener:
    (nullable id<AIMPubConvChangeListener>)listener;

/**
 * 删除所有会话的监听器
 */
- (void)removeAllConvListListener;

/**
 * 删除所有会话的变更监听器
 */
- (void)removeAllConvChangeListener;

/**
 * 生成标准单聊cid
 * @param senderId 发送者id
 * @param receiverId 接收者id
 */
+ (nonnull NSString *)generateStandardAppCid:(nonnull NSString *)senderId
                                  receiverId:(nonnull NSString *)receiverId;

/**
 * 判断是否为标准单聊
 * @param appCid 会话id
 */
+ (BOOL)isStandard:(nonnull NSString *)appCid;

/**
 * 获取标准单聊targetUid
 * @param selfAppUid 自身uid
 * @param appCid 会话id
 */
+ (nonnull NSString *)getTargetAppUid:(nonnull NSString *)selfAppUid
                               appCid:(nonnull NSString *)appCid;

@end
