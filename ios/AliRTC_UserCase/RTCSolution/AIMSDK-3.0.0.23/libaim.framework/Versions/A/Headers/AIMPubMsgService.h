// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgFilter.h"
#import "AIMMsgSendMediaProgress.h"
#import "AIMPubMessage.h"
#import "AIMPubMsgBizUpdateInfo.h"
#import "AIMPubMsgLocalExtensionUpdateInfo.h"
#import "AIMPubMsgReSendMessage.h"
#import "AIMPubMsgReadStatus.h"
#import "AIMPubMsgSendForwardMessage.h"
#import "AIMPubMsgSendMessage.h"
#import "AIMPubMsgSendReplyMessage.h"
#import "AIMPubNewMessage.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>
@protocol AIMMsgDeleteLocalMsgListener;
@protocol AIMMsgDeleteMsgListener;
@protocol AIMMsgForwardMsgListener;
@protocol AIMMsgRecallMsgListener;
@protocol AIMMsgUpdateLocalExtensionListener;
@protocol AIMMsgUpdateLocalMsgsBizInfoListener;
@protocol AIMPubMsgChangeListener;
@protocol AIMPubMsgCombineForwardMsgListener;
@protocol AIMPubMsgGetLocalMsgListener;
@protocol AIMPubMsgGetLocalMsgsListener;
@protocol AIMPubMsgGetMsgListener;
@protocol AIMPubMsgListLocalMsgsListener;
@protocol AIMPubMsgListMsgsReadStatus;
@protocol AIMPubMsgListNextMsgsListener;
@protocol AIMPubMsgListPreviousMsgsListener;
@protocol AIMPubMsgListener;
@protocol AIMPubMsgReSendMsgListener;
@protocol AIMPubMsgSendMsgListener;
@protocol AIMPubMsgSendMsgToLocalListener;

/**
 * 最大时间戳
 */
extern int64_t const AIMPubMsgServiceAimMaxMsgCursor;

@interface AIMPubMsgService : NSObject

/**
 * 获取上一页特定类型消息，按时间升序排列
 * 注意：该接口只返回本地连续数据
 * @param appCid 会话唯一id
 * @param cursor 消息事件游标,消息的创建时间，如果是最新的开始
 * AIM_MAX_MSG_CURSOR
 * @param count  返回的结果数量，最大100
 * @param listener 监听器
 */
- (void)listPreviousLocalMsgs:(nonnull NSString *)appCid
                       cursor:(int64_t)cursor
                        count:(int32_t)count
                     listener:
                         (nullable id<AIMPubMsgListLocalMsgsListener>)listener;

- (void)
    listPreviousLocalMsgsWithBlock:(nonnull NSString *)appCid
                            cursor:(int64_t)cursor
                             count:(int32_t)count
                         onSuccess:(nullable void (^)(
                                       NSArray<AIMPubMessage *> *_Nonnull msgs,
                                       BOOL hasMore))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 获取下一页特定类型消息，按时间升序排列
 * 注意：该接口只返回本地连续数据
 * @param appCid 会话唯一id
 * @param cursor 消息事件游标,消息的创建时间，如果是最新的开始
 * AIM_MAX_MSG_CURSOR
 * @param count  返回的结果数量，最大100
 * @param listener 监听器
 */
- (void)listNextLocalMsgs:(nonnull NSString *)appCid
                   cursor:(int64_t)cursor
                    count:(int32_t)count
                 listener:(nullable id<AIMPubMsgListLocalMsgsListener>)listener;

- (void)listNextLocalMsgsWithBlock:(nonnull NSString *)appCid
                            cursor:(int64_t)cursor
                             count:(int32_t)count
                         onSuccess:(nullable void (^)(
                                       NSArray<AIMPubMessage *> *_Nonnull msgs,
                                       BOOL hasMore))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure;

/**
 * 获取下一页消息，按时间升序排列
 * @param appCid 会话唯一id
 * @param cursor 消息事件游标,消息的创建时间，如果是最新的开始
 * AIM_MAX_MSG_CURSOR
 * @param count 返回的结果数量，最大100
 * @param listener 监听器
 */
- (void)listNextMsgs:(nonnull NSString *)appCid
              cursor:(int64_t)cursor
               count:(int32_t)count
            listener:(nullable id<AIMPubMsgListNextMsgsListener>)listener;

- (void)listNextMsgsWithBlock:(nonnull NSString *)appCid
                       cursor:(int64_t)cursor
                        count:(int32_t)count
                    onSuccess:(nullable void (^)(
                                  NSArray<AIMPubMessage *> *_Nonnull msgs,
                                  BOOL hasMore))onSuccess
                    onFailure:
                        (nullable void (^)(
                            NSArray<NSArray<AIMPubMessage *> *> *_Nonnull msgs,
                            DPSError *_Nonnull error))onFailure;

