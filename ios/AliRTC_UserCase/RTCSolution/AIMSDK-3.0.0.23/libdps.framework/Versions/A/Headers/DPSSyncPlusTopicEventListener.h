// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@protocol DPSSyncPlusTopicEventListener

/**
 * 开始同步服务端数据事件，一般在重连后触发
 */
- (void)onStartSyncServer;

/**
 * 完成服务端数据同步事件
 * @param isToolong2 是否是toolong2
 */
- (void)onEndSyncServer:(BOOL)isToolong2;

@end
