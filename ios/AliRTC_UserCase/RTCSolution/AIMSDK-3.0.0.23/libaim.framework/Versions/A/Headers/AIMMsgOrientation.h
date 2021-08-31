// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AIMMsgOrientation) {
  AIMMsgOrientationOrientationUnknown = -1,
  AIMMsgOrientationOrientationNormal = 1,
  AIMMsgOrientationOrientationFlipHorizontal = 2,
  AIMMsgOrientationOrientationRotate180 = 3,
  AIMMsgOrientationOrientationFlipVertical = 4,
  AIMMsgOrientationOrientationTranspose = 5,
  AIMMsgOrientationOrientationRotate90 = 6,
  AIMMsgOrientationOrientationTransverse = 7,
  AIMMsgOrientationOrientationRotate270 = 8,
};
