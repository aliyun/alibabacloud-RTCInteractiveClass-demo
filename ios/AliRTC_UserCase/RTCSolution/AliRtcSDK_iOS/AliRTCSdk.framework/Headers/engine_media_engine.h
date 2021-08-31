#ifndef engine_media_engine_h
#define engine_media_engine_h

#include "engine_define.h"

namespace AliRTCSdk
{

    /**
     * @defgroup AliRtcDef_cpp 关键类型定义
     * AliRtc 关键类型定义
     * @{
     */

    /**
     * @brief 音频track的类型
    */
    typedef enum {
      AliEngineAudioTrackNo = 0,
      AliEngineAudioTrackMic = 1,
      AliEngineAudioTrackEnd = 0xffffffff
    } AliEngineAudioTrack;

    /**
     * @brief 视频流类型
     */
    typedef enum {
        /** 无视频流 */
        AliEngineVideoTrackNo     = 0,
        /** 相机流 */
        AliEngineVideoTrackCamera = 1,
        /** 屏幕共享流 */
        AliEngineVideoTrackScreen = 2,
        /** 相机流和屏幕共享流 */
        AliEngineVideoTrackBoth   = 3,
    } AliEngineVideoTrack;


    /**
     * @brief 相机流类型
     */
    typedef enum {
      AliEngineVideoStreamTypeNone = 0,
      AliEngineVideoStreamTypeHigh = 1,
      AliEngineVideoStreamTypeLow = 2,
    } AliEngineVideoStreamType;

    /**
     * @brief 视频数据源
     */
    typedef enum {
      AliEngineVideoSourceCamera = 0,
      AliEngineVideoSourceScreenShare = 1,
      AliEngineVideosourceTypeMax,
    } AliEngineVideoSource;

    /**
     * @brief 录制视频数据源
    */
    typedef enum {
      /** 录制相机流视频 */
      AliEngineVideoRecordSourceCamera = 0,
      /** 录制屏幕流视频 */
      AliEngineVideoRecordSourceScreenShare = 1,
      /** 录制相机和屏幕流视频 */
      AliEngineVideoRecordSourceBoth = 2,
      /** 枚举边界（不允许使用） */
      AliEngineVideoRecordSourceTypeMax,
    } AliEngineVideoRecordSource;

    /**
     * @brief 视频数据类型
     */
    typedef enum {
        AliEngineVideoFormatUnknow  = -1,
        AliEngineVideoFormatBGRA    = 0,
        AliEngineVideoFormatI420    = 1,
        AliEngineVideoFormatNV21    = 2,
        AliEngineVideoFormatNV12    = 3,
        AliEngineVideoFormatRGBA    = 4,
        AliEngineVideoFormatI422    = 5,
        AliEngineVideoFormatARGB    = 6,
        AliEngineVideoFormatABGR    = 7,
        AliEngineVideoFormatRGB24   = 8,
        AliEngineVideoFormatBGR24   = 9,
        AliEngineVideoFormatRGB565  = 10,
        AliEngineVideoFormatTextureOES  = 11,
        AliEngineVideoFormatTexture2D  = 12,
        AliEngineVideoFormatH264  = 13,
    } AliEngineVideoFormat;

    /**
     * @brief 视频数据格式
     */
    typedef enum {
        AliEngineBufferTypeRawData          = 0,
        AliEngineBufferTypeTexture,
    } AliEngineBufferType;


    /**
     * @brief 视频纹理格式
     */
    typedef enum {
      AliEngineTextureTypeUnknown = -1,
      AliEngineTextureTypePre = 0,
      AliEngineTextureTypePost = 1,
    } AliEngineTextureType;

