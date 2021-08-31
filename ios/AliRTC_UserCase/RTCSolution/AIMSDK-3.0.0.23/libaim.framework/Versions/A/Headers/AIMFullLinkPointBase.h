// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 *基础埋点字段
 */
@interface AIMFullLinkPointBase : NSObject
- (nonnull instancetype)
    initWithTypeId:(int32_t)typeId
              tcId:(nonnull NSString *)tcId
           serveId:(nonnull NSString *)serveId
        sdkVersion:(nonnull NSString *)sdkVersion
               ext:(nonnull NSDictionary<NSString *, NSString *> *)ext
         traceType:(nonnull NSString *)traceType
      subTraceType:(nonnull NSString *)subTraceType
            stepId:(nonnull NSString *)stepId
            parent:(nonnull NSString *)parent
              code:(nonnull NSString *)code
         timeStamp:(int64_t)timeStamp
         direction:(int32_t)direction
            appKey:(nonnull NSString *)appKey
        appVersion:(nonnull NSString *)appVersion
          deviceId:(nonnull NSString *)deviceId
             index:(nonnull NSString *)index
               uid:(nonnull NSString *)uid;
+ (nonnull instancetype)
    AIMFullLinkPointBaseWithTypeId:(int32_t)typeId
                              tcId:(nonnull NSString *)tcId
                           serveId:(nonnull NSString *)serveId
                        sdkVersion:(nonnull NSString *)sdkVersion
                               ext:(nonnull NSDictionary<NSString *, NSString *>
                                        *)ext
                         traceType:(nonnull NSString *)traceType
                      subTraceType:(nonnull NSString *)subTraceType
                            stepId:(nonnull NSString *)stepId
                            parent:(nonnull NSString *)parent
                              code:(nonnull NSString *)code
                         timeStamp:(int64_t)timeStamp
                         direction:(int32_t)direction
                            appKey:(nonnull NSString *)appKey
                        appVersion:(nonnull NSString *)appVersion
                          deviceId:(nonnull NSString *)deviceId
                             index:(nonnull NSString *)index
                               uid:(nonnull NSString *)uid;

/**
 *固定5
 */
@property(nonatomic) int32_t typeId;

/**
 *上行event_id，下行rpc_id(不可为空)
 */
@property(nonatomic, nonnull) NSString *tcId;

/**
 *上行不填，下行rpcid(可为空)
 */
@property(nonatomic, nonnull) NSString *serveId;

/**
 *sdk版本
 */
@property(nonatomic, nonnull) NSString *sdkVersion;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *ext;

/**
 *链路类型
 */
@property(nonatomic, nonnull) NSString *traceType;

/**
 *子链路类型
 */
@property(nonatomic, nonnull) NSString *subTraceType;

/**
 *阶段
 */
@property(nonatomic, nonnull) NSString *stepId;

/**
 *上一阶段
 */
@property(nonatomic, nonnull) NSString *parent;

/**
 *succss/failure
 */
@property(nonatomic, nonnull) NSString *code;

/**
 *时间戳
 */
@property(nonatomic) int64_t timeStamp;

/**
 *上行/下行
 */
@property(nonatomic) int32_t direction;

@property(nonatomic, nonnull) NSString *appKey;

@property(nonatomic, nonnull) NSString *appVersion;

@property(nonatomic, nonnull) NSString *deviceId;

/**
 *索引字段，可填msgi/cid/uid等
 */
@property(nonatomic, nonnull) NSString *index;

/**
 *userid
 */
@property(nonatomic, nonnull) NSString *uid;

@end
