// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 群相关操作时的群成员信息（目前用于给服务端发送系统消息）
 */
@interface AIMPubGroupUserInfo : NSObject
- (nonnull instancetype)
    initWithUid:(nonnull NSString *)uid
       nickName:(nonnull NSString *)nickName
      extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMPubGroupUserInfoWithUid:(nonnull NSString *)uid
                      nickName:(nonnull NSString *)nickName
                     extension:(nonnull NSDictionary<NSString *, NSString *> *)
                                   extension;

/**
 * 用户id
 */
@property(nonatomic, nonnull) NSString *uid;

/**
 * 昵称
 */
@property(nonatomic, nonnull) NSString *nickName;

/**
 * 扩展信息
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
