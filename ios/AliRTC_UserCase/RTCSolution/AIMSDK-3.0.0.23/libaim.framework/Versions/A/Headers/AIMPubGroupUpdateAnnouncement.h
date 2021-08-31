// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 更新群公告参数
 */
@interface AIMPubGroupUpdateAnnouncement : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                          announcement:(nonnull NSString *)announcement;
+ (nonnull instancetype)
    AIMPubGroupUpdateAnnouncementWithAppCid:(nonnull NSString *)appCid
                               announcement:(nonnull NSString *)announcement;

/**
 * 群appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 群公告，最大2048字节
 */
@property(nonatomic, nonnull) NSString *announcement;

@end