    /**
     * @brief 视图显示模式
     */
    typedef enum {
        /** 自动模式 */
        AliEngineRenderModeAuto     = 0,
        /** 拉伸平铺模式 ，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频拉伸到推流设置的比例，画面会变形*/
        AliEngineRenderModeStretch  = 1,
        /** 填充黑边模式，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频上下或者左右填充黑边 */
        AliEngineRenderModeFill     = 2,
        /** 裁剪模式，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频宽或者高进行裁剪，画面内容会丢失 */
        AliEngineRenderModeCrop     = 3,
        /** 已废弃 */
        AliEngineRenderModeScroll   = 4,
        /** 沿用之前的显示模式 */
        AliEngineRenderModeNoChange = 99,
    } AliEngineRenderMode;

    /**
     * @brief 视频旋转角度
     */
    typedef enum {
        /** 沿用之前的旋转角度 */
      AliEngineRotationModeNoChange = -1,
        /** 0 */
      AliEngineRotationMode_0 = 0,
        /** 90 */
      AliEngineRotationMode_90 = 90,
        /** 180 */
      AliEngineRotationMode_180 = 180,
        /** 270 */
      AliEngineRotationMode_270 = 270,
    } AliEngineRotationMode;

    /**
     * @brief 音频声道类型
    */
    typedef enum {
      /** 单声道 */
      AliEngineMonoAudio = 1,
      /** 双声道 */
      AliEngineStereoAudio = 2,
    } AliEngineAudioNumChannelType;

    /**
     * @brief 音频采样率类型
     */
    typedef enum {
      /** 8000采样率 */
      AliEngineAudioSampleRate_8000 = 0,
      /** 11025采样率 */
      AliEngineAudioSampleRate_11025 = 1,
      /** 16000采样率 */
      AliEngineAudioSampleRate_16000 = 2,
      /** 22050采样率 */
      AliEngineAudioSampleRate_22050 = 3,
      /** 32000采样率 */
      AliEngineAudioSampleRate_32000 = 4,
      /** 44100采样率 */
      AliEngineAudioSampleRate_44100 = 5,
      /** 48000采样率 */
      AliEngineAudioSampleRate_48000 = 6,
    } AliEngineAudioSampleRate;

    /**
     * @brief 音频数据源类型
     */
    typedef enum {
      /** 本地推流的音频数据 */
      AliEngineAudiosourcePub = 0,
      /** 本地拉流混音的音频数据 */
      AliEngineAudiosourceSub = 1,
      /** 本地采集的音频数据 */
      AliEngineAudiosourceRawData = 2,
    } AliEngineAudioSource;

    /**
     * @brief 视频数据输出位置
     */
    typedef enum {
      AliEnginePositionPostCapture = 1 << 0,
      AliEnginePositionPreRender = 1 << 1,
      AliEnginePositionPreEncoder = 1 << 2,
    } AliEngineVideoObserPosition;

    /**
     * @brief 视频输出宽度对齐方式
     * AliEngineAlignmentDefault：保持原有视频宽度
     * AliEngineAlignmentEven：宽度偶数对齐
     * AliEngineAlignment4：宽度是4的倍数
     * AliEngineAlignment8：宽度是8的倍数
     * AliEngineAlignment16：宽度是16的倍数
     */
    typedef enum {
      AliEngineAlignmentDefault = 0,
      AliEngineAlignmentEven = 1,
      AliEngineAlignment4 = 2,
      AliEngineAlignment8 = 3,
      AliEngineAlignment16 = 4,
    } AliEngineVideoObserAlignment;

    /**
     * @brief 音频裸数据
     */
    typedef struct AliEngineAudioRawData {
        /** 音频数据 */
        void* dataPtr       = 0;
        /** 采样点数（单个声道） */
        int numOfSamples    = 0;
        /** 每个采样点的字节数 */
        int bytesPerSample  = 0;
        /** 声道数 */
        int numOfChannels   = 0;
        /** 采样率 */
        int sampleRate      = 0;
        /** 每秒采样点数 */
        int samplesPerSec   = 0;
    } AliEngineAudioRawData;

