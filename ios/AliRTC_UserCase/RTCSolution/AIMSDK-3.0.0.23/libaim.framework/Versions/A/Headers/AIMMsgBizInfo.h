// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 本地消息biz属性
 */
@interface AIMMsgBizInfo : NSObject
- (nonnull instancetype)initWithBizTag:(nonnull NSString *)bizTag
                               bizText:(nonnull NSString *)bizText;
+ (nonnull instancetype)AIMMsgBizInfoWithBizTag:(nonnull NSString *)bizTag
                                        bizText:(nonnull NSString *)bizText;

/**
 * tag
 */
@property(nonatomic, nonnull) NSString *bizTag;

/**
 * 内容
 */
@property(nonatomic, nonnull) NSString *bizText;

@end
