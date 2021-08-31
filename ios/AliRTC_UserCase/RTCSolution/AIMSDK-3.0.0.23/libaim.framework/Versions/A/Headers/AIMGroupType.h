// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群类型
 */
typedef NS_ENUM(NSInteger, AIMGroupType) {
  /**
   * 未知类型
   */
  AIMGroupTypeGroupTypeUnknow = -1,
  /**
   * 普通群
   */
  AIMGroupTypeGroupTypeNormal = 1,
  /**
   * 大群
   */
  AIMGroupTypeGroupTypeGig = 2,
};
