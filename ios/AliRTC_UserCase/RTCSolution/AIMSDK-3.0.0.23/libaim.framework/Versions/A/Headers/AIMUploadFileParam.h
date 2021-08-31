// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMFileAuthType.h"
#import <Foundation/Foundation.h>

/**
 * 多媒体上传相关参数
 */
@interface AIMUploadFileParam : NSObject
- (nonnull instancetype)initWithPath:(nonnull NSString *)path
                            mimeType:(nonnull NSString *)mimeType
                             bizType:(nonnull NSString *)bizType
                            authType:(AIMFileAuthType)authType
                         expiredTime:(int32_t)expiredTime;
+ (nonnull instancetype)AIMUploadFileParamWithPath:(nonnull NSString *)path
                                          mimeType:(nonnull NSString *)mimeType
                                           bizType:(nonnull NSString *)bizType
                                          authType:(AIMFileAuthType)authType
                                       expiredTime:(int32_t)expiredTime;

@property(nonatomic, nonnull) NSString *path;

@property(nonatomic, nonnull) NSString *mimeType;

@property(nonatomic, nonnull) NSString *bizType;

@property(nonatomic) AIMFileAuthType authType;

/**
 * 过期时间，单位分钟（取决于服务端实现），默认值为0，
 */
@property(nonatomic) int32_t expiredTime;

@end
