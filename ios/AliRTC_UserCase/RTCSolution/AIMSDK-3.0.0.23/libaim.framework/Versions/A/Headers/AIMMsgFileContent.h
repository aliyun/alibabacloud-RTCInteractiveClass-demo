// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 文件消息
 */
@interface AIMMsgFileContent : NSObject
- (nonnull instancetype)initWithLocalPath:(nonnull NSString *)localPath
                                 fileName:(nonnull NSString *)fileName
                                 fileType:(nonnull NSString *)fileType
                                  mediaId:(nonnull NSString *)mediaId
                                 mimeType:(nonnull NSString *)mimeType
                                      url:(nonnull NSString *)url
                                 fileSize:(int64_t)fileSize;
+ (nonnull instancetype)
    AIMMsgFileContentWithLocalPath:(nonnull NSString *)localPath
                          fileName:(nonnull NSString *)fileName
                          fileType:(nonnull NSString *)fileType
                           mediaId:(nonnull NSString *)mediaId
                          mimeType:(nonnull NSString *)mimeType
                               url:(nonnull NSString *)url
                          fileSize:(int64_t)fileSize;

/**
 * 本地路径
 */
@property(nonatomic, nonnull) NSString *localPath;

/**
 * 文件名称
 */
@property(nonatomic, nonnull) NSString *fileName;

/**
 * 文件类型
 */
@property(nonatomic, nonnull) NSString *fileType;

/**
 * media
 */
@property(nonatomic, nonnull) NSString *mediaId;

/**
 * 上传媒体类型（发送方）
 */
@property(nonatomic, nonnull) NSString *mimeType;

/**
 * url
 */
@property(nonatomic, nonnull) NSString *url;

/**
 * 文件大小
 */
@property(nonatomic) int64_t fileSize;

@end
