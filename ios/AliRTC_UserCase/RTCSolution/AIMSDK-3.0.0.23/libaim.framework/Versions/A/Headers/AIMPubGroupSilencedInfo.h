// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubGroupSilencedBlackListMemberInfo.h"
#import "AIMPubGroupSilencedWhiteListMemberInfo.h"
#import <Foundation/Foundation.h>

/**
 * 群禁言信息
 */
@interface AIMPubGroupSilencedInfo : NSObject
- (nonnull instancetype)
    initWithAppCid:(nonnull NSString *)appCid
     blacklistInfo:(nonnull NSArray<AIMPubGroupSilencedBlackListMemberInfo *> *)
                       blacklistInfo
         whitelist:(nonnull NSArray<AIMPubGroupSilencedWhiteListMemberInfo *> *)
                       whitelist;
+ (nonnull instancetype)
    AIMPubGroupSilencedInfoWithAppCid:(nonnull NSString *)appCid
                        blacklistInfo:
                            (nonnull NSArray<
                                AIMPubGroupSilencedBlackListMemberInfo *> *)
                                blacklistInfo
                            whitelist:
                                (nonnull NSArray<
                                    AIMPubGroupSilencedWhiteListMemberInfo *> *)
                                    whitelist;

/**
 * 群id
 */
@property(nonatomic, nonnull) NSString *appCid;

/**
 * 黑名单
 */
@property(nonatomic, nonnull)
    NSArray<AIMPubGroupSilencedBlackListMemberInfo *> *blacklistInfo;

/**
 * 白名单
 */
@property(nonatomic, nonnull)
    NSArray<AIMPubGroupSilencedWhiteListMemberInfo *> *whitelist;

@end
