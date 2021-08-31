// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 音频类型
 */
typedef NS_ENUM(NSInteger, AIMMsgAudioType) {
  AIMMsgAudioTypeAudioTypeUnknown = -1,
  AIMMsgAudioTypeAudioTypeOpus = 0,
  AIMMsgAudioTypeAudioTypeOgg = 1,
  AIMMsgAudioTypeAudioTypeAmr = 2,
};
