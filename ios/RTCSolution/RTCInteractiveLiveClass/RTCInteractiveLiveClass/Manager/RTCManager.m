//
//  RTCManager.m
//  LectureHall
//
//  Created by Aliyun on 2020/6/15.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "RTCManager.h"
#import "NetworkManager.h"
#import "AppConfig.h"
#import <CommonCrypto/CommonHMAC.h>

@interface RTCManager()<AliRtcEngineDelegate>

/**
 @brief SDK实例
 */
@property (nonatomic, strong) AliRtcEngine *engine;

@property (nonatomic, weak) id<RTCInteractiveClassDelegate> delegate;


@end

static dispatch_once_t onceToken;
static RTCManager *manager = nil;

@implementation RTCManager

+ (RTCManager *) sharedInstance{

    dispatch_once(&onceToken, ^{
        manager = [[super allocWithZone:NULL] init];
        
    });
    return manager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    return [RTCManager sharedInstance];
}

- (id)copyWithZone:(nullable NSZone *)zone {
    return [RTCManager sharedInstance];
}

- (id)mutableCopyWithZone:(nullable NSZone *)zone {
    return [RTCManager sharedInstance];
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
    [_engine enableSpeakerphone:YES];
    [_engine setDeviceOrientationMode:AliRtcOrientationModeLandscapeLeft];
    
    //关闭高清预览
    AliRtcCameraCapturerConfiguration *cameraConfig = [[AliRtcCameraCapturerConfiguration alloc] init];
    cameraConfig.preference = AliRtcCaptureOutputPreferencePerformance;
    cameraConfig.cameraDirection = AliRtcCameraDirectionFront;
    [_engine setCameraCapturerConfiguration:cameraConfig];
    
    //频道模式
    [_engine setChannelProfile:AliRtcInteractivelive];
    //手动推拉流
    [_engine setAutoPublish:NO withAutoSubscribe:NO];
    
}

+ (void)destroySharedInstance{
    [AliRtcEngine destroy];
    onceToken = 0;
    manager = nil;
}

- (void)login:(NSString *)channel name:(NSString *)name {
//    [NetworkManager GET:[kBaseUrl_InteractiveClass stringByAppendingString: @"getRtcAuth"] parameters:@{@"channelId":channel} completionHandler:^(NSString * _Nullable errString, NSDictionary * _Nullable resultDic) {
//        if(!errString){
//            AliRtcAuthInfo *authInfo = [[AliRtcAuthInfo alloc] init];
//            authInfo.appid = resultDic[@"appid"];
//            authInfo.user_id = resultDic[@"userid"];
//            authInfo.channel = channel;
//            authInfo.nonce = resultDic[@"nonce"];
//            authInfo.timestamp = [resultDic[@"timestamp"] longLongValue];
//            authInfo.token = resultDic[@"token"];
//            authInfo.gslb = resultDic[@"gslb"];
//            authInfo.agent = resultDic[@"agent"];
            AliRtcAuthInfo *authInfo = [RTCManager GenerateAliRtcAuthInfoWithChnnelId:channel];
            //设置为观众角色
            [self.engine setClientRole:AliRtcClientRolelive];
            [self.engine joinChannel:authInfo name:name onResult:^(NSInteger errCode) {
                
            }];
//        }else {
//            //鉴权请求失败
//            [self onJoinChannelResult:-1 authInfo:nil];
//        }
       
//    }];
}


+ (AliRtcAuthInfo *)GenerateAliRtcAuthInfoWithChnnelId:(NSString *)channelID {
    NSString *AppID = @"" ;  //修改为自己的appid 该方案仅为开发测试使用，正式上线需要使用服务端的AppServer
    NSString *AppKey = @"";  //修改为自己的appkey 该方案仅为开发测试使用，正式上线需要使用服务端的AppServer
    
    NSString *userID = [NSString stringWithFormat:@"%d%d",(int)[[NSDate new] timeIntervalSince1970],(int)arc4random()];
   
    NSString *nonce = [NSString stringWithFormat:@"AK-%@",[[NSUUID UUID] UUIDString]];
   
    NSTimeInterval interval = 48 * 60 * 60;//48小时时间戳
    NSDate *datenow = [[NSDate date] initWithTimeIntervalSinceNow:interval];//现在时间
    long long timestamp = (long)(long)([datenow timeIntervalSince1970]*1000);
   
    //获取到token
    NSString *token = [NSString stringWithFormat:@"%@%@%@%@%@%lld",AppID,AppKey,channelID,userID,nonce,timestamp];
   
    //将token加密
    const char *s = [token cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *keyData = [NSData dataWithBytes:s length:strlen(s)];
    uint8_t digest[CC_SHA256_DIGEST_LENGTH] = {0};
    CC_SHA256(keyData.bytes, (CC_LONG)keyData.length, digest);
    NSData *out = [NSData dataWithBytes:digest length:CC_SHA256_DIGEST_LENGTH];
    const unsigned *hashBytes = [out bytes];
    NSString *hash = [NSString stringWithFormat:@"%08x%08x%08x%08x%08x%08x%08x%08x",
    ntohl(hashBytes[0]), ntohl(hashBytes[1]), ntohl(hashBytes[2]),
    ntohl(hashBytes[3]), ntohl(hashBytes[4]), ntohl(hashBytes[5]),
    ntohl(hashBytes[6]), ntohl(hashBytes[7])];
    
//    NSString *nonce = [NSString stringWithFormat:@"AK-%@",[[NSUUID UUID] UUIDString]];
//    NSTimeInterval interval = 48 * 60 * 60;//48小时时间戳
//    NSDate *datenow = [[NSDate date] initWithTimeIntervalSinceNow:interval];//现在时间
//    long long timestamp = (long)(long)([datenow timeIntervalSince1970]*1000);
    NSArray *GSLB = @[@"https://rgslb.rtc.aliyuncs.com"];

    NSArray *agent = [NSArray array];
    AliRtcAuthInfo *authInfo = [[AliRtcAuthInfo alloc] init];
    authInfo.appid = AppID;
    authInfo.user_id = userID;
    authInfo.channel = channelID;
    authInfo.nonce = nonce;
    authInfo.timestamp = timestamp;
    authInfo.token = hash;
    authInfo.gslb = GSLB;
    authInfo.agent = agent;
    return authInfo;
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
     __weak typeof(self) weakSelf = self;
    if (newRole == AliRtcClientRoleInteractive)
    {
        //切换成主播
        [self.engine configLocalAudioPublish:YES];
        [self.engine configLocalCameraPublish:YES];
        [self.engine publish:^(int errCode) {
            //主播身份切换结果通知
            if([weakSelf.delegate respondsToSelector:@selector(onEnterSeatResult:)]) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [weakSelf.delegate onEnterSeatResult:errCode];
                }); 
            }
        }];
    }
    if ([self.delegate respondsToSelector:@selector(onUpdateRoleNotifyWithOldRole:newRole:)]) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.delegate onUpdateRoleNotifyWithOldRole:oldRole newRole:newRole];
        });
        
    }
    
}

