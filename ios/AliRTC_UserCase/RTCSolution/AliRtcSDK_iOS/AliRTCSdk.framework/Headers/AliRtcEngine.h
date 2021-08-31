/*
 * @brief This header file is part of Alibaba RTC engine sdk for iOS system
 *
 * @copyright Copyright (c) 2021, Alibaba Inc.
 * All rights reserved
 */

#import <UIKit/UIKit.h>
#import <UIKit/UIImage.h>

/**
 * @defgroup AliRtcDef_ios iOS关键类型定义
 * AliRTC功能的关键类型定义
 * @{
 */

/**
 * @brief 视频流类型
 */
typedef NS_ENUM(NSUInteger, AliRtcVideoTrack) {
    /** 无摄像头和屏幕共享 */
    AliRtcVideoTrackNo     = 0,
    /** 摄像头 */
    AliRtcVideoTrackCamera = 1,
    /** 屏幕共享 */
    AliRtcVideoTrackScreen = 2,
    /** 摄像头+屏幕共享 */
    AliRtcVideoTrackBoth   = 3,
};

/**
 * @brief 音频流类型
 */
typedef NS_ENUM(NSUInteger, AliRtcAudioTrack) {
    /** 无麦克风 */
    AliRtcAudioTrackNo   = 0,
    /** 麦克风 */
    AliRtcAudioTrackMic  = 1,
};


/**
 * @brief 网络质量
 */
typedef NS_ENUM(NSUInteger, AliRtcNetworkQuality) {
    /** 网络极好，流程度清晰度质量好 */
    AlivcRtcNetworkQualityExcellent  = 0,
    /** 网络好，流畅度清晰度和极好差不多 */
    AlivcRtcNetworkQualityGood       = 1,
    /** 网络较差，音视频流畅度清晰度有瑕疵，不影响沟通 */
    AlivcRtcNetworkQualityPoor       = 2,
    /** 网络差，视频卡顿严重，音频能正常沟通 */
    AlivcRtcNetworkQualityBad        = 3,
    /** 网络极差，基本无法沟通 */
    AlivcRtcNetworkQualityVeryBad    = 4,
    /** 网络中断 */
    AlivcRtcNetworkQualityDisconnect = 5,
    /** 未知 */
    AlivcRtcNetworkQualityUnknow     = 6,
};


/**
 * @brief 音频质量
*/
typedef NS_ENUM(NSInteger, AliRtcTranportAudioQuality) {
    /** 质量未知 */
    AliRtcAudioQulityUnknow = 0,
    /** 质量极好 */
    AliRtcAudioQulityExcellent = 1,
    /** 用户主观感觉和极好差不多 ，但码率可能略低于极好 */
    AliRtcAudioQulityGood = 2,
    /** 用户主观感受有瑕疵，但不影响沟通 */
    AliRtcAudioQulityPoor = 3,
    /** 勉强能沟通但不顺畅 */
    AliRtcAudioQulityBad = 4,
    /** 网络质量非常差，基本不能沟通 */
    AliRtcAudioQulityVeryBad = 5,
    /** 网络连接已断开，完全无法沟通 */
    AliRtcAudioQulityNetworkDisconnected = 6,
};

/**
 * @brief 音频编码模式
 */
typedef NS_ENUM(NSInteger, AliRtcAudioProfile) {
    /** 音频低音质模式，默认8000Hz采样率，单声道，最大编码码率12kbps */
    AliRtcEngineLowQualityMode        = 0x0000,
    /**（默认）标准音质模式，默认16000Hz采样率，单声道，最大编码码率24kbps */ 
    AliRtcEngineBasicQualityMode      = 0x0001,
    /** 高音质模式，默认48000Hz采样率，单声道，最大编码码率48kbps */
    AliRtcEngineHighQualityMode       = 0x0010,
    /** 立体声高音质模式，默认48000Hz采样率，双声道，最大编码码率64kbps */
    AliRtcEngineStereoHighQualityMode = 0x0011, 
    /** 超高音质模式，默认48000Hz采样率，单声道，最大编码码率96kbps */
    AliRtcEngineSuperHighQualityMode = 0x0012,
    /** 立体声超高音质模式，默认48000Hz采样率，双声道，最大编码码率128kbps */
    AliRtcEngineStereoSuperHighQualityMode = 0x0013, 
};

/**
 * @brief 音频场景模式
 */
typedef NS_ENUM(NSInteger, AliRtcAudioScenario) {
    /** 默认场景，一般的音视频通信场景推荐使用 */
    AliRtcSceneDefaultMode   = 0x0000,
    /** 教育场景，优先保证音频连续性与稳定性 */
    AliRtcSceneEducationMode = 0x0100,
    /** 媒体场景，保真人声与音乐音质, 连麦直播间推荐使用 */
    AliRtcSeneMediaMode      = 0x0200,
    /** 音乐场景，高保真音乐音质，乐器教学等对音乐音质有要求的场景推荐使用 */
    AliRtcSceneMusicMode     = 0x0300,
    /** 聊天室模式，适用于频繁上下麦的场景 */
    AliRtcSceneChatroomMode  = 0x0400,
};

/**
 * @brief 视图显示模式
 */
typedef NS_ENUM(NSUInteger, AliRtcRenderMode) {
    /** 自动模式 */
    AliRtcRenderModeAuto    = 0,
    /** 延伸模式 */
    AliRtcRenderModeStretch = 1,
    /** 填充模式 */
    AliRtcRenderModeFill    = 2,
    /** 裁剪模式 */
    AliRtcRenderModeCrop    = 3,
};

/**
 * @brief Log级别
 */
typedef NS_ENUM(NSUInteger, AliRtcLogLevel) {
    /** 只输出>=AliEngineLogLevelInfo 级别的日志*/
    AliRtcLogLevelInfo = 3,
    /** 只输出>=AliEngineLogLevelWarn 级别的日志*/
    AliRtcLogLevelWarn,
    /** 只输出>=AliEngineLogLevelError 级别的日志*/
    AliRtcLogLevelError,
    /** 只输出>=AliEngineLogLevelFatal 级别的日志*/
    AliRtcLogLevelFatal,
    /** 不输出日志 */
    AliRtcLogLevelNone,
};

/**
 * @brief 视频编码帧率
 */
typedef NS_ENUM(NSInteger, AliRtcVideoEncoderFrameRate) {
    /** 视频编码帧率 - 5帧 */
    AliRtcVideoEncoderFrameRate_FPS_5 = 5,
    /** 视频编码帧率 - 10帧 */
    AliRtcVideoEncoderFrameRate_FPS_10 = 10,
    /** 视频编码帧率 - 15帧 */
    AliRtcVideoEncoderFrameRate_FPS_15 = 15,
    /** 视频编码帧率 - 20帧 */
    AliRtcVideoEncoderFrameRate_FPS_20 = 20,
    /** 视频编码帧率 - 30帧 */
    AliRtcVideoEncoderFrameRate_FPS_30 = 30,
};

/**
 * @brief 视频编码码率
 */
typedef NS_ENUM(NSInteger, AliRtcVideoEncoderBitrate) {
    /** 视频编码标准码率 */
    AliRtcVideoEncoderStandardBitrate = 0,
};

/**
 * @brief 编码视频镜像模式
 */
typedef NS_ENUM(NSInteger, AliRtcVideoEncoderMirrorMode) {
    /** 视频编码不镜像 */
    AliRtcVideoEncoderMirrorModeDisabled = 0,
    /** 视频编码镜像 */
    AliRtcVideoEncoderMirrorModeEnabled = 1,
};

/**
 * @brief 视频旋转角度
 */
typedef NS_ENUM(NSInteger, AliRtcRotationMode) {
    /** 视频旋转角度 - 0 */
    AliRtcRotationMode_0    = 0,
    /** 视频旋转角度 - 90 */
    AliRtcRotationMode_90   = 90,
    /** 视频旋转角度 - 180 */
    AliRtcRotationMode_180  = 180,
    /** 视频旋转角度 - 270 */
    AliRtcRotationMode_270  = 270,
};

/**
 * @brief 编码视频旋转模式
 */
typedef NS_ENUM(NSInteger, AliRtcVideoEncoderOrientationMode) {
    /** 自适应，和采集视频保持一致 */
    AliRtcVideoEncoderOrientationModeAdaptive = 0,
    /** 固定横屏 */
    AliRtcVideoEncoderOrientationModeFixedLandscape = 1,
    /** 固定竖屏 */
    AliRtcVideoEncoderOrientationModeFixedPortrait = 2,
};

/**
 * @brief 视频设备方向
 */
typedef NS_ENUM(NSInteger, AliRtcOrientationMode) {
    /** 固定竖屏模式 */
    AliRtcOrientationModePortrait = 0,
    /** 固定左横屏模式 */
    AliRtcOrientationModeLandscapeLeft = 1,
    /** 固定倒立模式 */
    AliRtcOrientationModePortraitUpsideDown = 2,
    /** 固定右横屏模式 */
    AliRtcOrientationModeLandscapeRight = 3,
    /** 自适应模式 */
    AliRtcOrientationModeAuto = 4,
};

/**
 * @brief SDK对Audio Session的控制权限
 */
typedef NS_ENUM(NSInteger, AliRtcAudioSessionOperationRestriction) {
    /** 无限制，SDK完全控制AVAudioSession */
    AliRtcAudioSessionOperationRestrictionNone              = 0,
    /** SDK不能修改AVAudioSession的Category */
    AliRtcAudioSessionOperationRestrictionSetCategory       = 1 << 0,
    /** SDK不能修改AVAudioSession的配置，包括Category，Mode，CategoryOptions */
    AliRtcAudioSessionOperationRestrictionConfigureSession  = 1 << 1,
    /** SDK不能关闭AVAudioSession的活动状态，离开频道时，AVAudioSession依然处于活动状态 */
    AliRtcAudioSessionOperationRestrictionDeactivateSession = 1 << 2,
};


/**
 * @brief 相机流类型
 */
typedef NS_ENUM(NSInteger, AliRtcVideoStreamType) {
    /** 无，在OnSubscribeStreamTypeChanged回调表示当前未订阅 */
    AliRtcVideoStreamTypeNone = 0,
    /** 高码率，高分辨率流（大流） */
    AliRtcVideoStreamTypeHigh = 1,
    /** 低码率，低分辨率流（小流） */
    AliRtcVideoStreamTypeLow = 2,
};

/**
 * @brief 设备音量类型
 * @note 默认为Auto类型，SDK 内部会自动选择合适的音量类型，如无特殊需求，不推荐自行设置
 */
typedef NS_ENUM(NSInteger, AliRtcDeviceVolumeType) {
    /** SDK自动设置音量类型 */
    AliRtcDeviceVolumeTypeAuto = 0,
    /** 设置为媒体音量，适合媒体播放场景，音量可以调节到零 */
    AliRtcDeviceVolumeTypeMedia = 1,
    /** 设置为通话音量，适合通话场景，音量无法调节到零 */
    AliRtcDeviceVolumeTypeVOIP = 2,
};

/**
 * @brief 视频裸数据源类型
 */
typedef NS_ENUM(NSInteger, AliRtcVideoSource) {
    /** 视频流 */
    AliRtcVideosourceCameraType = 0,
    /** 屏幕共享流 */
    AliRtcVideosourceScreenShareType = 1,
    /** 占位符，无意义 */
    AliRtcVideosourceTypeMax,
};

/**
 * @brief 音频数据源类型
 */
typedef NS_ENUM(NSInteger, AliRtcAudioSource) {
    /** 本地推流的音频数据 */
    AliRtcAudiosourcePub = 0,
    /** 本地拉流混音的音频数据 */
    AliRtcAudiosourceSub = 1,
    /** 本地采集的音频数据 */
    AliRtcAudiosourceRawData = 2,
};

/**
 * @brief 视频数据格式
 */
typedef NS_ENUM(NSInteger, AliRtcVideoFormat) {
    AliRtcVideoFormat_UNKNOW = -1,
    AliRtcVideoFormat_BGRA = 0,
    AliRtcVideoFormat_I420,
    AliRtcVideoFormat_NV21,
    AliRtcVideoFormat_NV12,
    AliRtcVideoFormat_RGBA,
    AliRtcVideoFormat_I422,
    AliRtcVideoFormat_ARGB,
    AliRtcVideoFormat_ABGR,
    AliRtcVideoFormat_RGB24,
    AliRtcVideoFormat_BGR24,
    AliRtcVideoFormat_RGB565,
    AliRtcVideoFormat_H264,
};


/**
 * @brief 视频数据类型
 */
typedef NS_ENUM(NSInteger, AliRtcBufferType) {
    /** YUV裸数据 */
    AliRtcBufferType_Raw_Data = 0,
    /** CVPixelBuffer数据 */
    AliRtcBufferType_CVPixelBuffer,
};

/**
 * @brief 音频声道数
 */
typedef NS_ENUM(NSInteger, AliRtcAudioNumChannel) {
    /** 单声道 */
    AliRtcMonoAudio = 1,
    /** 双声道 */
    AliRtcStereoAudio = 2,
};

/**
 * @brief 文件录制质量
 */
typedef NS_ENUM(NSInteger, AliRtcRecordingQuality) {
    /** 低质量文件录制，文件体积较小，音质一般 */
    AliRtcRecording_Low_Quality = 0,
    /** 中等质量文件录制，文件体积中等，音质中等 */
    AliRtcRecording_Midium_Quality = 1,
    /** 高质量文件录制，文件体积较大，音质较好 */
    AliRtcRecording_High_Quality = 2,
};

/**
 * @brief 变声音效模式
 */
typedef NS_ENUM(NSInteger, AliRtcAudioEffectVoiceChangerMode) {
    /** 关闭变声音效 */
    AliRtcAudioEffectvVoiceChanger_OFF = 0,
    /** 老人 */
    AliRtcAudioEffectvVoiceChanger_OLD_MAN,
    /** 男孩 */
    AliRtcAudioEffectvVoiceChanger_BABYBOY,
    /** 女孩 */
    AliRtcAudioEffectvVoiceChanger_BABYGILR,
    /** 机器人 */
    AliRtcAudioEffectvVoiceChanger_ROBOT,
    /** 大魔王 */
    AliRtcAudioEffectvVoiceChanger_DAIMO,
    /** KTV */
    AliRtcAudioEffectvVoiceChanger_KTV,
    /** 回声 */
    AliRtcAudioEffectvVoiceChangerR_ECHO,
    /** 占位符 */
    AliRtcAudioEffectvVoiceChanger_MAX,
};

/**
 * @brief 音效混响模式
 */
typedef NS_ENUM(NSInteger, AliRtcAudioEffectReverbMode) {
    /** 关闭混响 */
    AliRtcAudioEffectReverb_Off = 0,
    /** 人声I */
    AliRtcAudioEffectReverb_Vocal_I,
    /** 人声II */
    AliRtcAudioEffectReverb_Vocal_II,
    /** 澡堂 */
    AliRtcAudioEffectReverb_Bathroom,
    /** 明亮小房间 */
    AliRtcAudioEffectReverb_Small_Room_Bright,
    /** 黑暗小房间 */
    AliRtcAudioEffectReverb_Small_Room_Dark,
    /** 中等房间 */
    AliRtcAudioEffectReverb_Medium_Room,
    /** 大房间 */
    AliRtcAudioEffectReverb_Large_Room,
    /** 教堂走廊 */
    AliRtcAudioEffectReverb_Church_Hall,
    /** 占位符 */
    AliRtcAudioEffectReverb_Mode_Max,
};

/**
 * @brief 音效混响参数
 */
typedef NS_ENUM(NSInteger, AliRtcAudioEffectReverbParamType) {
    /** 房间大小，取值范围：[0, 100] */
    AliRtcAudioEffectReverb_Room_Size = 0,
    /** 预延时，单位ms，取值范围：[0, 200] */
    AliRtcAudioEffectReverb_Pre_Delay,
    /** 混响感，取值范围：[0, 100] */
    AliRtcAudioEffectReverb_Revetberance,
    /** 消声，取值范围：[0, 100] */
    AliRtcAudioEffectReverb_Hf_Damping,
    /** 低音调，取值范围：[0, 100] */
    AliRtcAudioEffectReverb_Tone_Low,
    /** 高音调，取值范围：[0, 100] */
    AliRtcAudioEffectReverb_Tone_High,
    /** 干增益，取值范围：[-20, 10] */
    AliRtcAudioEffectReverb_Dry_Gain,
    /** 湿增益，取值范围：[-20, 10] */
    AliRtcAudioEffectReverb_Wet_Gain,
    /** 占位符 */
    AliRtcAudioEffectReverb_Type_Max,
};

/**
 * @brief 网络连接状态
*/
typedef NS_ENUM(NSInteger, AliRtcConnectionStatus) {
    /** 初始化完成 */
    AliRtcConnectionStatusInit = 0,
    /** 网络连接断开 */
    AliRtcConnectionStatusDisconnected,
    /** 建立网络连接中 */
    AliRtcConnectionStatusConnecting,
    /** 网络已连接 */
    AliRtcConnectionStatusConnected,
    /** 重新建立网络连接中 */
    AliRtcConnectionStatusReconnecting,
    /** 网络连接失败 */
    AliRtcConnectionStatusFailed,
};

/**
 * @brief 引起网络状态变更原因
*/
typedef NS_ENUM(NSInteger, AliRtcConnectionStatusChangeReason) {
    /** 未知原因 */
    AliRtcConnectionChangedDummyReason = 0,
    /** 媒体通道变更 */
    AliRtcConnectionChangedMediaPathChanged,
    /** 心跳超时 */
    AliRtcConnectionChangedSignalingHeartbeatTimeout,
    /** 心跳恢复 */
    AliRtcConnectionChangedSignalingHeartbeatAlive,
    /** DNS解析成功 */
    AliRtcConnectionChangedSignalingHttpdnsResolved,
    /** DNS解析失败 */
    AliRtcConnectionChangedSignalingHttpdnsFailure,
    /** GSLB请求失败 */
    AliRtcConnectionChangedSignalingGslbFailure,
    /** GSLB请求成功 */
    AliRtcConnectionChangedSignalingGslbSucccess,
    /** 加入频道失败 */
    AliRtcConnectionChangedSignalingJoinChannelFailure,
    /** 加入频道成功 */
    AliRtcConnectionChangedSignalingJoinChannelSuccess,
    /** 离开频道 */
    AliRtcConnectionChangedSignalingLeaveRoom,
    /** 信令建立连接 */
    AliRtcConnectionChangedSignalingConnecting,
};


/**
 * @brief 频道类型
 */
typedef NS_ENUM(NSInteger, AliRtcChannelProfile) {
    /** 通信模式 */
    AliRtcCommunication = 0,
    /** 互动模式 */
    AliRtcInteractivelive,
    /** 低延时互动直播模式 */
    AliRtcInteractiveWithLowLatencyLive,
};

/**
 * @brief 角色类型
 */
typedef NS_ENUM(NSInteger, AliRtcClientRole) {
    /** 互动角色 */
    AliRtcClientRoleInteractive = 0,
    /** 观众角色 */
    AliRtcClientRolelive,
};

/**
 * @brief 本地静音模式
*/
typedef NS_ENUM(NSInteger, AliRtcMuteLocalAudioMode) {
    /** 默认模式(静音全部，包括麦克风及外部输入音频) */
    AliRtcMuteAudioModeDefault = 0,
    /** 静音全部(包括麦克风及外部输入音频) */
    AliRtcMuteAllAudioMode,
    /** 只静音麦克风 */
    AliRtcMuteOnlyMicAudioMode,
    /** 占位符，无意义 */
    AliRtcMuteLocalAudioMax,
};


/**
 * @brief 镜像模式
 */
typedef NS_ENUM(NSInteger, AliRtcRenderMirrorMode) {
    /** 只有前置摄像头预览镜像，其余不镜像 */
    AliRtcRenderMirrorModeOnlyFrontCameraPreviewEnabled = 0,
    /** 镜像开启 */
    AliRtcRenderMirrorModeAllEnabled = 1,
    /** 镜像关闭 */
    AliRtcRenderMirrorModeAllDisabled = 2,
};

/**
 * @brief 音乐伴奏播放状态
 */
typedef NS_ENUM(NSInteger, AliRtcAudioPlayingStateCode) {
    /** 开始播放 */
    AliRtcAudioPlayingStarted       = 100,
    /** 停止播放 */
    AliRtcAudioPlayingStopped       = 101,
    /** 播放暂停 */
    AliRtcAudioPlayingPaused        = 102,
    /** 播放恢复 */
    AliRtcAudioPlayingResumed       = 103,
    /** 播放完毕 */
    AliRtcAudioPlayingEnded         = 104,
    /** 正在缓冲 */
    AliRtcAudioPlayingBuffering     = 105,
    /** 缓冲结束 */
    AliRtcAudioPlayingBufferingEnd  = 106,
    /** 播放失败 */
    AliRtcAudioPlayingFailed        = 107,
};

/**
 * @brief 音乐伴奏播放错误码
 */
typedef NS_ENUM(NSInteger, AliRtcAudioPlayingErrorCode) {
    /** 没有错误 */
    AliRtcAudioPlayingNoError        = 0,
    /** 打开文件失败 */
    AliRtcAudioPlayingOpenFailed     = -100,
    /** 解码文件失败 */
    AliRtcAudioPlayingDecodeFailed   = -101,
};

/**
 * @brief 录制类型
 */
typedef NS_ENUM(NSUInteger, AliRtcRecordType) {
    /** 录制单个音频文件 */
    AliRtcRecordTypeAudio = 0,
};

/**
 * @brief 录制格式
 */
typedef NS_ENUM(NSUInteger, AliRtcRecordFormat) {
    /** 录制AAC格式文件 */
    AliRtcRecordFormatAAC = 0,
    /** 录制WAV格式文件 */
    AliRtcRecordFormatWAV,
};

/**
 * @brief 录制音频质量
 */
typedef NS_ENUM(NSUInteger, AliRtcAudioQuality) {
    /** 低质量文件录制，文件体积较小，音质一般 */
    AliRtcAudioQualityLow = 0,
    /** 中等质量文件录制，文件体积中等，音质中等 */
    AliRtcAudioQualityMidium,
    /** 高质量文件录制，文件体积较大，音质较好 */
    AliRtcAudioQualityHigh,
};

/**
 * @brief 录制视频质量
 */
typedef NS_ENUM(NSUInteger, AliRtcVideoQuality) {
    /**  默认，和采集保持一致 */
    AliRtcVideoQualityDefault = 0,
};

/**
 * @brief 录制音频采样率
*/
typedef NS_ENUM(NSInteger, AliRtcAudioSampleRate) {
    /** 采样率：8000 */
    AliRtcAudioSampleRate_8000 = 0,
    /** 采样率：11025 */
    AliRtcAudioSampleRate_11025 = 1,
    /** 采样率：16000 */
    AliRtcAudioSampleRate_16000 = 2,
    /** 采样率：22050 */
    AliRtcAudioSampleRate_22050 = 3,
    /** 采样率：32000 */
    AliRtcAudioSampleRate_32000 = 4,
    /** 采样率：44100 */
    AliRtcAudioSampleRate_44100 = 5,
    /** 采样率：48000 */
    AliRtcAudioSampleRate_48000 = 6,
};

/**
 * @brief 音频路由
 */
typedef NS_ENUM(NSInteger, AliRtcAudioRouteType) {
    /** 默认的语音路由 */
    AliRtcAudioRouteTypeDefault        = 0,
    /** 耳机 */
    AliRtcAudioRouteTypeHeadset        = 1,
    /** 听筒 */
    AliRtcAudioRouteTypeEarpiece       = 2,
    /** 不带麦克风的耳机 */
    AliRtcAudioRouteTypeHeadsetNoMic   = 3,
    /** 手机扬声器 */
    AliRtcAudioRouteTypeSpeakerphone   = 4,
    /** 外接扬声器 */
    AliRtcAudioRouteTypeLoudSpeaker    = 5,
    /** 蓝牙耳机 */
    AliRtcAudioRouteTypeBlueTooth      = 6,
};

/**
 * @brief 视频数据输出位置内容
 */
typedef NS_ENUM(NSInteger, AliRtcVideoObserPosition) {
    /** 采集视频数据，对应输出回调onCaptureVideoSample */
    AliRtcPositionPostCapture = 1 << 0,
    /** 渲染视频数据，对应输出回调onRemoteVideoSample */
    AliRtcPositionPreRender = 1 << 1,
    /** 编码前视频数据，对应输出回调onPreEncodeVideoSample */
    AliRtcPositionPreEncoder = 1 << 2,
};
  
/**
 * @brief 视频输出宽度对齐方式
 */
typedef enum {
    /** 保持原有视频宽度(默认值) */
    AliRtcAlignmentDefault = 0,
    /** 宽度偶数对齐 */
    AliRtcAlignmentEven = 1,
    /** 宽度是4的倍数 */
    AliRtcAlignment4 = 2,
    /** 宽度是8的倍数 */
    AliRtcAlignment8 = 3,
    /** 宽度是16的倍数 */
    AliRtcAlignment16 = 4,
} AliRtcVideoObserAlignment;

/**
 * @brief Debug显示类型
 */
