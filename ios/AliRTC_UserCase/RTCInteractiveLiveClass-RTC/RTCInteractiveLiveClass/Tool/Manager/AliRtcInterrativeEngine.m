//
//  AliRtcInterrativeEngine.m
//  LectureHall
//
//  Created by Aliyun on 2020/6/15.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "AliRtcInterrativeEngine.h"
#import "NetworkManager.h"
#import "AppConfig.h"


@interface AliRtcInterrativeEngine()<AliRtcEngineDelegate>

/**
 @brief SDK实例
 */
@property (nonatomic, strong) AliRtcEngine *engine;

@property (nonatomic, strong) AliRtcAuthInfo *rtcAuthInfo;

@end

static dispatch_once_t onceToken;
static AliRtcInterrativeEngine *manager = nil;

@implementation AliRtcInterrativeEngine

+ (AliRtcInterrativeEngine *) sharedInstance{

    dispatch_once(&onceToken, ^{
        manager = [[super allocWithZone:NULL] init];
        
    });
    return manager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    return [AliRtcInterrativeEngine sharedInstance];
}

- (id)copyWithZone:(nullable NSZone *)zone {
    return [AliRtcInterrativeEngine sharedInstance];
}

- (id)mutableCopyWithZone:(nullable NSZone *)zone {
    return [AliRtcInterrativeEngine sharedInstance];
}


/**
 @brief 初始化SDK
 */
- (void)initializeSDK{
    //注意在sdk实例化之前设置
    [AliRtcEngine setH5CompatibleMode:YES];
    // 创建SDK实例，注册delegate，extras可以为空
    _engine = [AliRtcEngine sharedInstance:self extras:@""];
    //使用扬声器
#if TARGET_OS_IOS
    [_engine enableSpeakerphone:YES];
    
    //关闭高清预览
    AliRtcCameraCapturerConfiguration *cameraConfig = [[AliRtcCameraCapturerConfiguration alloc] init];
    cameraConfig.preference = AliRtcCaptureOutputPreferencePerformance;
    cameraConfig.cameraDirection = AliRtcCameraDirectionFront;
    [_engine setCameraCapturerConfiguration:cameraConfig];
    
#endif
    
    //频道模式
    [_engine setChannelProfile:AliRtcInteractivelive];
    //推送次要视频流
    [_engine publishLocalDualStream:YES];
    //设置音量回调频率和平滑系数
    [_engine enableAudioVolumeIndication:331 smooth:3 reportVad:1];
}

+ (void)destroySharedInstance{
    [AliRtcEngine destroy];
    onceToken = 0;
    manager = nil;
}


- (void)login:(NSString *)channel name:(NSString *)name {
    [NetworkManager GET:[kBaseUrl_InteractiveClass stringByAppendingString: @"getRtcAuth"] parameters:@{@"channelId":channel} completionHandler:^(NSString * _Nullable errString, NSDictionary * _Nullable resultDic) {
        if(!errString){
            AliRtcAuthInfo *authInfo = [[AliRtcAuthInfo alloc] init];
            authInfo.appId = resultDic[@"appid"];
            authInfo.userId = resultDic[@"userid"];
            authInfo.channelId = channel;
            authInfo.nonce = resultDic[@"nonce"];
            authInfo.timestamp = [resultDic[@"timestamp"] longLongValue];
            authInfo.token = resultDic[@"token"];
            authInfo.gslb = resultDic[@"gslb"];
            authInfo.agent = resultDic[@"agent"];
            self.rtcAuthInfo = authInfo;
            //设置为观众角色
            [self.engine setClientRole:AliRtcClientRolelive];
            [self.engine joinChannel:authInfo name:name onResult:^(NSInteger errCode, NSString * _Nonnull channel, NSInteger elapsed){}];
        }else {
            //鉴权请求失败
            [self onJoinChannelResult:-1 channel:channel elapsed:0];
        }
       
    }];
}

- (void)logout {
     [self.engine leaveChannel];
}

/// 上麦只需要切换角色
/// 成功的回调是 onUpdateRoleNotifyWithOldRole
- (int)enterSeat {
    return [self.engine setClientRole:AliRtcClientRoleInteractive];
}

