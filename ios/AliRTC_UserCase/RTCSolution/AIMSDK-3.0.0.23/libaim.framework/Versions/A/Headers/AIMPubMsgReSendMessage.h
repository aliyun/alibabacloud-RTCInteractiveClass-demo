// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 重新发送消息体
 */
@interface AIMPubMsgReSendMessage : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
           localid:(nonnull NSString *)localid
       callbackCtx:(nonnull NSDictionary<NSString *, NSString *> *)callbackCtx;
+ (nonnull instancetype)
    AIMPubMsgReSendMessageWithAppCid:(nonnull NSString *)appCid
                             localid:(nonnull NSString *)localid
                         callbackCtx:
                             (nonnull NSDictionary<NSString *, NSString *> *)
                                 callbackCtx;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) NSString *localid;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *callbackCtx;

@end
