// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgContent.h"
#import <Foundation/Foundation.h>

/**
 * 回复消息
 */
@interface AIMPubMsgSendReplyMessage : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
      referenceMid:(nonnull NSString *)referenceMid
      replyContent:(nonnull AIMPubMsgContent *)replyContent
         receivers:(nonnull NSArray<NSString *> *)receivers
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension
    localExtension:
        (nonnull NSDictionary<NSString *, NSString *> *)localExtension
       callbackCtx:(nonnull NSDictionary<NSString *, NSString *> *)callbackCtx;
+ (nonnull instancetype)
    AIMPubMsgSendReplyMessageWithAppCid:(nonnull NSString *)appCid
                           referenceMid:(nonnull NSString *)referenceMid
                           replyContent:(nonnull AIMPubMsgContent *)replyContent
                              receivers:(nonnull NSArray<NSString *> *)receivers
                              extension:
                                  (nonnull NSDictionary<NSString *, NSString *>
                                       *)extension
                         localExtension:
                             (nonnull NSDictionary<NSString *, NSString *> *)
                                 localExtension
                            callbackCtx:
                                (nonnull NSDictionary<NSString *, NSString *> *)
                                    callbackCtx;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) NSString *referenceMid;

@property(nonatomic, nonnull) AIMPubMsgContent *replyContent;

@property(nonatomic, nonnull) NSArray<NSString *> *receivers;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *localExtension;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *callbackCtx;

@end
