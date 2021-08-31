// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@interface AIMPubGroupMemberUpdateNick : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                   uid:(nonnull NSString *)uid
                                  nick:(nonnull NSString *)nick;
+ (nonnull instancetype)
    AIMPubGroupMemberUpdateNickWithAppCid:(nonnull NSString *)appCid
                                      uid:(nonnull NSString *)uid
                                     nick:(nonnull NSString *)nick;

/**
 *会话appCid
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 *用户id
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 *用户昵称
 */
@property(nonatomic, nonnull) NSString *nick;

@end
