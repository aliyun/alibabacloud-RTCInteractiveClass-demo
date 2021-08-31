// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>
@protocol DPSUtListener;

@interface DPSUtService : NSObject

/**
 * 注册监听器
 * @param listener 监听器
 */
- (BOOL)addListener:(nullable id<DPSUtListener>)listener;

/**
 * 删除监听器
 * @param listener 监听器
 */
- (BOOL)removeListener:(nullable id<DPSUtListener>)listener;

/**
 * 删除所有监听器
 */
- (void)removeAllListeners;

@end
