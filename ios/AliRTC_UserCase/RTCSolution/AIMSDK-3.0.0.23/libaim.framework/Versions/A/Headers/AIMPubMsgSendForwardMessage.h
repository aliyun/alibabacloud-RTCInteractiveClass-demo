// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 发送转发消息体
 */
@interface AIMPubMsgSendForwardMessage : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
              mids:(nonnull NSArray<NSString *> *)mids
          toAppCid:(nonnull NSString *)toAppCid
         receivers:(nonnull NSArray<NSString *> *)receivers
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension
       callbackCtx:(nonnull NSDictionary<NSString *, NSString *> *)callbackCtx;
+ (nonnull instancetype)
    AIMPubMsgSendForwardMessageWithAppCid:(nonnull NSString *)appCid
                                     mids:(nonnull NSArray<NSString *> *)mids
                                 toAppCid:(nonnull NSString *)toAppCid
                                receivers:
                                    (nonnull NSArray<NSString *> *)receivers
                                extension:(nonnull NSDictionary<NSString *,
                                                                NSString *> *)
                                              extension
                              callbackCtx:
                                  (nonnull NSDictionary<NSString *, NSString *>
                                       *)callbackCtx;

@property(nonatomic, nonnull) NSString *appCid;

/**
 * 需转发消息的mid列表
 */
@property(nonatomic, nonnull) NSArray<NSString *> *mids;

@property(nonatomic, nonnull) NSString *toAppCid;

@property(nonatomic, nonnull) NSArray<NSString *> *receivers;

/**
 * 如不为空，则替换转发消息的 extension，否则复用原extension
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *callbackCtx;

@end
