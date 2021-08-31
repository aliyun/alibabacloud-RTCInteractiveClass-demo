// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 多媒体下载相关参数
 */
@interface AIMDownloadFileParam : NSObject
- (nonnull instancetype)initWithDownloadUrl:(nonnull NSString *)downloadUrl
                                       path:(nonnull NSString *)path;
+ (nonnull instancetype)
    AIMDownloadFileParamWithDownloadUrl:(nonnull NSString *)downloadUrl
                                   path:(nonnull NSString *)path;

@property(nonatomic, nonnull) NSString *downloadUrl;

@property(nonatomic, nonnull) NSString *path;

@end
