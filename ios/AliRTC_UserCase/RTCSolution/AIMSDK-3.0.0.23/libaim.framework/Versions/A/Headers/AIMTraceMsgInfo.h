// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息信息字段
 */
@interface AIMTraceMsgInfo : NSObject
- (nonnull instancetype)
    initWithCid:(nonnull NSString *)cid
          msgId:(nonnull NSString *)msgId
     bizChainId:(nonnull NSString *)bizChainId
        msgType:(nonnull NSString *)msgType
         sender:(nonnull NSString *)sender
       receiver:(nonnull NSString *)receiver
      extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMTraceMsgInfoWithCid:(nonnull NSString *)cid
                     msgId:(nonnull NSString *)msgId
                bizChainId:(nonnull NSString *)bizChainId
                   msgType:(nonnull NSString *)msgType
                    sender:(nonnull NSString *)sender
                  receiver:(nonnull NSString *)receiver
                 extension:
                     (nonnull NSDictionary<NSString *, NSString *> *)extension;

/**
 *会话id
 */
@property(nonatomic, nonnull) NSString *cid;

/**
 *消息id
 */
@property(nonatomic, nonnull) NSString *msgId;

/**
 *sdk不填
 */
@property(nonatomic, nonnull) NSString *bizChainId;

/**
 *消息类型
 */
@property(nonatomic, nonnull) NSString *msgType;

/**
 *发送者
 */
@property(nonatomic, nonnull) NSString *sender;

/**
 *接收者
 */
@property(nonatomic, nonnull) NSString *receiver;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
