// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMessage.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>

/**
 * 获取下一页消息，按时间升序排列监听
 */
@protocol AIMPubMsgListNextMsgsListener

/**
 * 处理成功，返回连续的消息对象
 * @param msgs 消息列表
 * @param hasMore 是否有更多消息
 */
- (void)onSuccess:(nonnull NSArray<AIMPubMessage *> *)msgs
          hasMore:(BOOL)hasMore;

/**
 * 处理失败，返回失败原因
 * @param error 错误信息
 */
- (void)onFailure:(nonnull NSArray<NSArray<AIMPubMessage *> *> *)msgs
            error:(nonnull DPSError *)error;

@end
