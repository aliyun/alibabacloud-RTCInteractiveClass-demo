// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 消息已读状态
 */
@interface AIMPubMsgReadStatus : NSObject
- (nonnull instancetype)initWithAppCid:(nonnull NSString *)appCid
                                   mid:(nonnull NSString *)mid
                              readUids:(nonnull NSArray<NSString *> *)readUids
                            unreadUids:
                                (nonnull NSArray<NSString *> *)unreadUids;
+ (nonnull instancetype)
    AIMPubMsgReadStatusWithAppCid:(nonnull NSString *)appCid
                              mid:(nonnull NSString *)mid
                         readUids:(nonnull NSArray<NSString *> *)readUids
                       unreadUids:(nonnull NSArray<NSString *> *)unreadUids;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) NSString *mid;

@property(nonatomic, nonnull) NSArray<NSString *> *readUids;

@property(nonatomic, nonnull) NSArray<NSString *> *unreadUids;

@end
