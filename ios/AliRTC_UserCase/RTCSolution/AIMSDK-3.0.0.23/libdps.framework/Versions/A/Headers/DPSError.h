// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "DPSDefine.h"
#import "DPSErrDomain.h"
#import <Foundation/Foundation.h>

/**
 * DPSError
 */
DPS_DECL
@interface DPSError : NSObject
- (nonnull instancetype)initWithDomain:(DPSErrDomain)domain
                                  code:(int32_t)code
                      developerMessage:(nonnull NSString *)developerMessage
                                reason:(nonnull NSString *)reason
                             extraInfo:(nonnull NSString *)extraInfo
                                 scope:(nonnull NSString *)scope;
+ (nonnull instancetype)DPSErrorWithDomain:(DPSErrDomain)domain
                                      code:(int32_t)code
                          developerMessage:(nonnull NSString *)developerMessage
                                    reason:(nonnull NSString *)reason
                                 extraInfo:(nonnull NSString *)extraInfo
                                     scope:(nonnull NSString *)scope;

@property(nonatomic) DPSErrDomain domain;

/**
 * 错误值
 * 如果domain为client，错误值请参考DPS_Err_ClientCode
 * 如果domain为server，错误值请咨询服务端
 */
@property(nonatomic) int32_t code;

@property(nonatomic, nonnull) NSString *developerMessage;

/**
 * 以下成员只有在domain为server时有效
 */
@property(nonatomic, nonnull) NSString *reason;

@property(nonatomic, nonnull) NSString *extraInfo;

@property(nonatomic, nonnull) NSString *scope;

@end