typedef NS_ENUM(NSInteger, AliRtcShowDebugViewType){
    /** 不显示 */
    AliRtcShowTypeNone     = 0,
    /** 音频 */
    AliRtcShowTypeAudio    = 1,
    /** 视频 */
    AliRtcShowTypeVideo    = 2,
    /** 网络 */
    AliRtcShowTypeNetwork  = 3,
    /** 全部 */
    AliRtcShowTypeAll      = 4,
};

/**
 * @brief 录制音频设置
 */
typedef struct  {
    /** 音频采样率类型 */
    AliRtcAudioSampleRate sampleRate;
    /** 音频录制质量 */
    AliRtcAudioQuality quality;
    /** 是否允许录制外部pcm输入渲染数据 */
    bool enableRecordExternalRenderPCM;
}AliRtcRecordAudioConfig;

/**
 * @brief 录制视频设置
 */
typedef struct  {
    /** 视频质量 */
    AliRtcVideoQuality quality;
}AliRtcRecordVideoConfig;

/**
 * @brief 美颜参数
 */
@interface AliRtcBeautyConfig : NSObject
/** 美白等级，建议取值范围[0-1.0] */
@property (nonatomic, assign) float whiteningLevel;
/** 磨皮等级，建议取值范围[0-1.0] */
@property (nonatomic, assign) float smoothnessLevel;

@end


/**
 * @brief 错误码
 */
typedef NS_ENUM(NSInteger, AliRtcErrorCode) {
    /** 状态正常，无错误 */
    AliRtcErrNone                           = 0,

    /****************************************************
     * 入会错误码
     ****************************************************/
    /** AppId不存在，请在控制台创建应用 */
    AliRtcErrJoinBadAppId                   = 0x02010201,
    /** AppId已失效，请在控制台重新启用应用 */
    AliRtcErrJoinInvalidAppId               = 0x02010202,
    /**
     * 频道不存在，请尝试重新加入频道
     * 如会议发起者入会后又很快离会，第二个人随后入会，发现会议已经不存在了。
     */
    AliRtcErrJoinBadChannel                 = 0x02010204,
    /** 频道已经失效（目前频道有效期为48小时），请重新生成频道鉴权令牌（Token） */
    AliRtcErrJoinInvalidChannel             = 0x02010203,
    /** Token无效。 请重新生成频道鉴权令牌（Token） */
    AliRtcErrJoinBadToken                   = 0x02010205,
    /** 加入频道超时，请检查网络连接是否正常 */
    AliRtcErrJoinTimeout                    = 0x01020204,
    /** 参数错误，{@link AliRtcAuthInfo} 中的字段为空或者timestamp<=0，请检查字段是否完整 */
    AliRtcErrJoinBadParam                   = 0x01030101,
    /** 加入频道失败 */
    AliRtcErrJoinChannelFailed              = 0x01030202,

    /****************************************************
     * 日志模块错误码
     ****************************************************/  
    /** 日志模块已经初始化 */
    AliRtcErrLogAlreadyInit = 0x01030105,
    /** 日志模块根路径错误，请检查路径是否存在或路径是否具有写入权限 */
    AliRtcErrLogRootPathError = 0x01030106,

    /****************************************************
     * 音频设备错误码
     ****************************************************/
    /**
     * 采集设备初始化失败、采集设备媒体服务异常、音频设备被占用。
     * - Mac端和Windows端查看系统设置中音频设备是否有能量条
     * - iOS端和Android端确认是否被其他应用占用
     * - 如果都正常，请重启设备
     */
    AliRtcErrMicOpenFail                    = 0x01040404,
    /**
     * 播放设备初始化失败、播放设备媒体服务异常、音频设备被占用。
     * - Mac端和Windows端查看系统设置中音频设备是否有能量条
     * - iOS端和Android端确认是否被其他应用占用
     * - 如果都正常，请重启设备
     */
    AliRtcErrSpeakerOpenFail                = 0x01040405,
    /** 系统性能不足、采集设备媒体服务异常、音频设备被占用。建议重启应用或重启设备 */
    AliRtcErrMicInterrupt                   = 0x01040406,
    /** 系统性能不足，播放设备媒体服务异常，音频设备被占用。建议重启应用或重启设备 */
    AliRtcErrSpeakerInterrupt               = 0x01040407,
    /** 麦克风设备未授权，建议去系统设置中，打开麦克风授权，并且重新加入频道 */
    AliRtcErrMicAuthFail                    = 0x01040408,
    /** 无可用的音频采集设备，检查是否接入了可用的麦克风，并检查系统设置中，该设备是否被禁用 */
    AliRtcErrMicNotAvailable                = 0x01040409,
    /** 无可用的音频播放设备，检查是否接入了可用的扬声器或耳机，并检查系统设置中，该设备是否被禁用 */
    AliRtcErrSpeakerNotAvailable            = 0x01040410,

    /****************************************************
     * 视频设备错误码
     ****************************************************/
    /** 采集设备初始化失败，检查系统相机是否可用，移动端App是否占用了相机 */
    AliRtcErrCameraOpenFail                 = 0x01040104,
    /** 采集过程中出现异常，Mac、Winodows电脑相机采集灯熄灭，设备被强制中断。建议重新加入频道或者重启App */
    AliRtcErrCameraInterrupt                = 0x01040106,
    /** 渲染设备初始化失败，检查Windows端显卡驱动是否需要升级，移动端手机型号或者Android平板盒子等外设是否支持OpenGL */
    AliRtcErrDisplayOpenFail                = 0x01040201,
    /** 渲染过程中出现异常，系统异常错误导致渲染引擎报错，重新加入频道或者重启App */
    AliRtcErrDisplayInterrupt               = 0x01040202,

    /****************************************************
     * 网络错误码
     ****************************************************/
    /** 媒体通道建立失败，检查网络连接是否正常 */
    AliRtcErrIceConnectionConnectFail       = 0x01050201,
    /** 媒体通道重连失败，检查网络连接是否正常 */
    AliRtcErrIceConnectionReconnectFail     = 0x01050202,
    /** 信令心跳超时，检查网络连接是否正常 */
    AliRtcErrIceConnectionHeartbeatTimeout  = 0x0102020C,

    /****************************************************
     * 低延时互动直播模式相关错误码
     ****************************************************/
    /** 低延时互动直播信令失败 */
    AliRtcErrCdnLiveCommunicationFailed     = 0x01070003,
    /** 低延时互动直播媒体设置错误 */
    AliRtcErrCdnLiveMeidaSettingFailed      = 0x01070004,
    /** 低延时互动直播当前房间没有主播推流 */
    AliRtcErrCdnLiveNoneBroadcaster         = 0x01070005,
    /** 低延时互动直播错误，应用层需要重新创建新的SDK实例 */
    AliRtcErrCdnLiveNeedRestart             = 0x01070006,
    /** 低延时互动直播错误，应用层需要稍等一定时间（自定义间隔）重新创建新的SDK实例 */
    AliRtcErrCdnLiveNeedRestartAgainLater   = 0x01070007,
    /** 低延迟互动直播服务不可用或者服务降级，客户端应该选择其它方式拉超大方会流，即不从cdn sfu拉流 */
    AliRtcErrCdnLiveServiceUnavailable      = 0x01070008,
    /** 低延迟互动直播网络中断错误，销毁当前sdk实例重新创建sdk后重新走订阅流程 */
    AliRtcErrCdnLiveMediaConnectionInterruption = 0x01070009,

    /****************************************************
     * 推流相关错误码
     ****************************************************/
    /** 推流无效 */
    AliRtcErrPublishInvaild                 = 0x01030305,
    /** 未进入频道推流失败 */
    AliRtcErrPublishNotJoinChannel          = 0x01010406,
    /** 推送音频流失败 */
    AliRtcErrPublishAudioStreamFailed       = 0x01010450,
    /** 推送视频流失败 */
    AliRtcErrPublishVideoStreamFailed       = 0x01010451,
    /** 推送小流失败 */
    AliRtcErrPublishDualStreamFailed        = 0x01010452,
    /** 推送屏幕共享失败 */
    AliRtcErrPublishScreenShareFailed       = 0x01010453,
    /** 屏幕共享配置错误 */
    AliRtcErrPublishScreenShareConfigError  = 0x01010454,

    /****************************************************
     * 订阅相关错误码
     ****************************************************/
    /** 订阅无效 */
    AliRtcErrSubscribeInvaild               = 0x01030404,
    /** 未进入频道订阅错误 */
    AliRtcErrSubscribeNotJoinChannel        = 0x01010550,
    /** 订阅音频流失败 */
    AliRtcErrSubscribeAudioStreamFailed     = 0x01010551,
    /** 订阅视频流失败 */
    AliRtcErrSubscribeVideoStreamFailed     = 0x01010552,
    /** 订阅小流失败 */
    AliRtcErrSubscribeDualStreamFailed      = 0x01010553,
    /** 订阅屏幕共享失败 */
    AliRtcErrSubscribeScreenShareFailed     = 0x01010554,

    /****************************************************
     * 其他错误码
     ****************************************************/
    /** SDK状态错误，建议销毁SDK重新创建实例。 */
    AliRtcErrSdkInvalidState                = 0x01030204,
    /** 参数不匹配 */
    AliRtcErrInvalidArguments               = 0x01030103,
    /** Session已经被移除，建议销毁实例之后重新创建实例并加入频道。 */
    AliRtcErrSessionRemoved                 = 0x02010105,
    /** buffer队列饱和，用于外部输送裸数据功能，建议降低外部输入频次，设置等待20ms，并且单次不超过40ms数据。 */
    AliRtcErrAudioBufferFull                = 0x01070101,
    /** buffer队列饱和，用于外部输送裸数据功能，建议降低外部输入频次，设置等待视频帧间隔后再输入。 */
    AliRtcErrVideoBufferFull                = 0x01070102,
    /** 互动模式下设置角色错误 */
    AliRtcErrUpdateRoleChannel              = 0x01020201,
    /** SDK内部错误 */
    AliRtcErrInner                          = -1,
};

/**
 * @brief OnBye类型
 */
typedef NS_ENUM(NSInteger, AliRtcOnByeType) {
    /** 当前user被踢出channel */
    AliRtcOnByeBeKickedOut          = 1,
    /** channel已结束，需要离开会议 */
    AliRtcOnByeChannelTerminated    = 2,
    /** 相同userID在其他设备joinChannel，当前设备被下线 */
    AliRtcOnByeUserReplaced         = 3,
};

/**
 * @brief SDK问题反馈类型
 */
typedef NS_ENUM(NSInteger, AliRtcFeedbackType) {
    /** 视频设备问题 */
    AliRtcFeedbackVideoDeviceFail   = 101, 
    /** 视频无画面 */
    AliRtcFeedbackVideoNotRender    = 102, 
    /** 音频设备问题 */
    AliRtcFeedbackAudioDeviceFail   = 201, 
    /** 音频无声音 */
    AliRtcFeedbackAudioNotRender    = 202, 
    /** 音频回声异常 */
    AliRtcFeedbackAudioEchoError    = 203, 
    /** 会议状态异常：入会异常、离会异常等 */
    AliRtcFeedbackChannelTypeError  = 301, 
    /** SDK其他状态异常 */
    AliRtcFeedbackSDKTypeError      = 302, 
    /** 网络卡顿问题 */
    AliRtcFeedbackNetworkUnfluent   = 401, 
    /** 视频清晰问题 */
    AliRtcFeedbackVideoBlurring     = 402, 
    /** 未知类型 */
    AliRtcFeedbackUnkonw            = -1,  
};

/**
 * @brief 旁路推流LiveStream状态
 */
typedef NS_ENUM(NSInteger, AliRtcTrascodingLiveTaskStatus) {
    /** 任务开始 */
    AliRtcTrascodingLiveTaskStatusStart = 0,
    /** 任务更新 */
    AliRtcTrascodingLiveTaskStatusUpdate = 1,
    /** 任务已停止 */
    AliRtcTrascodingLiveTaskStatusStop = 2,
};

/**
 * @brief 旁路推流错误码
 */
typedef NS_ENUM(NSInteger, AliRtcTrascodingLiveStreamErrorCode) {
    AliRtcTrascodingLiveStreamErrorPublishOk            = 0,
    AliRtcTrascodingLiveStreamErrorStreamNotFound       = 0x01100001,
    AliRtcTrascodingLiveStreamErrorStreamAlreadyExist   = 0x01100002,
    AliRtcTrascodingLiveStreamErrorInvalidParam         = 0x01100003,
    AliRtcTrascodingLiveStreamErrorInternalError        = 0x01100004,
    AliRtcTrascodingLiveStreamErrorRtmpServerError      = 0x01100005,
    AliRtcTrascodingLiveStreamErrorRtmpStreamUrlError   = 0x01100006,
    AliRtcTrascodingLiveStreamErrorPublishTimeout       = 0x01100007,
    AliRtcTrascodingLiveStreamErrorNotAuthorized        = 0x01100008,
};

/**
 * @brief 跨频道转推事件
 */
typedef NS_ENUM(NSInteger, AliRtcChannelRelayEvent) {
    /** 跨频道转推开始 */
    AliRtcChannelRelayStart     = 0,
    /** 跨频道转推更新 */
    AliRtcChannelRelayUpdate    = 1,
    /** 跨频道转推结束 */
    AliRtcChannelRelayStop      = 2,
};

/**
 * @brief 跨频道转推事件
 */
typedef NS_ENUM(NSInteger, AliRtcChannelRelayState) {
    /** 跨频道转推初始化状态 */
    AliRtcChannelRelayStateInit         = 3,
    /** 跨频道转推连接中状态*/
    AliRtcChannelRelayStateConnecting   = 4,
    /** 跨频道转推运行中状态 */
    AliRtcChannelRelayStateRunning      = 5,
    /** 跨频道转推失败状态 */
    AliRtcChannelRelayStateFailure      = 6,
};

/**
 * @brief 采集偏好
 */
typedef NS_ENUM(NSInteger, AliRtcCaptureOutputPreference)  {
    /** SDK自动调整采集参数 */
    AliRtcCaptureOutputPreferenceAuto = 0,
    /** SDK优先保证设备性能，根据设置编码参数选择最接近的摄像头输出参数 */
    AliRtcCaptureOutputPreferencePerformance = 1,
    /** SDK优先保证视频预览质量，选择较高的摄像头输出参数 */
    AliRtcCaptureOutputPreferencePreview = 2,
};

/**
 * @brief 摄像头方向
*/
typedef NS_ENUM(NSInteger, AliRtcCameraDirection)  {
    /** 无效，不可用 */
    AliRtcCameraDirectionInvalid = -1,
    /** 后置摄像头 */
    AliRtcCameraDirectionBack = 0,
    /** 前置摄像头 */
    AliRtcCameraDirectionFront = 1,
};

/**
 * @brief 推流状态
*/
typedef NS_ENUM(NSInteger, AliRtcPublishState) {
    /** 0: SDK初始推流状态
     */
    AliRtcStatsPublishIdle = 0,
    /** 1: 未推流状态，可能是因为:
     * - 已设置停止推送媒体流
     * - 推送媒体流失败
     */
    AliRtcStatsNoPublish   = 1,
    /** 2: 推流链接建立过程中
     */
    AliRtcStatsPublishing  = 2,
    /** 3: 推流成功
     */
    AliRtcStatsPublished   = 3,
};

/**
 * @brief 订阅状态
 */
typedef NS_ENUM(NSInteger, AliRtcSubscribeState) {
    /** 初始状态 */
    AliRtcStatsSubscribeIdle = 0,
    /** 未订阅 */
    AliRtcStatsNoSubscribe   = 1,
    /** 订阅中 */
    AliRtcStatsSubscribing   = 2,
    /** 已订阅 */
    AliRtcStatsSubscribed    = 3,
};

/**
 * @brief 用户离线原因
 */
typedef NS_ENUM(NSInteger, AliRtcUserOfflineReason) {
    /** 用户主动离开 */
    AliRtcUserOfflineQuit = 0,
    /** 因过长时间收不到对方数据包，超时掉线 */
    AliRtcUserOfflineDropped = 1,
    /** 用户身份从主播切换为观众时触发 */
    AliRtcUserOfflineBecomeAudience = 2,
};

/**
 * @brief 实时数据
 */
typedef struct {
    /** 可用带宽(kb) */
    long long available_sent_kbitrate;
    /** 总发送码率(kb) */
    long long sent_kbitrate;
    /** 总接收码率(kb) */
    long long rcvd_kbitrate;
    /** 总发送数据量(bytes) */
    long long sent_bytes;
    /** 总接收数据量(bytes) */
    long long rcvd_bytes;
    /** 视频接受码率(kb) */
    long long video_rcvd_kbitrate;
    /** 视频发送码率(kb) */
    long long video_sent_kbitrate;
    /** 通话时长(s) */
    long long call_duration;
    /** 进程CPU使用量(%) */
    float cpu_usage;
    /** 系统CPU使用量(%) */
    float systemCpuUsage;
    /** 客户端到服务器的丢包率(%) */
    long long sent_loss_rate;
    /** 客户端到服务器的丢包数 */
    long long sent_loss_pkts;
    /** 客户端到服务器的总包数 */
    long long sent_expected_pkts;
    /** 客户端到服务器的下行丢包率（%） */
    long long rcvd_loss_rate;
    /** 客户端到服务器的下行丢包数 */
    long long rcvd_loss_pkts;
    /** 客户端到服务器的下行总包数 */
    long long rcvd_expected_pkts;
    /** 客户端到服务器的延迟(ms) */
    long long lastmile_delay;
} AliRtcStats;

/**
 * @brief 背景替换背景图缩放模式
*/
typedef NS_ENUM(NSUInteger, AliRtcBokehScaleModel) {
    /** 等比裁剪，当背景图像宽高比和视频数据宽高比不一致时, 为了保持等比例缩放, 会将背景图像裁剪到视频比例, 超出部分背景图片内容将会丢失 */
    AliRtcBokehScaleModelCrop = 0,
    /** 填充黑边，当背景图像宽高比和视频数据宽高比不一致时, 为了保持等比例缩放, 会对背景进行黑边填充 */
    AliRtcBokehScaleModelFill = 1,
};

/**
 * @brief 本地视频统计信息
 */
@interface AliRtcLocalVideoStats : NSObject

/** 视频流track类型 */
@property (nonatomic, assign) AliRtcVideoTrack track;
/** 目标编码码率 */
@property (nonatomic, assign) unsigned int target_encode_bitrate;
/** 实际编码码率 */
@property (nonatomic, assign) unsigned int actual_encode_bitrate;
/** 发送码率 */
@property (nonatomic, assign) unsigned int sent_bitrate;
/** 采集帧率 */
@property (nonatomic, assign) unsigned int capture_fps;
/** 发送帧率 */
@property (nonatomic, assign) unsigned int sent_fps;
/** 编码帧率 */
@property (nonatomic, assign) unsigned int encode_fps;
/** 每秒平均QP */
@property (nonatomic, assign) unsigned int avg_qp;

@end

/**
 * @brief 远端视频统计信息
 */
@interface AliRtcRemoteVideoStats : NSObject

@property (nonatomic, copy) NSString * _Nonnull userId; // 远端用户userID
@property (nonatomic, assign) AliRtcVideoTrack track;   // 视频流track类型
@property (nonatomic, assign) unsigned int width;           // width
@property (nonatomic, assign) unsigned int height;          // height
@property (nonatomic, assign) unsigned int decode_fps;      // 解码帧率
@property (nonatomic, assign) unsigned int render_fps;      // 渲染帧率
@property (nonatomic, assign) unsigned int frozen_times;    // 卡顿次数

@end

/**
 * @brief 本地音频统计信息
 */
@interface AliRtcLocalAudioStats : NSObject

@property (nonatomic, assign) AliRtcAudioTrack track;   // 音频流track类型
@property (nonatomic, assign) unsigned int num_channel;     // 声道数
@property (nonatomic, assign) unsigned int sent_samplerate; // 采样率
@property (nonatomic, assign) unsigned int sent_bitrate;    // 发送端音频的瞬时码率（Kbps）

@end

/**
 * @brief 远端音频统计信息
 */
@interface AliRtcRemoteAudioStats : NSObject

@property (nonatomic, copy) NSString * _Nonnull userId;    // 远端用户userID
@property (nonatomic, assign) AliRtcAudioTrack track;      // 音频流track类型
@property (nonatomic, assign) unsigned int quality;            // 远端用户发送的音频流质量, 具体类型参看AliRtcTranportAudioQuality
@property (nonatomic, assign) unsigned int audio_loss_rate;    // 回调周期内的音频丢帧率
@property (nonatomic, assign) unsigned int rcvd_bitrate;       // 接收流的瞬时码率（Kbps）
@property (nonatomic, assign) unsigned int total_frozen_times; // 远端用户加入频道后音频卡顿的累计时长 (ms)。
@property (nonatomic, assign) unsigned int network_transport_delay; // 发送端到接收端的网络延时（ms)
@property (nonatomic, assign) unsigned int jitter_buffer_delay; // 接受端到网络抖动缓存的网络延时（ms)

@end

/**
 * @brief 发言人音量信息
 */
@interface AliRtcUserVolumeInfo : NSObject

/** 发言人的用户ID */
@property (nonatomic, copy) NSString * _Nonnull uid;
/** 发言状态，YES：正在说话，NO：没有说话 */
@property (nonatomic, assign) BOOL speech_state;
/** 音量值，取值范围[0,255] */
@property (nonatomic, assign) int volume;

@end

/**
 * @brief 入会鉴权信息
 */
@interface AliRtcAuthInfo : NSObject

@property (nonatomic, retain) NSString * _Nonnull channelId;
@property (nonatomic, retain) NSString * _Nonnull userId;
@property (nonatomic, retain) NSString * _Nonnull appId;
@property (nonatomic, retain) NSString * _Nonnull nonce;
@property (nonatomic, retain) NSString * _Nonnull token;
@property (nonatomic, retain) NSString * _Nullable session;
@property (nonatomic, retain) NSString * _Nullable role;
@property (nonatomic, retain) NSArray <NSString *> * _Nullable gslb;
@property (nonatomic, retain) NSArray <NSString *> * _Nullable agent;
@property (nonatomic, assign) long long timestamp;

@end

/**
 * @brief 显示视图配置
*/
@interface AliVideoCanvas : NSObject
/** 显示视图 */
@property (nonatomic, strong) UIView * _Nonnull view;
/** 渲染模式，默认值为 {@link AliRtcRenderModeAuto} */
@property (nonatomic) AliRtcRenderMode renderMode;
/** 镜像模式，默认值为 {@link AliRtcRenderMirrorModeAllDisabled} */
@property (nonatomic) AliRtcRenderMirrorMode mirrorMode;
/** 背景颜色，格式为RGB的Hex */
@property (nonatomic) int backgroundColor;
/** 旋转角度，默认值为 {@link AliRtcRotationMode_0} */
@property (nonatomic, assign) AliRtcRotationMode rotationMode;

@end

/**
 * @brief 水印配置
 */
@interface AliRtcWatermarkConfig : NSObject
/** 预览水印是否可见  */
@property (nonatomic, assign) BOOL visibleInPreview;
/** 竖屏水印坐标信息  */
@property (nonatomic, assign) CGRect positionInPortraitMode;
/** 横屏水印坐标信息  */
@property (nonatomic, assign) CGRect positionInLandscapeMode;
/** 水印透明度  */
@property (nonatomic, assign) float alpha;
/** 归一化  */
@property (nonatomic, assign) BOOL normalized;

@end


/**
 * @brief 音频裸数据
 */
@interface AliRtcAudioDataSample : NSObject

@property (nonatomic, assign) long dataPtr;
@property (nonatomic, assign) int numOfSamples;
@property (nonatomic, assign) int bytesPerSample;
@property (nonatomic, assign) int numOfChannels;
@property (nonatomic, assign) int samplesPerSec;

@end

/**
 * @brief 视频裸数据
 */
@interface AliRtcVideoDataSample : NSObject

@property (nonatomic, assign) AliRtcVideoFormat format;
@property (nonatomic, assign) AliRtcBufferType type;
@property (nonatomic, assign) CVPixelBufferRef _Nullable pixelBuffer;
@property (nonatomic, assign) long dataPtr;
@property (nonatomic, assign) long dataYPtr;
@property (nonatomic, assign) long dataUPtr;
@property (nonatomic, assign) long dataVPtr;
@property (nonatomic, assign) long dataLength;
@property (nonatomic, assign) int strideY;
@property (nonatomic, assign) int strideU;
@property (nonatomic, assign) int strideV;
@property (nonatomic, assign) int stride;
@property (nonatomic, assign) int height;
@property (nonatomic, assign) int width;
@property (nonatomic, assign) int rotation;
@property (nonatomic, assign) long long timeStamp;

@end

/**
 * @brief 跨频道转推配置
 */
@interface AliRtcChannelRelayConfiguration : NSObject

@property (nonatomic, copy, readonly) NSDictionary<NSString*,AliRtcAuthInfo*> *_Nullable destChannelInfos;

- (void)addDestChannelInfoWithChannelId:(NSString *_Nullable)channeId
                               authInfo:(AliRtcAuthInfo *_Nullable)authInfo;

- (void)removeDestChannelInfo:(NSString *_Nullable)channeId;

- (void)removeAllDestChannelInfo;

@end


/**
 * @brief 消息通道消息
 * @note 已废弃使用
 */
@interface AliRtcMessage : NSObject

