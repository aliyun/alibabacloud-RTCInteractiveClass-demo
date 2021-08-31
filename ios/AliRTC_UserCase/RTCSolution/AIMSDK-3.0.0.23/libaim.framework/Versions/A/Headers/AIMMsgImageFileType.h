// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 图片类型
 */
typedef NS_ENUM(NSInteger, AIMMsgImageFileType) {
  AIMMsgImageFileTypeImageFileTypeUnknown = -1,
  AIMMsgImageFileTypeImageFileTypeWebp = 1,
  AIMMsgImageFileTypeImageFileTypePNG = 2,
  AIMMsgImageFileTypeImageFileTypeJPG = 3,
  AIMMsgImageFileTypeImageFileTypeGIF = 4,
};
