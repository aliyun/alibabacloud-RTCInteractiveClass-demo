// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgBizInfo.h"
#import "AIMMsgSendStatus.h"
#import "AIMPubMsgContent.h"
#import "AIMPubMsgRecallFeature.h"
#import <Foundation/Foundation.h>

/**
 * 消息体
 */
@interface AIMPubMessage : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
               mid:(nonnull NSString *)mid
           localid:(nonnull NSString *)localid
            sender:(nonnull NSString *)sender
         senderTag:(int64_t)senderTag
         createdAt:(int64_t)createdAt
       unreadCount:(int32_t)unreadCount
     receiverCount:(int32_t)receiverCount
         receivers:(nonnull NSArray<NSString *> *)receivers
            isRead:(BOOL)isRead
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension
    localExtension:
        (nonnull NSDictionary<NSString *, NSString *> *)localExtension
     userExtension:(nonnull NSDictionary<NSString *, NSString *> *)userExtension
           content:(nonnull AIMPubMsgContent *)content
            status:(AIMMsgSendStatus)status
          isDelete:(BOOL)isDelete
          isRecall:(BOOL)isRecall
     isDisableRead:(BOOL)isDisableRead
           isLocal:(BOOL)isLocal
           bizInfo:(nonnull AIMMsgBizInfo *)bizInfo
     recallFeature:(nonnull AIMPubMsgRecallFeature *)recallFeature;
+ (nonnull instancetype)
    AIMPubMessageWithAppCid:(nonnull NSString *)appCid
                        mid:(nonnull NSString *)mid
                    localid:(nonnull NSString *)localid
                     sender:(nonnull NSString *)sender
                  senderTag:(int64_t)senderTag
                  createdAt:(int64_t)createdAt
                unreadCount:(int32_t)unreadCount
              receiverCount:(int32_t)receiverCount
                  receivers:(nonnull NSArray<NSString *> *)receivers
                     isRead:(BOOL)isRead
                  extension:
                      (nonnull NSDictionary<NSString *, NSString *> *)extension
             localExtension:
                 (nonnull NSDictionary<NSString *, NSString *> *)localExtension
              userExtension:
                  (nonnull NSDictionary<NSString *, NSString *> *)userExtension
                    content:(nonnull AIMPubMsgContent *)content
                     status:(AIMMsgSendStatus)status
                   isDelete:(BOOL)isDelete
                   isRecall:(BOOL)isRecall
              isDisableRead:(BOOL)isDisableRead
                    isLocal:(BOOL)isLocal
                    bizInfo:(nonnull AIMMsgBizInfo *)bizInfo
              recallFeature:(nonnull AIMPubMsgRecallFeature *)recallFeature;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) NSString *mid;

@property(nonatomic, nonnull) NSString *localid;

@property(nonatomic, nonnull) NSString *sender;

@property(nonatomic) int64_t senderTag;

@property(nonatomic) int64_t createdAt;

@property(nonatomic) int32_t unreadCount;

@property(nonatomic) int32_t receiverCount;

@property(nonatomic, nonnull) NSArray<NSString *> *receivers;

@property(nonatomic) BOOL isRead;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *localExtension;

@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *userExtension;

@property(nonatomic, nonnull) AIMPubMsgContent *content;

@property(nonatomic) AIMMsgSendStatus status;

@property(nonatomic) BOOL isDelete;

@property(nonatomic) BOOL isRecall;

@property(nonatomic) BOOL isDisableRead;

@property(nonatomic) BOOL isLocal;

@property(nonatomic, nonnull) AIMMsgBizInfo *bizInfo;

@property(nonatomic, nonnull) AIMPubMsgRecallFeature *recallFeature;

@end
