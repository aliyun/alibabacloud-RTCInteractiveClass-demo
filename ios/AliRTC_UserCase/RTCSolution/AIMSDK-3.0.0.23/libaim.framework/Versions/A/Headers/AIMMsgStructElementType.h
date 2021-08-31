// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 本地结构化消息类型
 */
typedef NS_ENUM(NSInteger, AIMMsgStructElementType) {
  /**
   * 未知节点
   */
  AIMMsgStructElementTypeElementTypeUnknown = 0,
  /**
   * 文本节点
   */
  AIMMsgStructElementTypeElementTypeText = 1,
  /**
   * uid 节点
   */
  AIMMsgStructElementTypeElementTypeUid = 2,
  /**
   * at 节点
   */
  AIMMsgStructElementTypeElementTypeAt = 3,
};