//角色变化通知
- (void)onUpdateRoleNotifyWithOldRole:(AliRtcClientRole)oldRole
                              newRole:(AliRtcClientRole)newRole
{
    if (newRole == AliRtcClientRoleInteractive)
    {
        //切换成主播
        if([self.delegate respondsToSelector:@selector(onEnterSeatResult:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate onEnterSeatResult:0];
            });
        }
 
    }else {
        //切换成观众
        if([self.delegate respondsToSelector:@selector(onLeaveSeatResult:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate onLeaveSeatResult:0];
            });
        }
    }
}

///  下麦需要停止推流 成功的回调是 onUpdateRoleNotifyWithOldRole
- (void)leaveSeat {
     [self.engine setClientRole:AliRtcClientRolelive];
}

- (int)muteLocalMic:(BOOL)mute {
    return [self.engine muteLocalMic:mute mode:AliRtcMuteAudioModeDefault];
}

- (int)muteLocalCamera:(BOOL)mute forTrack:(AliRtcVideoTrack)track {
    if (mute) {
        [self.engine stopPreview];
    }else{
        [self.engine startPreview];
    }
    return [self.engine muteLocalCamera:mute forTrack:track];
}

- (int)switchCamera {
#if TARGET_OS_IOS
    return [self.engine switchCamera];
#else
    return 0;
#endif
}

- (int)setRemoteViewConfig:(AliVideoCanvas *)canvas uid:(NSString *)uid forTrack:(AliRtcVideoTrack)track {
    return [self.engine setRemoteViewConfig:canvas uid:uid forTrack:track];
}

- (int)setLocalViewConfig:(AliVideoCanvas *)viewConfig forTrack:(AliRtcVideoTrack)track {
    return [self.engine setLocalViewConfig:viewConfig forTrack:track];
}

- (int)stopPreview {
    return [self.engine stopPreview];
}

- (int)startPreview {
    return [self.engine startPreview];
}

- (void)subscribeRemoteTrack:(NSString *)uid preferMaster:(BOOL)master enable:(BOOL)enable {
    
    [self.engine subscribeRemoteAudioStream:uid sub:enable];
    
    AliRtcVideoStreamType type = master ? AliRtcVideoStreamTypeHigh:AliRtcVideoStreamTypeLow;
    [self.engine setRemoteVideoStreamType:uid type:type];
    [self.engine subscribeRemoteVideoStream:uid track:AliRtcVideoTrackCamera sub:enable];
    [self.engine subscribeRemoteVideoStream:uid track:AliRtcVideoTrackScreen sub:enable];
}
 

- (AliRtcEngine *)engine {
    if (!_engine) {
        [self initializeSDK];
    }
    return _engine;
}
 
- (void)onOccurError:(int)error message:(NSString * _Nonnull)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (error == AliRtcErrSdkInvalidState || error == AliRtcErrIceConnectionHeartbeatTimeout || error == AliRtcErrSessionRemoved ) {
            if ([self.delegate respondsToSelector:@selector(onSDKError:)])
            {
                [self.delegate onSDKError:error];
            }
        }
    });
}

- (void)onOccurWarning:(int)warn message:(NSString * _Nonnull)message
{
    if ([self.delegate respondsToSelector:@selector(onOccurWarning:)])
    {
        dispatch_async(dispatch_get_main_queue(), ^{
             [self.delegate onOccurWarning:warn];
        });
       
    }
}


- (void)onBye:(int)code {
    
    NSLog(@"%d",code);
    
    if (code == 2)
    {
        if ([self.delegate respondsToSelector:@selector(onRoomdestroy)])
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate onRoomdestroy];
            });
        }
    }
}

- (void)onJoinChannelResult:(int)result channel:(NSString *_Nonnull)channel elapsed:(int) elapsed {
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if ([self.delegate respondsToSelector:@selector(onJoinChannelResult:authInfo:)]) {
            [self.delegate onJoinChannelResult:result authInfo:self.rtcAuthInfo];
        }
    });
}

