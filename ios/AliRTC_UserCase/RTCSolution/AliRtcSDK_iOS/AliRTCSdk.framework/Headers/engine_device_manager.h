#ifndef engine_device_manager_h
#define engine_device_manager_h

#include "engine_define.h"
#include "engine_utils.h"

namespace AliRTCSdk
{

    /**
     * @defgroup AliRtcDef_cpp 关键类型定义
     * AliRtc 关键类型定义
     * @{
     */

    /**
    * @brief 设备连接类型
    */
    typedef enum {
        AliEngineDeviceTransportTypeUnknown         = 0,
        AliEngineDeviceTransportTypeBuiltIn         = 1,
        AliEngineDeviceTransportTypeBluetooth       = 2,
        AliEngineDeviceTransportTypeUSB             = 3,
        AliEngineDeviceTransportTypeAggregate       = 4,
        AliEngineDeviceTransportTypeVirtual         = 5,
        AliEngineDeviceTransportTypePCI             = 6,
        AliEngineDeviceTransportTypeFireWire        = 7,
        AliEngineDeviceTransportTypeBluetoothLE     = 8,
        AliEngineDeviceTransportTypeHDMI            = 9,
        AliEngineDeviceTransportTypeDisplayPort     = 10,
        AliEngineDeviceTransportTypeAirPlay         = 11,
        AliEngineDeviceTransportTypeAVB             = 12,
        AliEngineDeviceTransportTypeThunderbolt     = 13
    } AliEngineDeviceTransportType;

    /**
     * @brief 设备信息
     */
    typedef struct {
        String deviceName;
        String deviceID;
        AliEngineDeviceTransportType deviceTransportType;
    } AliEngineDeviceInfo;

    /**
     * @}
     */

    /**
     * @brief 设备列表
    */
    class ALI_RTC_API AliEngineDeviceInfoList {
    public:
      virtual unsigned int GetCount() = 0;
      virtual AliEngineDeviceInfo GetDeviceInfo(unsigned int index) = 0;
      virtual void Release() = 0;
    };

    /**
     * @defgroup AliEngine AliEngine
     * AliRtc 核心接口类
     * @{
     */

    /**
     * @brief 音频设备相关功能
    */
    class ALI_RTC_API IAliEngineAudioDeviceManager
    {
    public:
      /**
       * @brief 获取系统中的录音设备列表
      */
      virtual AliEngineDeviceInfoList* GetAudioCaptureList() = 0;

      /**
       * @brief 获取使用的录音设备名称
       * @return 当前音频采集设备名称
      */
      virtual String GetCurrentAudioCaptureName() = 0;

      /**
       * @brief 获取使用的录音设备ID
       * @return 当前音频采集设备ID
      */
      virtual String GetCurrentAudioCaptureID() = 0;

      /**
       * @brief 选择录音设备名称
       * @param captureName 音频采集设备名称
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentAudioCaptureName(const char* captureName) = 0;

      /**
       * @brief 选择录音设备ID
       * @param captureID 音频采集设备ID
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentAudioCaptureID(const char* captureID) = 0;

      /**
       * @brief 获取系统中的扬声器列表
       * @return 音频播放设备列表
      */
      virtual AliEngineDeviceInfoList* GetAudioPlayerList() = 0;

      /**
       * @brief 获取当前使用的扬声器名称
       * @return 当前音频播放设备名
      */
      virtual String GetCurrentAudioPlayerName() = 0;

      /**
       * @brief 获取当前使用的扬声器ID
       * @return 当前音频播放设备ID
      */
      virtual String GetCurrentAudioPlayerID() = 0;

      /**
       * @brief 选择扬声器名称
       * @param playerName 音频播放设备名称
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentAudioPlayerName(const char* playerName) = 0;

      /**
       * @brief 选择扬声器ID
       * @param playerID 音频播放设备ID
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentAudioPlayerID(const char* playerID) = 0;

      /**
       * @brief 设置音频采集设备音量，音量范围[0, 100]
       * @param volume 音量值
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetRecordingDeviceVolume(int volume) = 0;

      /**
       * @brief 获取音频采集设备音量
       * @return
       * - >=0: 音量
       * - <0: 失败
      */
      virtual int GetRecordingDeviceVolume() = 0;

      /**
       * @brief 设置音频播放设备音量，音量范围[0, 100]
       * @param volume 音量值
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetPlaybackDeviceVolume(int volume) = 0;

      /**
       * @brief 获取音频播放设备音量
       * @return 设备音量
      */
      virtual int GetPlaybackDeviceVolume() = 0;
        