///  下麦需要停止推流 成功的回调是 onUpdateRoleNotifyWithOldRole
- (void)leaveSeat
{
    __weak typeof(self) weakSelf = self;
    [self.engine configLocalAudioPublish:NO];
    [self.engine configLocalCameraPublish:NO];
    [self.engine publish:^(int errCode) {
        if (errCode == 0) {
            [weakSelf.engine setClientRole:AliRtcClientRolelive];
        }
        //主播下麦结果通知
        if([weakSelf.delegate respondsToSelector:@selector(onLeaveSeatResult:)]) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf.delegate onLeaveSeatResult:errCode];
            });
        }
    }];
}


- (int)muteLocalMic:(BOOL)mute {
    return [self.engine muteLocalMic:mute];
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
    return [self.engine switchCamera];
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

- (void)configRemoteTrack:(NSString *)uid preferMaster:(BOOL)master enable:(BOOL)enable {
    [self.engine configRemoteCameraTrack:uid preferMaster:master enable:enable];
    [self.engine configRemoteScreenTrack:uid enable:enable];
    [self.engine configRemoteAudio:uid enable:enable];
    
}

- (void)subscribe:(NSString *)uid onResult:(void (^)(NSString *uid, AliRtcVideoTrack vt, AliRtcAudioTrack at))onResult {
    [self.engine subscribe:uid onResult:onResult];
}
 

- (AliRtcEngine *)engine {
    if (!_engine) {
        [self initializeSDK];
    }
    return _engine;
}
 
- (void)onOccurError:(int)error
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (error == AliRtcErrSdkInvalidState || error == AliRtcErrIceConnectionHeartbeatTimeout || error == AliRtcErrSessionRemoved ) {
            if ([self.delegate respondsToSelector:@selector(onSDKError:)])
            {
                [self.delegate onSDKError:error];
            }
        } else {
            if ([self.delegate respondsToSelector:@selector(onOccurError:)])
            {
                [self.delegate onOccurError:error];
            }
        } 
    });
   
}

- (void)onOccurWarning:(int)warn
{
    if ([self.delegate respondsToSelector:@selector(onOccurWarning:)])
    {
        dispatch_async(dispatch_get_main_queue(), ^{
             [self.delegate onOccurWarning:warn];
        });
       
    }
}


- (void)onBye:(int)code {
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

- (void)onJoinChannelResult:(int)result authInfo:(AliRtcAuthInfo *)authInfo {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onJoinChannelResult:authInfo:)]) {
            [self.delegate onJoinChannelResult:result authInfo:authInfo];
        }
    });
}

- (void)onLeaveChannelResult:(int)result {
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

- (void)onSubscribeChangedNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onSubscribeChangedNotify:audioTrack:videoTrack:)]) {
            [self.delegate onSubscribeChangedNotify:uid audioTrack:audioTrack videoTrack:videoTrack];
        }
    });
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

- (void)onRemoteUserOffLineNotify:(NSString *)uid {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onRemoteUserOffLineNotify:)]) {
            [self.delegate onRemoteUserOffLineNotify:uid];
        }
    });
}

- (void)onRemoteUserOnLineNotify:(NSString *)uid {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(onRemoteUserOnLineNotify:)]) {
            [self.delegate onRemoteUserOnLineNotify:uid];
        }
    });
}
- (NSString *)displayName:(NSString *)userid {

    NSString *displayName = @"";
    NSString *displayName_utf8 = [self.engine getUserInfo:userid][@"displayName"];
    
    if (displayName_utf8) {
        displayName = [NSString stringWithUTF8String:[displayName_utf8 cString]];
    }
    return displayName;
}
 


@end