    /**
     * @brief 视频裸数据
     */
    typedef struct AliEngineVideoRawData {
        AliEngineVideoFormat format = AliEngineVideoFormatUnknow;
        AliEngineBufferType type    = AliEngineBufferTypeRawData;
        long dataLength  = 0;
        void* pixelBuffer = 0;
        void* dataPtr    = 0;
        void* dataYPtr   = 0;
        void* dataUPtr   = 0;
        void* dataVPtr   = 0;
        int strideY      = 0;
        int strideU      = 0;
        int strideV      = 0;
        int height       = 0;
        int width        = 0;
        int rotation     = 0;
        int stride       = 0;
        long long timeStamp = 0;
        int textureId    = 0;
        float transformMatrix[16] = {0};    
    } AliEngineVideoRawData;

    /**
     * @}
     */

    /**
     * @defgroup AliEngineCallback 回调及监听
     * AliRtc 回调及监听
     * @{
     */

    /**
     * @brief 音频数据监听接口
     */
    class ALI_RTC_API IAudioFrameObserver {
    public:
      virtual ~IAudioFrameObserver() {}
      /**
       * @brief 本地采集音频数据回调
       * @details 本地麦克风采集到的原始音频数据，{@link IAliEngineMediaEngine::SubscribeAudioData}订阅类型为 AliEngineAudiosourceRawData 时触发此回调
       * @param audioRawData 音频数据，详见{@link AliEngineAudioRawData}
       */
      virtual bool OnRawDataAudioFrame(AliEngineAudioRawData audioRawData) = 0;

      /**
       * @brief 本地推流音频数据回调
       * @details 本地采集并经过音频处理后待编码推流的音频数据，{@link IAliEngineMediaEngine::SubscribeAudioData}订阅类型为 AliEngineAudiosourcePub 时触发此回调
       * @param audioRawData 音频数据，详见{@link AliEngineAudioRawData}
       */
      virtual bool OnPublishAudioFrame(AliEngineAudioRawData audioRawData) = 0;

      /**
       * @brief 本地订阅音频数据回调
       * @details 远端所有用户混音后待播放的音频数据，{@link IAliEngineMediaEngine::SubscribeAudioData}订阅类型为 AliEngineAudiosourceSub 时触发此回调
       * @param audioRawData 音频数据，详见{@link AliEngineAudioRawData}
       */
      virtual bool OnSubscribeAudioFrame(AliEngineAudioRawData audioRawData) = 0;
        
      /**
       * @brief 混音前每一路远端用户的音频数据回调
       * @details 混音前每一路远端用户的音频数据，{@link IAliEngineMediaEngine::SubscribeAudioData}订阅类型为 AliEngineAudiosourceSub 时触发此回调
       * @param uid 远端用户ID
       * @param audioRawData 音频数据，详见{@link AliEngineAudioRawData}
       */
      virtual bool OnPlaybackAudioFrameBeforeMixing(const char *uid, AliEngineAudioRawData audioRawData) = 0;
    };

    /**
     * @brief 视频数据对象
     */
    class ALI_RTC_API IVideoFrameObserver {
    public:
      virtual ~IVideoFrameObserver() {}
      /**
       * @brief 订阅的本地采集视频数据回调
       * @param videoSource 视频数据源
       * @param videoRawData 视频裸数据
       * @return
       * - true: 需要写回SDK（只对I420和native(ios/mac)有效）
       * - false: 不需要写回SDK
       */
      virtual bool OnCaptureVideoSample(AliEngineVideoSource videoSource, AliEngineVideoRawData &videoRawData) = 0;

      /**
       * @brief 订阅的本地编码前视频数据回调
       * @param videoSource 视频数据源
       * @param videoRawData 视频裸数据
       * @return
       * - true: 需要写回SDK（只对I420和native(ios/mac)有效）
       * - false: 不需要写回SDK
       */
      virtual bool OnPreEncodeVideoSample(AliEngineVideoSource videoSource, AliEngineVideoRawData &videoRawData) = 0;