@property (nonatomic, strong) NSString * _Nullable tID;
@property (nonatomic, strong) NSString * _Nullable contentType;
@property (nonatomic, strong) NSString * _Nullable content;
@end

/**
 * @brief 消息通道Response
 * @note 已废弃使用
 */
@interface AliRtcMessageResponse : NSObject

@property (nonatomic, assign) int result;
@property (nonatomic, strong) NSString * _Nullable contentType;
@property (nonatomic, strong) NSString * _Nullable content;
@end

/**
 * @brief 摄像头采集偏好
*/
@interface AliRtcCameraCapturerConfiguration : NSObject

@property (nonatomic) AliRtcCaptureOutputPreference preference;
@property (nonatomic) AliRtcCameraDirection cameraDirection;

@end

typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingDisplayType) {
    NOT_DISPLAY = 0,
    ALWAYS = 1,
    WHEN_NO_VIDEO = 2
};

/**
* @brief 旁路直播图片
*/
@interface AliRtcLiveTranscodingImage : NSObject
@property (nonatomic, copy) NSString *_Nullable url;
@property (nonatomic, assign) float alpha;
@property (nonatomic, assign) AliRtcLiveTranscodingDisplayType display;
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;
@property (nonatomic, assign) int width;
@property (nonatomic, assign) int height;
@property (nonatomic, assign) int zOrder;
@end

typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingFontType) {
  NOTO_SERIF_CJKSC_REGULAR = 0,
  ALIBABA_PUHUITI_REGULAR = 1,
  ALIBABA_PUHUITI_BOLD = 2,
  ALIBABA_PUHUITI_Heavy = 3,
  ALIBABA_PUHUITI_LIGHT = 4,
  ALIBABA_PUHUITI_MEDIUM = 5
};

/**
* @brief 旁路直播文字格式
*/
@interface AliRtcLiveTranscodingText : NSObject
@property (nonatomic, copy) NSString *_Nullable text;
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;
@property (nonatomic, assign) int zOrder;
@property (nonatomic, assign) AliRtcLiveTranscodingFontType fontType;
@property (nonatomic, assign) int fontSize;
@property (nonatomic, assign) int fontColor;//0xRRGGBB
@end

/**
* @brief 旁路直播输入类型
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingSegmentType) {
    /** 无人像分割 */
    AliRtcLiveTranscodingNoBody = 0,
    /** 人像分割 */
    AliRtcLiveTranscodingBody = 1
};

/**
* @brief 旁路直播输入类型
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingSourceType) {
    /** 相机流 */
    AliRtcLiveTranscodingCamera = 0,
    /** 屏幕流 */
    AliRtcLiveTranscodingShareScreen = 1
};

/**
 * @brief 旁路直播用户自定义窗格信息
*/
@interface AliRtcLiveTranscodingPane : NSObject
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;
@property (nonatomic, assign) int width;
@property (nonatomic, assign) int height;
@property (nonatomic, assign) int zOrder;
@property (nonatomic, copy) NSString *_Nonnull userId;
@property (nonatomic, assign) AliRtcLiveTranscodingSourceType sourceType;
@property (nonatomic, assign) AliRtcLiveTranscodingSegmentType segmentType;
@property (nonatomic, copy) NSArray<AliRtcLiveTranscodingImage *> *_Nullable images;
@property (nonatomic, copy) NSArray<AliRtcLiveTranscodingText *> *_Nullable texts;

@end

/** 旁路直播 **/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingState) {
    AliRtcLiveTranscodingState_IDLE = 0,
    AliRtcLiveTranscodingState_CONNNECT = 1,
    AliRtcLiveTranscodingState_RUNNING = 2,
    AliRtcLiveTranscodingState_RECOVERING = 3,
    AliRtcLiveTranscodingState_FAILURE = 4,
    AliRtcLiveTranscodingState_END = 5
};

/**
* @brief 旁路模式
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingMixMode) {
    /** 单路模式 */
    AliRtcLiveTranscodingSINGLE = 0,
    /** 混流模式 */
    AliRtcLiveTranscodingMIX = 1
};

/**
* @brief 旁路直播转推流模式
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingStreamType) {
    /** 原始流 */
    AliRtcLiveTranscodingOrigin = 0,
    /** 音频 */
    AliRtcLiveTranscodingAudio = 1,
    /** 视频 */
    AliRtcLiveTranscodingVideo = 2
};

/**
* @brief 旁路直播媒体处理模式
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingMediaProcessMode) {
    /** 通用模式 */
    AliRtcLiveTranscodingNormal = 0,
    /** 虚拟背景模式 */
    AliRtcLiveTranscodingVirtualBackground = 1
};

/**
* @brief 旁路直播裁剪模式
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingCropMode) {
    /** 剪裁 */
    AliRtcLiveTranscodingCrop = 1,
    /** 填充 */
    AliRtcLiveTranscodingFill = 2
};

/**
* @brief 旁路直播时钟格式
*/
@interface AliRtcLiveTranscodingClockWidget : NSObject
@property (nonatomic, assign) int x;
@property (nonatomic, assign) int y;
@property (nonatomic, assign) AliRtcLiveTranscodingFontType fontType;
@property (nonatomic, assign) int fontSize;
@property (nonatomic, assign) int fontColor;  // 0xRRGGBB
@property (nonatomic, assign) int zOrder;
@end

/**
* @brief 旁路直播音频采样
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingAudioSampleRate) {
    AliRtcLiveTranscoding_HZ_48000 = 0,
    AliRtcLiveTranscoding_HZ_44100 = 1,
    AliRtcLiveTranscoding_HZ_32000 = 2,
    AliRtcLiveTranscoding_HZ_16000 = 3,
    AliRtcLiveTranscoding_HZ_8000 = 4
};

/**
* @brief 旁路直播自定义编码参数
*/
@interface AliRtcLiveTranscodingEncodeParam : NSObject
@property (nonatomic, assign) int videoWidth; //(0-1920]
@property (nonatomic, assign) int videoHeight; //(0-1920]
@property (nonatomic, assign) int videoFramerate; //[1,60]
@property (nonatomic, assign) int videoBitrate; //[1kbps,10000kbps]
@property (nonatomic, assign) int videoGop; //[1,60]
@property (nonatomic, assign) AliRtcLiveTranscodingAudioSampleRate audioSamplerate;
@property (nonatomic, assign) int audioBitrate; //[8kbps,500kbps]
@property (nonatomic, assign) int audioChannels; //[1,2]
@end

/**
* @brief 旁路直播计费规格
*/
typedef NS_ENUM(NSUInteger, AliRtcLiveTranscodingTaskProfile) {
    AliRtcLiveTranscoding_Profile_1IN_1080P = 0,
    AliRtcLiveTranscoding_Profile_1IN_720P = 1,
    AliRtcLiveTranscoding_Profile_1IN_360P = 2,
    AliRtcLiveTranscoding_Profile_2IN_1080P = 3,
    AliRtcLiveTranscoding_Profile_2IN_720P = 4,
    AliRtcLiveTranscoding_Profile_2IN_360P = 5,
    AliRtcLiveTranscoding_Profile_4IN_1080P = 6,
    AliRtcLiveTranscoding_Profile_4IN_720P = 7,
    AliRtcLiveTranscoding_Profile_4IN_360P = 8,
    AliRtcLiveTranscoding_Profile_9IN_1080P = 9,
    AliRtcLiveTranscoding_Profile_9IN_720P = 10,
    AliRtcLiveTranscoding_Profile_9IN_360P = 11,
    AliRtcLiveTranscoding_Profile_12IN_1080P = 12,
    AliRtcLiveTranscoding_Profile_12IN_720P = 13,
    AliRtcLiveTranscoding_Profile_12IN_360P = 14,
    AliRtcLiveTranscoding_Profile_16IN_1080P = 15,
    AliRtcLiveTranscoding_Profile_16IN_720P = 16,
    AliRtcLiveTranscoding_Profile_16IN_360P = 17,
    AliRtcLiveTranscoding_Profile_Mixed = 9999 // only audio
};

/**
* @brief 旁路模式单路参数
*/
@interface AliRtcLiveTranscodingSingleParam : NSObject
/** 用户id */
@property (nonatomic, copy) NSString *_Nullable userId;
/** 推流模式 */
@property (nonatomic, assign) AliRtcLiveTranscodingStreamType streamType;
/** 旁路直播输入类型 */
@property (nonatomic, assign) AliRtcLiveTranscodingSourceType sourceType;
@end

/**
* @brief 旁路模式混流参数
*/
@interface AliRtcLiveTranscodingMixParam : NSObject
/** 旁路直播计费规格 */
@property (nonatomic, assign) AliRtcLiveTranscodingTaskProfile taskProfile;
/** 旁路直播自定义编码参数 */
@property (nonatomic, strong) AliRtcLiveTranscodingEncodeParam *_Nullable encodeParam;
/** 旁路直播用户列表 */
@property (nonatomic, strong) NSArray<AliRtcLiveTranscodingPane *> *_Nullable users;
/** 背景色 */
@property (nonatomic, assign) int backgroundColor; //0xRRGGBB
/** 背景图片列表 */
@property (nonatomic, strong) NSArray<AliRtcLiveTranscodingImage *> *_Nullable backgrounds;
/** 水印列表 */
@property (nonatomic, strong) NSArray<AliRtcLiveTranscodingImage *> *_Nullable watermarks;
/** 时钟组件列表 */
@property (nonatomic, strong) NSArray<AliRtcLiveTranscodingClockWidget *> *_Nullable clockWidgets;
/** 剪裁模式 */
@property (nonatomic, assign) AliRtcLiveTranscodingCropMode cropMode;
/** 媒体处理模式 */
@property (nonatomic, assign) AliRtcLiveTranscodingMediaProcessMode mediaProcessMode;
@end

/**
 * @brief 旁路模式参数
*/
@interface AliRtcLiveTranscodingParam : NSObject
/** 旁路模式 */
@property (nonatomic, assign) AliRtcLiveTranscodingMixMode mixMode;
/** 路模式单路参数 */
@property (nonatomic, strong) AliRtcLiveTranscodingSingleParam *_Nullable singleParam;
/** 旁路模式混流参数 */
@property (nonatomic, strong) AliRtcLiveTranscodingMixParam *_Nullable mixParam;
@end

/**
 * @brief 相机流视频编码属性设置
*/
@interface AliRtcVideoEncoderConfiguration : NSObject

/** 视频分辨率，默认值640x480，最大值1920x1080
*/
@property (nonatomic, assign) CGSize dimensions;

/** 视频帧率，默认值15, 最大值30
*/
@property (nonatomic, assign) NSInteger frameRate;

/** 视频编码码率(Kbps)
- 默认值 512
- 设置为0，表示由SDK内部根据视频分辨率和码率计算合适的编码码率
- 码率设置根据分辨率和帧率有对应的合理范围，该值设置在合理范围内有效，否则SDK会自动调节码率到有效值
 
@note
以下码表列举常见的分辨率、帧率对应的编码码率设置的区间

 | 分辨率                  | 帧率(fps)     | 最小码率 (Kbps)                    | 推荐码率(Kbps)             |最大码率(Kbps)
 |--------------------- |--------------|---------------------------------|----------------------------|------------
 | 120 * 120              | 5                 | 10                                         | 25                                    | 75
 | 120 * 120              | 10               | 17                                         | 50                                    | 150
 | 120 * 120              | 15               | 25                                         | 70                                    | 210
 | 120 * 120              | 20               | 34                                         | 90                                    | 270
 | 120 * 120              | 30               | 50                                         | 115                                  | 345
 | 160 * 120              | 5                 | 10                                         | 30                                    | 90
 | 160 * 120              | 10               | 20                                         | 55                                    | 165
 | 160 * 120              | 15               | 30                                         | 80                                    | 240
 | 160 * 120              | 20               | 40                                         | 100                                  | 300
 | 160 * 120              | 30               | 60                                         | 130                                  | 390
 | 180 * 180              | 5                 | 10                                         | 50                                    | 150
 | 180 * 180              | 10               | 17                                         | 70                                    | 210
 | 180 * 180              | 15               | 26                                         | 100                                  | 300
 | 180 * 180              | 20               | 34                                         | 130                                  | 390
 | 180 * 180              | 30               | 51                                         | 180                                  | 540
 | 240 * 180              | 5                 | 15                                         | 60                                    | 180
 | 240 * 180              | 10               | 30                                         | 90                                    | 270
 | 240 * 180              | 15               | 45                                         | 130                                  | 390
 | 240 * 180              | 20               | 60                                         | 165                                  | 495
 | 240 * 180              | 30               | 90                                         | 230                                  | 690
 | 320 * 180              | 5                 | 15                                         | 65                                    | 195
 | 320 * 180              | 10               | 30                                         | 110                                  | 330
 | 320 * 180              | 15               | 45                                         | 170                                  | 510
 | 320 * 180              | 20               | 60                                         | 220                                  | 660
 | 320 * 180              | 30               | 90                                         | 300                                  | 900
 | 240 * 240              | 5                 | 15                                         | 70                                    | 140
 | 240 * 240              | 10               | 30                                         | 100                                  | 200
 | 240 * 240              | 15               | 45                                         | 150                                  | 300
 | 240 * 240              | 20               | 60                                         | 200                                  | 400
 | 240 * 240              | 30               | 90                                         | 256                                  | 512
 | 320 * 240              | 5                 | 20                                         | 100                                  | 200
 | 320 * 240              | 10               | 40                                         | 170                                  | 340
 | 320 * 240              | 15               | 60                                         | 256                                  | 512
 | 320 * 240              | 20               | 80                                         | 320                                  | 640
 | 320 * 240              | 30               | 120                                       | 400                                  | 800
 | 424 * 240              | 5                 | 26                                         | 100                                  | 200
 | 424 * 240              | 10               | 53                                         | 170                                  | 340
 | 424 * 240              | 15               | 79                                         | 260                                  | 520
 | 424 * 240              | 20               | 105                                       | 340                                  | 680
 | 424 * 240              | 30               | 158                                       | 430                                  | 860
 | 360 * 360              | 5                 | 30                                         | 120                                  | 240
 | 360 * 360              | 10               | 60                                         | 180                                  | 360
 | 360 * 360              | 15               | 90                                         | 260                                  | 520
 | 360 * 360              | 20               | 120                                       | 330                                  | 660
 | 360 * 360              | 30               | 180                                       | 400                                  | 800
 | 480 * 360              | 5                 | 40                                         | 150                                  | 300
 | 480 * 360              | 10               | 80                                         | 240                                  | 480
 | 480 * 360              | 15               | 120                                       | 350                                  | 700
 | 480 * 360              | 20               | 160                                       | 430                                  | 860
 | 480 * 360              | 30               | 240                                       | 512                                  | 1024
 | 640 * 360              | 5                 | 83                                         | 200                                  | 400
 | 640 * 360              | 10               | 165                                       | 340                                  | 680
 | 640 * 360              | 15               | 248                                       | 512                                  | 1024
 | 640 * 360              | 20               | 330                                       | 600                                  | 1200
 | 640 * 360              | 30               | 495                                       | 700                                  | 1400
 | 480 * 480              | 5                 | 83                                         | 170                                  | 340
 | 480 * 480              | 10               | 165                                       | 260                                  | 520
 | 480 * 480              | 15               | 248                                       | 400                                  | 800
 | 480 * 480              | 20               | 330                                       | 470                                  | 940
 | 480 * 480              | 30               | 495                                       | 600                                  | 1200
 | 640 * 480              | 5                 | 110                                       | 200                                  | 400
 | 640 * 480              | 10               | 220                                       | 350                                  | 700
 | 640 * 480              | 15               | 330                                       | 512                                  | 1024
 | 640 * 480              | 20               | 440                                       | 600                                  | 1200
 | 640 * 480              | 30               | 660                                       | 700                                  | 1400
 | 840 * 480              | 5                 | 180                                       | 256                                  | 512
 | 840 * 480              | 10               | 360                                       | 512                                  | 1024
 | 840 * 480              | 15               | 540                                       | 610                                  | 1220
 | 840 * 480              | 20               | 720                                       | 800                                  | 1600
 | 840 * 480              | 30               | 1080                                     | 930                                  | 1860
 | 960 * 720              | 5                 | 250                                       | 250                                  | 600
 | 960 * 720              | 10               | 500                                       | 500                                  | 750
 | 960 * 720              | 15               | 750                                       | 750                                  | 1125
 | 960 * 720              | 20               | 1000                                     | 1000                                | 1500
 | 960 * 720              | 30               | 1500                                     | 1500                                | 2250
 | 1280 * 720            | 5                 | 400                                       | 400                                  | 600
 | 1280 * 720            | 10               | 800                                       | 800                                  | 1200
 | 1280 * 720            | 15               | 1200                                     | 1200                                | 1800
 | 1280 * 720            | 20               | 1600                                     | 1600                                | 2400
 | 1280 * 720            | 30               | 2400                                     | 2400                                | 3600
 | 1920 * 1080          | 5                 | 500                                       | 500                                  | 750
 | 1920 * 1080          | 10               | 1000                                     | 1000                                | 1500
 | 1920 * 1080          | 15               | 1500                                     | 1500                                | 2250
 | 1920 * 1080          | 20               | 2000                                     | 2000                                | 3000
 | 1920 * 1080          | 30               | 3000                                     | 3000                                | 4500
 | 2560 * 1440          | 5                 | 800                                       | 800                                  | 1200
 | 2560 * 1440          | 10               | 1600                                     | 1600                                | 2400
 | 2560 * 1440          | 15               | 2400                                     | 2400                                | 3600
 | 2560 * 1440          | 20               | 3200                                     | 3200                                | 4800
 | 2560 * 1440          | 30               | 4800                                     | 4800                                | 7200
 | 3840 * 2160          | 5                 | 1000                                     | 1000                                | 1500
 | 3840 * 2160          | 10               | 2000                                     | 2000                                | 3000
 | 3840 * 2160          | 15               | 3000                                     | 3000                                | 4500
 | 3840 * 2160          | 20               | 4000                                     | 4000                                | 6000
 | 3840 * 2160          | 30               | 6000                                     | 6000                                | 9000
*/
@property (nonatomic, assign) NSInteger bitrate;

/** 推流镜像，默认AliRtcVideoEncoderMirrorModeDisabled，详见 {@link AliRtcVideoEncoderMirrorMode}
*/
@property (nonatomic, assign) AliRtcVideoEncoderMirrorMode mirrorMode;

/** 视频输出方向，默认AliRtcVideoEncoderOrientationModeAdaptive，详见 {@link AliRtcVideoEncoderOrientationMode}
*/
@property (nonatomic, assign) AliRtcVideoEncoderOrientationMode orientationMode;

/** 推流旋转，默认AliRtcRotationMode_0，详见 {@link AliRtcRotationMode}
*/
@property (nonatomic, assign) AliRtcRotationMode rotationMode;

@end

/**
 * @brief 屏幕流编码属性设置
*/
@interface AliRtcScreenShareEncoderConfiguration : NSObject

/** 视频分辨率，默认值0x0，最大值3840x2160
 @note
 默认值表示推流分辨率等于屏幕采集的分辨率
*/
@property (nonatomic, assign) CGSize dimensions;

/** 视频帧率，默认值5, 最大值30
*/
@property (nonatomic, assign) NSInteger frameRate;

/** 视频编码码率(Kbps)
- 默认值 512
- 设置为0，表示由SDK内部根据视频分辨率和码率计算合适的编码码率
- 码率设置根据分辨率和帧率有对应的合理范围，该值设置在合理范围内有效，否则SDK会自动调节码率到有效值
 
@note
以下码表列举常见的分辨率、帧率对应的编码码率设置的区间

 | 分辨率                  | 帧率(fps)     | 最小码率 (Kbps)                    | 推荐码率(Kbps)             |最大码率(Kbps)
 |--------------------- |--------------|---------------------------------|----------------------------|------------
 | 120 * 120              | 5                 | 10                                         | 25                                    | 75
 | 120 * 120              | 10               | 17                                         | 50                                    | 150
 | 120 * 120              | 15               | 25                                         | 70                                    | 210
 | 120 * 120              | 20               | 34                                         | 90                                    | 270
 | 120 * 120              | 30               | 50                                         | 115                                  | 345
 | 160 * 120              | 5                 | 10                                         | 30                                    | 90
 | 160 * 120              | 10               | 20                                         | 55                                    | 165
 | 160 * 120              | 15               | 30                                         | 80                                    | 240
 | 160 * 120              | 20               | 40                                         | 100                                  | 300
 | 160 * 120              | 30               | 60                                         | 130                                  | 390
 | 180 * 180              | 5                 | 10                                         | 50                                    | 150
 | 180 * 180              | 10               | 17                                         | 70                                    | 210
 | 180 * 180              | 15               | 26                                         | 100                                  | 300
 | 180 * 180              | 20               | 34                                         | 130                                  | 390
 | 180 * 180              | 30               | 51                                         | 180                                  | 540
 | 240 * 180              | 5                 | 15                                         | 60                                    | 180
 | 240 * 180              | 10               | 30                                         | 90                                    | 270
 | 240 * 180              | 15               | 45                                         | 130                                  | 390
 | 240 * 180              | 20               | 60                                         | 165                                  | 495
 | 240 * 180              | 30               | 90                                         | 230                                  | 690
 | 320 * 180              | 5                 | 15                                         | 65                                    | 195
 | 320 * 180              | 10               | 30                                         | 110                                  | 330
 | 320 * 180              | 15               | 45                                         | 170                                  | 510
 | 320 * 180              | 20               | 60                                         | 220                                  | 660
 | 320 * 180              | 30               | 90                                         | 300                                  | 900
 | 240 * 240              | 5                 | 15                                         | 70                                    | 140
 | 240 * 240              | 10               | 30                                         | 100                                  | 200
 | 240 * 240              | 15               | 45                                         | 150                                  | 300
 | 240 * 240              | 20               | 60                                         | 200                                  | 400
 | 240 * 240              | 30               | 90                                         | 256                                  | 512
 | 320 * 240              | 5                 | 20                                         | 100                                  | 200
 | 320 * 240              | 10               | 40                                         | 170                                  | 340
 | 320 * 240              | 15               | 60                                         | 256                                  | 512
 | 320 * 240              | 20               | 80                                         | 320                                  | 640
 | 320 * 240              | 30               | 120                                       | 400                                  | 800
 | 424 * 240              | 5                 | 26                                         | 100                                  | 200
 | 424 * 240              | 10               | 53                                         | 170                                  | 340
 | 424 * 240              | 15               | 79                                         | 260                                  | 520
 | 424 * 240              | 20               | 105                                       | 340                                  | 680
 | 424 * 240              | 30               | 158                                       | 430                                  | 860
 | 360 * 360              | 5                 | 30                                         | 120                                  | 240
 | 360 * 360              | 10               | 60                                         | 180                                  | 360
 | 360 * 360              | 15               | 90                                         | 260                                  | 520
 | 360 * 360              | 20               | 120                                       | 330                                  | 660
 | 360 * 360              | 30               | 180                                       | 400                                  | 800
 | 480 * 360              | 5                 | 40                                         | 150                                  | 300
 | 480 * 360              | 10               | 80                                         | 240                                  | 480
 | 480 * 360              | 15               | 120                                       | 350                                  | 700
 | 480 * 360              | 20               | 160                                       | 430                                  | 860
 | 480 * 360              | 30               | 240                                       | 512                                  | 1024
 | 640 * 360              | 5                 | 83                                         | 200                                  | 400
 | 640 * 360              | 10               | 165                                       | 340                                  | 680
 | 640 * 360              | 15               | 248                                       | 512                                  | 1024
 | 640 * 360              | 20               | 330                                       | 600                                  | 1200
 | 640 * 360              | 30               | 495                                       | 700                                  | 1400
 | 480 * 480              | 5                 | 83                                         | 170                                  | 340
 | 480 * 480              | 10               | 165                                       | 260                                  | 520
 | 480 * 480              | 15               | 248                                       | 400                                  | 800
 | 480 * 480              | 20               | 330                                       | 470                                  | 940
 | 480 * 480              | 30               | 495                                       | 600                                  | 1200
 | 640 * 480              | 5                 | 110                                       | 200                                  | 400
 | 640 * 480              | 10               | 220                                       | 350                                  | 700
 | 640 * 480              | 15               | 330                                       | 512                                  | 1024
 | 640 * 480              | 20               | 440                                       | 600                                  | 1200
 | 640 * 480              | 30               | 660                                       | 700                                  | 1400
 | 840 * 480              | 5                 | 180                                       | 256                                  | 512
 | 840 * 480              | 10               | 360                                       | 512                                  | 1024
 | 840 * 480              | 15               | 540                                       | 610                                  | 1220
 | 840 * 480              | 20               | 720                                       | 800                                  | 1600
 | 840 * 480              | 30               | 1080                                     | 930                                  | 1860
 | 960 * 720              | 5                 | 250                                       | 250                                  | 600
 | 960 * 720              | 10               | 500                                       | 500                                  | 750
 | 960 * 720              | 15               | 750                                       | 750                                  | 1125
 | 960 * 720              | 20               | 1000                                     | 1000                                | 1500
 | 960 * 720              | 30               | 1500                                     | 1500                                | 2250
 | 1280 * 720            | 5                 | 400                                       | 400                                  | 600
 | 1280 * 720            | 10               | 800                                       | 800                                  | 1200
 | 1280 * 720            | 15               | 1200                                     | 1200                                | 1800
 | 1280 * 720            | 20               | 1600                                     | 1600                                | 2400
 | 1280 * 720            | 30               | 2400                                     | 2400                                | 3600
 | 1920 * 1080          | 5                 | 500                                       | 500                                  | 750
 | 1920 * 1080          | 10               | 1000                                     | 1000                                | 1500
 | 1920 * 1080          | 15               | 1500                                     | 1500                                | 2250
 | 1920 * 1080          | 20               | 2000                                     | 2000                                | 3000
 | 1920 * 1080          | 30               | 3000                                     | 3000                                | 4500
 | 2560 * 1440          | 5                 | 800                                       | 800                                  | 1200
 | 2560 * 1440          | 10               | 1600                                     | 1600                                | 2400
 | 2560 * 1440          | 15               | 2400                                     | 2400                                | 3600
 | 2560 * 1440          | 20               | 3200                                     | 3200                                | 4800
 | 2560 * 1440          | 30               | 4800                                     | 4800                                | 7200
 | 3840 * 2160          | 5                 | 1000                                     | 1000                                | 1500
 | 3840 * 2160          | 10               | 2000                                     | 2000                                | 3000
 | 3840 * 2160          | 15               | 3000                                     | 3000                                | 4500
 | 3840 * 2160          | 20               | 4000                                     | 4000                                | 6000
 | 3840 * 2160          | 30               | 6000                                     | 6000                                | 9000
*/
@property (nonatomic, assign) NSInteger bitrate;