/**
 * 获取上一页消息，按时间升序排列
 * @param appCid 会话唯一id
 * @param cursor 消息事件游标,消息的创建时间，如果是最新的开始
 * AIM_MAX_MSG_CURSOR
 * @param count 返回的结果数量，最大100
 * @param listener 监听器
 */
- (void)listPreviousMsgs:(nonnull NSString *)appCid
                  cursor:(int64_t)cursor
                   count:(int32_t)count
                listener:
                    (nullable id<AIMPubMsgListPreviousMsgsListener>)listener;

- (void)
    listPreviousMsgsWithBlock:(nonnull NSString *)appCid
                       cursor:(int64_t)cursor
                        count:(int32_t)count
                    onSuccess:(nullable void (^)(
                                  NSArray<AIMPubMessage *> *_Nonnull msgs,
                                  BOOL hasMore))onSuccess
                    onFailure:
                        (nullable void (^)(
                            NSArray<NSArray<AIMPubMessage *> *> *_Nonnull msgs,
                            DPSError *_Nonnull error))onFailure;

/**
 * 发送消息
 * @param msg 发送的消息对象
 * @param listener 监听器
 * @param userData 用户数据（"trace_id"："_trace_id_example"）
 */
- (void)sendMessage:(nonnull AIMPubMsgSendMessage *)msg
           listener:(nullable id<AIMPubMsgSendMsgListener>)listener
           userData:(nonnull NSDictionary<NSString *, NSString *> *)userData;

- (void)
    sendMessageWithBlock:(nonnull AIMPubMsgSendMessage *)msg
              onProgress:(nullable void (^)(double progress))onProgress
               onSuccess:
                   (nullable void (^)(AIMPubMessage *_Nonnull msg))onSuccess
               onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure
                userData:
                    (nonnull NSDictionary<NSString *, NSString *> *)userData;

/**
 * 重发消息
 * @param resendMsg 重发消息结构
 * @param listener 监听器
 * @param userData 用户数据
 */
- (void)resendMessage:(nonnull AIMPubMsgReSendMessage *)resendMsg
             listener:(nullable id<AIMPubMsgReSendMsgListener>)listener
             userData:(nonnull NSDictionary<NSString *, NSString *> *)userData;

- (void)resendMessageWithBlock:(nonnull AIMPubMsgReSendMessage *)resendMsg
                    onProgress:(nullable void (^)(double progress))onProgress
                     onSuccess:(nullable void (^)(AIMPubMessage *_Nonnull msg))
                                   onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure
                      userData:(nonnull NSDictionary<NSString *, NSString *> *)
                                   userData;

/**
 * 发送消息到本地不发送
 * @param msg 发送的消息对象
 * @param listener 监听器
 */
- (void)sendMessageTolocal:(nonnull AIMPubMsgSendMessage *)msg
                  listener:
                      (nullable id<AIMPubMsgSendMsgToLocalListener>)listener;

- (void)sendMessageTolocalWithBlock:(nonnull AIMPubMsgSendMessage *)msg
                          onSuccess:(nullable void (^)(
                                        AIMPubMessage *_Nonnull msg))onSuccess
                          onFailure:(nullable void (^)(
                                        DPSError *_Nonnull error))onFailure;

/**
 * 通过mid获取消息,本地不存在到服务端拉取
 * @param appCid 会话唯一id
 * @param mid 消息唯一id
 * @param listener 监听器
 */
- (void)getMessage:(nonnull NSString *)appCid
               mid:(nonnull NSString *)mid
          listener:(nullable id<AIMPubMsgGetMsgListener>)listener;