      /**
       * @brief 静音音频采集设备
       * @param mute 是否静音
       * - true: 设备设置为静音
       * - false: 设备设置为不静音
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetRecordingDeviceMute(bool mute) = 0;
 
      /**
        * @brief 获取音频采集设备静音状态
        * @return
        * - true：已静音状态
        * - false: 非静音状态
      */
      virtual bool GetRecordingDeviceMute() = 0;
 
      /**
        * @brief 静音音频播放设备
        * @param mute 是否静音
        * - true: 设备设置为静音
        * - false: 设备设置为不静音
        * @return
        * - 0: 成功
        * - 非0: 失败
      */
      virtual int SetPlaybackDeviceMute(bool mute) = 0;
 
      /**
        * @brief 获取音频播放设备静音状态
        * @return
        * - true：已静音状态
        * - false: 非静音状态
      */
      virtual bool GetPlaybackDeviceMute() = 0;

      /**
       * @brief 开始测试音频采集设备
       * @param deviceName 音频采集设备名称
       * @param callbackInterval 音量回调频率(毫秒，默认值200毫秒)
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 开始测试后音量信息通过 {@link AliEngineEventListener::OnAudioDeviceRecordLevel} 回调返回
       */
      virtual int StartTestAudioRecordByName(const char *deviceName, int callbackInterval = 0) = 0;

      /**
       * @brief 开启麦克风设备测试(按设备id)
       * @param deviceId 设备id
       * @param callbackInterval 音量回调频率(毫秒，默认值200毫秒)
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 开始测试后音量信息通过 {@link AliEngineEventListener::OnAudioDeviceRecordLevel} 回调返回
       */
      virtual int StartTestAudioRecordById(const char * deviceId, int callbackInterval = 0) = 0;

      /**
       * @brief 停止测试音频采集设备
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 请在 {@link AliEngine::JoinChannel} 之前调用
       */
      virtual int StopTestAudioRecord() = 0;

      /**
       * @brief 开始测试音频播放设备
       * @param deviceName 音频播放设备名称
       * @param filePath 音频文件路径
       * @param callbackInterval 音量回调频率(毫秒，默认值200毫秒)
       * @param loopCycles 重复播放次数， -1为循环播放
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 开始测试后音量信息通过 {@link AliEngineEventListener::OnAudioDevicePlayoutLevel} 回调返回
       */
      virtual int StartTestAudioPlayoutByName(const char* deviceName,
        const char* filePath,
        int callbackInterval = 0,
        int loopCycles = 0) = 0;

      /**
       * @brief 开启扬声器设备测试(按设备id)
       * @param deviceId 设备ID
       * @param filePath 测试wave文件绝对路径
       * @param callbackInterval 音量回调频率(毫秒，默认值200毫秒)
       * @param loopCycles 循环播放次数(默认播放一次)
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 开始测试后音量信息通过 {@link AliEngineEventListener::OnAudioDevicePlayoutLevel} 回调返回
       */
      virtual int StartTestAudioPlayoutById(const char* deviceId,
        const char* filePath,
        int callbackInterval = 0,
        int loopCycles = 0) = 0;


      /**
       * @brief 停止测试音频播放设备
       * @return
       * - 0: 成功
       * - 非0: 失败
       * @note 请在 {@link AliEngine::JoinChannel} 之前调用
      */
      virtual int StopTestAudioPlayout() = 0;

      /**
       * @brief 释放IAliEngineAudioDeviceManager资源
      */
      virtual void Release() = 0;

    protected:
      virtual ~IAliEngineAudioDeviceManager() {}
    };

    /**
     * @brief 视频设备相关功能
    */
    class ALI_RTC_API IAliEngineVideoDeviceManager
    {
    public:
      /**
       * @brief 获取摄像头列表
      */
      virtual AliEngineDeviceInfoList* GetCameraList() = 0;

      /**
       * @brief 获取当前使用的摄像头名称
      */
      virtual String GetCurrentCameraName() = 0;

      /**
       * @brief 获取当前使用的摄像头ID
      */
      virtual String GetCurrentCameraID() = 0;

      /**
       * @brief 选择摄像头名称
       * @param cameraName 摄像头名称
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentCameraName(const char* cameraName) = 0;

      /**
       * @brief 选择摄像头ID
       * @param cameraID 摄像头ID
       * @return
       * - 0: 成功
       * - 非0: 失败
      */
      virtual int SetCurrentCameraID(const char* cameraID) = 0;

      /**
       * @brief 释放IAliEngineVideoDeviceManager资源
      */
      virtual void Release() = 0;

    protected:
      virtual ~IAliEngineVideoDeviceManager() {}
    };

    /**
     * @}
     */
    
}

#endif /* engine_device_manager_h */