/** 推流旋转，默认AliRtcRotationMode_0，详见 {@link AliRtcRotationMode}
*/
@property (nonatomic, assign) AliRtcRotationMode rotationMode;
@end

/**
 * @brief 视频状态
 */
typedef NS_ENUM(NSInteger, AliRtcVideoState){
    /** 视频关闭 */
    AliRtcVideoClose     = 0,
    /** 视频打开 */
    AliRtcVideoOpen    = 1,
};

/**
 * @brief 视频状态变化原因
 */
typedef NS_ENUM(NSInteger, AliRtcVideoReason){
    /** 由客户端触发 */
    AliRtcVideoChangeByClient     = 0,
    /** 由服务器触发 */
    AliRtcVideoChangeByServer    = 1,
};

/**
 * @brief Qos反馈外置编码器请求帧类型
 */
typedef NS_ENUM(NSInteger, AliRtcVideoEncodedFrameType) {
    /** 默认无 */
    AliRtcVideoEncodedFrameNULL,
    /** IDR帧 */
    AliRtcVideoEncodedFrameIDR,
    /** LTR帧 */
    AliRtcVideoEncodedFrameLTR,
    /** B帧 */
    AliRtcVideoEncodedFrameB,
};

/**
 * @brief Qos反馈外置编码器参数结构体
 */
@interface AliRtcVideoExternalEncoderParameter : NSObject

@property (nonatomic, assign) NSInteger width;
@property (nonatomic, assign) NSInteger height;
@property (nonatomic, assign) NSInteger frame_rate;
@property (nonatomic, assign) NSInteger bitrate_bps;
@end


/** @} AliRtcDef_ios */

#pragma mark - 回调
/**
 * @defgroup AliRtcEngineDelegate_ios AliRtcEngineDelegate
 * AliRTC功能的事件回调接口
 * @{
 */
@protocol AliRtcEngineDelegate <NSObject>
@optional

/**
 * @brief 加入频道回调
 * @details 当应用调用 {@link AliRtcEngine::joinChannel:name:onResult:} 方法时，该回调表示成功/失败加入频道，并且返回频道加入的相关信息以及加入频道耗时
 * @param result 加入频道结果
 * - 0：成功
 * - 非0：失败
 *   - {@link AliRtcErrJoinBadAppId} : AppId不存在，请检查入会参数authinfo中appId是否正确
 *   - {@link AliRtcErrJoinInvalidAppId} : AppId已失效，请检查入会参数authinfo中appId是否正确
 *   - {@link AliRtcErrJoinBadChannel} : 频道不存在，请检查入会参数authinfo中channelId是否正确
 *   - {@link AliRtcErrJoinInvalidChannel} : 频道已失效，请检查入会参数authinfo中channelId是否正确
 *   - {@link AliRtcErrJoinBadToken} : token不存在，请检查入会参数authinfo生成算法是否与官网文档一致
 *   - {@link AliRtcErrJoinTimeout} : 加入频道超时，请检查当前网络是否为弱网或限速
 *   - {@link AliRtcErrJoinBadParam} : 参数错误，请检查入会参数authinfo生成是否存在非法字符，或与官网文档是否一致
 *
 * @param channel 加入频道名
 * @param elapsed 加入频道耗时
 * @note 此回调等同于joinChannel接口的block参数，二者择一处理即可
 */
- (void)onJoinChannelResult:(int)result channel:(NSString *_Nonnull)channel elapsed:(int) elapsed;

/**
 * @brief 加入频道回调
 * @details 当应用调用 {@link AliRtcEngine::joinChannel:name:onResultWithUserId:} 方法时，该回调表示成功/失败加入频道，并且返回频道加入的相关信息以及加入频道耗时
 * @param result 加入频道结果
 * - 0：成功
 * - 非0：失败
 *   - {@link AliRtcErrJoinBadAppId} : AppId不存在，请检查入会参数authinfo中appId是否正确
 *   - {@link AliRtcErrJoinInvalidAppId} : AppId已失效，请检查入会参数authinfo中appId是否正确
 *   - {@link AliRtcErrJoinBadChannel} : 频道不存在，请检查入会参数authinfo中channelId是否正确
 *   - {@link AliRtcErrJoinInvalidChannel} : 频道已失效，请检查入会参数authinfo中channelId是否正确
 *   - {@link AliRtcErrJoinBadToken} : token不存在，请检查入会参数authinfo生成算法是否与官网文档一致
 *   - {@link AliRtcErrJoinTimeout} : 加入频道超时，请检查当前网络是否为弱网或限速
 *   - {@link AliRtcErrJoinBadParam} : 参数错误，请检查入会参数authinfo生成是否存在非法字符，或与官网文档是否一致
 *
 * @param channel 加入频道名
 * @param userId   用户ID
 * @param elapsed 加入频道耗时
 * @note 此回调等同于joinChannel接口的block参数，二者择一处理即可
 */
- (void)onJoinChannelResult:(int)result channel:(NSString *_Nonnull)channel userId:(NSString *_Nonnull)userId elapsed:(int) elapsed;

/**
 * @brief 离开频道回调
 * @details 调用 {@link  AliRtcEngine::leaveChannel} 方法后，该回调表示成功/失败离开频道，回调将会返回离会的result和该频道的基本信息
 * @param result 离开频道结果，成功返回0，失败返回错误码
 * @param stats 本次频道内会话的数据统计信息。
 * @note 调用 {@link AliRtcEngine::leaveChannel} 接口后返回，如果 {@link AliRtcEngine::leaveChannel} 后直接调用 {@link AliRtcEngine::destroy} 将不会收到此回调
 */
- (void)onLeaveChannelResult:(int)result stats:(AliRtcStats)stats;

/**
 * @brief 音频推流变更回调
 * @param oldState 之前的推流状态，详见 {@link AliRtcPublishState}
 * @param newState 当前的推流状态，详见 {@link AliRtcPublishState}
 * @param elapseSinceLastState 状态变更时间间隔(毫秒)
 * @param channel 当前频道id
 */