- (void)getMessageWithBlock:(nonnull NSString *)appCid
                        mid:(nonnull NSString *)mid
                  onSuccess:
                      (nullable void (^)(AIMPubMessage *_Nonnull msg))onSuccess
                  onFailure:
                      (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 通过mid获取本地消息
 * @param appCid 会话唯一id
 * @param localId 消息本地唯一id
 * @param listener 监听器
 */
- (void)getLocalMessage:(nonnull NSString *)appCid
                localId:(nonnull NSString *)localId
               listener:(nullable id<AIMPubMsgGetLocalMsgListener>)listener;

- (void)
    getLocalMessageWithBlock:(nonnull NSString *)appCid
                     localId:(nonnull NSString *)localId
                   onSuccess:
                       (nullable void (^)(AIMPubMessage *_Nonnull msg))onSuccess
                   onFailure:
                       (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 根据条件获取本地消息
 * 注意：该接口只返回本地数据，且不保证连续
 * @param appCid 会话唯一id
 * @param cursor 消息事件游标,消息的创建时间，如果是最新的开始
 * AIM_MAX_MSG_CURSOR
 * @param count  返回的结果数量，最大100
 * @param forward true: cursor 时间更大的数据， false： cursor时间更小的数据
 * @param filter 过滤条件
 * @param listener 监听器
 */
- (void)getLocalMessages:(nonnull NSString *)appCid
                  cursor:(int64_t)cursor
                   count:(int32_t)count
                 forward:(BOOL)forward
                  filter:(nonnull AIMMsgFilter *)filter
                listener:(nullable id<AIMPubMsgGetLocalMsgsListener>)listener;

- (void)getLocalMessagesWithBlock:(nonnull NSString *)appCid
                           cursor:(int64_t)cursor
                            count:(int32_t)count
                          forward:(BOOL)forward
                           filter:(nonnull AIMMsgFilter *)filter
                        onSuccess:(nullable void (^)(
                                      NSArray<AIMPubMessage *> *_Nonnull msgs))
                                      onSuccess
                        onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                      onFailure;

/**
 * 删除消息，消息将从列表中移除，同步入云端
 * @param appCid 会话唯一id
 * @param mids 消息id列表
 * @param listener 监听器
 */
- (void)deleteMessage:(nonnull NSString *)appCid
                 mids:(nonnull NSArray<NSString *> *)mids
             listener:(nullable id<AIMMsgDeleteMsgListener>)listener;

- (void)deleteMessageWithBlock:(nonnull NSString *)appCid
                          mids:(nonnull NSArray<NSString *> *)mids
                     onSuccess:(nullable void (^)())onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 删除本地消息，云端不同步
 * @param appCid 会话唯一id
 * @param localIds 消息id
 * @param listener 监听器
 */
- (void)deleteLocalMessage:(nonnull NSString *)appCid
                  localIds:(nonnull NSArray<NSString *> *)localIds
                  listener:(nullable id<AIMMsgDeleteLocalMsgListener>)listener;

- (void)deleteLocalMessageWithBlock:(nonnull NSString *)appCid
                           localIds:(nonnull NSArray<NSString *> *)localIds
                          onSuccess:(nullable void (^)())onSuccess
                          onFailure:(nullable void (^)(
                                        DPSError *_Nonnull error))onFailure;

/**
 * 撤回一条已发送的消息
 * @param appCid 会话唯一id
 * @param mid 消息id
 * @param listener 监听器
 */
- (void)recallMessage:(nonnull NSString *)appCid
                  mid:(nonnull NSString *)mid
             listener:(nullable id<AIMMsgRecallMsgListener>)listener;

- (void)recallMessageWithBlock:(nonnull NSString *)appCid
                           mid:(nonnull NSString *)mid
                     onSuccess:(nullable void (^)())onSuccess
                     onFailure:
                         (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 全量更新本地消息 local extension，不同步到云端
 * @param updateInfos 更新消息Extension信息列表
 * @param listener 监听器
 */
- (void)updateLocalExtension:
            (nonnull NSArray<AIMPubMsgLocalExtensionUpdateInfo *> *)updateInfos
                    listener:(nullable id<AIMMsgUpdateLocalExtensionListener>)
                                 listener;

- (void)updateLocalExtensionWithBlock:
            (nonnull NSArray<AIMPubMsgLocalExtensionUpdateInfo *> *)updateInfos
                            onSuccess:(nullable void (^)())onSuccess
                            onFailure:(nullable void (^)(
                                          DPSError *_Nonnull error))onFailure;

/**
 * 根据 key 局部更新本地消息 local extension, 不同步到云端
 * @param updateInfos 更新消息Extension信息列表
 * @param listener 监听器
 */
- (void)updateLocalExtensionByKey:
            (nonnull NSArray<AIMPubMsgLocalExtensionUpdateInfo *> *)updateInfos
                         listener:
                             (nullable id<AIMMsgUpdateLocalExtensionListener>)
                                 listener;

- (void)updateLocalExtensionByKeyWithBlock:
            (nonnull NSArray<AIMPubMsgLocalExtensionUpdateInfo *> *)updateInfos
                                 onSuccess:(nullable void (^)())onSuccess
                                 onFailure:
                                     (nullable void (^)(
                                         DPSError *_Nonnull error))onFailure;

/**
 * 更新本地消息 biz 相关字段
 * @param updateInfos 更新消息Biz信息列表
 * @param listener 监听器
 */
- (void)
    updateLocalMessagesBizInfo:
        (nonnull NSArray<AIMPubMsgBizUpdateInfo *> *)updateInfos
                      listener:
                          (nullable id<AIMMsgUpdateLocalMsgsBizInfoListener>)
                              listener;

- (void)updateLocalMessagesBizInfoWithBlock:
            (nonnull NSArray<AIMPubMsgBizUpdateInfo *> *)updateInfos
                                  onSuccess:(nullable void (^)())onSuccess
                                  onFailure:
                                      (nullable void (^)(
                                          DPSError *_Nonnull error))onFailure;

/**
 * 获取消息已读状态
 * @param appCid 会话唯一id
 * @param mid 消息唯一id
 * @param listener 监听器
 */
- (void)listMessagesReadStatus:(nonnull NSString *)appCid
                           mid:(nonnull NSString *)mid
                      listener:
                          (nullable id<AIMPubMsgListMsgsReadStatus>)listener;

- (void)listMessagesReadStatusWithBlock:(nonnull NSString *)appCid
                                    mid:(nonnull NSString *)mid
                              onSuccess:
                                  (nullable void (^)(
                                      AIMPubMsgReadStatus *_Nonnull status))
                                      onSuccess
                              onFailure:(nullable void (^)(
                                            DPSError *_Nonnull error))onFailure;

/**
 * 读取接收到消息，消息进入已读状态，同步入云端
 * 人数。
 * @param appCid 会话唯一id
 * @param mids 批量消息mid
 */
- (void)updateMessageToRead:(nonnull NSString *)appCid
                       mids:(nonnull NSArray<NSString *> *)mids;

/**
 * 生成消息localId,本地唯一
 */
- (int64_t)generateMsgLocalId;

/**
 * 注册消息变动的监听器，如，消息新增、删除、更新
 * @param listener 消息监听器
 */
- (BOOL)addMsgListener:(nullable id<AIMPubMsgListener>)listener;

/**
 * 删除消息的监听器
 * @param listener 消息监听器
 */
- (BOOL)removeMsgListener:(nullable id<AIMPubMsgListener>)listener;

/**
 * 删除所有消息的监听器
 */
- (void)removeAllMsgListener;

/**
 * 注册消息属性变更的监听器
 * @param listener 变更监听器
 */
- (BOOL)addMsgChangeListener:(nullable id<AIMPubMsgChangeListener>)listener;

/**
 * 删除消息的属性监听器
 * @param listener 变更监听器
 */
- (BOOL)removeMsgChangeListener:(nullable id<AIMPubMsgChangeListener>)listener;

/**
 * 删除所有消息的属性监听器
 */
- (void)removeAllMsgChangeListener;

/**
 * 回复消息
 * @param msg 发送的回复消息对象
 * @param listener 监听器
 */
- (void)replyMessage:(nonnull AIMPubMsgSendReplyMessage *)msg
            listener:(nullable id<AIMPubMsgReSendMsgListener>)listener
            userData:(nonnull NSDictionary<NSString *, NSString *> *)userData;

- (void)
    replyMessageWithBlock:(nonnull AIMPubMsgSendReplyMessage *)msg
               onProgress:(nullable void (^)(double progress))onProgress
                onSuccess:
                    (nullable void (^)(AIMPubMessage *_Nonnull msg))onSuccess
                onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure
                 userData:
                     (nonnull NSDictionary<NSString *, NSString *> *)userData;

/**
 * 转发消息
 * @param msg 发送的消息对象
 * @param listener 监听器
 * @param userData 用户数据（"trace_id"："_trace_id_example"）
 */
- (void)forwardMessage:(nonnull AIMPubMsgSendForwardMessage *)mgs
              listener:(nullable id<AIMMsgForwardMsgListener>)listener
              userData:(nonnull NSDictionary<NSString *, NSString *> *)userData;

- (void)forwardMessageWithBlock:(nonnull AIMPubMsgSendForwardMessage *)mgs
                      onSuccess:(nullable void (^)())onSuccess
                      onFailure:
                          (nullable void (^)(DPSError *_Nonnull error))onFailure
                       userData:(nonnull NSDictionary<NSString *, NSString *> *)
                                    userData;

/**
 * 合并转发消息
 * @param msg 发送的消息对象
 * @param listener 监听器
 * @param userData 用户数据（"trace_id"："_trace_id_example"）
 */
- (void)combineForwardMessage:(nonnull AIMPubMsgSendForwardMessage *)mgs
                     listener:(nullable id<AIMPubMsgCombineForwardMsgListener>)
                                  listener
                     userData:(nonnull NSDictionary<NSString *, NSString *> *)
                                  userData;

- (void)
    combineForwardMessageWithBlock:(nonnull AIMPubMsgSendForwardMessage *)mgs
                         onSuccess:(nullable void (^)(
                                       AIMPubMessage *_Nonnull msg))onSuccess
                         onFailure:(nullable void (^)(DPSError *_Nonnull error))
                                       onFailure
                          userData:
                              (nonnull NSDictionary<NSString *, NSString *> *)
                                  userData;

@end
