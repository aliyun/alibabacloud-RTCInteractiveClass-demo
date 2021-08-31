// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgAudioType.h"
#import <Foundation/Foundation.h>

/**
 * 音频消息内容
 */
@interface AIMMsgAudioContent : NSObject
- (nonnull instancetype)initWithLocalPath:(nonnull NSString *)localPath
                               uploadPath:(nonnull NSString *)uploadPath
                                 mimeType:(nonnull NSString *)mimeType
                                      url:(nonnull NSString *)url
                                  mediaId:(nonnull NSString *)mediaId
                               binaryData:(nonnull NSData *)binaryData
                                audioType:(AIMMsgAudioType)audioType
                                 duration:(int64_t)duration;
+ (nonnull instancetype)
    AIMMsgAudioContentWithLocalPath:(nonnull NSString *)localPath
                         uploadPath:(nonnull NSString *)uploadPath
                           mimeType:(nonnull NSString *)mimeType
                                url:(nonnull NSString *)url
                            mediaId:(nonnull NSString *)mediaId
                         binaryData:(nonnull NSData *)binaryData
                          audioType:(AIMMsgAudioType)audioType
                           duration:(int64_t)duration;

/**
 * 语音本地路径（发送方），本地原始语音数据路径
 */
@property(nonatomic, nonnull) NSString *localPath;

/**
 * 上传本地路径（发送方）
 * 需要上传到服务端的语音文件路径，如加密，压缩的数据
 */
@property(nonatomic, nonnull) NSString *uploadPath;

/**
 * 上传媒体类型（发送方）
 */
@property(nonatomic, nonnull) NSString *mimeType;

/**
 * 语音文件url，服务端上传成功后返回
 */
@property(nonatomic, nonnull) NSString *url;

/**
 * media id，SDK 内部将语音文件上传成功后得到的 media_id
 * 发送文件时，如果 media_id 不为空，则使用该media_id发送
 */
@property(nonatomic, nonnull) NSString *mediaId;

/**
 * 语音数据,只是下行使用
 */
@property(nonatomic, nonnull) NSData *binaryData;

/**
 * 语音数据类型  AIMMsgAudioType
 */
@property(nonatomic) AIMMsgAudioType audioType;

/**
 * 语音时长
 */
@property(nonatomic) int64_t duration;

@end