- (void)onAudioPublishStateChanged:(AliRtcPublishState)oldState newState:(AliRtcPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 视频推流变更回调
 * @param oldState 之前的推流状态，详见 {@link AliRtcPublishState}
 * @param newState 当前的推流状态，详见 {@link AliRtcPublishState}
 * @param elapseSinceLastState 状态变更时间间隔(毫秒)
 * @param channel 当前频道id
*/
- (void)onVideoPublishStateChanged:(AliRtcPublishState)oldState newState:(AliRtcPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 次要流推流变更回调
 * @param oldState 之前的推流状态，详见 {@link AliRtcPublishState}
 * @param newState 当前的推流状态，详见 {@link AliRtcPublishState}
 * @param elapseSinceLastState 状态变更时间间隔(毫秒)
 * @param channel 当前频道id
*/
- (void)onDualStreamPublishStateChanged:(AliRtcPublishState)oldState newState:(AliRtcPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 屏幕分享推流变更回调
 * @param oldState 之前的推流状态，详见 {@link AliRtcPublishState}
 * @param newState 当前的推流状态，详见 {@link AliRtcPublishState}
 * @param elapseSinceLastState 状态变更时间间隔(毫秒)
 * @param channel 当前频道id
*/
- (void)onScreenSharePublishStateChanged:(AliRtcPublishState)oldState newState:(AliRtcPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 远端用户（通信模式）/（互动模式，主播角色）加入频道回调
 * @details 该回调在以下场景会被触发
 * - 通信模式：远端用户加入频道会触发该回调，如果当前用户在加入频道前已有其他用户在频道中，当前用户加入频道后也会收到已加入频道用户的回调
 * - 互动模式：
 *   - 远端主播角色用户加入频道会触发该回调，如果当前用户在加入频道前已有其他主播在频道中，当前用户加入频道后也会收到已加入频道主播的回调
 *   - 远端观众角色调用 {@link AliRtcEngine::setClientRole:} 切换为主播角色 {@link AliEngineClientRoleInteractive}，同时设置了推流时，会触发该回调
 *
 * @param uid 用户ID 从App server分配的唯一标示符
 * @param elapsed 用户加入频道时的耗时
 * @note 互动模式下回调行为
 * - 主播间可以互相收到加入频道回调
 * - 观众可以收到主播加入频道回调
 * - 主播无法收到观众加入频道回调
 */
- (void)onRemoteUserOnLineNotify:(NSString *_Nonnull)uid elapsed:(int)elapsed;

/**
 * @brief 远端用户（通信模式）/（互动模式，主播角色）离开频道回调
 * @details 该回调在以下场景会被触发
 * - 通信模式：远端用户离开频道会触发该回调
 * - 互动模式：
 *   - 远端主播角色 {@link AliRtcClientRoleInteractive} 离开频道
 *   - 远端主播切换调用 {@link AliRtcEngine::setClientRole:} 切换为观众角色 {@link AliRtcClientRolelive}，会触发该回调
 * - 通信模式和互动模式主播角色情况下，当长时间收不到远端用户数据，超时掉线时，会触发该回调
 *
 * @param uid 用户ID 从App server分配的唯一标示符
 * @param reason 用户离线的原因，详见 {@link AliRtcUserOfflineReason}
 */
- (void)onRemoteUserOffLineNotify:(NSString *_Nonnull)uid offlineReason:(AliRtcUserOfflineReason)reason;

/**
 * @brief 远端用户的音视频流发生变化回调
 * @details 该回调在以下场景会被触发
 * - 当远端用户从未推流变更为推流（包括音频和视频）
 * - 当远端用户从已推流变更为未推流（包括音频和视频）
 * - 互动模式下，调用 {@link AliRtcEngine::setClientRole:} 切换为主播角色 {@link AliRtcClientRoleInteractive}，同时设置了推流时，会触发该回调
 *
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param audioTrack 音频流类型，详见 {@link AliRtcAudioTrack}
 * @param videoTrack 视频流类型，详见 {@link AliRtcVideoTrack}
 * @note 该回调仅在通信模式用户和互动模式下的主播角色才会触发
 */
- (void)onRemoteTrackAvailableNotify:(NSString *_Nonnull)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack;

/**
 * @brief 音频流订阅情况变更回调
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param oldState 之前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param newState 当前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
 * @param channel 当前频道id
 */
- (void)onAudioSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 相机流订阅情况变更回调
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param oldState 之前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param newState 当前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
 * @param channel 当前频道id
 */
- (void)onVideoSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 屏幕分享流订阅情况变更回调
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param oldState 之前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param newState 当前的订阅状态，详见 {@link AliRtcSubscribeState}
 * @param elapseSinceLastState 两次状态变更时间间隔(毫秒)
 * @param channel 当前频道id
 */
- (void)onScreenShareSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 大小流订阅情况变更回调
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param oldStreamType 之前的订阅的大小流类型，详见 {@link AliRtcVideoStreamType}
 * @param newStreamType 当前的订阅的大小流类型，详见 {@link AliRtcVideoStreamType}
 * @param elapseSinceLastState 大小流类型变更时间间隔(毫秒)
 * @param channel 当前频道id
 */
- (void)onSubscribeStreamTypeChanged:(NSString *_Nonnull)uid oldStreamType:(AliRtcVideoStreamType)oldStreamType newStreamType:(AliRtcVideoStreamType)newStreamType elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel;

/**
 * @brief 当用户角色发生变化时通知
 * @param oldRole 变化前角色类型，参考 {@link AliRtcClientRole}
 * @param newRole 变化后角色类型，参考 {@link AliRtcClientRole}
 * @note 调用 {@link AliRtcEngine::setClientRole:} 方法切换角色成功时触发此回调
 */
- (void)onUpdateRoleNotifyWithOldRole:(AliRtcClientRole)oldRole newRole:(AliRtcClientRole)newRole;

/**
 * @brief 网络质量变化时发出的消息
 * @param uid 网络质量发生变化的uid
 * @param upQuality  上行网络质量
 * @param downQuality  下行网络质量
 * @note 当网络质量发生变化时触发，uid为@""时代表self的网络质量变化
 */
- (void)onNetworkQualityChanged:(NSString *_Nonnull)uid
               upNetworkQuality:(AliRtcNetworkQuality)upQuality
             downNetworkQuality:(AliRtcNetworkQuality)downQuality;

/**
 * @brief 是否推静态图片
 * @details 通过 {@link AliRtcEngine::setPublishImage:} 设置替代图片，上行网络状态差的情况下触发该回调。
 * @param trackType 视频流类型
 * @param isStaticFrame
 * - YES: 上行网络差，开始推静态图片
 * - NO: 上行网络恢复，推正常采集数据
 */
- (void)onPublishStaticVideoFrame:(AliRtcVideoTrack)trackType
                   isStaticFrame:(BOOL)isStaticFrame;

/**
 * @brief 网络连接断开
 */
- (void)onConnectionLost;

/**
 * @brief 网络连接正在尝试重连中
 */
- (void)onTryToReconnect;

/**
 * @brief 网络连接重连成功
 */
- (void)onConnectionRecovery;

/**
 * @brief 网络连接状态改变的回调
 * @param status 当前状态值, 对应值参考枚举 {@link AliRtcConnectionStatus}
 * @param reason 引起状态变化的具体原因, 对应值参考枚举 {@link AliRtcConnectionStatusChangeReason}
*/
- (void)onConnectionStatusChange:(AliRtcConnectionStatus)status reason:(AliRtcConnectionStatusChangeReason)reason;

/**
 * @brief 被服务器踢出/会议结束频道的消息
 * @param code 原因参考 {@link AliRtcOnByeType}
 */
- (void)onBye:(int)code;

/**
 * @brief 如果engine出现warning，通过这个回调通知app
 * @param warn  Warning type
 * @param message 警告描述
 */
- (void)onOccurWarning:(int)warn message:(NSString *_Nonnull)message;

/**
 * @brief 如果engine出现error，通过这个回调通知app
 * @param error Error类型，参考 {@link AliRtcErrorCode}
 * @param message 错误描述
 */
- (void)onOccurError:(int)error  message:(NSString *_Nonnull)message;

/**
 * @brief 当前设备性能不足
 */
- (void)onPerformanceLow;

/**
 * @brief 当前设备性能恢复
*/
- (void)onPerformanceRecovery;

/**
 * @brief 音频首包发送回调
 * @details 在首个音频数据包发送出去时触发此回调
 * @param timeCost 发送耗时，从入会开始到音频首包发送出去的耗时
 */
- (void)onFirstAudioPacketSentWithTimecost:(int)timeCost;

/**
 * @brief 视频首包发送回调
 * @param videoTrack 发送视频track，参考 {@link AliRtcVideoTrack}
 * @param timeCost 耗时（毫秒）
 * @note 该接口用于视频首包发送的回调
*/
- (void)onFirstVideoPacketSentWithVideoTrack:(AliRtcVideoTrack)videoTrack
                                    timeCost:(int)timeCost;

/**
 * @brief 音频首包接收回调
 * @details 在接收到远端首个音频数据包时触发此回调
 * @param uid 远端用户ID，从App server分配的唯一标识符
 * @param timeCost 接收耗时，从入会开始到音频首包接收到的耗时
 */
- (void)onFirstAudioPacketReceivedWithUid:(NSString *_Nonnull)uid
                                 timeCost:(int)timeCost;

/**
 * @brief 视频首包接收回调
 * @param uid 远端用户ID，从App server分配的唯一标示符
 * @param videoTrack 接收视频track，参考 {@link AliRtcVideoTrack}
 * @param timeCost 耗时（毫秒）
 * @note 该接口用于视频首包接收的回调
*/
- (void)onFirstVideoPacketReceivedWithUid:(NSString *_Nonnull)uid
                          videoTrack:(AliRtcVideoTrack)videoTrack
                            timeCost:(int)timeCost;

/**
 * @brief 已解码远端音频首帧回调
 * @param uid 远端用户ID，从App server分配的唯一标识符
 * @param elapsed 从本地用户加入频道直至该回调触发的延迟, 单位为毫秒
 */
- (void)onFirstRemoteAudioDecodedWithUid:(NSString *_Nonnull)uid elapsed:(int)elapsed;

/**
 * @brief 远端用户的第一帧视频帧显示时触发这个消息
 * @param uid 远端用户ID，从App server分配的唯一标示符
 * @param videoTrack 屏幕流或者相机流，参考 {@link AliRtcVideoTrack}
 * @param width 视频宽度
 * @param height 视频高度
 * @param elapsed 本地用户加入频道直至该回调触发的延迟总耗时（毫秒）
 * @note 该接口用于远端用户的第一帧视频帧显示时的回调
 */
- (void)onFirstRemoteVideoFrameDrawn:(NSString *_Nonnull)uid videoTrack:(AliRtcVideoTrack)videoTrack width:(int)width height:(int)height elapsed:(int)elapsed;

/**
 * @brief 预览开始显示第一帧视频帧时触发这个消息
 * @param width 本地预览视频宽度
 * @param height 本地预览视频高度
 * @param elapsed 从本地用户加入频道直至该回调触发的延迟总耗时（毫秒）
 * @note 该接口用于预览开始显示第一帧视频帧时的回调
 */
- (void)onFirstLocalVideoFrameDrawn:(int)width height:(int)height elapsed:(int)elapsed;

/**
 * @brief 订阅的音频数据回调
 * @details {@link AliRtcEngine::subscribeAudioData:}订阅音频数据成功后，回调对应类型的音频数据
 * @param audioSource 音频数据源类型，详见 {@link AliRtcAudioSource}
 * @param audioSample 音频数据，详见 {@link AliRtcAudioDataSample}
 * @note 请不要在此回调函数中做任何耗时操作，否则可能导致声音异常
 */
- (void)onAudioSampleCallback:(AliRtcAudioSource)audioSource audioSample:(AliRtcAudioDataSample *_Nonnull)audioSample;

/**
 * @brief 混音前每一路远端用户的音频数据回调
 * @details 混音前每一路远端用户的音频数据，{@link AliRtcEngine::subscribeAudioData:}订阅类型为AliRtcAudiosourceSub时触发此回调
 * @param uid 远端用户ID
 * @param audioSample 音频数据，详见 {@link AliRtcAudioDataSample}
 * @note 请不要在此回调函数中做任何耗时操作，否则可能导致声音异常
 */
- (void)onPlaybackAudioFrameBeforeMixing:(NSString *_Nonnull)uid audioSample:(AliRtcAudioDataSample *_Nonnull)audioSample;

/**
 * @brief 订阅的音频音量，语音状态和uid
 * @param array 表示回调用户音量信息数组，包含用户uid,语音状态以及音量，uid为"0"表示本地说话人。
 * @param totalVolume 混音后的总音量，范围[0,255]。在本地用户的回调中，totalVolume;为本地用户混音后的音量；在远端用户的回调中，totalVolume; 为所有说话者混音后的总音量
 */
- (void)onAudioVolumeCallback:(NSArray <AliRtcUserVolumeInfo *> *_Nullable)array totalVolume:(int)totalVolume;

/**
 * @brief 订阅当前正在说话的人
 * @param uid 说话人uid, 为"0"表示本地说话人。其返回的是当前时间段内声音最大的用户ID，而不是瞬时声音最大的用户ID
*/
- (void)onActiveSpeaker:(NSString *_Nonnull)uid;

/**
 * @brief 视频输出数据是否由用户来获取
 * @return
 * - YES: 用户获取
 * - NO（默认）: sdk通过回调向外抛出
 */ 
- (BOOL)onGetIfUserFetchObserverData;

/**
 * @brief 视频数据输出格式
 * @return 期望视频输出格式
 * @note 在注册 {@link AliRtcEngine::registerVideoSampleObserver} 后触发回调，应用可返回期望输出的视频数据格式，默认返回 AliRtcYUV420
 */
- (AliRtcVideoFormat)onGetVideoFormatPreference;
  
 /**
 * @brief 视频数据输出对齐方式
 * @return 期望视频数据对齐方式
 * @note 在注册 {@link AliRtcEngine::registerVideoSampleObserver} 后触发回调，应用可返回期望输出的视频数据格式，默认返回  {@link AliRtcAlignmentDefault} ，不需要对齐
*/
- (AliRtcVideoObserAlignment)onGetVideoAlignment;

/**
 * @brief 视频数据输出位置
 * @return 期望视频输出，参考 {@link AliRtcVideoObserPosition}
 * @note 在注册 {@link AliRtcEngine::registerVideoSampleObserver} 后触发回调，应用可返回期望输出的视频内容，对应数据将分别从onCaptureVideoSample/onPreEncodeVideoSample/onRemoteVideoSample
 * @note 默认返回全部类型数据，即 {@link AliRtcPositionPostCapture} | {@link AliRtcPositionPreRender} | {@link AliRtcPositionPreEncoder}
 */
- (NSInteger)onGetVideoObservedFramePosition;

/**
 * @brief 视频输出数据是否需要镜像
 * @return
 * - YES: 镜像
 * - NO: 不镜像（默认）
 */ 
- (BOOL)onGetObserverDataMirrorApplied;

/**
 * @brief 拉流视频数据是否平滑输出
 * @return
 * - YES: 平滑输出
 * - NO: 直接输出（默认）
 * @note 只在 {@link onGetIfUserFetchObserverData} 为 NO 时有效
 */ 
- (BOOL)onGetSmoothRenderingEnabled;

/**
 * @brief 订阅的本地采集视频数据回调
 * @param videoSource 视频流类型
 * @param videoSample 视频裸数据
 * @return
 * - YES: 需要写回SDK（只对I420和CVPixelBuffer(ios/mac)有效）
 * - NO: 不需要写回SDK
*/
- (BOOL)onCaptureVideoSample:(AliRtcVideoSource)videoSource videoSample:(AliRtcVideoDataSample *_Nonnull)videoSample;

/**
 * @brief 订阅的本地编码前视频数据回调
 * @param videoSource 视频流类型
 * @param videoSample 视频裸数据
 * @return
 * - YES: 需要写回SDK（只对I420和CVPixelBuffer(ios/mac)有效）
 * - NO: 不需要写回SDK
*/
- (BOOL)onPreEncodeVideoSample:(AliRtcVideoSource)videoSource videoSample:(AliRtcVideoDataSample *_Nonnull)videoSample;

/**
 * @brief 订阅的远端视频数据回调
 * @param uid 用户ID
 * @param videoSource 视频流类型
 * @param videoSample 视频裸数据
 * @return
 * - YES: 需要写回SDK（只对I420和CVPixelBuffer(ios/mac)有效）
 * - NO: 不需要写回SDK
*/
- (BOOL)onRemoteVideoSample:(NSString *_Nonnull)uid videoSource:(AliRtcVideoSource)videoSource videoSample:(AliRtcVideoDataSample *_Nonnull)videoSample;


/**
 * @brief 远端用户静音/取消静音回调
 * @param uid 远端用户ID
 * @param isMute 该用户是否静音
 * - YES: 静音
 * - NO: 取消静音
 */
- (void)onUserAudioMuted:(NSString *_Nonnull)uid audioMuted:(BOOL)isMute;

/**
 * @brief 对端用户发送视频黑帧数据发送通知
 * @param uid 执行muteVideo的用户
 * @param isMute
 * - YES: 推流黑帧
 * - NO: 正常推流
 * @note 该接口用于对端用户发送视频黑帧数据时的回调
 */
- (void)onUserVideoMuted:(NSString *_Nonnull)uid videoMuted:(BOOL)isMute;

/**
 * @brief 对端用户关闭相机流采集发送通知
 * @param uid 执行EnableLocalVideo的用户
 * @param isEnable
 * - YES: 打开相机流采集
 * - NO: 关闭相机流采集
 * @note 该接口用于对端用户关闭相机流采集时的回调
 */
- (void)onUserVideoEnabled:(NSString *_Nullable)uid videoEnabled:(BOOL)isEnable;

/**
 * @brief 用户音频被中断通知（一般用户打电话等音频被抢占场景）
 * @param uid 音频被中断的用户ID
 */
- (void)onUserAudioInterruptedBegin:(NSString *_Nonnull)uid;

/**
 * @brief 用户音频中断结束通知（对应onUserAudioInterruptedBegin）
 * @param uid 音频中断结束的用户ID
 */
- (void)onUserAudioInterruptedEnded:(NSString *_Nonnull)uid;

/**
 * @brief 远端用户应用退到后台
 * @param uid 用户
 */
- (void)onUserWillResignActive:(NSString *_Nonnull)uid;

/**
 * @brief 远端用户应用返回前台
 * @param uid 用户
 */
- (void)onUserWillBecomeActive:(NSString *_Nonnull)uid;

/**
 * @brief OpenGL上下文创建回调
 * @param context OpenGL上下文
 * @note 该回调是在SDK内部OpenGL上下文创建的时候触发
 */
- (void)onTextureCreate:(void *_Nullable)context;

/**
 * @brief OpenGL纹理更新回调
 * @param textureId OpenGL纹理ID
 * @param width OpenGL纹理宽
 * @param height OpenGL纹理高
 * @param videoSample 视频帧数据，详见 {@link AliRtcVideoDataSample}
 * @return OpenGL纹理ID
 * @note
 * - 该回调会在每一帧视频数据上传到OpenGL纹理之后触发，当外部注册了OpenGL纹理数据观测器，在该回调中可以对纹理进行处理，并返回处理后的纹理ID
 * - 注意该回调返回值必须为有效的纹理ID，如果不做任何处理必须返回参数textureId
 */
- (int)onTextureUpdate:(int)textureId width:(int)width height:(int)height videoSample:(AliRtcVideoDataSample *_Nonnull)videoSample;

/**
 * @brief OpenGL上下文销毁回调
 * @note 该回调是在SDK内部OpenGL上下文销毁的时候触发
 */
- (void)onTextureDestory;

/**
 * @brief 本地伴奏播放状态回调
 * @details 该回调在伴奏播放状态发生改变时触发，并通知当前的播放状态和错误码
 * @param playState 当前播放状态，详情参考 {@link AliRtcAudioPlayingStateCode}
 * @param errorCode 播放错误码，详情参考 {@link AliRtcAudioPlayingErrorCode}
 */
- (void)onAudioPlayingStateChanged:(AliRtcAudioPlayingStateCode)playState errorCode:(AliRtcAudioPlayingErrorCode)errorCode;

/**
 * @brief 远端用户伴奏播放开始回调
 * @param uid 远端用户ID，从App server分配的唯一标识符
 */
- (void)onRemoteAudioAccompanyStarted:(NSString *_Nonnull)uid;

/**
 * @brief 远端用户伴奏播放结束回调
 * @param uid 远端用户ID，从App server分配的唯一标识符
 */
- (void)onRemoteAudioAccompanyFinished:(NSString *_Nonnull)uid;

/**
 * @brief 本地音效播放结束回调
 * @param soundId 用户给该音效文件分配的唯一ID
 */
- (void)onAudioEffectFinished:(int)soundId;

/**
 * @brief 用户鉴权信息即将过期通知，收到后30秒鉴权过期
 * @note 该回调在鉴权信息30秒前触发，收到该回调后应该及时更新鉴权信息，参考 {@link AliRtcEngine::refreshAuthInfo:}
 */
- (void)onAuthInfoWillExpire;

/**
 * @brief 用户调用需要鉴权的接口，服务端返回信息过期
 * @note 该回调触发代表鉴权信息已过期，想要继续在会中，需要重新入会，参考 {@link AliRtcEngine::joinChannel:name:onResultWithUserId:}
 */
- (void)onAuthInfoExpired;

/**
 * @brief 网络质量探测回调
 * @param networkQuality 网络质量 {@link AliRtcNetworkQuality}
 * @note 当调用 {@link AliRtcEngine::startLastmileDetect} 后会触发该回调
 */
- (void)onLastmileDetectResultWithQuality:(AliRtcNetworkQuality)networkQuality;

/**
 * @brief 视频分辨率变更
 * @param uid   用户ID。从App server分配的唯一标示符
 * @param videoTrack 屏幕流或者相机流
 * @param width 视频宽度
 * @param height 视频高度
*/
- (void)onVideoResolutionChanged:(NSString *_Nonnull)uid videoTrack:(AliRtcVideoTrack)videoTrack width:(int)width height:(int)height;

/**
 * @brief 文件录制回调事件
 * @param event 录制事件，0：录制开始，1：录制结束，2：打开文件失败，3：写文件失败
 * @param filePath 录制文件路径
 * @note 该接口用于文件录制时的事件回调
 */
- (void)onMediaRecordEvent:(int)event filePath:(NSString *_Nullable)filePath;

/**
 * @brief 实时数据回调(2s触发一次)
 * @param stats 统计信息
 */
- (void)onRtcStats:(AliRtcStats)stats;

/**
 * @brief 本地视频统计信息(2s触发一次)
 * @param localVideoStats 本地视频统计信息
 * @note SDK每两秒触发一次此统计信息回调
 */
- (void)onRtcLocalVideoStats:(AliRtcLocalVideoStats *_Nonnull)localVideoStats;

/**
 * @brief 远端视频统计信息(2s触发一次)
 * @param remoteVideoStats 远端视频统计信息
 */
- (void)onRtcRemoteVideoStats:(AliRtcRemoteVideoStats *_Nonnull)remoteVideoStats;

/**
 * @brief 本地音频统计信息(2s触发一次)
 * @param localAudioStats 本地视频统计信息
 * @note SDK每两秒触发一次此统计信息回调
 */
- (void)onRtcLocalAudioStats:(AliRtcLocalAudioStats *_Nonnull)localAudioStats;

/**
 * @brief 远端音频统计信息(2s触发一次)
 * @param remoteAudioStats 远端音频统计信息
 */
- (void)onRtcRemoteAudioStats:(AliRtcRemoteAudioStats *_Nonnull)remoteAudioStats;

/**
 * @brief 收到媒体扩展信息回调
 * @param uid 发送用户ID
 * @param data 媒体扩展信息
 * @note 当一端通过 {@link AliRtcEngine::sendMediaExtensionMsg:repeatCount:} 发送信息后，其他端通过该回调接收数据
 */
- (void)onMediaExtensionMsgReceived:(NSString *_Nonnull)uid message:(NSData *_Nonnull)data;

/**
 * @brief 下行消息通道(接收消息) 
 * @param messageInfo 消息内容 
 * @note 该接口接收到下行消息后，使用 {@link AliRtcEngine::sendDownlinkMessageResponse:} 发送反馈消息
 * @note 已废弃使用
 * @deprecated
 */
- (void)onDownlinkMessageNotify:(AliRtcMessage *_Nonnull)messageInfo;

/** 
 * @brief 上行消息返回结果(接收消息)
 * @param resultInfo 发送结果
 * @note 使用 {@link AliRtcEngine::sendUplinkMessage:} 发送消息后，会触发该接口接收上行消息反馈
 * @note 已废弃使用
 * @deprecated
 */
- (void)onUplinkMessageResponse:(AliRtcMessageResponse *_Nonnull)resultInfo;

/**
 * @brief 音频路由发生变化回调（仅适用于Android、iOS平台）
 * @details 所谓“音频路由”，是指声音是从手机的扬声器还是从听筒中播放出来，音频路由变化也就是声音的播放位置发生了变化
 * - 当音频路由为听筒时，声音比较小，只有将耳朵凑近才能听清楚，隐私性较好，适合用于接听电话。
 * - 当音频路由为扬声器时，声音比较大，不用将手机贴脸也能听清，因此可以实现“免提”的功能。
 *
 * @param routing 当前使用的音频路由，详情参考 {@link AliRtcAudioRouteType}
 */
- (void)onAudioRouteChanged:(AliRtcAudioRouteType)routing;

/**
 * @brief 截图回调
 * @param uid 远端用户uid
 * @param videoTrack 截图视频track，参考 {@link AliRtcVideoTrack}
 * @param image 截图数据
 * @param success 截图结果
 * @note 成功时image返回截图数据，失败返回nil
 */
- (void)onSnapshotComplete:(NSString*_Nullable)uid videoTrack:(AliRtcVideoTrack)videoTrack image:(UIImage* _Nullable)image success:(BOOL)success;

/**
 * @brief 旁路推流状态改变回调
 * @param streamURL 流地址
 * @param state 推流状态, 参考 {@link AliRtcLiveTranscodingState}
 * @param errCode 错误码, 参考 {@link AliRtcTrascodingLiveStreamErrorCode}
 * @note 该接口用于旁路推流状态改变的回调
 */
- (void)onPublishLiveStreamStateChanged:(NSString *_Nonnull)streamURL state:(AliRtcLiveTranscodingState)state errCode:(AliRtcTrascodingLiveStreamErrorCode)errCode;

/**
 * @brief 旁路任务状态改变回调
 * @param streamURL  流地址
 * @param state 任务状态, 参考 {@link AliRtcTrascodingLiveTaskStatus}
 * @note 该接口用于旁路任务状态改变的回调
 */
- (void)onPublishTaskStateChanged:(NSString *_Nonnull)streamURL state:(AliRtcTrascodingLiveTaskStatus)state;

/**
 * @brief 跨频道转推状态变化通知
 * @param state 当前连麦状态，参考 {@link AliRtcChannelRelayEvent}
 * @param code 当前错误码，参考 {@link AliRtcChannelRelayErrorCode}
 * @param message 状态描述信息
 */
- (void)onChannelRelayStateChanged:(int)state code:(int)code message:(NSString *_Nullable)message;

/**
 * @brief 跨频道转推事件通知
 * @param event 状态码，参考 {@link AliRtcChannelRelayEvent}
 */
- (void)onChannelRelayEvent:(int)event;

/**
 * @brief 用户remote video change通知
 * @param uid 需要被通知的用户
 * @param trackType 变化视频track
 * @param state 视频状态的类型
 * @param reason 触发状态变化的原因
 */
- (void)onRemoteVideoChanged:(NSString *_Nonnull)uid trackType:(AliRtcVideoTrack)trackType state:(AliRtcVideoState)state reason:(AliRtcVideoReason)reason;

/**
 * @brief Qos参数发生变化通知
 * @param trackType 变化视频track
 * @param parameter qos参数结构体
 */
- (void)onRequestVideoExternalEncoderParameter:(AliRtcVideoTrack)trackType parameter:(AliRtcVideoExternalEncoderParameter *_Nullable)parameter;

/**
 * @brief Qos请求帧类型发生变化通知
 * @param trackType 变化视频track
 * @param frameType 请求参考帧类型
 */
- (void)onRequestVideoExternalEncoderFrame:(AliRtcVideoTrack)trackType frameType:(AliRtcVideoEncodedFrameType)frameType;


@end
/** @} AliRtcEngineDelegate_ios AliRtcEngineDelegate */

#pragma mark - 接口主类
/**
 * @defgroup AliRtc_ios AliRtcEngine
 * AliRTC功能的主要接口类
 * @{
 */
@interface AliRtcEngine : NSObject <AliRtcEngineDelegate>

#pragma mark - "Engine的生命周期，工作参数以及频道操作"
/**
 * @name Engine的生命周期，工作参数以及频道操作
 * @{
 */

/**
 * @brief 获取一个AliRtcEngine实例
 * @param delegate 用于接收AliRTC回调的代理。
 * @param extras 用于接收来自客户灰度下发的参数，通过JSON配置SDK的特别功能，可以是空字符串。详情请参见官网[有关extras功能说明](https://help.aliyun.com/document_detail/200048.htm?spm=a2c4g.11186623.2.111.4b89466bJosuro#task-2025192)。
 * @details 该方法为同步调用，以单例的形式提供对象创建。
 * @note 注意 同一时间只会存在一个主实例。
 * @note 创建子实例，请参考使用 {@link createChannelWithDelegate:extras:}
 */
+ (instancetype _Nonnull )sharedInstance:(id<AliRtcEngineDelegate>_Nullable)delegate extras:(NSString *_Nullable)extras;

/**
 * @brief 销毁AliRtcEngine实例
 * @details 调用该方法将会释放所有内部使用的资源,当完成音视频通信之后都建议调用该方法释放实例.调用该方法后，你将不能再使用 {@link AliRtcEngine} 的其他方法和任何回调，如需要再次使用需要重新调用 {@link AliRtcEngine::sharedInstance:extras:} 方法创建一个新的实例。
 * @note 该接口为同步接口，需要等待内部资源释放之后才能执行其他方法，为避免主线程阻塞，建议开发者放在子线程调用该方法，但需要注意的是如需在销毁后再次创建 {@link AliRtcEngine} 实例，请开发者务必保证 destroy 方法执行结束后再创建实例。
 * @note 为避免死锁，不建议在任何SDK的回调中调用本方法
 */
+ (void)destroy;

/**
 * @brief 查询SDK当前版本号
 * @return 当前的SDK版本号，格式为字符串，例："2.5.0.x"
 * @note 在任何时刻都可以调用
 */
+ (NSString *_Nonnull)getSdkVersion;

/**
 * @brief 设置SDK日志文件保存路径
 * @param logDirPath 日志文件保存目录的绝对路径，该参数是一个目录路径，而不是文件的路径。
 * @return 
 * - 0，成功
 * - 非0，失败。其中有两种错误码，释义如下：
 *   - {@link AliRtcErrLogRootPathError} : 路径已存在或因权限问题不可访问。
 *   - {@link AliRtcErrLogAlreadyInit} : log对象已经初始化过。
 * 
 * @note 调用此接口，请在调用其他所有SDK接口前调用本接口，避免日志出现丢失。同时，App必须保证指定的目录已存在并且可以写入。
 * @note 如果，目标路径不可写入或创建日志文件失败，则会使用默认日志路径。本次设置将无效。
 */
+ (int)setLogDirPath:(NSString *_Nullable)logDirPath;

/**
 * @brief 上传日志文件
 * @details 用户主动调用此接口，将当前日志目录下的所有未上传的日志文件进行压缩、打包、上传。
 * @note 上传过程中，如果有进入频道等操作，会自动停止上传行为，避免影响入会体验。
 */
+ (void)uploadLog;

/**
 * @brief 根据错误码，获取错误码描述
 * @param errCode 错误码，详见 {@link AliRtcErrorCode}
 * @return 错误码描述字符串
 * @note 在任何时刻都可以调用
 */
+ (NSString *_Nullable)getErrorDescription:(NSInteger)errCode;

/**
 * @brief 是否分发回调到主线程队列
 * @details 设置是否分发回调到主线程队列，当enabled 为 NO 时，将分发至设置的回调队列，见 {@link setDelegateQueue:}，如果未设置，则使用SDK内部默认子线程队列
 * @param enabled
 * - YES: 回调分发至主线程队列
 * - NO: 回调分发至 {@link setDelegateQueue:} 设置的队列
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 回调默认分发至主线程队列(Default:YES)
 */
- (int)enableDelegateMainQueue:(BOOL)enabled;

/**
 * @brief 指定回调线程队列
 * @param queue 回调queue
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note enableDelegateMainQueue为YES时，此接口设置无效，回调线程为主线程;
 * @note enableDelegateMainQueue为NO时，可通过此接口指定回调线程，若不设置，则使用SDK的默认子线程
 */
- (int)setDelegateQueue:(NSOperationQueue *_Nullable)queue;

/**
 * @brief 设置音频模式还是音视频模式
 * @param audioOnly
 * - YES: 只有音频推流和拉流（纯音频）
 * - NO: 音视频都支持
 * @return 
 * - 0: 成功
 * - 非0: 失败
 * @note 只可以在 {@link joinChannel:name:onResultWithUserId:} 之前设置
 */
- (int)setAudioOnlyMode:(BOOL)audioOnly;

/**
 * @brief 加入频道
 * @param authInfo    认证信息，从App Server获取。
 * @param userName    任意用于显示的用户名称。不是用户ID
 * @param onResult    当joinChannel执行结束后调用这个回调
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 已废弃
 */
- (int)joinChannel:(AliRtcAuthInfo *_Nonnull)authInfo name:(NSString *_Nullable)userName onResult:(void(^_Nullable)(NSInteger errCode, NSString * _Nonnull channel, NSInteger elapsed))onResult;

/**
 * @brief 加入频道
 * @details 该方法让用户加入频道，一个频道内可以加入多个用户进行互相通话。
 * @details 一般在调用该方法前会根据场景先选择频道模式，通过调用 {@link setChannelProfile:} 实现，默认频道模式为通信模式 {@link AliRtcChannelProfile::AliRtcCommunication}
 * ``` objc
 * // 设置频道为互动模式
 * [self.engine setChannelProfile:AliRtcInteractivelive];
 * // 设置角色为主播角色
 * [self.engine setClientRole:AliRtcClientRoleInteractive];
 * // 加入频道 onResult和onJoinChannelResult均会回调
 * [self.engine joinChannel:authInfo name:name onResult:^(NSInteger errCode, NSString * channel, NSString * userId, NSInteger elapsed){
 *  if (errCode == 0) {
 *      //加入频道成功
 *  } else {
 *      //加入频道失败
 *  }
 * }];
 * ```
 * @param authInfo    认证信息，从App Server获取。
 * @param userName    任意用于显示的用户名称。不是用户ID
 * @param onResult    当joinChannel执行结束后调用这个回调
 * @return
 * - 0: 成功
 * - 非0: 失败
 *   - 失败原因错误码见回调函数：{@link  onJoinChannelResult:channel:userId:elapsed:}
 *
 * @note
 *    - 该接口异步接口。是否成功入会，通过 {@link onJoinChannelResult:channel:userId:elapsed:} 判断，参数onResult也会回调
 *    - 正常情况一个Appid对应一个App，只有同一个AppId的应用可进行互相童话,不同AppId和channelID不同都不能互通
 *    - 当入会成功后，会触发远端用户收到 {@link onRemoteUserOnLineNotify:elapsed:} 回调
 *    - 如果已在会中想重新入会，需要先调用 {@link leaveChannel} 离会，且确保 {@link onLeaveChannelResult:stats:} 回调收到后，再次调用进行入会
 *    - 如果用户是观众角色，已在会中，可以通过  {@link switchChannel:}  进行快速切换其他房间
 *    - 用户加入频道后，默认订阅频道内所有其他用户的音视频流，默认推送音视频流到远端，因此将会产生计费，如果想要取消默认订阅可以 {@link joinChannel:name:onResultWithUserId:} 前调用 {@link setDefaultSubscribeAllRemoteAudioStreams:} 和 {@link  setDefaultSubscribeAllRemoteVideoStreams:}
 *    - 不同频道中的主播可以通过调用 {@link startChannelRelay:} 实现跨频道通信，可以方便的实现两个不同直播间主播的互通联动
 */
- (int)joinChannel:(AliRtcAuthInfo *_Nonnull)authInfo name:(NSString *_Nullable)userName onResultWithUserId:(void(^_Nullable)(NSInteger errCode, NSString * _Nonnull channel, NSString * _Nonnull userId, NSInteger elapsed))onResult;

/**
 * @brief 设置自定义参数
 * @param param   自定义参数
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setParameter:(NSString * _Nonnull)param;


/**
 * @brief  离开频道
 * @details 调用该方法代表离开频道，即挂断或者停止通话。
 * @details 该方法为异步方法，调用后收到 {@link onLeaveChannelResult:stats:} 代表退出频道完成，同时会触发远端用户收到 {@link onRemoteUserOffLineNotify:offlineReason:}   回调。
 * @details 如果未加入频道入会，{@link leaveChannel} 不会有任何影响。加入频道后，必须要调用该方法离开频道，否则无法加入其他频道。
 * @return
 * - 0: 成功
 * - 非0: 失败
 *   - 失败原因错误码见回调函数：{@link  onLeaveChannelResult:stats:}
 *
 * @note
 *  - 如果调用了 {@link leaveChannel} 后立刻调用 {@link AliRtcEngine::destroy} 方法，SDK将会无法触发 {@link  onLeaveChannelResult:stats:} 回调
 *
 */
- (int)leaveChannel;

/**
 * @brief 切换频道
 * @details 当我们已经在一个频道中想要加入另外一个频道时，通常我们需要离会之后在收到离会回调之后再加入到另外一个频道中，调用方法可以实现快速切换频道。
 * @details 成功调用该方切换频道后，本地会先收到离开原频道的回调 {@link onLeaveChannelResult:stats:} ，再收到成功加入新频道的回调 {@link onJoinChannelResult:channel:userId:elapsed:}.
 * @param authInfo  认证信息，从App Server获取。
 * @return
 * - 0: 成功
 * - 非0: 失败
 *   - {@link AliRtcErrInner}：SDK未初始化或已销毁
 *   - {@link AliRtcErrSdkInvalidState}：当前未加入任何频道或者频道模式和角色不匹配，请确认频道为互动模式，用户角色为观众
 *   - {@link AliRtcErrInvalidArguments}：鉴权信息非法，请确认是否使用同一个authinfo多次加入同一个频道
 *
 * @note 该方法需要在加入一个频道后才可以调用
 * @note 该方法仅在互动模式AliRtcInteractiveLive和观看角色AliRtcClientRoleLive下调用有效
 */
- (int)switchChannel:(AliRtcAuthInfo *_Nonnull)authInfo;

/**
 * @brief 设置频道模式
 * @details 根据业务需求可以配置不同的频道模式，AliRTC会根据不用的频道模式模式采用不用的策略，目前主要提供通信模式(默认)、互动模式、低延迟互动直播模式
 *
 * 【通信模式 AliRtcCommunication】
 *  - 该适用于音视频通话场景，所有加入频道的人都可以推/拉音视频流
 *  - 该模式典型的应用场景：1v1语音聊天、1v1视频聊天、远程问诊、远程面试等
 *
 * 【互动模式 AliRtcInteractivelive】
 *  - 该模式适用于互动场景，在该模式下有主播和观众两种角色，主播、观众角色可以进行切换，可以通过 {@link setClientRole:} 进行设置。
 *    - 主播角色：可以推流、拉流
 *    - 观众角色：只可以拉流
 *  - 该模式典型的应用场景：语聊房、在线教育大班课等
 *
 * 【低延迟互动直播模式 AliRtcInteractiveWithLowLatencyLive】
 *  - 该模式适用于大型直播场景，与互动模式的差别是观众端使用 {@link startLiveStreamingWithAuthInfo:onResult:} 进行拉流
 *  - 该模式典型应用场景：千人大方会、在线直播培训等
 *
 * @param profile 频道模式类型, 详细请参考 {@link AliRtcChannelProfile}
 * @return
 * - 0: 成功
 * - 非0: 失败
 *   - AliRtcErrInner(-1) : SDK未初始化或已销毁
 *
 * @note
 *  - 相同频道内的用户必须使用同一种频道模式
 *  - 该方法只在入会之前调用有效，会议中不可以重新设置，{@link leaveChannel} 后可以重新设置
 */
- (int)setChannelProfile:(AliRtcChannelProfile)profile;

/**
 * @brief 设置互动模式下的用户角色
 * @details 该方法在 ChannelProfile 设置为 {@link AliRtcInteractivelive} 时有效
 * @details 该方法为异步方法，可以在入会前调用，也可以在入会后调用进行用户角色切换，默认角色为：观众角色
 * - 加入频道前，调用该方法，不会触发任何回调，在入会成功后角色自动生效：
 *   - 若设置的角色为主播，入会成功后将会触发一次开始推流动作，远端用户将会触发 {@link onRemoteUserOnLineNotify:elapsed:} 回调
 *     - 注意：是否真正触发推流，与是否设置过允许推流相关，详见：{@link publishLocalVideoStream:} 和 {@link publishLocalAudioStream:}
 *   - 若设置的角色为观众，本地不会推流，远端用户也不会收到相关回调
 * - 加入频道后，调用该方法，当前调用用户将会收到 {@link onUpdateRoleNotifyWithOldRole:newRole:} 回调：
 *   - 从观众变为主播时，将会触发一次开始推流动作，远端用户将会触发 {@link onRemoteUserOnLineNotify:elapsed:} 回调
 *     - 注意：是否真正触发推流，与是否设置过允许推流相关，详见：{@link publishLocalVideoStream:} 和 {@link publishLocalAudioStream:}
 *   - 从主播变为观众时，将会触发本地停止推流，同时远端用户将会触发 {@link onRemoteUserOffLineNotify:offlineReason:} 回调
 *
 * @param role 用户角色类型 {@link AliRtcClientRole}
 * @return
 * - 0: 成功
 * - <0: 失败
 *   - AliRtcErrInner(-1) : SDK未初始化或已销毁
 *
 * @note 只在频道模式为 {@link AliRtcInteractivelive} 下调用有意义，入会前/会议中均可设置
 * @note 加入频道后，调用该方法，需要等 {@link onUpdateRoleNotifyWithOldRole:newRole:} 回调后，才能再次调用有效
 */
- (int)setClientRole:(AliRtcClientRole)role;

/**
 * @brief 获取互动模式下当前用户角色
 * @return AliRtcClientRole 当前用户角色类型
 * @note 只在频道模式为 {@link AliRtcInteractivelive} 下调用有意义
 */
- (AliRtcClientRole)getCurrentClientRole;

/**
 * @brief 刷新鉴权信息
 * @details 该方法用于更新鉴权信息 {@link AliRtcAuthInfo} ，主要为了防止鉴权过期，导致推流失败，当我们收到 {@link onAuthInfoWillExpire} 回调时，应用应当更新鉴权信息
 * @param authInfo 鉴权信息
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)refreshAuthInfo:(AliRtcAuthInfo *_Nonnull)authInfo;

/** @} */

#pragma mark - "设置和操作本地的媒体"
/**
 * @name 设置和操作本地的媒体
 * @{
 */

/**
 * @brief 设置本地预览显示视图
 * @param viewConfig 本地视频显示属性, 详细见 {@link AliVideoCanvas}
 * @param track  只支持 {@link AliRtcVideoTrackCamera} 和 {@link AliRtcVideoTrackScreen}
 * @return
 * - 0 : 成功
 * - < 0 : 失败
 * @note 支持joinChannel之前和之后切换窗口。如果canvas或者 {@link AliVideoCanvas::view} 为nil，则停止显示。
 *       如果需要重新设置 {@link AliVideoCanvas::renderMode}，请保持canvas中其他属性不变，仅修改
 *       {@link AliVideoCanvas::renderMode}。
 *       如果需要重新设置 {@link AliVideoCanvas::mirrorMode}，请保持canvas中其他属性不变，仅修改
 *       {@link AliVideoCanvas::mirrorMode}。
 */
- (int)setLocalViewConfig:(AliVideoCanvas *_Nullable)viewConfig forTrack:(AliRtcVideoTrack)track;

/**
 * @brief 开启本地视频预览
 * @return
 * - 0 : 成功
 * - <0 : 失败
 * @note 如果没有调用 {@link setLocalViewConfig:forTrack:} 设置显示的view，则无法预览。
 * 可以在 {@link joinChannel:name:onResultWithUserId:} 之前就开启预览会自动打开摄像头。
 */
- (int)startPreview;

/**
 * @brief 关闭本地视频预览
 * @return
 * - 0 : 成功
 * - < 0 : 失败
 * @note {@link leaveChannel} 会自动停止本地预览；如果没有在推相机流，则会自动关闭摄像头。
 */
- (int)stopPreview;

/**
 * @brief 设置camera采集偏好
 * @param config 偏好设置
 *      - preference: {@link AliRtcCaptureOutputPreference::AliRtcCaptureOutputPreferencePreview} 高清预览，采集优先保证视频预览质量
 *                    {@link AliRtcCaptureOutputPreference::AliRtcCaptureOutputPreferencePerformance} 采集选择最接近推流的分辨率，优先保证设备性能
 *                    {@link AliRtcCaptureOutputPreference::AliRtcCaptureOutputPreferenceAuto} 自动调整采集分辨率
 *      - cameraDirection: 设置采集方向，前置摄像头或后置摄像头
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 必须在打开摄像头之前设置，如 {@link AliRtcEngine::startPreview}，{@link AliRtcEngine::joinChannel:name:onResult:} / {@link AliRtcEngine::joinChannel:name:onResultWithUserId:}之前设置
 */
- (int)setCameraCapturerConfiguration:(AliRtcCameraCapturerConfiguration* _Nonnull )config;

/**
 * @brief 禁用或启用本地视频采集
 * @param enabled
 * - YES : 启用本地视频采集
 * - NO : 禁用本地视频采集
 * @return
 * - 0 : 成功
 * - < 0 : 失败
 * @note 默认为开启状态, 通过监听 {@link #onUserVideoEnabled:videoEnabled: } 获取用法是否禁用或启用本地视频采集状态。
 */
- (int)enableLocalVideo:(BOOL)enabled;

/**
 * @brief 是否将停止本地视频数据发送
 * @param mute  YES表示视频数据发送黑帧；NO表示恢复正常
 * @param track  只支持 {@link AliRtcVideoTrackCamera}
 * @return 
 * - 0: 表示Success
 * - 非0: 表示Failure
 * @note 发送黑色的视频帧。本地预览也呈现黑色。采集，编码，发送模块仍然工作，
 *       只是视频内容是黑色帧
*/
- (int)muteLocalCamera:(BOOL)mute forTrack:(AliRtcVideoTrack)track;

/**
 * @brief 是否推送本地视频流
 * @param enabled 是否开启/关闭本地视频流推流
 * - YES: 开启视频流推送
 * - NO: 关闭视频流推送
 * @return
 * - 0: 设置成功
 * - <0: 设置失败
 *   - AliRtcErrInner: SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - SDK默认设置为推送视频流，加入频道前调用此接口设置推送视频流，将在加入频道成功时生效，加入频道成功后可以随时调用此接口开启/关闭视频流推送
 * - 若当前频道模式为 {@link AliRtcInteractivelive} 模式，只有用户角色为 {@link AliRtcClientRoleInteractive} 时SDK才会允许允许推送视频流，因此该模式下调用此接口设置推流时，需要同时配合调用接口 {@link AliRtcEngine::setClientRole:} 更改角色
 * - 本地视频流内容默认为摄像头采集视频，如需自定义输入视频推送内容，可参考接口 {@link AliRtcEngine::setExternalVideoSource:useTexture:sourceType:renderMode:} 使用外部视频输入替换摄像头采集
 * - 本地视频推流结果发生变化时，SDK会触发 {@link AliRtcEngineDelegate::onVideoPublishStateChanged:newState:elapseSinceLastState:channel:} 回调通知视频推流最新状态
*/
- (int)publishLocalVideoStream:(BOOL)enabled;

/**
 * @brief 设置相机流视频编码属性
 * @details 该方法用于设置相机流视频编码属性对应的视频参数，如分辨率、帧率、码率、视频方向等 所有设置的参数都有相应的范围限制，如果设置的参数不在有效范围内，SDK会自动调节
 * @param config 预定义的编码属性，详见 {@link AliRtcVideoEncoderConfiguration}
 * @note
 * - 该方法在入会前和入会后都可以调用，如果每次入会只需要设置一次相机流视频编码属性，建议在入会前调用
*/
- (void)setVideoEncoderConfiguration:(AliRtcVideoEncoderConfiguration* _Nonnull)config;

/**
 * @brief 设置屏幕流视频编码属性
 * @details 该方法用于设置屏幕流视频编码属性对应的视频参数，如分辨率、帧率、码率、视频方向等 所有设置的参数都有相应的范围限制，如果设置的参数不在有效范围内，SDK会自动调节
 * @param config 预定义的屏幕共享编码属性，详见 {@link AliRtcScreenShareEncoderConfiguration}
 * @note
 * - 该方法在入会前和入会后都可以调用，如果每次入会只需要设置一次屏幕流视频编码属性，建议在入会前调用
*/
- (void)setScreenShareEncoderConfiguration:(AliRtcScreenShareEncoderConfiguration* _Nonnull)config;

/**
 * @brief 停止/恢复本地音频数据发送
 * @param mute
 * - YES: 本地音频发送空帧
 * - NO: 恢复正常音频数据发送
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note mute是指音频流发送静音帧，采集和编码模块仍然在工作。
 */
- (int)muteLocalMic:(BOOL)mute __attribute__((deprecated("已经废弃，建议使用muteLocalMic:mode:接口")));

/**
 * @brief 停止/恢复本地音频数据发送
 * @param mute  YES表示静音本地音频，发送静音帧; NO表示取消静音;
 * @param mode  静音模式，静音模式分三种，详见 {@link AliRtcMuteLocalAudioMode}，默认模式为静音本地麦克风采集音频和所有外部输入音频;
 * @return 
 * - 0: 成功
 * - 非0: 失败
 * @note 静音是指音频流发送静音帧,采集和编码模块仍然在工作
 */
- (int)muteLocalMic:(BOOL)mute mode:(AliRtcMuteLocalAudioMode)mode;

/**
 * @brief 是否推送音频流
 * @param enabled 是否开启/关闭本地音频流推流
 * - YES: 开启音频流推送
 * - NO: 关闭音频流推送
 * @return
 * - 0: 设置成功
 * - <0: 设置失败
 *  - AliRtcErrInner: SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - SDK默认设置推送音频流，加入频道前调用此接口设置推送音频流，将在加入频道成功时生效，加入频道成功后可以随时调用此接口开启/关闭音频流推送
 * - 若当前频道模式为 {@link AliRtcInteractivelive} 模式，只有用户角色为 {@link AliRtcClientRoleInteractive} 时SDK才会允许允许推送视频流，因此该模式下调用此接口设置推流时，需要同时配合调用接口 {@link AliRtcEngine::setClientRole:} 更改角色
 * - 本地音频流内容默认为麦克风采集音频，如需自定义输入音频推送内容，可参考接口 {@link AliRtcEngine::setExternalAudioSource:withSampleRate:channelsPerFrame:} 使用外部音频输入替换麦克风采集
 * - 本地音频推流结果发生变化时，SDK会触发 {@link AliRtcEngineDelegate:onAudioPublishStateChanged:newState:elapseSinceLastState:channel:} 回调通知音频推流最新状态
 */
- (int)publishLocalAudioStream:(BOOL)enabled;

/** @} */

#pragma mark - "操作来自远端的媒体"
/**
 * @name 操作来自远端的媒体
 * @{
 */

/**
 * @brief 设置远端视频显示视图
 * @param canvas 本地视频显示属性, 详细见 {@link AliVideoCanvas}
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param track  只支持 {@link AliRtcVideoTrack#AliRtcVideoTrackCamera} 和 {@link AliRtcVideoTrack#AliRtcVideoTrackScreen}
 * @return
 * - 0 ：成功
 * - < 0 ：失败
 * @note 支持joinChannel之前和之后切换窗口。如果canvas或者 {@link AliVideoCanvas#view} 为nil，则停止显示。
 *       如果需要重新设置 {@link AliVideoCanvas#renderMode}，请保持canvas中其他属性不变，仅修改
 *       {@link AliVideoCanvas#renderMode}。
 *       如果需要重新设置 {@link AliVideoCanvas#mirrorMode}，请保持canvas中其他属性不变，仅修改
 *       {@link AliVideoCanvas#mirrorMode}。
 */
- (int)setRemoteViewConfig:(AliVideoCanvas *_Nullable)canvas uid:(NSString *_Nonnull)uid forTrack:(AliRtcVideoTrack)track;

/**
 * @brief 调节本地播放的指定远端用户音量
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param volume 播放音量，取值范围[0,100] 0：静音；100：原始音量
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setRemoteAudioVolume:(NSString *_Nonnull)uid volume:(NSInteger)volume;

/**
 * @brief 停止/恢复远端指定用户的音频流的播放
 * @param uid  用户ID , 从App server分配的唯一标示符
 * @param mute YES表示停止播放; NO表示恢复播放
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 拉流和解码不受影响, 支持joinChannel之前和之后设置
 */
- (int)muteRemoteAudioPlaying:(NSString *_Nonnull)uid mute:(BOOL)mute;

/**
 * @brief 停止/恢复远端的所有音频流的播放
 * @param mute YES表示停止播放；NO表示恢复播放
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 拉流和解码不受影响, 支持joinChannel之前和之后设置
 */
- (int)muteAllRemoteAudioPlaying:(BOOL)mute;

/**
 * @brief mute/unmute远端的所有视频track的渲染
 * @param mute    YES表示停止渲染；NO表示恢复渲染
 * @return 0表示Success 非0表示Failure
 * @note 拉流和解码不受影响。支持joinChannel之前和之后设置
 */
- (int)muteAllRemoteVideoRendering:(BOOL)mute;

/** @} */

#pragma mark - "用户管理"
/**
 * @name 用户管理
 * @{
 */

/**
 * @brief 查询是否设置推送视频流
 * @return
 * - YES: 已设置推送
 * - NO: 未设置推送
 * @note
 *  - SDK默认设置推送视频流，如果需要取消推送视频流，可以通过 {@link  AliRtcEngine::publishLocalVideoStream:} 方法设置为不推送
*/
- (BOOL)isLocalVideoStreamPublished;

/**
 * @brief 查询是否设置推送音频流
 * @return
 * - YES: 已设置推送
 * - NO: 未设置推送
 * @note
 *  - SDK默认设置推送音频流，如果需要取消推送音频流，可以通过 {@link AliRtcEngine::publishLocalAudioStream:} 方法设置为不推送
*/
- (BOOL)isLocalAudioStreamPublished;

/**
 * @brief 是否推送次要视频流
 * @param enabled 是否开启/关闭次要视频流推送
 * - YES: 开启次要视频流推送
 * - NO: 关闭次要视频流推送
 * @return
 * - 0: 设置成功
 * - <0: 设置失败
 *  - AliRtcErrInner: SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 *  - 次要视频流为低分辨率的本地视频流，视频内容与本地视频流相同，分辨率默认为160 x 120 (或 160 x 90)，宽高比与本地视频流一致。开启次要视频流推送后，接收方可以通过 {@link AliRtcEngine::setRemoteVideoStreamType:type:} 方法选择订阅高分辨率或低分辨率视频流
 *  - 次要视频流只在推送视频流的前提下才会推送，设置推送次要视频流前，请确认已通过 {@link AliRtcEngine::publishLocalVideoStream:} 方法开启视频流推送
 *  - SDK默认设置不推送次要视频流，加入频道前调用此接口设置推送次要视频流，将在加入频道成功时生效，加入频道成功后可以随时调用此接口开启/关闭次要视频流推送
 *  - 次要视频推流结果发生变化时，SDK会触发 {@link AliRtcEngineDelegate::onDualStreamPublishStateChanged:newState:elapseSinceLastState:channel:} 回调通知次要视流最新状态
*/
- (int)publishLocalDualStream:(BOOL)enabled;

/**
 * @brief 查询是否设置推送次要流
 * @return
 * - YES: 已设置推送
 * - NO: 未设置推送
 * @note
 *  - SDK默认设置不推送次要视频流，如果需要推送次要视频流，可以通过接口 {@link AliRtcEngine::publishLocalDualStream:} 方法设置为推送
*/
- (BOOL)isDualStreamPublished;

/**
 * @brief 启动屏幕分享
 * @return 0: 成功；其他: 失败
 */
- (int)startScreenShare;

/**
 * @brief 停止屏幕分享
 * @return 0: 成功；其他: 失败
 */
- (int)stopScreenShare;

/**
 * @brief 查询是否设置推送屏幕分享
 * @return
 * - YES: 已设置推送
 * - NO: 未设置推送
 * @note
 *  - SDK默认设置不推送屏幕分享，如果需要推送屏幕共享，可以通过 {@link AliRtcEngine::startScreenShare} 方法开启屏幕共享推送
*/
- (BOOL)isScreenSharePublished;

/**
 * @brief 设置订阅相机流格式，大流或小流
 * @param uid  用户ID，从App server分配的唯一标示符
 * @param streamType 流类型
 * - {@link AliRtcVideoStreamTypeNone} : 无效参数，设置不会有任何效果
 * - {@link AliRtcVideoStreamTypeHigh} : 大流
 * - {@link AliRtcVideoStreamTypeLow} : 小流
 * @return
 * - 0:设置成功
 * - 非0:设置失败
 *   - {@link AliRtcErrInner} :
 *     - SDK内部状态错误，需检查是否创建SDK实例成功
 *     - 参数不合法，需要检查参数是否正确
 *     - 纯音频模式不支持该设置，请确认是否在纯音频模式下
 *     - 视频订阅禁止，请检查是否调用了subscribeAllRemoteVideoStreams:NO
 *
 * @note 推流端当前默认不推送小流，只有发送端调用了 {@link publishLocalDualStream:} 打开双流模式，接收端才可以选择订阅大流还是小流，否则订阅的只能是大流；
 * @note 如果调用了subscribeAllRemoteVideoStreams:NO，该方法调用不生效
 */
- (int)setRemoteVideoStreamType:(NSString *_Nonnull)uid type:(AliRtcVideoStreamType)streamType;

/**
 * @brief 设置默认订阅的相机流格式，大流或小流；如果不设置，则默认订阅大流；
 * @param streamType 流类型
 * - {@link AliRtcVideoStreamTypeNone} : 无效参数，设置不会有任何效果
 * - {@link AliRtcVideoStreamTypeHigh} : 大流
 * - {@link AliRtcVideoStreamTypeLow} : 小流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} :
 *     - SDK内部状态错误，需检查是否创建SDK实例成功
 *     - 纯音频模式不支持该设置，请确认是否在纯音频模式下
 *     - 视频订阅禁止，请检查是否调用了subscribeAllRemoteVideoStreams:NO
 *
 * @note 如果调用了subscribeAllRemoteVideoStreams:NO，该方法调用不生效
 */
- (int)setRemoteDefaultVideoStreamType:(AliRtcVideoStreamType)streamType;

/**
 * @brief 停止/恢复订阅所有远端音频流
 * @param sub 是否订阅所有远端音频流
 * - YES:订阅所有用户的音频流
 * - NO:停止订阅所有用户的音频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} : SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - 该方法为是否订阅音频流总开关，入会前入会后均可以调用；
 * - 如果设置了 subscribeAllRemoteAudioStreams:NO，后面调用 {@link setDefaultSubscribeAllRemoteAudioStreams:} 和 {@link subscribeRemoteAudioStream:sub:} 都不会生效；
 */
- (int)subscribeAllRemoteAudioStreams:(BOOL)sub;

/**
 * @brief 停止/恢复订阅所有远端视频流
 * @param sub 是否订阅所有远端视频流
 * - YES:订阅所有用户的视频流
 * - NO:停止订阅所有用户的视频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} : SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - 该方法为是否订阅视频流总开关，入会前入会后均可以调用
 * - 如果设置了 subscribeAllRemoteVideoStreams:NO，后面调用 {@link setDefaultSubscribeAllRemoteVideoStreams:} 和 {@link subscribeRemoteVideoStream:track:sub:} 都不会生效；
 */
- (int)subscribeAllRemoteVideoStreams:(BOOL)sub;

/**
 * @brief 停止/恢复订阅特定远端用户的音频流
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param sub 是否订阅远端用户的音频流
 * - YES:订阅指定用户的音频流
 * - NO:停止订阅指定用户的音频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} :
 *     - SDK内部状态错误，需检查是否创建SDK实例成功
 *     - 音频订阅禁止，请检查是否调用了subscribeAllRemoteAudioStreams:NO
 *
 * @note
 * - 如果之前有调用过 {@link subscribeAllRemoteAudioStreams:} 停止订阅所有远端音频，则此接口调用无效；
 * - {@link subscribeAllRemoteAudioStreams:} 是全局控制，subscribeRemoteAudioStream 是单独控制。
 */
- (int)subscribeRemoteAudioStream:(NSString *_Nonnull)uid sub:(BOOL)sub;

/**
 * @brief 停止/恢复订阅远端用户的视频流
 * @param uid 用户ID，从App server分配的唯一标示符
 * @param track 视频流类型
 * - {@link AliRtcVideoTrackNo} : 无效参数，设置不会有任何效果
 * - {@link AliRtcVideoTrackCamera} : 相机流
 * - {@link AliRtcVideoTrackScreen} : 屏幕共享流
 * - {@link AliRtcVideoTrackBoth} : 相机流和屏幕共享流
 * @param sub 是否订阅远端用户的视频流
 * - YES:订阅指定用户的视频流
 * - NO:停止订阅指定用户的视频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} :
 *     - SDK内部状态错误，需检查是否创建SDK实例成功
 *     - 视频订阅禁止，请检查是否调用了subscribeAllRemoteVideoStreams:NO
 *
 * @note
 * - 如果之前有调用过 {@link subscribeAllRemoteVideoStreams:} 停止订阅所有远端视频，则此接口调用无效；
 * - {@link subscribeAllRemoteVideoStreams:} 是全局控制，SubscribeRemoteVideoStream 是单独控制。
 */
- (int)subscribeRemoteVideoStream:(NSString *_Nonnull)uid track:(AliRtcVideoTrack)track sub:(BOOL)sub;

/**
 * @brief 设置是否默认订阅音频流
 * @param sub 是否默认订阅音频流
 * - YES:(Default)默认订阅音频流，
 * - NO:默认不订阅音频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} : SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - 入会前入会后均可调用；
 * - 如果在加入频道前调用 setDefaultSubscribeAllRemoteAudioStreams:NO，则入会后默认不再订阅任何音频流；
 * - 如果在加入频道后调用 setDefaultSubscribeAllRemoteAudioStreams:NO，默认不再订阅设置后加入频道的用户的音频流；
 * - 不管是否默认订阅，都可以调用 {@link subscribeRemoteAudioStream:sub:}，对指定的用户进行订阅或取消订阅操作；
 * - 订阅行为统一受到 {@link subscribeAllRemoteAudioStreams:} 这个总开关控制，假设 {@link subscribeAllRemoteAudioStreams:} 设置为NO，则订阅全部关闭，其他启动行为全部不生效；
 */
- (int)setDefaultSubscribeAllRemoteAudioStreams:(BOOL)sub;

/**
 * @brief 设置是否默认订阅视频流
 * @param sub 是否默认订阅视频流
 * - YES:(Default)默认订阅视频流
 * - NO:默认不订阅视频流
 * @return
 * - 0:设置成功
 * - <0:设置失败
 *   - {@link AliRtcErrInner} : SDK内部状态错误，需检查是否创建SDK实例成功
 *
 * @note
 * - 入会前入会后均可调用；
 * - 如果在加入频道前调用 setDefaultSubscribeAllRemoteVideoStreams:NO，则入会后默认不再订阅任何视频流；
 * - 如果在加入频道后调用 setDefaultSubscribeAllRemoteVideoStreams:NO，默认不再订阅设置后加入频道的用户的视频流；
 * - 不管是否默认订阅，都可以调用 {@link subscribeRemoteVideoStream:track:sub:}，对指定的用户进行订阅或取消订阅操作；
 * - 订阅行为统一受到 {@link subscribeAllRemoteVideoStreams:} 这个总开关控制，假设 {@link subscribeAllRemoteVideoStreams:} 设置为NO，则订阅全部关闭，其他启动行为全部不生效；
 */
- (int)setDefaultSubscribeAllRemoteVideoStreams:(BOOL)sub;

/**
 * @brief 获取远端在线用户列表
 * @return 当前频道内所有在线用户userid列表
 * @note 若当前频道ChannelProfile设置为 {@link AliRtcInteractivelive} 模式，只有设置角色为 {@link AliRtcClientRoleInteractive} 的用户为在线用户，本方法不返回角色为 {@link AliRtcClientRoleLive} 的用户
*/
- (NSArray<NSString *> *_Nullable)getOnlineRemoteUsers;

/**
 * @brief 查询用户是否在线
 * @param uid 用户ID，从App server分配的唯一标示符。不可为NULL
 * @return 
 *  - YES，用户在线
 *  - NO，用户不在线
 * @note 根据特定的UserID，查询该用户是否在线。
 */
- (BOOL)isUserOnline:(NSString *_Nonnull)uid;

/**
 * @brief 获取当前网络链接状态
 * @return 当前链接状态, 参考 {@link AliRtcConnectionStatus}
 * @note 网络链接状态发生变化时，SDK会通过 {@link onConnectionStatusChange:reason:} 回调通知
 * @note 入会前调用此接口，均返回状态 {@link AliRtcConnectionStatusDisconnected}
 */
- (AliRtcConnectionStatus)getCurrentConnectionStatus;

/** @} */

#pragma mark - "设备管理"
/**
 * @name 设备管理
 * @{
 */

/**
 * @brief 设置音频输出为听筒还是扬声器
 * @param enable
 * - YES: 扬声器模式(默认)
 * - NO: 听筒模式
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)enableSpeakerphone:(BOOL)enable;

/**
 * @brief 获取当前音频输出为听筒还是扬声器
 * @return 
 * - YES: 扬声器模式；
 * - NO: 听筒模式
 */
- (BOOL)isEnableSpeakerphone;

/**
 * @brief 设置录音音量
 * @param volume 录音音量，取值范围[0,400]
 * - 0：静音
 * - <100：减小音量
 * - >100：放大音量
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setRecordingVolume:(NSInteger)volume;

/**
 * @brief 设置播放音量
 * @param volume 播放音量，取值范围[0,400]
 * - 0：静音
 * - <100：减小音量
 * - >100：放大音量
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setPlayoutVolume:(NSInteger)volume;

/**
 * @brief 设置音频profile
 * @param audio_profile 音频采集/编码模式参数, 详见 {@link AliRtcAudioProfile};
 * @param audio_scene 音频场景模式参数,详见 {@link AliRtcAudioScenario};
 * @return 
 * - 0: 成功
 * - 其他: 失败
 * @note 只支持 {@link joinChannel:name:onResultWithUserId:} 前设置有效；
 */
- (int)setAudioProfile:(AliRtcAudioProfile)audio_profile audio_scene:(AliRtcAudioScenario)audio_scene;

/**
 * @brief 设置SDK对AVAudioSession的控制权限
 * @param restriction 控制权限
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setAudioSessionOperationRestriction:(AliRtcAudioSessionOperationRestriction)restriction;

/**
 * @brief 设置SDK设备音量类型
 * @param type 音量类型
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setDeviceVolumeType:(AliRtcDeviceVolumeType)type;

/**
 * @brief 切换前后摄像头
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 只有iOS和android提供这个接口
 */
- (int)switchCamera;

/**
 * @brief 获取当前摄像头方向，默认前置摄像头
 * @return 摄像头方向
 * - AliRtcCameraDirectionFront 前置
 * - AliRtcCameraDirectionBack 后置
 * - AliRtcCameraDirectionInvalid 无效
 * @note 只有iOS和android提供这个接口，在Camera 已经open之后调用，否则会返回 {@link AliRtcCameraDirectionInvalid}
 */
- (AliRtcCameraDirection)getCurrentCameraDirection;

/**
 * @brief 设置摄像头缩放
 * @param zoom   缩放级别，范围从 1 到 camera支持的最大 zoom值
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 只有iOS和android提供这个接口
 */
 - (int)setCameraZoom:(float)zoom;

/**
 * @brief 设置摄像头闪光灯开关
 * @param flash  是否打开闪光灯
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 只有iOS和android提供这个接口，一般后置摄像头有闪光灯功能
 */
- (int)setCameraFlash:(BOOL)flash;

/**
 * @brief 摄像头是否支持手动聚焦
 * @return 
 * - YES: 支持
 * - NO: 不支持
 * @note 只有iOS和android提供这个接口，用来检查当前camera是否可以设置聚焦点
 */
- (BOOL)isCameraFocusPointSupported;

/**
 * @brief 摄像头是否支持设置曝光点
 * @return 
 * - YES: 支持
 * - NO: 不支持
 * @note 只有iOS和android提供这个接口，用来检查当前camera是否可以设置曝光点
 */
- (BOOL)isCameraExposurePointSupported;

/**
 * @brief 设置摄像头手动聚焦点
 * @param point   聚焦点坐标
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 只有iOS和android提供这个接口，调用后camera对所设点做一次曝光调整，后面一直保持这个对焦值
 */
- (int)setCameraFocusPoint:(CGPoint)point;

/**
 * @brief 设置摄像头曝光点
 * @param point  曝光点
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 只有iOS和android提供这个接口，调用后camera对所设点做一次曝光调整，后面一直保持这个曝光值
 */
- (int)setCameraExposurePoint:(CGPoint)point;

/**
 * @brief 摄像头是否支持人脸聚焦
 * @return
 * - YES: 支持
 * - NO: 不支持
 * @note 只有iOS和android提供这个接口，在camera没有打开的情况下返回 NO，
 *       在camera打开的情况下，如果当前camera同时支持人脸识别和对焦功能则返回 YES
*/
- (BOOL)isCameraAutoFocusFaceModeSupported;

/**
 * @brief 设置摄像头人脸对焦
 * @param enable  YES: 开启; NO:关闭
 * @return
 * - YES: 成功
 * - NO: 失败
 * @note 只有iOS和android提供这个接口，如果 {@link AliRtcEngine::isCameraAutoFocusFaceModeSupported} 返回 YES
 *      且此调用enable为 YES 的情况下，实时对焦到采集到数据的人脸上
*/
- (BOOL)setCameraAutoFocusFaceModeEnabled:(BOOL)enable;

/**
 * @brief 开启音频采集
 * @details 此接口可以控制提前打开音频采集，如果不设置，则SDK会自动控制音频采集设备：
 * - 如果打开推送音频流 {@link publishLocalAudioStream:}，SDK在入会后会打开音频采集
 * - 如果关闭推送音频流 {@link publishLocalAudioStream:}，SDK在入会后不会打开音频采集
 *
 * @note 
 * - 调用此接口后，离会后采集设备保持开启状态
 */
- (void)startAudioCapture;

/**
 * @brief 开启音频采集
 * @details 此接口可以控制提前打开音频采集，如果不设置，则SDK会自动控制音频采集设备：
 * - 如果打开推送音频流 {@link publishLocalAudioStream:}，SDK在入会后会打开音频采集
 * - 如果关闭推送音频流 {@link publishLocalAudioStream:}，SDK在入会后不会打开音频采集
 *
 * @param keepAlive YES: 离会后采集设备保持开启状态；NO: 离会后采集设备关闭
 */
- (void)startAudioCapture:(BOOL)keepAlive;

/**
 * @brief 关闭音频采集
 * @note 调用此接口后，入会后、离会再入会，采集设备保持关闭状态
 */
- (void)stopAudioCapture;

/**
 * @brief 开启音频播放
 * @note 此接口可以控制提前打开音频播放，如果不设置，则SDK会在订阅到音频流后自动打开音频播放
 */
- (void)startAudioPlayer;

/**
 * @brief 关闭音频播放
 * @note 此接口可以控制关闭音频播放，与 {@link startAudioPlayer} 对应
 */
- (void)stopAudioPlayer;

/** @} */

#pragma mark - "其他"
/**
 * @name 其他
 * @{
 */

/**
 * @brief 设置日志等级
 * @param logLevel Log级别，详见 {@link AliRtcLogLevel} 枚举类型
 * @note 设置 SDK 的输出日志等级。默认值为 {@link AliRtcLogLevel::AliRtcLogLevelInfo}
 * @note 调用此接口，请在仅次于 SetLogDirPath 接口调用之后再调用本接口，避免因日志等级切换造成的打印丢失。
 */
- (void)setLogLevel:(AliRtcLogLevel)logLevel;

/**
 * @brief 检查camera是否打开
 * @return
 * - YES: 表示摄像头已打开
 * - NO: 表示摄像头没有打开
 * @note 该接口用于检查当前camera的状态
 */
- (BOOL)isCameraOn;

/**
 * @brief 获取状态：当前是否在频道中
 * @return 
 *  - YES: 表示当前已经加入了频道。
 *  - NO: 表示当前不在频道中。
 * @note 该方法可在加入频道前或加入频道后调用。
 */
- (BOOL)isInCall;

/**
 * @brief 查询是否纯音频模式
 * @return 
 * - YES: 表示纯音频模式  
 * - NO: 表示非纯音频模式
 */
- (BOOL)isAudioOnly;

/**
 * @brief 查询远端用户状态
 * @param uid 用户ID。从App server分配的唯一标示符
 * @return dict App提供的容器，用于存放用户数据，dict类型为字典类型，通过{Key,Value}进行访问。
 *  - dict[userID] != @""  成功
 *  - dict[userID] == @""  失败
 * @note 通过 uid 查询，指定远端用户的状态信息，在参数dict中，以字典{key,value}的形式，返回用户的全部状态信息。
 * @note Key信息: 
 *  - userID: 远端用户的ID。
 *  - isOnline: 远端用户是否在线。
 *  - sessionID: 远端用户的会话ID。
 *  - callID: 当前会话的callID。
 *  - displayName: 远端用户的名称。
 *  - hasAudio: 远端用户是否推送了音频流。
 *  - hasCameraMaster: 远端用户是否推送了相机大流。
 *  - hasCameraSlave: 远端用户是否推送了相机小流。
 *  - hasScreenSharing: 远端用户是否推送了屏幕流。
 *  - requestAudio, 本端是否订阅了此远端用户的音频流。
 *  - requestCameraMaster, 本端是否订阅了此远端用户的相机大流。此状态，系在成功订阅该用户摄像头大流前的状态。
 *  - requestCameraSlave, 本端是否订阅了此远端用户的相机小流。此状态，系在成功订阅该用户摄像头小流前的状态。
 *  - requestScreenSharing, 本端是否订阅了此远端用户的屏幕流。此状态，系在成功订阅该用户屏幕共享前的状态。
 *  - preferCameraMaster, 远端用户是否开启了大流优先。
 *  - subScribedAudio: 本端是否拉到了此远端用户的音频流。
 *  - subScribedCameraMaster: 本端是否拉到了此远端用户的相机大流。 
 *  - subScribedCamearSlave: 本端是否拉到了此远端用户的相机小流。
 *  - subScribedScreenSharing: 本端是否拉到了此远端用户的屏幕流。
 *  - hasCameraView: 本端是否设置了此远端用户相机流的view。
 *  - hasScreenView: 本端是否设置了此远端用户屏幕流的view。
 *  - muteAudioPlaying: 本端是否静音了此远端用户。
 */
- (NSDictionary *_Nullable)getUserInfo:(NSString *_Nonnull)uid;

/**
 * @brief 设置H5兼容模式
 * @details 互动模式下，是否需要与Web SDK互通。如果使用Native SDK用户加入频道，需要与通过Web SDK加入频道的用户进行互通，则必须使用H5兼容模式,否则，Web用户查看Native用户将是黑屏。
 * @param comp 
 * - YES: 兼容H5。
 * - NO: 传统模式，不兼容H5。
 * 
 * @note 不支持在创建AliRtcEngine实例之后更改H5兼容模式，必须在创建实例之前就调用此方法。
 */
+ (void)setH5CompatibleMode:(BOOL)comp;

/**
 * @brief 检查当前是否兼容H5、与Web SDK互通
 * @return 
 * - YES: 兼容H5。
 * - NO: 不兼容H5。
 */
+ (BOOL)getH5CompatibleMode;

/**
 * 展示用户Debug数据
 * @param view 对外展示的View，由客户传入，显示样式由客户指定
 * @param showType 展示类型:0: 不显示 1.音频 2.视频 3.全部；另外可以传入特殊的值来展示
 * @param userId 对应用户ID
 */
- (int)showDebugView:(UITextView * _Nonnull)view showType:(AliRtcShowDebugViewType)showType userId:(NSString * _Nullable)userId;

/** @} */

#pragma mark - "音视频裸数据输入输出"
/**
 * @name 音视频裸数据输入输出
 * @{
 */

/**
 * @brief 设置回调音频声道数，默认单声道 （混音前数据不支持该参数设置）
 * @param audioNumChannel 声道数，必须是 {@link AliRtcAudioNumChannel}
 * @note 需在 {@link subscribeAudioData:} 前进行设置
 */
- (void)setSubscribeAudioNumChannel:(AliRtcAudioNumChannel)audioNumChannel;

/**
 * @brief 设置回调音频采样率，默认44100（混音前数据不支持该参数设置）
 * @param audioSampleRate 采样率，必须是 {@link AliRtcAudioSampleRate}
 * @note 需在 {@link subscribeAudioData:} 前进行设置
 */
- (void)setSubscribeAudioSampleRate:(AliRtcAudioSampleRate)audioSampleRate;

/**
 * @brief 订阅音频数据
 * @param audioSource 音频数据源类型，详见 {@link AliRtcAudioSource}
 * @note 订阅音频数据输出前，需先通过 {@link setSubscribeAudioNumChannel:} 与 {@link setSubscribeAudioSampleRate:} 设置输出音频数据参数
 */
- (void)subscribeAudioData:(AliRtcAudioSource)audioSource;

/**
 * @brief 取消订阅音频数据
 * @param audioSource 音频数据源类型，详见 {@link AliRtcAudioSource}
 */
- (void)unSubscribeAudioData:(AliRtcAudioSource)audioSource;

/**
 * @brief 设置音量回调频率和平滑系数
 * @param interval 时间间隔，单位毫秒，最小值不得小于10ms, 建议设置300-500ms, <= 0表示不启用音量提示和说话人提示功能
 * @param smooth 平滑系数，数值越大平滑程度越高，反之越低，实时性越好，建议设置3，范围[0, 9];
 * @param reportVad 说话人检测开关
 * - 1: 开启
 * - 0: 关闭
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 设置之后，音频音量和说话人uid会分别通过 {@link AliRtcEngineDelegate::onAudioVolumeCallback:totalVolume:} 和 {@link AliRtcEngineDelegate::onActiveSpeaker:} 回调
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval smooth:(NSInteger)smooth reportVad:(NSInteger)reportVad;

/**
 * @brief 订阅视频数据
*/
- (void)registerVideoSampleObserver;

/**
 * @brief 取消订阅视频数据
*/
- (void)unregisterVideoSampleObserver;

NS_ASSUME_NONNULL_BEGIN
/**
 * @brief 主动获取采集数据
 * @param videoTrack 视频流类型
 * @param p_sample 数据接收对象
 * @return
 * - YES: 成功
 * - NO: 失败
 *
 * @note 仅在 {@link onGetIfUserFetchObserverData} 返回 YES 时有效
 */
- (BOOL)getVideoCaptureData:(AliRtcVideoTrack)videoTrack videoSample:(AliRtcVideoDataSample**)p_sample;

/**
 * @brief 主动获取编码前数据
 * @param videoTrack 视频流类型
 * @param p_sample 数据接收对象
 * @return
 * - YES: 成功
 * - NO: 失败
 *
 * @note 仅在 {@link onGetIfUserFetchObserverData} 返回 YES 时有效
 */
- (BOOL)getVideoPreEncoderData:(AliRtcVideoTrack)videoTrack videoSample:(AliRtcVideoDataSample**)p_sample;

/**
 * @brief 主动获取拉流数据，onGetIfUserFetchObserverData 返回 YES 时有效
 * @param uid 远端用户ID
 * @param videoTrack 视频流类型
 * @param p_sample 数据接收对象
 * @return
 * - YES: 成功
 * - NO: 失败
 *
 * @note 仅在 {@link onGetIfUserFetchObserverData} 返回 YES 时有效
 */
- (BOOL)getVideoRenderData:(NSString*)uid videoTrack:(AliRtcVideoTrack)videoTrack videoSample:(AliRtcVideoDataSample**)p_sample;

NS_ASSUME_NONNULL_END

/**
 * @brief 注册本地相机流视频OpenGL纹理数据观测器
 * @note
 * - 成功注册本地相机流视频OpenGL纹理数据观测器后，SDK 会在捕捉到视频帧时，触发onTextureCreate、onTextureUpdate、onTextureDestory回调
 * - 该接口只能对本地相机流视频有效
 */
- (void)registerLocalVideoTexture;

/**
 * @brief 取消注册本地相机流视频OpenGL纹理数据观测器
 */
- (void)unregisterLocalVideoTexture;


/**
 * @brief 启用外部视频输入源
 * @param enable
 * - YES 开启
 * - NO 关闭
 * @param type 流类型，详见 {@link AliRtcVideoSource}
 * - AliRtcVideosourceCameraType 外部输入视频数据走相机流通道，如果当前相机采集打开中，调用该接口设置enable为YES，sdk会替换掉相机采集
 * - AliRtcVideosourceScreenShareType 外部输入视频数据走屏幕流通道，如果当前屏幕共享采集打开中，调用该接口设置enable为YES，sdk会替换掉屏幕共享采集
 * @param renderMode 处理模式，外部输入视频源宽高比和推流profile不一致时，会按照对应的rendermode做对应处理，详见 {@link AliRtcRenderMode}
 * - AliRtcRenderModeAuto 自动（默认） 如果外部输入的视频宽高比和推流设置的宽高比不一致时，维持外部输入的视频宽高比，等比例缩放宽高到推流设置的宽高范围内，注意此模式下为了保证原始视频的比例和内容完整性，会导致实际推流的分辨率和设置的不一致
 * - AliRtcRenderModeStretch 拉伸平铺，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频拉伸到推流设置的比例，画面会变形
 * - AliRtcRenderModeFill 填充黑边，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频上下或者左右填充黑边
 * - AliRtcRenderModeCrop 裁剪，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频宽或者高进行裁剪，画面内容会丢失
 * @return
 * - 0: 成功
 * - 非0: 失败
*/
- (int)setExternalVideoSource:(BOOL)enable sourceType:(AliRtcVideoSource)type renderMode:(AliRtcRenderMode)renderMode;

/**
 * @brief 输入视频数据
 * @param frame 帧数据，详见 {@link AliRtcVideoDataSample}
 * @param type 流类型，详见 {@link AliRtcVideoSource}
 * - AliRtcVideosourceCameraType 外部输入视频数据走相机流通道
 * - AliRtcVideosourceScreenShareType 外部输入视频数据走屏幕流通道
 *  @return
 * - 0: 成功
 * - 非0: 失败
 * @note 如果返回值为errorCode中的AliRtcErrVideoBufferFull，代表当前buffer队列塞满，需要等待后再继续输送数据
*/
- (int)pushExternalVideoFrame:(AliRtcVideoDataSample *_Nonnull)frame sourceType:(AliRtcVideoSource)type;

/**
 * @brief 设置是否启用外部音频输入源
 * @param enable YES:开启; NO:关闭
 * @param sampleRate 采样率 16k, 48k...
 * @param channelsPerFrame 声道数 1:单声道; 2:双声道
 * @return
 * - >=0: 成功
 * - <0: 失败
 */
- (int)setExternalAudioSource:(BOOL)enable withSampleRate:(NSUInteger)sampleRate channelsPerFrame:(NSUInteger)channelsPerFrame;

/**
 * @brief 输入外部音频数据推流到远端
 * @param data 音频数据buffer
 * @param samples 音频数据buffer长度
 * @param timestamp 时间戳
 * @return 
 * - <0: 表示失败;
 * - 0: 表示成功;
 * - 返回值为 {@link AliRtcErrorCode::AliRtcErrAudioBufferFull}时，需要在间隔投递数据时间长度后再次重试投递
 * @note 为了保证语音连续性，sdk内部会有buffer缓存送进来的音频数据，以每次送10ms数据为例，如果返回 {@link AliRtcErrorCode::AliRtcErrAudioBufferFull} 时，说明内部缓冲区已满，建议等待20ms后再重新送当前数据帧；
 */
- (int)pushExternalAudioFrameRawData:(void *_Nonnull)data samples:(NSUInteger)samples timestamp:(NSTimeInterval)timestamp;

/**
 * @brief 设置外部音频音量
 * @param vol 音量，取值范围[0,100]
 * @return
 * - >=0: 成功
 * - <0: 失败
 * @note 同时设置外部音频输入音量与外部音频播放音量
 */
- (int)setExternalAudioVolume:(int)vol;

/**
 * @brief 获取混音音量
 * @return 
 * - >=0: 正常混音音量,范围[0-100]
 * - <0: 失败
 */
- (int)getExternalAudioVolume;

/**
 * @brief 设置是否与麦克风采集音频混合
 * @param mixed YES：混音；NO：完全替换麦克风采集数据
 * @return
 * - 0: 成功
 * - 非0: 失败
 */
- (int)setMixedWithMic:(BOOL)mixed;

/**
 * @brief 设置是否启用外部输入音频播放
 * @param enable YES:开启; NO:关闭
 * @param sampleRate 采样率 16000 48000...
 * @param channelsPerFrame 声道数 1:单声道; 2:双声道
 * @return
 * - >=0: 成功
 * - <0: 失败
 */
- (int)setExteranlAudioRender:(BOOL)enable sampleRate:(NSUInteger)sampleRate channelsPerFrame:(NSUInteger)channelsPerFrame;

/**
 * @brief 输入外部音频数据本地播放
 * @param audioSamples 音频数据buffer
 * @param sampleLength 音频数据buffer长度
 * @param sampleRate 输入音频数据的采样率
 * @param channelsPerFrame 输入音频数据的声道数
 * @param timestamp 时间戳
 * @return 
 * - <0: 表示失败;
 * - 0: 表示成功;
 * - 返回值为 {@link AliRtcErrorCode::AliRtcErrAudioBufferFull} 时，需要在间隔投递数据时间长度后再次重试投递
 * @note 为了保证语音连续性，sdk内部会有buffer缓存送进来的音频数据，以每次送10ms数据为例，如果返回 {@link AliRtcErrorCode::AliRtcErrAudioBufferFull} 时，说明内部缓冲区已满，建议等待20ms后再重新送当前数据帧；
 */
- (int)pushExternalAudioRenderRawData:(const void* _Nullable)audioSamples sampleLength:(NSUInteger)sampleLength sampleRate:(NSUInteger)sampleRate channelsPerFrame:(NSUInteger)channelsPerFrame timestamp:(long long)timestamp;

/** @} */

#pragma mark - "音乐伴奏音效"
/**
 * @name 音乐伴奏音效
 * @{
 */

/**
 * @brief 设置变调参数
 * @param value 变调参数，范围：[0.5, 2.0]，1.0表示音调不变，小于1.0表示音调降低，大于1.0表示音调升高，默认1.0
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 加入频道前和频道过程中调用都生效
 */
- (int)setAudioEffectPitchValue:(double)value;

/**
 * @brief 设置变声音效模式
 * @param mode 参考 {@link AliRtcAudioEffectVoiceChangerMode} 对应的变声音效模式值
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 加入频道前和频道过程中调用都生效
 */
- (int)setAudioEffectVoiceChangerMode:(AliRtcAudioEffectVoiceChangerMode)mode;

/**
 * @brief 设置混响音效模式
 * @param mode 参考 {@link AliRtcAudioEffectReverbMode} 对应的混响模式
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 加入频道前和频道过程中调用都生效
 */
- (int)setAudioEffectReverbMode:(AliRtcAudioEffectReverbMode)mode;

/**
 * @brief 设置混响音效类型
 * @param type 参考 {@link AliRtcAudioEffectReverbParamType} 对应的混响类型
 * @param value 混响参数值，不同混响类型的取值范围参考 {@link AliRtcAudioEffectReverbParamType} 中取值说明
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 需要在 {@link setAudioEffectReverbMode:} 之后调用
 */
- (int)setAudioEffectReverbParamType:(AliRtcAudioEffectReverbParamType)type value:(float)value;

/**
 * @brief 开始伴奏混音
 * @param filePath 伴奏文件路径
 * @param onlyLocalPlay 是否只本地播放
 * @param replaceMic 是否替换掉MIC 
 * @param loopCycles 循环次数，可以设置-1(无限循环)或者>0的正整数次，其他值无效
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 * @note 异步接口，可通过 {@link onAudioPlayingStateChanged:errorCode:} 监听播放器状态
 */
- (int)startAudioAccompanyWithFile:(NSString *_Nonnull)filePath onlyLocalPlay:(BOOL)onlyLocalPlay replaceMic:(BOOL)replaceMic loopCycles:(NSInteger)loopCycles;

/**
 * @brief 停止伴奏混音
 * @return
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)stopAudioAccompany;

/**
 * @brief 设置伴奏音量
 * @param volume 伴奏音量，取值范围[0,100]
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 * @note 同时设置伴奏本地播放音量与伴奏推流音量
 */
- (int)setAudioAccompanyVolume:(NSInteger)volume;

/**
 * @brief 设置伴奏推流音量
 * @param volume 伴奏推流音量，取值范围[0,100]
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)setAudioAccompanyPublishVolume:(NSInteger)volume;

/**
 * @brief 获取伴奏推流音量
 * @return 
 * - [0, 100]: 成功
 * - 其他值: 返回错误码
 */
- (int)getAudioAccompanyPublishVolume;

/**
 * @brief 设置伴奏本地播放音量
 * @param volume 伴奏本地播放音量，取值范围[0,100]
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)setAudioAccompanyPlayoutVolume:(NSInteger)volume;

/**
 * @brief 获取伴奏本地播放音量
 * @return 
 * - [0, 100]: 成功
 * - 其他值: 返回错误码
 */
- (int)getAudioAccompanyPlayoutVolume;


/**
 * @brief 暂停伴奏混音
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)pauseAudioAccompany;

/**
 * @brief 重新开始伴奏混音
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)resumeAudioAccompany;

/**
 * @brief 获取伴奏文件时长, 单位为毫秒
 * @return
 * - >=0: 伴奏文件时长
 * - <0: 返回错误码
 */
- (int)getAudioAccompanyDuration;

/**
 * @brief 获取伴奏文件播放进度，单位为毫秒
 * @return 
 * - >=0: 伴奏文件播放进度
 * - <0: 返回错误码
 */
- (int)getAudioAccompanyCurrentPosition;

/**
 * @brief 设置伴奏文件的播放位置
 * @param pos 进度条位置，单位为毫秒
 * @return 
 * - 0: 成功
 * - 非0: 返回错误码
 */
- (int)setAudioAccompanyPosition:(int)pos;

/**
 * @brief 预加载音效文件
 * @param soundId 用户给该音效文件分配的ID
 * @param filePath 音效文件路径，支持本地文件和网络url
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 音效相关接口为同步接口, 建议使用本地文件
 */
- (int)preloadAudioEffectWithSoundId:(NSInteger)soundId filePath:(NSString *_Nonnull)filePath;

/**
 * @brief 删除预加载的音效文件
 * @param soundId 用户给该音效文件分配的ID
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 音效soundId应与预加载 {@link preloadAudioEffectWithSoundId:filePath:} 时传入的ID相同
 */
- (int)unloadAudioEffectWithSoundId:(NSInteger)soundId;

/**
 * @brief 开始播放音效
 * @details 开始播放音效接口，可以多次调用该方法传入不同的soundId和filePath，同时播放多个音效文件，音效文件播放结束后，SDK 会触发 {@link onAudioEffectFinished:} 回调
 * @param soundId 用户给该音效文件分配的ID，每个音效均有唯一的ID，如果你已通过 {@link preloadAudioEffectWithSoundId:filePath:} 将音效加载至内存，确保这里的soundId与 {@link preloadAudioEffectWithSoundId:filePath:} 设置的soundId相同
 * @param filePath 文件路径，支持本地文件和网络url
 * @param cycles 音效循环播放次数
 * - ≥0：循环播放次数，例如，设置3表示总共播放3次
 * - -1：无限循环播放
 * @param publish 是否将音效传到远端
 * - YES：发布，本地用户和远端用户都能听到音效
 * - NO：不发布，只有本地用户能听到音效
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)playAudioEffectWithSoundId:(NSInteger)soundId filePath:(NSString *_Nonnull)filePath cycles:(NSInteger)cycles publish:(BOOL)publish;

/**
 * @brief 停止播放音效
 * @param soundId 用户给该音效文件分配的ID，每个音效均有唯一的ID，如果你已通过 {@link preloadAudioEffectWithSoundId:filePath:} 将音效加载至内存，确保这里的soundId与 {@link preloadAudioEffectWithSoundId:filePath:} 设置的soundId相同
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)stopAudioEffectWithSoundId:(NSInteger)soundId;

/**
 * @brief 停止播放所有音效
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)stopAllAudioEffects;

/**
 * @brief 设置音效推流混音音量
 * @param soundId 用户给该音效文件分配的ID
 * @param volume 推流混音音量，范围是：[0, 100]，默认值：50
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 该方法需要在 {@link playAudioEffectWithSoundId:filePath:cycles:publish:} 后调用
 */
- (int)setAudioEffectPublishVolumeWithSoundId:(NSInteger)soundId volume:(NSInteger)volume;

/**
 * @brief 获取音效推流混音音量
 * @param soundId 用户给该音效文件分配的ID
 * @return
 * - [0, 100]：音效推流混音音量
 * - 其他：错误值
 * @note 音效推流混音音量有效范围为：[0, 100]，该方法需要在 {@link playAudioEffectWithSoundId:filePath:cycles:publish:} 后调用
 */
- (int)getAudioEffectPublishVolumeWithSoundId:(NSInteger)soundId;

/**
 * @brief 设置音效本地播放音量
 * @param soundId 用户给该音效文件分配的ID
 * @param volume 音效本地播放音量，范围：[0, 100]，默认值：50
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 该方法需要在 {@link playAudioEffectWithSoundId:filePath:cycles:publish:} 后调用
 */
- (int)setAudioEffectPlayoutVolumeWithSoundId:(NSInteger)soundId volume:(NSInteger)volume;

/**
 * @brief 获取音效本地播放音量
 * @param soundId 用户给该音效文件分配的ID
 * @return
 * - [0, 100]：音效本地播放音量
 * - 其他：错误值
 * @note 音效本地播放音量有效范围为：[0, 100]，该方法需要在 {@link playAudioEffectWithSoundId:filePath:cycles:publish:} 后调用
 */
- (int)getAudioEffectPlayoutVolumeWithSoundId:(NSInteger)soundId;

/**
 * @brief 设置所有音效本地播音量
 * @param volume 音效本地播放音量，范围：[0, 100]，默认值：50
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)setAllAudioEffectsPlayoutVolume:(NSInteger)volume;

/**
 * @brief 设置所有音效推流混音音量
 * @param volume 推流混音音量，范围是：[0, 100]，默认值：50
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)setAllAudioEffectsPublishVolume:(NSInteger)volume;

/**
 * @brief 暂停音效
 * @param soundId 用户给该音效文件分配的ID
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)pauseAudioEffectWithSoundId:(NSInteger)soundId;

/**
 * @brief 暂停所有音效
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)pauseAllAudioEffects;

/**
 * @brief 恢复指定音效文件
 * @param soundId 用户给该音效文件分配的ID
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)resumeAudioEffectWithSoundId:(NSInteger)soundId;

/**
 * @brief 恢复所有音效文件
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)resumeAllAudioEffects;

/**
 * @brief 是否开启语音活动检测
 * @param enable YES表示开启, NO表示关闭, 默认关闭
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note
 * - 入会前调用或入会后推音频流之前调用有效。
 * - 开启语音活动检测可以在检测到没有语音的情况下，每隔400ms编码发送静音包，节省用户流量。
*/
- (int)enableAudioDTX:(BOOL)enable;

/**
 * @brief 开启音频静音检测（Audio Mute Detection, 静音不发送音频包）
 * @param enable YES表示开启,NO表示关闭,默认关闭;
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note
 * - 入会前调用或入会后推音频流之前调用有效。
 * - 开启此选项可以在关闭麦克风或者静音 {@link muteLocalMic:mode:} 并且静音模式为 {@link AliRtcMuteLocalAudioMode:AliRtcMuteAudioModeDefault} 或者 {@link AliRtcMuteLocalAudioMode:AliRtcMuteAllAudioMode} 的模式下，停止音频编码和音频包的发送，节省用户流量。
*/
- (int)enableAudioAMD:(BOOL)enable;

/**
 * @brief 启用耳返
 * @param enable 是否启用耳返  YES：开启； NO：关闭  默认: 关闭
 * @return
 * - 0：成功
 * - 非0：失败
 * @note 所有设备都支持耳返，建议戴耳机的情况下开启耳返，效果更好
 */
- (int)enableEarBack:(BOOL)enable;

/**
 * @brief 设置耳返音量
 * @param volume 音量大小，范围是：[0 ~ 100]，默认值为100
 * @return
 * - 0：成功
 * - 非0：失败
 */
- (int)setEarBackVolume:(NSInteger)volume;

 /**
  * @brief 开启智能降噪
  * @return 
  * - 0: 成功
  * - 非0: 返回错误码
  * @note 
  * - 智能降噪功能以插件形式提供，调用该接口前，请确保已集成了AliRTC提供的PluginMindRTC.framework
  * - 此接口可以通话过程中控制打开智能降噪功能，通话过程中可以支持开启和关闭智能降噪
  * - 默认关闭，开启后可能导致功耗增加，智能降噪适合于会议，教育等语音通讯为主的场景，不适合有背景音乐的场景
  */
- (int)startIntelligentDenoise;

/**
 * @brief 关闭智能降噪
 * @note 此接口可以通话过程中控制关闭智能降噪功能
 */
- (void)stopIntelligentDenoise;

/**
 * @brief 启用音乐模式
 * @param enable 是否启用音乐模式, YES表示开启, NO表示关闭, 默认关闭
 * @return 
 * - 0: 成功
 * - <0: 失败
 * @note 此接口支持会议中过程中动态开启关闭，对有音乐的场景有一定程度的音质提升，最佳的音乐场景体检建议通过接口 {@link setAudioProfile:audio_scene:} 中设置场景为 {@link AliRtcAudioScenario::AliRtcSceneMusicMode} 来实现;
 */
- (int)enableMusicMode:(BOOL)enable;

/** @} */

#pragma mark - "文件录制"
/**
 * @name 文件录制
 * @{
 */

/**
 * @brief 开始录制
 * @details SDK提供了屏录录制的功能，可以录制本地或远端的音频流、视频流、相机流
 * @param recordType 录制类型 详细定义见 {@link AliRtcRecordType}
 * @param recordFormat 录制文件格式 详细定义见 {@link AliRtcRecordFormat}
 * @param filePath 文件路径
 * @param audioConfig 音频设置 详细定义见 {@link AliRtcRecordAudioConfig}
 * @param videoConfig 视频设置 详细定义见 {@link AliRtcRecordVideoConfig}
 * @return
 * - YES: 成功
 * - NO: 失败
 */
- (BOOL)startRecord:(AliRtcRecordType)recordType recordFormat:(AliRtcRecordFormat)recordFormat filePath:(NSString*_Nonnull)filePath audioConfig:(AliRtcRecordAudioConfig*_Nullable)audioConfig videoConfig:(AliRtcRecordVideoConfig*_Nullable)videoConfig;


/**
 * @brief 停止录制
 * @details SDK提供了停止录制的功能
 */
- (void)stopRecord;

/** @} */

#pragma mark - "网络测试"
/**
 * @name  网络测试
 * @{
 */

/**
 * @brief 开始网络质量探测
 * @details 网络质量探测需要在未入会  {@link joinChannel:name:onResultWithUserId:} 情况下调用，探测结果在 {@link onLastmileDetectResultWithQuality:} 中回调
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)startLastmileDetect;

/**
 * @brief 停止网络质量探测
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)stopLastmileDetect;

/** @} */

#pragma mark - "低延时互动直播模式"
/**
 * @name 低延时互动直播模式
 * @{
 */

/**
 * @deprecated
 * @brief 开始低延时互动直播拉流
 * @details 该方法仅在低延迟互动模式 {@link AliRtcInteractiveWithLowLatencyLive } 下，角色为观众 {@link AliRtcClientRolelive } 时调用有意义
 * @param authInfo 入会鉴权信息
 * @param onResult 拉流结果，errCode
 * - 0: 成功
 * - 非0: 失败
 *   - {@link AliRtcErrCdnLiveCommunicationFailed} : 低延时互动直播信令失败
 *   - {@link AliRtcErrCdnLiveMeidaSettingFailed} : 低延时互动直播媒体设置错误
 *   - {@link AliRtcErrCdnLiveNoneBroadcaster} : 低延时互动直播当前房间没有主播推流
 *   - {@link AliRtcErrCdnLiveNeedRestart} : 低延时互动直播错误，应用层需要重新创建新的SDK实例
 *   - {@link AliRtcErrCdnLiveNeedRestartAgainLater} : 低延时互动直播错误，应用层需要稍等一定时间（自定义间隔）重新创建新的SDK实例
 *   - {@link AliRtcErrCdnLiveServiceUnavailable} : 低延时互动直播服务不可用或者服务降级
 *   - {@link AliRtcErrCdnLiveMediaConnectionInterruption} : 低延时互动直播网络中断错误
 *
 * @note 该接口已废弃
 */
- (void)startLiveStreamingWithAuthInfo:(AliRtcAuthInfo *_Nonnull)authInfo onResult:(void(^_Nullable)(int errCode))onResult;

/**
 * @deprecated
 * @brief 停止低延时互动直播拉流
 * @return
 * - 0: 成功
 * - 非0: 失败
 * @note 该方法仅在低延迟互动模式下，角色为观众时调用有意义
 * @note 该接口已废弃
 */
- (int)stopLiveStreaming;

/**
 * @brief 设置低延时互动直播拉流渲染Canvas
 * @param canvas 渲染参数，包含了窗口以及渲染方式
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 该接口已废弃
 */
- (int)setLiveStreamingViewConfig:(AliVideoCanvas *_Nullable)canvas;

/** @} */

#pragma mark - "美颜控制"
/**
 * @name 美颜控制
 * @{
 */

/**
 * @brief 美颜功能是否可用
 */
- (BOOL)isBeautifierAvailable;

/**
 * @brief 美颜功能是否开启
 */
- (BOOL)isBeautifierEnabled;


/**
 * @brief 开启或关闭美颜功能, 并设置美颜效果参数
 * @param enable
 * - YES 开启美颜功能
 * - NO 关闭美颜功能
 * @param config 美颜效果参数, 详细定义见 {@link AliRtcBeautyConfig}
 * @return
 * - 0 : 成功
 * - < 0 : 失败
 */
- (int)setBeautyEffect:(BOOL)enable config:(AliRtcBeautyConfig *_Nullable)config;

/** @} */

#pragma mark - "视频画面截图"
/**
 * @name 视频画面截图
 * @{
 */

/**
 * @brief 视频截图功能
 * @param userId 用户ID，userId 为nil或者为""代表本地用户
 * @param type 视频流类型，只支持 {@link AliRtcVideoTrack::AliRtcVideoTrackCamera} 和 {@link AliRtcVideoTrack::AliRtcVideoTrackScreen}
 * @return
 * - 0 : 仅代表调用该接口成功，是否获取到截图画面，详细见 {@link AliRtcEngineDelegate::onSnapshotComplete:videoTrack:image:success:}
 * - < 0 : 失败
 * @note 视频截图功能为异步接口, 通过监听 {@link AliRtcEngineDelegate::onSnapshotComplete:videoTrack:image:success:} 回调获取当前截图画面。
 */
- (int)snapshotVideo:(NSString*_Nullable)userId type:(AliRtcVideoTrack)type;

/** @} */

#pragma mark - "媒体扩展信息"
/**
 * @name 媒体扩展信息
 * @{
 */

/**
 * @brief 发送媒体扩展信息
 * @details SDK提供了发送和接收媒体扩展信息的功能，接收端参考 {@link AliRtcEngineDelegate::onMediaExtensionMsgReceived:message:}，使用场景：
 * - 使用媒体扩展信息传递时间戳，计算端到端的网络延迟，或者跟自身其他业务做数据同步
 * - 使用媒体扩展信息传递位控制信息。目前可以传递8 Byte数据，即64位，每一位或几位可以表示控制信息，用于自身业务上的指令传输
 * 
 * @param data 扩展信息内容, 长度限制为最大8字节
 * @param repeatCount 重复次数，代表消息冗余度，用于防止网络丢包导致的消息丢失
 * @return
 * - 0: 成功
 * - <0: 失败
 *      - ERR_INNER(-1): SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
 * 
 * @note 使用媒体扩展信息时需要复用音视频数据通道，因此必须控制自定义消息的发送频率和消息数据长度，使用限制如下：
 * - 每秒最多发送30条消息
 * - 为了不影响媒体数据的传输质量，自定义消息体长度限制为8 Byte，可以用来传输时间戳，位控制信息等
 * - sendMediaExtensionMsg函数中repeatCount参数为自定义消息冗余度，若大于1，则会发送多次，防止网络丢包导致的消息丢失，此时房间里的其他人也会收到多次相同的消息，需要去重
 * - 发送的自定义消息，在旁路直播时，房间里的订阅者也一样会收到
 * - 目前H5端不支持发送和接收媒体扩展信息
 */
- (int)sendMediaExtensionMsg:(NSData *_Nonnull)data repeatCount:(int)repeatCount;

/**
 * @brief 添加水印
 * @details SDK提供了添加水印的功能，适用于推送屏幕流或者相机流场景
 * @param track 视频流类型，只支持 {@link AliRtcVideoTrack::AliRtcVideoTrackCamera} 和 {@link AliRtcVideoTrack::AliRtcVideoTrackScreen}
 * @param imageUrl png 文件路径
 * @param config 水印配置 详细定义见 {@link AliRtcWatermarkConfig}
 * @return
 * - 0 : 成功
 * - -1 : 失败
 * @note 目前水印图片仅仅支持png格式
 */
- (int)addVideoWatermark:(AliRtcVideoTrack)track image:(NSString*_Nonnull)imageUrl config:(AliRtcWatermarkConfig *_Nullable)config;

/**
 * @brief 去除水印
 * @details SDK提供了清理水印的功能，适用于推送屏幕流或者相机流场景
 * @param track 视频流类型，只支持 {@link AliRtcVideoTrack::AliRtcVideoTrackCamera} 和 {@link AliRtcVideoTrack::AliRtcVideoTrackScreen}
 * @return
 * - 0 : 成功
 * - -1 : 失败
 */
- (int)clearVideoWatermark:(AliRtcVideoTrack)track;

/**
 * @brief 设置上行弱网替代图片
 * @param imageUrl 图片路径
 * @return
 * - 0: 成功
 * - 非0: 失败
 *
 * @note 当遇到弱网时，回调 {@link onPublishStaticVideoFrame:isStaticFrame:} 将触发，并使用该接口设置图片进行推流
 */
- (int)setPublishImage:(NSString*_Nullable)imageUrl;

/** @} */

#pragma mark - "问题上报"
/**
 * @name 问题上报
 * @{
 */

/**
 * @brief SDK问题反馈
 * @param uid 问题用户id (允许为nil)
 * @param channelId 问题频道id (允许为nil)
 * @param description 问题描述(支持中英文, 必填)
 * @param type 问题类型，参考 {@link AliRtcFeedbackType}
 * @param timeStamp 问题发生的时间戳 (Unix时间戳，大致时间，无需特别精确，可以为0)
 * @note 该接口在入会前、会中、离会后均可以调用，推荐会中或者离会前调用，尽可能带上所有参数信息
 */
- (void)postFeedbackWithUid:(NSString *_Nullable)uid channleId:(NSString *_Nullable)channelId description:(NSString *_Nonnull)description type:(AliRtcFeedbackType)type timeStamp:(NSTimeInterval)timeStamp;

/** @} */

#pragma mark - "消息通道"
/**
 * @name 消息通道
 * @{
 */

/**
 * @brief 发送下行通道消息(反馈消息处理结果)
 * @param messageInfo 信息内容
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 接收到下行通道消息 {@link AliRtcEngineDelegate::onDownlinkMessageNotify:} 后，使用该接口发送下行接收反馈消息
 * @note 已废弃使用
 * @deprecated
 */
- (int)sendDownlinkMessageResponse:(AliRtcMessage *_Nonnull)messageInfo;

/**
 * @brief 发送上行通道消息
 * @param messageInfo 信息内容
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 使用该接口发送上行通道消息成功后，接收反馈消息见 {@link AliRtcEngineDelegate::onUplinkMessageResponse:}
 * @note 已废弃使用
 * @deprecated
 */
- (int)sendUplinkMessage:(AliRtcMessage *_Nonnull)messageInfo;

/** @} */

#pragma mark - "多频道"
/**
 * @name 多频道
 * @{
 */

/**
 * @brief 创建子频道
 * @param delegate delegate
 * @param extras extras [可以为空 @""]，参考文档：[extras参数配置说明](https://help.aliyun.com/document_detail/200048.html)。
 * @note 创建的子频道实例，需要通过 {@link destroyChannel} 进行释放
 * @return 成功返回子频道实例，失败返回nil
 */
- (AliRtcEngine *_Nullable)createChannelWithDelegate:(id<AliRtcEngineDelegate>_Nonnull)delegate extras:(NSString *_Nullable)extras;

/**
 * @brief 销毁子频道
 * @details 使用 {@link joinChannel:name:onResultWithUserId:} 加入的是主频道，不需要调用destroyChannel销毁
 */
- (void)destroyChannel;

/** @} */

#pragma mark - "旁路转推"
/**
 * @name 旁路转推
 * @{
 */

/**
 * @brief 开启旁路直播
 * @details SDK提供了开启旁路直播的功能，可以把实时音视频流经过混流、混音处理转为标准直播流并推送至指定CDN供应商
 * @param streamURL 推流地址
 * @param trancoding 推流所需参数 详细定义见 {@link AliRtcLiveTranscodingParam}
 * @return
 * - 0 : 成功
 * - 非0 : 失败
 *   - ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
 *   - 其他 : 返回值参考官网错误码
 */
- (int)startPublishLiveStreamWithURL:(NSString *_Nonnull)streamURL liveTranscoding:(AliRtcLiveTranscodingParam *_Nonnull)trancoding;

/**
 * @brief 更新旁路直播相关参数
 * @details SDK提供了更新旁路直播的功能，用于实时更新旁路直播参数
 * @param streamURL 推流地址
 * @param trancoding 推流所需参数 详细定义见 {@link AliRtcLiveTranscodingParam}
 * @return
 * - 0 : 成功
 * - 非0 : 失败
 *   - ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
 *   - 其他 : 返回值参考官网错误码
 */
- (int)updatePublishLiveStreamWithURL:(NSString *_Nonnull)streamURL liveTranscoding:(AliRtcLiveTranscodingParam *_Nonnull)trancoding;

/**
 * @brief 停止旁路直播
 * @details SDK提供了停止旁路直播相关参数的功能
 * @param streamURL 推流地址
 * @return
 * - 0 : 成功
 * - 非0 : 失败
 *   - ERR_INNER(-1) : SDK内部错误，可能的情况为SDK未初始化或者SDK销毁后调用
 *   - 其他 : 返回值参考官网错误码
 */
- (int)stopPublishLiveStreamWithURL:(NSString *_Nonnull)streamURL;

/**
* @brief 获得旁路直播状态
* @param streamURL 推流地址
* @return AliRtcLiveTranscodingState
*/
- (AliRtcLiveTranscodingState)GetPublishLiveStreamStateWithURL:(NSString *_Nonnull)streamURL;

#pragma mark - "跨频道转推"
/**
 * @name 跨频道转推
 * @{
 */

/**
 * @brief 开启跨频道转推
 * @details 普通情况下，一个主播只可以在一个频道内推拉流，该接口可以实现跨频道能力，支持主播（在A频道）将A频道的流推送到B频道，B频道相当于一个新主播入会并推流，对应的入会和推流回调依然会回调，与主播直接加入B频道行为一致。
 * @details 如果两个频道内的两个主播互相向对应的频道进行跨频道转推，就可以实现主播间的跨频道连麦，典型场景如：两个直播间的主播PK功能。如下图示例：
 * <pre>
 *                  channel-A                     channel-B
 *               ---------------                ---------------
 *  跨频道转发前: |  主播 A       |              |  主播 B        |
 *              |  观众 U1 U2   |              |  观众 U3 U4    |
 *               ---------------                ---------------
 *
 *                  channel-A                     channel-B
 *               ---------------                ---------------
 *  跨频道转发后: |  主播 A B     |              |  主播 B A      |
 *              |  观众 U1 U2   |              |  观众 U3 U4    |
 *               ---------------                ---------------
 * </pre>
 * @param configuration 频道配置信息 {@link AliRtcChannelRelayConfiguration}
 * @return
 * - 0: 成功
 * - <0: 失败
 * @note 发起跨频道转推需要满足三个条件
 * - 会议模式为互动模式或者低延迟互动模式
 * - 必须是主播角色
 * - 必须在会议中
 */
- (int)startChannelRelay:(AliRtcChannelRelayConfiguration *_Nonnull)configuration;

/**
 * @brief 更新跨频道转推
 * @param configuration 频道配置信息 {@link AliRtcChannelRelayConfiguration}
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)updateChannelRelay:(AliRtcChannelRelayConfiguration *_Nonnull)configuration;

/**
 * @brief 停止跨频道转推
 * @return
 * - 0: 成功
 * - <0: 失败
 */
- (int)stopChannelRelay;

/**
 * @brief 设置视频流属性
 * @param track 视频流类型，详细见 {@link AliRtcVideoTrack}
 * @param attr 视频流属性
 * @note 已废弃使用。
 */
- (void)setPublishVideoStreamAttribute:(AliRtcVideoTrack)track attr:(NSString *_Nullable)attr;

/**
 * @brief 开启/关闭内置加解密功能：需要在入会前调用
 * @param enable 是否开启
 * @return
 * - 0 : 成功
 * - 非0 : 失败
 */
- (int)enableEncryption:(BOOL)enable;

#pragma mark - "虚拟背景"

/**
 * @brief 开启/关闭虚拟背景替换功能
 * @details 需要集成虚拟背景插件，虚拟背景简介及下载详见[官网组件文档](https://help.aliyun.com/document_detail/260223.html) ；
 * @param enable 是否开启；
 * @param path 虚拟背景本地图片路径，支持JPG，PNG 格式；
 * @param model 背景图缩放模式，裁剪或缩放；
 * - AliRtcBokehScaleModelCrop: 等比裁剪，当背景图像宽高比和视频数据宽高比不一致时, 为了保持等比例缩放, 会将背景图像裁剪到视频比例, 超出部分背景图片内容将会丢失；
 * - AliRtcBokehScaleModelFill: 填充黑边，当背景图像宽高比和视频数据宽高比不一致时, 为了保持等比例缩放， 会对背景进行黑边填充，背景图片内容会全部保留；
 * @return
 * - 0: 成功
 * - < 0: 失败 详见 {@link AliRtcPluginErrorCode}；
 *   - AliRtcPluginErrorLoadError：未进行官网组件集成，详见[虚拟背景集成文档](https://help.aliyun.com/document_detail/254861.html) ；
 *   - AliRtcPluginErrorInitError： 参数错误，请检查图片路径地址；
 *
 * @note
 * - 支持平台详见[官网发布日志](https://help.aliyun.com/document_detail/261183.html) ；
 * - 可重复调用，背景图及缩放模式与之前设置不一致，会进行实时更新；
 * - 与背景虚化为替换关系，如开启虚拟背景开关后再次开启背景虚化，则只有背景虚化效果；
*/
- (int)enableBackgroundExchange:(BOOL)enable imagePath:(NSString *_Nonnull)path scalMode:(AliRtcBokehScaleModel)model;

/**
 * @brief 开启/关闭虚拟背景虚化功能
 * @details 需要集成虚拟背景插件，虚拟背景简介及下载详见[官网组件文档](https://help.aliyun.com/document_detail/260223.html) ；
 *  需要下载及集成虚拟背景插件，背景替换与背景虚化不可同时使用，如开启虚拟背景开关后再次开启背景虚化，则只有背景虚化效果；
 * @param enable 是否开启；
 * @param blurDegree  虚化程度 取值范围 [0-100]；
 * @return
 * - 0: 成功
 * - < 0: 失败 详见 {@link AliRtcPluginErrorCode}；
 *   - AliRtcPluginErrorLoadError：未进行官网组件集成，详见[虚拟背景集成文档](https://help.aliyun.com/document_detail/254861.html) ；
 *   - AliRtcPluginErrorInitError： 参数错误，请检查虚化程度取值；
 *
 * @note
 * - 支持平台详见[官网发布日志](https://help.aliyun.com/document_detail/261183.html) ；
 * - 虚化程度范围  [0-100]；
 * - 可重复调用，虚化值如果与之前设置不一致，会进行实时更新；
 * - 与虚拟背景为替换关系，如开启背景虚化开关后再次开启虚拟背景，则只有虚拟背景效果；
*/
- (int)enableBackgroundBlur:(BOOL)enable blurDegree:(uint32_t)blurDegree;


/** @} */

@end

/** @} AliRtc_ios AliRtcEngine */