      /**
       * @brief 订阅的远端视频数据回调
       * @param uid 用户ID
       * @param videoSource 视频数据源
       * @param videoRawData 视频裸数据
       * @return
       * - true: 需要写回SDK（只对I420和native(ios/mac)有效）
       * - false: 不需要写回SDK
       */
      virtual bool OnRemoteVideoSample(const char *uid,
        AliEngineVideoSource videoSource,
        AliEngineVideoRawData &videoRawData) = 0;

      /**
       * @brief 视频输出数据是否由用户来获取
       * @return
       * - true: 用户获取
       * - false（默认）: sdk通过回调向外抛出
       */ 
      virtual bool GetIfUserFetchObserverData() {return false;}
  
      /**
       * @brief 视频数据输出格式
       * @return 期望视频输出格式
       */ 
      virtual AliEngineVideoFormat GetVideoFormatPreference() { return AliEngineVideoFormatI420; }

      /**
       * @brief 视频输出宽度对齐方式
       * @return 期望视频输出宽度对齐方式
       */ 
      virtual AliEngineVideoObserAlignment GetVideoAlignment() { return AliEngineAlignmentDefault; }

      /**
       * @brief 视频数据输出内容
       * @return 期望视频输出内容，参考 {@link AliEngineVideoObserPosition}
       */
      virtual uint32_t GetObservedFramePosition() { return static_cast<uint32_t>(AliEnginePositionPostCapture | AliEnginePositionPreRender); };

      /**
       * @brief 视频输出数据是否需要镜像
       * @return true, 镜像；false（默认）, 不镜像
       */
      virtual bool GetObserverDataMirrorApplied() {return false;}

      /**
       * @brief 拉流视频数据是否平滑输出
       * @return 
       * - true: 平滑输出
       * - false（默认）: 直接输出，只在 GetIfUserFetchObserverData 为false时有效
       */
      virtual bool GetSmoothRenderingEnabled() {return false;}
    };


    /**
     * @brief OpenGL纹理数据观测器
     */
    class ALI_RTC_API IVideoTextureObserver {
    public:
      virtual ~IVideoTextureObserver() {}
      /**
       * @brief OpenGL上下文创建回调
       * @param context OpenGL上下文
       * @note 该回调是在SDK内部OpenGL上下文创建的时候触发
       */
      virtual void OnTextureCreate(void* context) {}

      /**
       * @brief OpenGL纹理更新回调
       * @param textureId OpenGL纹理ID
       * @param width OpenGL纹理高
       * @param height OpenGL纹理宽
       * @param videoRawData 视频帧数据，详见 {@link AliRTCSdk::AliEngineVideoRawData}
       * @return OpenGL纹理ID
       * @note
       * - 该回调会在每一帧视频数据上传到OpenGL纹理之后触发，当外部注册了OpenGL纹理数据观测器，在该回调中可以对纹理进行处理，并返回处理后的纹理ID
       * - 注意该回调返回值必须为有效的纹理ID，如果不做任何处理必须返回参数textureId
       */
      virtual int OnTextureUpdate(int textureId, int width, int height, AliEngineVideoRawData &videoRawData) { return 0; }

      /**
       * @brief OpenGL上下文销毁回调
       * @note 该回调是在SDK内部OpenGL上下文销毁的时候触发
       */
      virtual void OnTextureDestory() {}
    };

    /**
     * @}
     */

    /**
     * @defgroup AliEngine AliEngine
     * AliRtc 核心接口类
     * @{
     */

    /**
     * @brief 音视频媒体数据相关功能
     */
    class ALI_RTC_API IAliEngineMediaEngine
    {
    public:
      /**
       * 释放IAliEngineMediaEngine资源
       */
      virtual void Release() = 0;

      /**
       * @brief 订阅视频数据输出
       * @param observer 视频数据接收对象
       * @note 输出数据将通过IVideoFrameObserver回调返回
       */
      virtual void RegisterVideoSampleObserver(IVideoFrameObserver* observer) = 0;

