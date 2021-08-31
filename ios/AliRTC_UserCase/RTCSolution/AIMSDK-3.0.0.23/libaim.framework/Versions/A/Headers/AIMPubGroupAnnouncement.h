// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@interface AIMPubGroupAnnouncement : NSObject
- (nonnull instancetype)initWithAnnouncement:(nonnull NSString *)announcement
                                 operatorUid:(nonnull NSString *)operatorUid
                                  modifyTime:(int64_t)modifyTime;
+ (nonnull instancetype)
    AIMPubGroupAnnouncementWithAnnouncement:(nonnull NSString *)announcement
                                operatorUid:(nonnull NSString *)operatorUid
                                 modifyTime:(int64_t)modifyTime;

/**
 * 公告文本，最大2048字节
 */
@property(nonatomic, nonnull) NSString *announcement;

/**
 * 公告的操作者
 */
@property(nonatomic, nonnull) NSString *operatorUid;

/**
 * 公告的修改事件，单位毫秒
 */
@property(nonatomic) int64_t modifyTime;

@end
