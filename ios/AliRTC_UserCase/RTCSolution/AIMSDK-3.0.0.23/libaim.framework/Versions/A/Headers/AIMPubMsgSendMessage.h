// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgContent.h"
#import <Foundation/Foundation.h>

/**
 * 发送消息体
 */
@interface AIMPubMsgSendMessage : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
           content:(nonnull AIMPubMsgContent *)content
         receivers:(nonnull NSArray<NSString *> *)receivers
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension
    localExtension:
        (nonnull NSDictionary<NSString *, NSString *> *)localExtension
       callbackCtx:(nonnull NSDictionary<NSString *, NSString *> *)callbackCtx;
+ (nonnull instancetype)
    AIMPubMsgSendMessageWithAppCid:(nonnull NSString *)appCid
                           content:(nonnull AIMPubMsgContent *)content
                         receivers:(nonnull NSArray<NSString *> *)receivers
                         extension:
                             (nonnull NSDictionary<NSString *, NSString *> *)
                                 extension
                    localExtension:
                        (nonnull NSDictionary<NSString *, NSString *> *)
                            localExtension
                       callbackCtx:
                           (nonnull NSDictionary<NSString *, NSString *> *)
                               callbackCtx;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) AIMPubMsgContent *content;

@property(nonatomic, nonnull) NSArray<NSString *> *receivers;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@property(nonatomic, nonnull)
    NSDictionary<NSString *, NSString *> *localExtension;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *callbackCtx;

@end