      /**
       * @brief 取消订阅视频数据输出
       * @param observer 视频数据接收对象
       */
      virtual void UnRegisterVideoSampleObserver(IVideoFrameObserver* observer) = 0;

      /**
       * @brief 主动获取采集数据
       * @param type 视频流类型 {@link AliRTCSdk::AliEngineVideoTrack}
       * @param videoRaw 数据接收对象
       * @return
       * - true: 成功
       * - false: 失败
       * @note 仅在 {@link IVideoFrameObserver::GetIfUserFetchObserverData} 返回true时有效
       */
      virtual bool GetVideoCaptureData(AliEngineVideoTrack type, AliEngineVideoRawData &videoRaw) = 0;

      /**
       * @brief 主动获取编码前数据
       * @param type 视频流类型 {@link AliRTCSdk::AliEngineVideoTrack}
       * @param videoRaw 数据接收对象
       * @return
       * - true: 成功
       * - false: 失败
       * @note 仅在 {@link IVideoFrameObserver::GetIfUserFetchObserverData} 返回true时有效
       */
      virtual bool GetVideoPreEncoderData(AliEngineVideoTrack type, AliEngineVideoRawData &videoRaw) = 0;

      /**
       * @brief 主动获取拉流数据
       * @param uid 用户ID。从App server分配的唯一标示符
       * @param type 视频流类型 {@link AliRTCSdk::AliEngineVideoTrack}
       * @param videoRaw 数据接收对象
       * @return
       * - true: 成功
       * - false: 失败
       * @note 仅在 {@link IVideoFrameObserver::GetIfUserFetchObserverData} 返回true时有效
       */
      virtual bool GetVideoRenderData(const char *uid,AliEngineVideoTrack type, AliEngineVideoRawData &videoRaw) = 0;

      /**
       * @brief 注册本地相机流视频OpenGL纹理数据观测器
       * @param observer OpenGL纹理数据观测器。非空值，传空调用失败。详见 {@link AliRTCSdk::IVideoTextureObserver}
       * @note
       * - 成功注册本地相机流视频OpenGL纹理数据观测器后，SDK会在捕捉到每个视频帧时，触发你在 IVideoTextureObserver 接口中实现的回调
       * - 该接口只能对本地相机流视频有效
       * - 该接口只适用于Android和iOS平台
       */
      virtual void RegisterLocalVideoTextureObserver(IVideoTextureObserver* observer) = 0;

      /**
       * @brief 取消注册本地相机流视频OpenGL纹理数据观测器
       * @param observer OpenGL纹理数据观测器
       * @note 该接口只适用于Android和iOS平台
       */
      virtual void UnRegisterLocalVideoTextureObserver(IVideoTextureObserver* observer) = 0;

      /**
       * @brief 订阅音频数据输出
       * @param observer 音频数据监听对象实例：{@link IAudioFrameObserver}
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 调用前需要先通过 {@link SetSubscribeAudioNumChannel} / {@link SetSubscribeAudioSampleRate} / {@link SubscribeAudioData} 接口设置需要输出的音频数据参数
       */
      virtual int RegisterAudioFrameObserver(IAudioFrameObserver* observer) = 0;
        
      /**
       * @brief 取消订阅音频数据输出
       * @param observer 音频数据监听对象实例: {@link IAudioFrameObserver}
       */
      virtual void UnRegisterAudioFrameObserver(IAudioFrameObserver* observer) = 0;
      
      /**
       * @brief 订阅音频事件（默认订阅）, 如音频啸叫
       * @return
       * - 0: 成功
       * - 非0: 失败
       */
      virtual int RegisterAudioEventObserver() = 0;
        
      /**
       * @brief 取消订阅音频事件
       */
      virtual void UnRegisterAudioEventObserver() = 0;

