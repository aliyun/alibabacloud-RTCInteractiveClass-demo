// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgImageCompressType.h"
#import "AIMMsgImageFileType.h"
#import "AIMMsgOrientation.h"
#import <Foundation/Foundation.h>

/**
 * 图片消息
 */
@interface AIMMsgImageContent : NSObject
- (nonnull instancetype)
    initWithLocalPath:(nonnull NSString *)localPath
           uploadPath:(nonnull NSString *)uploadPath
             mimeType:(nonnull NSString *)mimeType
          originalUrl:(nonnull NSString *)originalUrl
         thumbnailUrl:(nonnull NSString *)thumbnailUrl
          blurredData:(nonnull NSData *)blurredData
              mediaId:(nonnull NSString *)mediaId
             fileName:(nonnull NSString *)fileName
               height:(int32_t)height
                width:(int32_t)width
                 size:(int32_t)size
                 type:(AIMMsgImageCompressType)type
             fileType:(AIMMsgImageFileType)fileType
          orientation:(AIMMsgOrientation)orientation
            extension:(nonnull NSDictionary<NSString *, NSString *> *)extension;
+ (nonnull instancetype)
    AIMMsgImageContentWithLocalPath:(nonnull NSString *)localPath
                         uploadPath:(nonnull NSString *)uploadPath
                           mimeType:(nonnull NSString *)mimeType
                        originalUrl:(nonnull NSString *)originalUrl
                       thumbnailUrl:(nonnull NSString *)thumbnailUrl
                        blurredData:(nonnull NSData *)blurredData
                            mediaId:(nonnull NSString *)mediaId
                           fileName:(nonnull NSString *)fileName
                             height:(int32_t)height
                              width:(int32_t)width
                               size:(int32_t)size
                               type:(AIMMsgImageCompressType)type
                           fileType:(AIMMsgImageFileType)fileType
                        orientation:(AIMMsgOrientation)orientation
                          extension:
                              (nonnull NSDictionary<NSString *, NSString *> *)
                                  extension;

/**
 * 图片本地路径（发送方）
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
 * 图片url
 */
@property(nonatomic, nonnull) NSString *originalUrl;

/**
 * 缩略图url
 */
@property(nonatomic, nonnull) NSString *thumbnailUrl;

/**
 * 模糊图数据
 */
@property(nonatomic, nonnull) NSData *blurredData;

/**
 * media id
 */
@property(nonatomic, nonnull) NSString *mediaId;

/**
 * 图片名字
 */
@property(nonatomic, nonnull) NSString *fileName;

/**
 * 高(像素)
 */
@property(nonatomic) int32_t height;

/**
 * 宽(像素)
 */
@property(nonatomic) int32_t width;

/**
 * 文件大小(B)
 */
@property(nonatomic) int32_t size;

/**
 * 图片类型 AIMMsgImageType
 */
@property(nonatomic) AIMMsgImageCompressType type;

/**
 * 文件类型 AIMMsgImageFileType
 */
@property(nonatomic) AIMMsgImageFileType fileType;

/**
 * 旋转类型 AIMMsgOrientation
 */
@property(nonatomic) AIMMsgOrientation orientation;

/**
 * 扩展信息
 */
@property(nonatomic, nonnull) NSDictionary<NSString *, NSString *> *extension;

@end
