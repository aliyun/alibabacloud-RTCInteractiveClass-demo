// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMDownloadFileParam.h"
#import "AIMImageDimensions.h"
#import "AIMImageSizeType.h"
#import "AIMMediaAuthInfo.h"
#import "AIMUploadFileParam.h"
#import <Foundation/Foundation.h>
#import <libdps/DPSError.h>
@protocol AIMDownloadFileListener;
@protocol AIMUploadFileListener;

@interface AIMMediaService : NSObject

/**
 * 上传文件
 * @param param 发送内容
 * @param listener 回调
 */
- (void)uploadFile:(nonnull AIMUploadFileParam *)param
          listener:(nullable id<AIMUploadFileListener>)listener;

- (void)
    uploadFileWithBlock:(nonnull AIMUploadFileParam *)param
               onCreate:(nullable void (^)(NSString *_Nonnull taskId))onCreate
                onStart:(nullable void (^)())onStart
             onProgress:(nullable void (^)(int64_t currentSize,
                                           int64_t totalSize))onProgress
              onSuccess:(nullable void (^)(NSString *_Nonnull mediaId))onSuccess
              onFailure:(nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 下载文件
 * @param param 下载内容
 * @param listener 回调
 */
- (void)downloadFile:(nonnull AIMDownloadFileParam *)param
            listener:(nullable id<AIMDownloadFileListener>)listener;

- (void)
    downloadFileWithBlock:(nonnull AIMDownloadFileParam *)param
                 onCreate:(nullable void (^)(NSString *_Nonnull taskId))onCreate
                  onStart:(nullable void (^)())onStart
               onProgress:(nullable void (^)(int64_t currentSize,
                                             int64_t totalSize))onProgress
                onSuccess:(nullable void (^)(NSString *_Nonnull path))onSuccess
                onFailure:
                    (nullable void (^)(DPSError *_Nonnull error))onFailure;

/**
 * 取消文件任务
 * @param taskId 任务id
 */
- (void)cancelFileTask:(nonnull NSString *)taskId;

/**
 * media 解析(image)
 * @param mediaId 媒体id
 * @param size 图片大小
 */
- (nonnull NSString *)transferMediaIdToImageUrl:(nonnull NSString *)mediaId
                                           size:(AIMImageSizeType)size;

/**
 * media 解析(image)
 * @param mediaId 媒体id
 * @param size 图片大小
 * @param bizType 业务类型
 */
- (nonnull NSString *)
    transferMediaIdToImageUrlWithBizType:(nonnull NSString *)mediaId
                                    size:(AIMImageSizeType)size
                                 bizType:(nonnull NSString *)bizType;

/**
 * media 解析(file)
 * @param mediaId 媒体id
 */
- (nonnull NSString *)transferMediaIdToUrl:(nonnull NSString *)mediaId;

/**
 * media 解析(file)
 * @param mediaId 媒体id
 * @param bizType 业务类型
 */
- (nonnull NSString *)
    transferMediaIdToUrlWithBizType:(nonnull NSString *)mediaId
                            bizType:(nonnull NSString *)bizType;

/**
 * media 解析鉴权(image)
 * @param mediaId 媒体id
 * @param size 图片大小
 * @param authInfo 鉴权信息
 */
- (nonnull NSString *)transferMediaIdToAuthImageUrl:(nonnull NSString *)mediaId
                                               size:(AIMImageSizeType)size
                                           authInfo:(nonnull AIMMediaAuthInfo *)
                                                        authInfo;

/**
 * media 解析鉴权(image)
 * @param mediaId 媒体id
 * @param size 图片大小
 * @param authInfo 鉴权信息
 * @param bizType 业务类型
 */
- (nonnull NSString *)
    transferMediaIdToAuthImageUrlBizType:(nonnull NSString *)mediaId
                                    size:(AIMImageSizeType)size
                                authInfo:(nonnull AIMMediaAuthInfo *)authInfo
                                 bizType:(nonnull NSString *)bizType;

/**
 * media 解析鉴权(file)
 * @param mediaId 媒体id
 * @param authInfo 鉴权信息
 */
- (nonnull NSString *)transferMediaIdToAuthUrl:(nonnull NSString *)mediaId
                                      authInfo:
                                          (nonnull AIMMediaAuthInfo *)authInfo;

/**
 * media 解析鉴权(file)
 * @param mediaId 媒体id
 * @param authInfo 鉴权信息
 * @param bizType 业务类型
 */
- (nonnull NSString *)
    transferMediaIdToAuthUrlBizType:(nonnull NSString *)mediaId
                           authInfo:(nonnull AIMMediaAuthInfo *)authInfo
                            bizType:(nonnull NSString *)bizType;

/**
 * 解析url常量部分
 * @param url 下载url
 */
- (nonnull NSString *)getUrlConstantPart:(nonnull NSString *)url;

/**
 * 获取图片尺寸
 */
- (nonnull AIMImageDimensions *)transferMediaIdToImageDimensions:
    (nonnull NSString *)mediaId;

@end
