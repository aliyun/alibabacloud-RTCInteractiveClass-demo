// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 图片尺寸类型
 */
typedef NS_ENUM(NSInteger, AIMImageSizeType) {
  /**
   * 默认图
   */
  AIMImageSizeTypeIstDefault = -1,
  /**
   * 原始图
   */
  AIMImageSizeTypeIstOrigin = 0,
  /**
   * 模糊图
   */
  AIMImageSizeTypeIstFuzzy = 1,
  /**
   * 缩略图
   */
  AIMImageSizeTypeIstThumb = 2,
  /**
   * 大图
   */
  AIMImageSizeTypeIstBig = 3,
  AIMImageSizeTypeIst120x120 = 100,
  AIMImageSizeTypeIst200x200 = 101,
  AIMImageSizeTypeIst1200x1200 = 102,
  AIMImageSizeTypeIst250x10000 = 103,
  AIMImageSizeTypeIst480x480 = 104,
  AIMImageSizeTypeIst640x640 = 105,
};
