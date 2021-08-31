// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMPubMsgInnerCombineContent.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgCombineForward : NSObject
- (nonnull instancetype)
    initWithSender:(nonnull NSString *)sender
            appCid:(nonnull NSString *)appCid
               mid:(nonnull NSString *)mid
         createdAt:(int64_t)createdAt
    combineContent:(nonnull AIMPubMsgInnerCombineContent *)combineContent
         extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMPubMsgCombineForwardWithSender:(nonnull NSString *)sender
                               appCid:(nonnull NSString *)appCid
                                  mid:(nonnull NSString *)mid
                            createdAt:(int64_t)createdAt
                       combineContent:(nonnull AIMPubMsgInnerCombineContent *)
                                          combineContent
                            extension:
                                (nonnull NSDictionary<NSString *, NSString *> *)
                                    extension;

@property(nonatomic, nonnull) NSString *sender;

@property(nonatomic, nonnull) NSString *appCid;

@property(nonatomic, nonnull) NSString *mid;

@property(nonatomic) int64_t createdAt;

@property(nonatomic, nonnull) AIMPubMsgInnerCombineContent *combineContent;

@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
