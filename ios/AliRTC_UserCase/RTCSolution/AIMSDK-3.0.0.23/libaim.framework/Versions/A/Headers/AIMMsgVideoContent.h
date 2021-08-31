// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgImageFileType.h"
#import <Foundation/Foundation.h>

/**
 *视频消息内容
 */
@interface AIMMsgVideoContent : NSObject
- (nonnull instancetype)initWithLocalPath:(nonnull NSString *)localPath
                               uploadPath:(nonnull NSString *)uploadPath
                                 mimeType:(nonnull NSString *)mimeType
                                      url:(nonnull NSString *)url
                                  mediaId:(nonnull NSString *)mediaId
                           coverLocalPath:(nonnull NSString *)coverLocalPath
                          coverUploadPath:(nonnull NSString *)coverUploadPath
                                 coverUrl:(nonnull NSString *)coverUrl
                             coverMediaId:(nonnull NSString *)coverMediaId
                            coverFileType:(AIMMsgImageFileType)coverFileType
                            coverMimeType:(nonnull NSString *)coverMimeType
                                 fileName:(nonnull NSString *)fileName
                                 fileType:(nonnull NSString *)fileType
                                 fileSize:(int64_t)fileSize
                                 duration:(int64_t)duration
                                   height:(int32_t)height
                                    width:(int32_t)width
                               coverWidth:(int32_t)coverWidth
                              coverHeight:(int32_t)coverHeight;
+ (nonnull instancetype)
    AIMMsgVideoContentWithLocalPath:(nonnull NSString *)localPath
                         uploadPath:(nonnull NSString *)uploadPath
                           mimeType:(nonnull NSString *)mimeType
                                url:(nonnull NSString *)url
                            mediaId:(nonnull NSString *)mediaId
                     coverLocalPath:(nonnull NSString *)coverLocalPath
                    coverUploadPath:(nonnull NSString *)coverUploadPath
                           coverUrl:(nonnull NSString *)coverUrl
                       coverMediaId:(nonnull NSString *)coverMediaId
                      coverFileType:(AIMMsgImageFileType)coverFileType
                      coverMimeType:(nonnull NSString *)coverMimeType
                           fileName:(nonnull NSString *)fileName
                           fileType:(nonnull NSString *)fileType
                           fileSize:(int64_t)fileSize
                           duration:(int64_t)duration
                             height:(int32_t)height
                              width:(int32_t)width
                         coverWidth:(int32_t)coverWidth
                        coverHeight:(int32_t)coverHeight;

/**
 * 视频本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *localPath;

/**
 * 上传本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *uploadPath;

/**
 * 上传媒体类型（发送方）
 */
@property(nonatomic, nonnull) NSString *mimeType;

/**
 * 视频文件url
 */
@property(nonatomic, nonnull) NSString *url;

/**
 * media id
 */
@property(nonatomic, nonnull) NSString *mediaId;

/**
 * 视频封面本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *coverLocalPath;

/**
 * 视频封面上传本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *coverUploadPath;

/**
 * 视频封面
 */
@property(nonatomic, nonnull) NSString *coverUrl;

/**
 * 视频封面 media id
 */
@property(nonatomic, nonnull) NSString *coverMediaId;

/**
 * 视频封面类型（发送方）ImageFileType
 */
@property(nonatomic) AIMMsgImageFileType coverFileType;

@property(nonatomic, nonnull) NSString *coverMimeType;

/**
 * 视频名字
 */
@property(nonatomic, nonnull) NSString *fileName;

/**
 * 文件类型，取文件后缀
 */
@property(nonatomic, nonnull) NSString *fileType;

/**
 * 文件大小(B)
 */
@property(nonatomic) int64_t fileSize;

/**
 * 视频时长(ms)
 */
@property(nonatomic) int64_t duration;

/**
 * 视频高度
 */
@property(nonatomic) int32_t height;

/**
 * 视频宽度
 */
@property(nonatomic) int32_t width;

/**
 * 视频封面宽度
 */
@property(nonatomic) int32_t coverWidth;

/**
 * 视频封面高度
 */
@property(nonatomic) int32_t coverHeight;

@end
