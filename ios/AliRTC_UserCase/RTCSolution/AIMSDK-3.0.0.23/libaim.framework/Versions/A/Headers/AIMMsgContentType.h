// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息内容类型
 */
typedef NS_ENUM(NSInteger, AIMMsgContentType) {
  AIMMsgContentTypeContentTypeUnknow = -1,
  AIMMsgContentTypeContentTypeText = 1,
  AIMMsgContentTypeContentTypeImage = 2,
  AIMMsgContentTypeContentTypeAudio = 3,
  AIMMsgContentTypeContentTypeVideo = 4,
  AIMMsgContentTypeContentTypeGeo = 5,
  AIMMsgContentTypeContentTypeStruct = 6,
  AIMMsgContentTypeContentTypeLink = 7,
  AIMMsgContentTypeContentTypeAt = 8,
  AIMMsgContentTypeContentTypeFile = 9,
  AIMMsgContentTypeContentTypeReply = 10,
  AIMMsgContentTypeContentTypeCombineForward = 11,
  AIMMsgContentTypeContentTypeCustom = 101,
};
