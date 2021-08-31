// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 创建单聊参数
 */
@interface AIMPubConvCreateSingleConvParam : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
               ext:(nonnull NSDictionary<NSString *, NSString *> *)ext
              uids:(nonnull NSArray<NSString *> *)uids
               ctx:(nonnull NSDictionary<NSString *, NSString *> *)ctx
           isLocal:(BOOL)isLocal;
+ (nonnull instancetype)
    AIMPubConvCreateSingleConvParamWithAppCid:(nonnull NSString *)appCid
                                          ext:(nonnull NSDictionary<
                                                  NSString *, NSString *> *)ext
                                         uids:
                                             (nonnull NSArray<NSString *> *)uids
                                          ctx:(nonnull NSDictionary<
                                                  NSString *, NSString *> *)ctx
                                      isLocal:(BOOL)isLocal;

/**
 * 选填，支持使用客户端自己设置appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 选填，会话扩展信息
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *ext;

/**
 * 选填，单聊双方的uid（FYI：如果ctx为空，此项必填。如果拿不到uids，需要在ctx中带上nick信息）
 */
@property(nonatomic, nonnull) NSArray<NSString *> *uids;

/**
 * 选填，上下文信息（FYI：如果uids为空，此项必填，需要带上单聊双方的nick信息用于创建会话）
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *ctx;

/**
 * 选填，创建本地会话，本地会话没有rpc同步服务端
 * 创建本地会话需要传appCid和uids，当发送消息时服务端会自动创建对应uids的会话，appCid要保证和服务端的生成规则一致
 */
@property(nonatomic) BOOL isLocal;

@end
