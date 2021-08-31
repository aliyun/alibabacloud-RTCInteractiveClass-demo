// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息撤回类型
 */
typedef NS_ENUM(NSInteger, AIMMsgRecallType) {
  /**
   * 未知
   */
  AIMMsgRecallTypeRecallTypeUnknown = -1,
  /**
   * 发送者撤回
   */
  AIMMsgRecallTypeRecallTypeSender = 0,
  /**
   * 群主撤回
   */
  AIMMsgRecallTypeRecallTypeGroupOwner = 1,
  /**
   * 系统撤回
   */
  AIMMsgRecallTypeRecallTypeSystem = 2,
  /**
   * 安全撤回
   */
  AIMMsgRecallTypeRecallTypeSecurity = 3,
  /**
   * 业务方自定义撤回，可通过 AIMMsgRecallFeature.extension 配合使用
   */
  AIMMsgRecallTypeRecallTypeCustom = 101,
};