      /**
       * @brief 设置输出音频声道数，默认单声道（混音前数据不支持该参数设置）
       * @param audioNumChannel 声道数，必须是 {@link AliEngineAudioNumChannelType}
       * @note 需在 {@link SubscribeAudioData} 前进行设置
       */
      virtual void SetSubscribeAudioNumChannel(AliEngineAudioNumChannelType audioNumChannel) = 0;

      /**
       * @brief 设置输出音频采样率，默认44.1k（混音前数据不支持该参数设置）
       * @param audioSampleRate 采样率，必须是 {@link AliEngineAudioSampleRate}
       * @note 需在 {@link SubscribeAudioData} 前进行设置
       */
      virtual void SetSubscribeAudioSampleRate(AliEngineAudioSampleRate audioSampleRate) = 0;

      /**
       * @brief 订阅音频数据
       * @param audioSource 音频数据源类型，详见 {@link AliEngineAudioSource}
       * @note 订阅音频数据输出前，需先通过 {@link SetSubscribeAudioNumChannel} 与 {@link SetSubscribeAudioSampleRate} 设置输出音频数据参数
       */
      virtual void SubscribeAudioData(AliEngineAudioSource audioSource) = 0;

      /**
       * @brief 取消订阅音频数据
       * @param audioSource 音频数据源类型，详见 {@link AliEngineAudioSource}
       */
      virtual void UnsubscribeAudioData(AliEngineAudioSource audioSource) = 0;

      /**
       * @brief 启用外部视频输入源
       * @param enable
       * - true 开启
       * - false 关闭
       * @param type 流类型，详见 {@link AliRTCSdk::AliEngineVideoTrack}
       * - AliEngineVideoTrackCamera 外部输入视频数据走相机流通道，如果当前相机采集打开中，调用该接口设置enable为true，sdk会替换掉相机采集
       * - AliEngineVideoTrackScreen 外部输入视频数据走屏幕流通道，如果当前屏幕共享采集打开中，调用该接口设置enable为true，sdk会替换掉屏幕共享采集
       * @param renderMode 处理模式，外部输入视频源宽高比和推流profile不一致时，会按照对应的rendermode做对应处理，详见 {@link AliRTCSdk::AliEngineRenderMode}
       * - AliEngineRenderModeAuto 自动（默认），如果外部输入的视频宽高比和推流设置的宽高比不一致时，维持外部输入的视频宽高比，等比例缩放宽高到推流设置的宽高范围内，注意此模式下为了保证原始视频的比例和内容完整性，会导致实际推流的分辨率和设置的不一致
       * - AliEngineRenderModeStretch 拉伸平铺，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频拉伸到推流设置的比例，画面会变形
       * - AliEngineRenderModeFill 填充黑边，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频上下或者左右填充黑边
       * - AliEngineRenderModeCrop 裁剪，如果外部输入的视频宽高比和推流设置的宽高比不一致时，将输入视频宽或者高进行裁剪，画面内容会丢失
       * @return
       * - 0: 成功
       * - 非0: 失败
       */
      virtual int SetExternalVideoSource(bool enable,
        AliEngineVideoTrack type,
        AliEngineRenderMode renderMode) = 0;

      /**
       * @brief 输入视频数据
       * @param frame 帧数据，详见 {@link AliRTCSdk::AliEngineVideoRawData}
       * @param type 流类型，详见 {@link AliRTCSdk::AliEngineVideoTrack}
       * - AliEngineVideoTrackCamera 外部输入视频数据走相机流通道
       * - AliEngineVideoTrackScreen 外部输入视频数据走屏幕流通道
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 如果返回值为errorCode中的AliRtcErrVideoBufferFull，代表当前buffer队列塞满，需要等待后再继续输送数据
       */
      virtual int PushExternalVideoFrame(const AliEngineVideoRawData &frame,
        AliEngineVideoTrack type) = 0;

