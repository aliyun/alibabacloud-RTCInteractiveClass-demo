//
//  AliRtcInterrativeEngineDelegate.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AliRtcInterrativeEngineDelegate <NSObject>

/// 远端用户下线通知
/// @param uid 用户id
- (void)onRemoteUserOffLineNotify:(NSString *)uid;

/// 远端用户上线通知
/// @param uid 用户id
- (void)onRemoteUserOnLineNotify:(NSString *)uid;

/// 自己上麦通知
/// @param errorCode 结果
- (void)onEnterSeatResult:(int)errorCode;

/// 自己下线通知
/// @param errorCode 结果
- (void)onLeaveSeatResult:(int)errorCode;

/// 房间被销毁通知
- (void)onRoomdestroy;

/**
* @brief 如果engine出现warning，通过这个回调通知app
* @param warn  Warning type
*/
- (void)onOccurWarning:(int)warn;
/**
* @brief 如果engine出现严重error，通过这个回调通知app
* @param error  错误类型
*/
- (void)onSDKError:(int)error;

/**
* @brief 加入频道结果
* @param result 加入频道结果，成功返回0，失败返回错误码
* @param authInfo 鉴权信息 成功返回，失败返回nil
* @note 此回调等同于joinChannel接口的block，二者择一处理即可
*/
- (void)onJoinChannelResult:(int)result authInfo:(AliRtcAuthInfo *)authInfo;

/**
* @brief 离开频道结果
* @param result 离开频道结果，成功返回0，失败返回错误码
* @note 调用leaveChannel接口后返回，如果leaveChannel后直接调用destroy，将不会收到此回调
*/
- (void)onLeaveChannelResult:(int)result;

/**
* @brief 当远端用户的流发生变化时，返回这个消息
* @note 远方用户停止推流，也会发送这个消息
*/
- (void)onRemoteTrackAvailableNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack;

/**
 * @brief 用户muteAudio通知
 * @param uid 执行muteAudio的用户
 * @param isMute YES:静音 NO:未静音
 */
- (void)onUserAudioMuted:(NSString *)uid audioMuted:(BOOL)isMute;

/**
 * @brief 用户muteVideo通知
 * @param uid 执行muteVideo的用户
 * @param isMute YES:推流黑帧 NO:正常推流
 */
- (void)onUserVideoMuted:(NSString *)uid videoMuted:(BOOL)isMute;

/**
 * @brief 网络质量变化时发出的消息
 * @param uid 网络质量发生变化的uid
 * @param upQuality  上行网络质量
 * @param downQuality  下行网络质量
 * @note 当网络质量发生变化时触发，uid为@""时代表self的网络质量变化
 */
- (void)onNetworkQualityChanged:(NSString *)uid
               upNetworkQuality:(AliRtcNetworkQuality)upQuality
             downNetworkQuality:(AliRtcNetworkQuality)downQuality;

/**
 * @brief 订阅的音频音量，语音状态和uid
 * @param array 表示回调用户音量信息数组，包含用户uid,语音状态以及音量，uid为"0"表示本地说话人。
 * @param totalVolume 混音后的总音量，范围[0,255]。在本地用户的回调中，totalVolume;为本地用户混音后的音量；在远端用户的回调中，totalVolume; 为所有说话者混音后的总音量
 */
- (void)onAudioVolumeCallback:(NSArray <AliRtcUserVolumeInfo *> *_Nullable)array totalVolume:(int)totalVolume;


@end

NS_ASSUME_NONNULL_END
