// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Push ack 状态
 */
@interface DPSPushAckStatus : NSObject

/**
 * @brief 回复客户端处理成功（状态码:200）
 */
- (void)ackSuccess;

/**
 * @brief 回复客户端无法识别此消息包（状态码:400）
 */
- (void)ackInvalid;

/**
 * @brief 回复客户端处理异常（状态码:500）
 */
- (void)ackException;

/**
 * @brief 回复特定的状态码
 * @param code   状态码
 */
- (void)ackStatus:(int32_t)code;

@end