      /**
      * @brief 设置是否启用外部音频输入推流
      * @param enable true:开启; false:关闭
      * @param sampleRate 采样率 16k 48k...
      * @param channelsPerFrame 声道数 1:单声道; 2:双声道
      * @return
      * - >=0: 成功
      * - <0: 失败
      */
      virtual int SetExternalAudioSource(bool enable,
        unsigned int sampleRate,
        unsigned int channelsPerFrame) = 0;

      /**
       * @brief 输入外部音频数据推流到远端
       * @param data 音频数据buffer
       * @param sampleLen 音频数据buffer长度
       * @param timestamp 时间戳
       * @return 
       * - <0: 表示失败;
       * - 0: 表示成功;
       * - 返回值为 {@link AliEngineErrorAudioBufferFull} 时，需要在间隔投递数据时间长度后再次重试投递
       * @note 为了保证语音连续性，sdk内部会有buffer缓存送进来的音频数据，以每次送10ms数据为例，如果返回 {@link AliEngineErrorAudioBufferFull} 时，说明内部缓冲区已满，建议等待20ms后再重新送当前数据帧；
       */
      virtual int PushExternalAudioFrameRawData(const void * data,
        unsigned int sampleLen,
        double timestamp) = 0;

      /**
       * @brief 设置混音音量
       * @param vol 音量 0-100
       * @return
       * - 0: 成功
       * - 非0: 失败
       */
      virtual int SetExternalAudioPublishVolume(int vol) = 0;

      /**
       * @brief 获取混音音量
       * @return vol 音量
       */
      virtual int GetExternalAudioPublishVolume() = 0;

      /**
      * @brief 设置推流音频是否与麦克风采集音频混合
      * @param mixed 是否混音
      * - true: 混音
      * - false: 完全替换麦克风采集数据
      * @return
      * - 0: 成功
      * - 非0: 失败
      * @note 推流音频包括以下几类：
      * - 外部音频输入推流 {@link IAliEngineMediaEngine::SetExternalAudioSource}
      * - 系统声音采集 {@link AliEngine::EnableSystemAudioRecording}
      * - 伴奏 {@link AliEngine::StartAudioAccompany}
      * - 音效 {@link AliEngine::PlayAudioEffect}
      */
      virtual int SetMixedWithMic(bool mixed) = 0;

      /**
      * @brief 设置是否启用外部输入音频播放
      * @param enable 是否开启
      * - true: 开启
      * - false: 关闭
      * @param sampleRate 采样率 16k 48k...
      * @param channelsPerFrame 声道数 1:单声道; 2:双声道
      * @return
      * - 0: 成功
      * - 非0: 失败
      */
      virtual int SetExteranlAudioRender(bool enable, unsigned int sampleRate, unsigned int channelsPerFrame) = 0;

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
       * - 返回值为 {@link AliEngineErrorAudioBufferFull} 时，需要在间隔投递数据时间长度后再次重试投递
       * @note 为了保证语音连续性，sdk内部会有buffer缓存送进来的音频数据，以每次送10ms数据为例，如果返回{@link AliEngineErrorAudioBufferFull}时，说明内部缓冲区已满，建议等待20ms后再重新送当前数据帧；
       */
      virtual int PushExternalAudioRenderRawData(const void* audioSamples, unsigned int sampleLength, unsigned int sampleRate, unsigned int channelsPerFrame, long long timestamp) = 0;

      /**
       * @brief 设置音频外部播放源音量
       * @param volScal 音量值
       * @return
       * - 0: 成功
       * - 非0: 失败
       */
      virtual int SetExternalAudioRenderVolume(int volScal) = 0;

      /**
       * @brief 获取音频外部播放源音量
       * @return
       * - >=0: 音量值
       * - <0: 失败
       */
      virtual int GetExternalAudioRenderVolume() = 0;

    protected:
      virtual ~IAliEngineMediaEngine() {}
    };

    /**
     * @}
     */
    
}

#endif /* engine_media_engine_h */
