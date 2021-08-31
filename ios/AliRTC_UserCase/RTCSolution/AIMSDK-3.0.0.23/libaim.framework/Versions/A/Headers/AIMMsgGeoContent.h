// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgImageFileType.h"
#import <Foundation/Foundation.h>

/**
 * 位置消息内容
 */
@interface AIMMsgGeoContent : NSObject
- (nonnull instancetype)initWithPicLocalPath:(nonnull NSString *)picLocalPath
                               picUploadPath:(nonnull NSString *)picUploadPath
                                    mimeType:(nonnull NSString *)mimeType
                                      picUrl:(nonnull NSString *)picUrl
                                  picMediaId:(nonnull NSString *)picMediaId
                                 picFileType:(AIMMsgImageFileType)picFileType
                                    picWidth:(int32_t)picWidth
                                   picHeight:(int32_t)picHeight
                                    latitude:(double)latitude
                                   longitude:(double)longitude
                                locationName:(nonnull NSString *)locationName;
+ (nonnull instancetype)
    AIMMsgGeoContentWithPicLocalPath:(nonnull NSString *)picLocalPath
                       picUploadPath:(nonnull NSString *)picUploadPath
                            mimeType:(nonnull NSString *)mimeType
                              picUrl:(nonnull NSString *)picUrl
                          picMediaId:(nonnull NSString *)picMediaId
                         picFileType:(AIMMsgImageFileType)picFileType
                            picWidth:(int32_t)picWidth
                           picHeight:(int32_t)picHeight
                            latitude:(double)latitude
                           longitude:(double)longitude
                        locationName:(nonnull NSString *)locationName;

/**
 * 位置图片本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *picLocalPath;

/**
 * 上传本地路径（发送方）
 */
@property(nonatomic, nonnull) NSString *picUploadPath;

/**
 * 上传媒体类型（发送方）
 */
@property(nonatomic, nonnull) NSString *mimeType;

/**
 * 位置图片
 */
@property(nonatomic, nonnull) NSString *picUrl;

/**
 * 位置图片 media id
 */
@property(nonatomic, nonnull) NSString *picMediaId;

/**
 * 位置图片类型 AIMMsgImageFileType
 */
@property(nonatomic) AIMMsgImageFileType picFileType;

/**
 * 宽度
 */
@property(nonatomic) int32_t picWidth;

/**
 * 高度
 */
@property(nonatomic) int32_t picHeight;

/**
 * 维度
 */
@property(nonatomic) double latitude;

/**
 * 经度
 */
@property(nonatomic) double longitude;

/**
 * 地理位置名称
 */
@property(nonatomic, nonnull) NSString *locationName;

@end
