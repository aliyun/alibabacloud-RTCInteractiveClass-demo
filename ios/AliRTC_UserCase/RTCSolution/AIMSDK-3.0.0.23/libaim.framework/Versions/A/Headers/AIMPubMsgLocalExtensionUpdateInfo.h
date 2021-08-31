// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 更新本地消息extension
 */
@interface AIMPubMsgLocalExtensionUpdateInfo : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
           localid:(nonnull NSString *)localid
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMPubMsgLocalExtensionUpdateInfoWithAppCid:(nonnull NSString *)appCid
                                        localid:(nonnull NSString *)localid
                                      extension:
                                          (nonnull NSDictionary<NSString *,
                                                                NSString *> *)
                                              extension;

/**
 * 会话id
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 消息localid
 */
@property(nonatomic, nonnull) NSString *localid;

/**
 * 扩展内容
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