- (void)onLeaveChannelResult:(int)result stats:(AliRtcStats)stats{
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onLeaveChannelResult:)]) {
            [self.delegate onLeaveChannelResult:result];
        }
    });
}

- (void)onRemoteTrackAvailableNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onRemoteTrackAvailableNotify:audioTrack:videoTrack:)]) {
            [self.delegate onRemoteTrackAvailableNotify:uid audioTrack:audioTrack videoTrack:videoTrack];
        }
    });
}

- (void)onAudioSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel{
//    if (newState == AliRtcStatsSubscribed) {
//        dispatch_async(dispatch_get_main_queue(), ^{
//             if ([self.delegate respondsToSelector:@selector(onSubscribeChangedNotify:audioTrack:videoTrack:)]) {
//                 [self.delegate onSubscribeChangedNotify:uid audioTrack:AliRtcAudioTrackMic videoTrack:AliRtcVideoTrackNo];
//             }
//         });
//    }
   
}
 
- (void)onVideoSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel{
//    if (newState == AliRtcStatsSubscribed) {
//    dispatch_async(dispatch_get_main_queue(), ^{
//         if ([self.delegate respondsToSelector:@selector(onSubscribeChangedNotify:audioTrack:videoTrack:)]) {
//             [self.delegate onSubscribeChangedNotify:uid audioTrack:AliRtcAudioTrackMic videoTrack:AliRtcVideoTrackCamera];
//         }
//     });
//    }
}
 
- (void)onScreenShareSubscribeStateChanged:(NSString *_Nonnull)uid oldState:(AliRtcSubscribeState)oldState newState:(AliRtcSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState channel:(NSString *_Nonnull)channel{
//    if (newState == AliRtcStatsSubscribed) {
//    dispatch_async(dispatch_get_main_queue(), ^{
//         if ([self.delegate respondsToSelector:@selector(onSubscribeChangedNotify:audioTrack:videoTrack:)]) {
//             [self.delegate onSubscribeChangedNotify:uid audioTrack:AliRtcAudioTrackMic videoTrack:AliRtcVideoTrackScreen];
//         }
//     });
//    }
}



- (void)onSubscribeChangedNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if ([self.delegate respondsToSelector:@selector(onSubscribeChangedNotify:audioTrack:videoTrack:)]) {
//            [self.delegate onSubscribeChangedNotify:uid audioTrack:audioTrack videoTrack:videoTrack];
//        }
//    });
}

- (void)onUserAudioMuted:(NSString *)uid audioMuted:(BOOL)isMute {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onUserAudioMuted:audioMuted:)]) {
            [self.delegate onUserAudioMuted:uid audioMuted:isMute];
        }
    });
}


- (void)onUserVideoMuted:(NSString *)uid videoMuted:(BOOL)isMute {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onUserVideoMuted:videoMuted:)]) {
            [self.delegate onUserVideoMuted:uid videoMuted:isMute];
        }
    });
}

- (void)onRemoteUserOffLineNotify:(NSString *)uid offlineReason:(AliRtcUserOfflineReason)reason {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onRemoteUserOffLineNotify:)]) {
            [self.delegate onRemoteUserOffLineNotify:uid];
        }
    });
}

- (void)onRemoteUserOnLineNotify:(NSString *)uid elapsed:(int)elapsed{
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onRemoteUserOnLineNotify:)]) {
            [self.delegate onRemoteUserOnLineNotify:uid];
        }
    });
}

- (void)onAudioVolumeCallback:(NSArray<AliRtcUserVolumeInfo *> *)array totalVolume:(int)totalVolume {
        
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onAudioVolumeCallback:totalVolume:)]) {
            [self.delegate onAudioVolumeCallback:array totalVolume:totalVolume];
        }
    });
}

- (NSString *)getDisplayNameWithUid:(NSString *)userid {

    NSString *displayName = @"";
    NSString *displayName_utf8 = [self.engine getUserInfo:userid][@"displayName"];
    
    if (displayName_utf8) {
        displayName = displayName_utf8;
    }
    return displayName_utf8;
}

@end
