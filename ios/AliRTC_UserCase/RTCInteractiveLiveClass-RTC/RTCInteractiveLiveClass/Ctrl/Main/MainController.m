//
//  MainController.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/22.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "MainController.h"
#import "RTCRemoteUserManager.h"
#import "MainRemoterUserCCell.h"
#import "RTCRemoteUserModel.h"
#import "OnLineListController.h" //在线列表
#import "LCChatController.h" //实时互动
#import "LCTipsInfoAlert.h"  //提示框
#import "MainViewRightButton.h"
#import "MinTeacherInfoView.h"
#import "AliImInterrativeEngine.h"
#import "CommonUtils.h"
#import "LCClassEndController.h"
#import "NavigationController.h"
#import "AliRtcInterrativeEngine.h"
#import "UIImage+Color.h"
#import "NetworkManager.h"
#import "AppConfig.h"
#import "Masonry.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "UIColor+Hex.h"
#import "RTCHUD.h"


@interface MainController ()<UICollectionViewDelegateFlowLayout,AliRtcInterrativeEngineDelegate,AliImInterrativeEngineDelegate>
/// 占位图
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *emptyView;
/// 教师小窗口位置 （左侧顶部）
@property (weak, nonatomic) IBOutlet UIView *teacherView;
/// 主屏视图
@property (weak, nonatomic) IBOutlet UIView *videoView;
/// 远端学生用户
@property (weak, nonatomic) IBOutlet UICollectionView *remoteUserView;
/// 右侧按钮容器视图
@property (strong, nonatomic)  UIView *rightBtnsView;
/// 返回按钮
@property (nonatomic,strong) UIButton *backBtn;
/// SDK管理
@property (nonatomic, strong) AliRtcInterrativeEngine *rtcManager;
/// IM管理
@property(nonatomic,strong) AliImInterrativeEngine *imManager;
/// 远端用户管理
@property(nonatomic, strong) RTCRemoteUserManager *remoteUserManager;
/// 教师小视图
@property(nonatomic,strong) MinTeacherInfoView *teacherInfoView;
/// 当前画面人
@property(nonatomic,strong) UILabel *nickLbl;
/// 顶部正在讲话标签
@property(nonatomic,strong) UILabel *speakLbl;
/// 聊天控制器
@property (nonatomic,weak) LCChatController *chatVC;
/// 学生在线列表
@property(nonatomic, strong) NSMutableArray<RTCRemoteUserModel *> *studentArray;
/// 在线列表
@property(nonatomic, strong) NSMutableArray *onlineArray;
/// 主屏显示的用户
@property(nonatomic,strong) RTCRemoteUserModel *remoteUsermodel;
/// 自己
@property(nonatomic,strong) RTCRemoteUserModel *me;
/// 记录远端用户音频变化先收到回调（用户还未上线）
@property (nonatomic, strong) NSMutableDictionary *audioDict;
/// 记录远端用视频变化先收到回调（用户还未上线）
@property (nonatomic, strong) NSMutableDictionary *videoDict;
/// 自己网络是否较差
@property (nonatomic, assign) BOOL selfNetworkIsPoor;
/// 是否连麦
@property (nonatomic, assign) BOOL isJoinChannel;
/// 有新消息是否标红(YES:需要标红，NO:不需要标红)，默认NO
@property (nonatomic, assign) BOOL isMsgRed;
/// 开始时间
@property (nonatomic,copy) NSString *startTime;
/// 教师名称
@property (nonatomic,copy) NSString *teacherName;
/// 记录当前用户的uid
@property (nonatomic, copy) NSString *userId;
/// 本地相机预览canvas
@property(nonatomic,strong) AliVideoCanvas *localCanvas;
/// 是否已显示结束页面 默认NO 未显示
@property (nonatomic, assign) BOOL isShowEndView;

@end

@implementation MainController

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setBackgroundImage:[[UIImage alloc] init] forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:[[UIImage alloc] init]];
    self.navigationController.navigationBar.hidden = YES;
}

- (void)viewWillDisappear:(BOOL)animated{
    [self.navigationController.navigationBar setBackgroundImage:nil forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:nil];
    self.navigationController.navigationBar.hidden = NO;
}

//支持旋转
-(BOOL)shouldAutorotate{
    return NO;
}

//支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscapeRight;
}

//一开始的方向  很重要
-(UIInterfaceOrientation)preferredInterfaceOrientationForPresentation{
    return UIInterfaceOrientationLandscapeRight;
}

#pragma mark - lifecycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initUI];
    
    [self login];
}

#pragma mark - login
- (void)login {
    self.remoteUserView.hidden = NO;
    self.isJoinChannel = NO;
    [self.rtcManager login:self.channel name:self.userName];
    [self setupMainRenderView];
}

#pragma mark - alirtcengine delegate
/// 自己上麦通知
/// @param errorCode 结果
- (void)onEnterSeatResult:(int)errorCode {
    if (errorCode == 0) {
        self.isJoinChannel = YES;
        [self.rtcManager startPreview];
        [self loadData];
        [self buildBtns];
    }
}

/// 自己下线通知
/// @param errorCode 结果
- (void)onLeaveSeatResult:(int)errorCode {
    if (errorCode == 0) {
        self.isJoinChannel = NO;
        [self.rtcManager stopPreview];
        [self loadData];
        [self buildBtns];
    }
}

/// 房间被销毁通知
- (void)onRoomdestroy {
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        [self logout];
    });
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self showAlertWithTitle:@"提示" message:@"每节课体验时长最多10分钟，到时间后自动退出，如继续体验，请重新进入教室。" sureName:@"我知道了"];
    });
}

/// 如果engine出现warning，通过这个回调通知app
/// @param warn Warning type
- (void)onOccurWarning:(int)warn {
    
}

/// 如果engine出现严重error，通过这个回调通知app
/// @param error 错误类型
- (void)onSDKError:(int)error {
    NSString *errMsg = @"";
    if (error == AliRtcErrSdkInvalidState) {
        errMsg = @"sdk 状态错误";
    }else if (error == AliRtcErrIceConnectionHeartbeatTimeout) {
        errMsg = @"信令心跳超时";
    }else if (error == AliRtcErrSessionRemoved) {
        errMsg = @"Session 已经被移除，Session 不存在";
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        [self showAlertWithTitle:@"错误提示" message:errMsg sureName:@"确定"];
    });
}

/// 加入频道结果(此回调等同于joinChannel接口的block，二者择一处理即可)
/// @param result 加入频道结果，成功返回0，失败返回错误码
/// @param authInfo 权限信息
- (void)onJoinChannelResult:(int)result authInfo:(AliRtcAuthInfo *)authInfo {
    
    if (result != 0) {
        [RTCHUD showHud:@"加入房间失败" inView:self.view];
        dispatch_after(2, dispatch_get_main_queue(), ^{
            [self dismissViewControllerAnimated:YES completion:nil];
        });
    } else {
        
        [self loadData];
        self.userId = authInfo.userId;
        //IM相关
        [self.imManager login:authInfo.userId channel:self.channel displayName:self.userName];
    }
}

/// 离开频道结果 (调用leaveChannel接口后返回，如果leaveChannel后直接调用destroy，将不会收到此回调)
/// @param result 离开频道结果，成功返回0，失败返回错误码
- (void)onLeaveChannelResult:(int)result {
    if (result == 0) {
        [self logout];
        [self showClassEndView];
    } else {
        [RTCHUD showHud:@"离会失败" inView:self.view];
    }
}

/// 当远端用户的流发生变化时，返回这个消息 ,远方用户停止推流，也会发送这个消息
- (void)onRemoteTrackAvailableNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
    
    //在这里订阅，老师订阅大流 学生订阅小流
    if([[self.rtcManager getDisplayNameWithUid:uid] hasSuffix:@"老师"]) {
        
        [self.rtcManager subscribeRemoteTrack:uid preferMaster:YES enable:YES];
    }else {
        
        [self.rtcManager subscribeRemoteTrack:uid preferMaster:NO enable:YES];
    }
    
    [self subscribeChangedNotify:uid audioTrack:audioTrack videoTrack:videoTrack];
}

- (void)subscribeChangedNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
    
    //收到远端订阅回调
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.remoteUserManager updateRemoteUser:uid forTrack:videoTrack];
        
        if (videoTrack == AliRtcVideoTrackCamera) {
            AliVideoCanvas *canvas = [[AliVideoCanvas alloc] init];
            canvas.renderMode = AliRtcRenderModeFill;
            canvas.view = [self.remoteUserManager cameraView:uid];
            canvas.backgroundColor = 0xffffff;
            [self.rtcManager setRemoteViewConfig:canvas uid:uid forTrack:videoTrack];
        }else if (videoTrack == AliRtcVideoTrackScreen) {
            AliVideoCanvas *canvas = [[AliVideoCanvas alloc] init];
            canvas.renderMode = AliRtcRenderModeFill;
            canvas.view = [self.remoteUserManager screenView:uid];
            canvas.backgroundColor = 0xffffff;
            [self.rtcManager setRemoteViewConfig:canvas uid:uid forTrack:videoTrack];
        }else if (videoTrack == AliRtcVideoTrackBoth) {
            AliVideoCanvas *canvas = [[AliVideoCanvas alloc] init];
            canvas.renderMode = AliRtcRenderModeFill;
            canvas.view = [self.remoteUserManager screenView:uid];
            canvas.backgroundColor = 0xffffff;
            [self.rtcManager setRemoteViewConfig:canvas uid:uid forTrack:AliRtcVideoTrackScreen];
        }
        
        if (videoTrack == AliRtcVideoTrackCamera || videoTrack == AliRtcVideoTrackBoth) {
            
            RTCRemoteUserModel *cameraModel = [self.remoteUserManager findUser:uid forTrack:AliRtcVideoTrackCamera];
            
            if ([[self.videoDict allKeys] containsObject:cameraModel.uid] && cameraModel) {
                BOOL mute = [self.videoDict[cameraModel.uid] boolValue];
                cameraModel.videoMuted = mute;
                [self.videoDict removeObjectForKey:cameraModel.uid];
            }
        }
        
        if([self.remoteUserManager allOnlineUsers].count>0){
            //如果视频流有流 并且是老师 则放到主屏幕
            if(videoTrack != AliRtcVideoTrackNo){
                if([[self.rtcManager getDisplayNameWithUid:uid] hasSuffix:@"老师"]) {
                    RTCRemoteUserModel *teacherCamera = [self.remoteUserManager findUser:uid forTrack:AliRtcVideoTrackCamera];
                    RTCRemoteUserModel *teacherScreen = [self.remoteUserManager findUser:uid forTrack:AliRtcVideoTrackScreen];
                    
                    if (videoTrack == AliRtcVideoTrackBoth) { //摄像头+屏幕共享
                        
                        self.remoteUsermodel = teacherScreen;
                        self.teacherInfoView.userModel = teacherCamera;
                        
                        AliVideoCanvas *canvas = [[AliVideoCanvas alloc] init];
                        canvas.renderMode = AliRtcRenderModeFill;
                        canvas.view = self.teacherInfoView.renderview;
                        canvas.backgroundColor = 0xffffff;
                        [self.rtcManager setRemoteViewConfig:canvas uid:uid forTrack:AliRtcVideoTrackCamera];
                    }else if (videoTrack == AliRtcVideoTrackScreen) { //屏幕共享
                        
                        self.remoteUsermodel = teacherScreen;
                        self.teacherInfoView.userModel = teacherScreen;
                    }else { //摄像头
                        
                        self.teacherInfoView.userModel = teacherCamera;
                        self.remoteUsermodel = teacherCamera;
                    }
                }
            } else {
                //停止推流
                if([self.remoteUsermodel.uid isEqual:uid]) {
                    self.remoteUsermodel =  self.studentArray.firstObject;
                }
            }
        }
        [self loadData];
    });
}

/// 用户muteAudio通知
/// @param uid 执行muteAudio的用户
/// @param isMute YES:静音 NO:未静音
- (void)onUserAudioMuted:(NSString *)uid audioMuted:(BOOL)isMute {
    if ([self.remoteUserManager findUser:uid].count) {
        [self.remoteUserManager updateRemoteUer:uid forAudioMuted:isMute];
    }else {
        [self.audioDict setValue:@(isMute) forKey:uid];
    }
    
    [self loadData];
}

/// 用户muteVideo通知
/// @param uid 执行muteVideo的用户
/// @param isMute YES:推流黑帧 NO:正常推流
- (void)onUserVideoMuted:(NSString *)uid videoMuted:(BOOL)isMute {
    
    if ([self.remoteUserManager findUser:uid].count) {
        [self.remoteUserManager updateRemoteUer:uid forVideoMuted:isMute];
    }else {
        [self.videoDict setValue:@(isMute) forKey:uid];
    }
    
    [self loadData];
}

/// 网络质量变化时发出的消息 (当网络质量发生变化时触发，uid为@""时代表self的网络质量变化)
/// @param uid 网络质量发生变化的uid
/// @param upQuality 上行网络质量
/// @param downQuality 下行网络质量
- (void)onNetworkQualityChanged:(NSString *)uid
               upNetworkQuality:(AliRtcNetworkQuality)upQuality
             downNetworkQuality:(AliRtcNetworkQuality)downQuality {
    
    if([uid isEqualToString:@""] || [uid isEqualToString:self.userId]) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            UIView *view = [UIApplication sharedApplication].keyWindow;
            if (downQuality == AlivcRtcNetworkQualityDisconnect) { //当前网络存在异常
                
                if (!self.selfNetworkIsPoor) {
                    self.selfNetworkIsPoor = YES;
                    [RTCHUD showHud:@"当前网络存在异常" inView:view];
                }
            }else if (downQuality > AlivcRtcNetworkQualityBad) { //当前网络信号弱
                
                if (!self.selfNetworkIsPoor) {
                    self.selfNetworkIsPoor = YES;
                    [RTCHUD showHud:@"当前网络信号弱" inView:view];
                }
            }else {
                self.selfNetworkIsPoor = NO;
            }
        });
    }
}

/// 远端用户上线
/// @param uid 用户id
- (void)onRemoteUserOnLineNotify:(NSString *)uid {
    
    [self.remoteUserManager updateRemoteUser:uid forTrack:AliRtcVideoTrackNo];
    [self loadData];
}

/// 用户下线通知
/// @param uid 用户id
- (void)onRemoteUserOffLineNotify:(NSString *)uid {
    
    [self.remoteUserManager remoteUserOffLine:uid];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        //判断是否是老师
        if ([self.remoteUsermodel.uid isEqualToString:uid]) {
            
            [self showClassEndView];
        }else {
            
            [self loadData];
        }
    });
}

/// 订阅的音频音量，语音状态和uid
/// @param array 表示回调用户音量信息数组，包含用户uid,语音状态以及音量，uid为"0"表示本地说话人
/// @param totalVolume 混音后的总音量，范围[0,255]。在本地用户的回调中，totalVolume;为本地用户混音后的音量；在远端用户的回调中，totalVolume; 为所有说话者混音后的总音量
- (void)onAudioVolumeCallback:(NSArray <AliRtcUserVolumeInfo *> *_Nullable)array totalVolume:(int)totalVolume {
    
    NSMutableString *muStr = [NSMutableString string];
    for (AliRtcUserVolumeInfo *info in array) {
        if (![info.uid isEqualToString:@"0"] && info.speech_state) {
            [muStr appendFormat:@"%@、",[self.rtcManager getDisplayNameWithUid:info.uid]];
        }
    }
    NSString *resultStr = @"";
    if (muStr.length) {
        resultStr = [muStr substringToIndex:muStr.length -1];
    }
    
    self.speakLbl.hidden = resultStr.length == 0;
    self.speakLbl.text = [NSString stringWithFormat:@"%@正在发言",resultStr];
    
    CGFloat w = self.speakLbl.text.length * 12 + 8;
    [_speakLbl mas_updateConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.width.equalTo(@(w));
    }];
}

#pragma mark - AliImInterrativeEngineDelegate 消息信令相关(接收) -
- (void)imUpdateSingleMessage:(LCIMMessage *)msg {
    
    if (self.isMsgRed == NO) {
        self.isMsgRed = YES;
        UIButton *msgBtn = [self.rightBtnsView viewWithTag:4];
        msgBtn.selected = YES;
    }
}

- (void)imUpdateMessages:(NSArray<LCIMMessage *> *)messages {
    [self.chatVC updateMessages:messages];
}

- (void)imGroupMembersChanged:(NSArray<AIMPubGroupMember *> *)members {
    
    [self.onlineArray removeAllObjects];
    for (AIMPubGroupMember *member in members) {
        RTCRemoteUserModel *user = [RTCRemoteUserModel new];
        user.displayName = member.groupNick;
        user.uid = member.uid;
        
        if ([user.displayName isEqualToString:@"主持人"]) {
            user.displayName = self.teacherName;
        }
        
        if ([member.uid containsString:self.userId]) {
            user.uid = @"me";
        }
        [self.onlineArray addObject:user];
    }
}

/// 收到老师反馈举手信令
/// @param mute 是否同意举手(YES:同意举手,NO:拒绝举手)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteBackHandUpCommand:(BOOL)mute userId:(NSString *)uid {
    
    if (mute) { //同意连麦
        
        UIButton *handUpBtn = [self.rightBtnsView viewWithTag:3];
        handUpBtn.selected = YES;
        [self.rtcManager enterSeat];
    }else { //拒绝连麦
        
        [RTCHUD showHud:@"你已被老师拒绝连麦" inView:self.view];
    }
}

/// 收到静音指令
/// @param mute 是否静音 (YES:关闭麦克风，NO:打开麦克风)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteMuteMicCommand:(BOOL)mute userId:(NSString *)uid {
    
    if (self.isJoinChannel) {
        
        UIButton *muteBtn = [self.rightBtnsView.subviews firstObject];
        
        muteBtn.selected = !mute;
        [self BtnClick:muteBtn type:0];
        NSString *showStr = mute ? @"你已被老师静音" : @"你已被老师取消静音";
        [RTCHUD showHud:showStr inView:self.view];
    }
}

/// 收到相机流指令
/// @param mute 是否关闭相机流 (YES:关闭相机流，NO:打开相机流)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteMuteCameraCommand:(BOOL)mute userId:(NSString *)uid {
    
    if (self.isJoinChannel) {
        UIButton *cameraBtn = [self.rightBtnsView viewWithTag:1];
        cameraBtn.selected = !mute;
        [self BtnClick:cameraBtn type:0];
        NSString *showStr = mute ? @"你已被老师关闭摄像头" : @"你已被老师取消关闭摄像头";
        [RTCHUD showHud:showStr inView:self.view];
    }
}

/// 收到全员静音指令
/// @param mute 是否全员静音 (YES:全员静音，NO:解除全员静音)
- (void)imReceiveRemoteMuteAllMicCommand:(BOOL)mute {
    
    if (self.isJoinChannel) {
        UIButton *muteBtn = [self.rightBtnsView.subviews firstObject];
        muteBtn.selected = !mute;
        [self BtnClick:muteBtn type:0];
    }
    NSString *showStr = mute ? @"全员静音" : @"取消全员静音";
    [RTCHUD showHud:showStr inView:self.view];
}

- (void)imSendMessageFailure:(NSString *)error {
    
    [[UIApplication sharedApplication].keyWindow endEditing:YES];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [RTCHUD showHud:error inView:[UIApplication sharedApplication].keyWindow];
    });
}

#pragma mark - logout
- (void)logout {
    _localCanvas = nil;
    _remoteUsermodel = nil;
    [self.remoteUserManager removeAllUser];
    [self.studentArray removeAllObjects];
    self.isJoinChannel = NO;
    [self.rtcManager logout];
    [self.imManager logout];
    [AliImInterrativeEngine destroySharedInstance];
}

#pragma mark - loadData -
- (void)loadData{
    
    //移除学生在线列表
    [self.studentArray removeAllObjects];
    
    //上麦后把自己添加到小窗口数组
    if(self.isJoinChannel && ![self.remoteUsermodel.uid isEqual:@"me"]) {
        [self.studentArray addObject:self.me];
    }
    
    //把远端用户添加到小窗口数组 (不包含老师)
    for (RTCRemoteUserModel *userModel in [self.remoteUserManager allOnlineUsers]) {
        
        if ([[self.audioDict allKeys] containsObject:userModel.uid]) {
            BOOL mute = [self.audioDict[userModel.uid] boolValue];
            userModel.audioMuted = mute;
            [self.audioDict removeObjectForKey:userModel.uid];
        }
        
        if(![[self.rtcManager getDisplayNameWithUid:userModel.uid] hasSuffix:@"老师"]) {
            if(userModel.track > AliRtcVideoTrackNo) {
                [self.studentArray addObject:userModel];
            }
        }else {
            self.teacherInfoView.userModel = userModel;
            self.teacherName = [self.rtcManager getDisplayNameWithUid:userModel.uid];
        }
    }
    
    //刷新小窗口
    [self.remoteUserView reloadData];
    //刷新主窗口
    [self setupMainRenderView];
}

/// 设置主屏幕的view
-(void)setupMainRenderView{
    if(_remoteUsermodel){
        
        [_remoteUsermodel.view setFrame:self.videoView.bounds];
        [self.videoView addSubview:_remoteUsermodel.view];
        [self.videoView bringSubviewToFront:_remoteUsermodel.view];
        
        self.nickLbl.text = [self.rtcManager getDisplayNameWithUid:_remoteUsermodel.uid];
        CGFloat w = self.nickLbl.text.length * 12 + 8;
        [_nickLbl mas_updateConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.width.equalTo(@(w));
        }];
    }
}

#pragma mark - 在线列表/申请连麦/实时互动/静音/相机 按钮点击 -
- (void)BtnClick:(UIButton *)btn {
    [self BtnClick:btn type:1];
}

/// 在线列表/申请连麦/实时互动/静音/相机 按钮点击
/// @param btn 按钮
/// @param type 类型：区分是主动操作还是被动操作，为1时 主动操作，显示主动提示
- (void)BtnClick:(UIButton*)btn type:(NSInteger)type {
    
    switch (btn.tag) {
        case 0://静音
        {
            btn.selected = !btn.selected;
            self.me.audioMuted = btn.isSelected;
            [self.rtcManager muteLocalMic:btn.isSelected];
            [self onUserAudioMuted:@"me" audioMuted:btn.isSelected];
            if (type == 1) {
                [RTCHUD showHud:[NSString stringWithFormat:@"已%@静音",btn.isSelected?@"关闭":@"开启"] inView:self.view];
            }
        }
            break;
        case 1://相机
        {
            btn.selected = !btn.selected;
            self.me.videoMuted = btn.isSelected;
            int tag = 300;
            if (btn.isSelected) {
                UIView *view = [[UIView alloc] initWithFrame:self.localCanvas.view.bounds];
                view.backgroundColor = [UIColor blackColor];
                view.tag = tag;
                [self.localCanvas.view addSubview:view];
            } else {
                for (UIView *view in self.localCanvas.view.subviews) {
                    if (view.tag == tag) {
                        [view removeFromSuperview];
                    }
                }
            }
            [self.rtcManager muteLocalCamera:btn.isSelected forTrack:AliRtcVideoTrackCamera];
            [self onUserVideoMuted:@"me" videoMuted:btn.isSelected];
            if (type == 1) {
                [RTCHUD showHud:[NSString stringWithFormat:@"已%@摄像头",btn.isSelected?@"关闭":@"开启"] inView:self.view];
            }
        }
            break;
        case 2://在线列表
        {
            OnLineListController *VC = [[OnLineListController alloc] init];
            VC.modalPresentationStyle = UIModalPresentationOverCurrentContext|UIModalPresentationFullScreen;
            VC.seatArray = self.studentArray;
            VC.onlineArray = self.onlineArray;
            [self presentViewController:VC animated:NO completion:nil];
        }
            break;
        case 3://申请连麦
        {
            if (!btn.isSelected) {
                
                LCTipsInfoAlert *alert = [[LCTipsInfoAlert alloc] initWithIcon:@"tip_blue" message:@"您确定要向老师申请连麦吗？" sureName:@"确定" cancelName:@"取消"];
                __weak typeof(self) weakSelf = self;
                alert.submitblock = ^{
                    //请求连麦
                    [weakSelf.imManager sendHandUp:YES];
                };
                [alert show];
            }else {
                
                //取消连麦
                [self.rtcManager leaveSeat];
                btn.selected = NO;
                [self.remoteUserView reloadData];
                [RTCHUD showHud:@"听众模式" inView:self.view];
            }
        }
            break;
        case 4://实时互动
        {
            LCChatController *VC = [[LCChatController alloc] init];
            self.chatVC = VC;
            VC.modalPresentationStyle = UIModalPresentationOverCurrentContext|UIModalPresentationFullScreen;
            [VC updateMessages:[self.imManager getGroupMessages]];
            
            __weak typeof(self) weakSelf = self;
            VC.backClick = ^{
                
                btn.selected = NO;
                weakSelf.isMsgRed = NO;
            };
            [self presentViewController:VC animated:NO completion:nil];
        }
            break;
        default:
            break;
    }
    
    [self.remoteUserView reloadData];
}

#pragma mark - showClassEndView -
- (void)showClassEndView {
    
    if (self.isShowEndView) return;
    self.isShowEndView = YES;

    dispatch_async(dispatch_get_main_queue(), ^{
        
        LCClassEndController *vc = [[LCClassEndController alloc] init];
        NavigationController *nav = [[NavigationController alloc] initWithRootViewController:vc];
        nav.modalPresentationStyle = UIModalPresentationFullScreen;
        [self presentViewController:nav animated:YES completion:^{
            [vc classEAndWithTeacherName:self.teacherName startTime:[self.startTime longLongValue] onlineUsers:self.onlineArray.count connectUsers:self.studentArray.count];
            [self logout];
        }];
    });
}

#pragma mark - button actions
-(void)back{
    
    [self exitChanel:nil];
}

-(void)exitChanel:(id)sender{
    
    LCTipsInfoAlert *alert = [[LCTipsInfoAlert alloc] initWithIcon:@"tip_red" message:@"您确定要退出教室吗？" sureName:@"确定" cancelName:@"取消"];
    __weak typeof(self) weakSelf = self;
    alert.submitblock = ^{
        [weakSelf showClassEndView];
    };
    [alert show];
}

#pragma mark - alert function
- (void)showAlertWithTitle:(NSString *)title message:(NSString *)msg sureName:(NSString *)sureName {
    
    __weak typeof(self) weakSelf = self;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                             message:msg
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:sureName style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf logout];
            [weakSelf dismissViewControllerAnimated:YES completion:nil];
        });
    }];
    [alertController addAction:confirm];
    [self.navigationController presentViewController:alertController animated:YES completion:nil];
}

#pragma mark - UI funcions
-(void)initUI{
    
    self.automaticallyAdjustsScrollViewInsets = NO;
    //防止屏幕锁定
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    
    if (@available(iOS 11.0, *)) {
        self.remoteUserView.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
    } else {
        // Fallback on earlier versions
    }
    [self.remoteUserView registerClass:[MainRemoterUserCCell class] forCellWithReuseIdentifier:@"cell"];
    
    _remoteUserManager = [RTCRemoteUserManager shareManager];
    
    self.rtcManager = [AliRtcInterrativeEngine sharedInstance];
    self.rtcManager.delegate = self;
    
    self.imManager = [AliImInterrativeEngine sharedInstance];
    self.imManager.delegate = self;
    
    self.audioDict = [NSMutableDictionary dictionary];
    self.videoDict = [NSMutableDictionary dictionary];
    self.startTime = [CommonUtils currentTimeStr];
    self.isMsgRed = NO;
    
    
    [self.teacherView addSubview:self.teacherInfoView];
    [self.view addSubview:self.rightBtnsView];
    [self.view addSubview:self.backBtn];
    [self.view addSubview:self.nickLbl];
    [self.view addSubview:self.speakLbl];
    
    
    [_rightBtnsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.view.mas_centerY);
        make.right.equalTo(self.view.mas_right).mas_offset(-24);
        make.width.equalTo(@(48));
        make.height.equalTo(@(178));
    }];
    
    [_backBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.view.mas_right).mas_offset(-10);
        make.top.equalTo(self.view.mas_top);
        make.size.mas_equalTo(CGSizeMake(160, 44));
    }];
    
    [_nickLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.equalTo(self.videoView.mas_left).mas_offset(18);
        make.top.equalTo(self.videoView.mas_top).mas_offset(12);
        make.height.equalTo(@(20));
        make.width.equalTo(@(80));
    }];
    
    [_speakLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.equalTo(_nickLbl.mas_left);
        make.top.equalTo(_nickLbl.mas_bottom).mas_offset(4);
        make.height.equalTo(@(20));
        make.width.equalTo(@(80));
    }];
    
    //进来直接横屏，需处理一下
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self buildBtns];
        [self setupMainRenderView];
    });
}

-(void)buildBtns{
    
    //先将所有按钮移除
    for (UIView *v in self.rightBtnsView.subviews) {
        [v removeFromSuperview];
    }
    
    NSArray *btnsArr;
    if (self.isJoinChannel) {
        
        btnsArr = @[
            @{@"img":@"my_mute",@"selectedImg":@"my_mute_off",@"title":@"静音",@"selectedtitle":@"静音"},
            @{@"img":@"my_camera",@"selectedImg":@"my_camera_off",@"title":@"摄像头",@"selectedtitle":@"摄像头"},
            @{@"img":@"online_list",@"selectedImg":@"online_list",@"title":@"在线列表",@"selectedtitle":@"在线列表"},
            @{@"img":@"handup",@"selectedImg":@"endMate",@"title":@"申请连麦",@"selectedtitle":@"结束连麦"},
            @{@"img":@"message",@"selectedImg":@"message_tip",@"title":@"实时互动",@"selectedtitle":@"实时互动"},
        ];
    }else {
        
        btnsArr = @[
            @{@"img":@"online_list",@"selectedImg":@"online_list",@"title":@"在线列表",@"selectedtitle":@"在线列表"},
            @{@"img":@"handup",@"selectedImg":@"endMate",@"title":@"申请连麦",@"selectedtitle":@"结束连麦"},
            @{@"img":@"message",@"selectedImg":@"message_tip",@"title":@"实时互动",@"selectedtitle":@"实时互动"},
        ];
    }
    
    int width = 48;
    int height = 54;
    CGFloat rightHeight = btnsArr.count * height + 16;
    [_rightBtnsView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.height.equalTo(@(rightHeight));
    }];
    
    for (int i=0; i<btnsArr.count; i++) {
        
        MainViewRightButton *btn = [[MainViewRightButton alloc] initWithFrame:CGRectMake(0, height * i, width, height)];
        btn.tag = self.isJoinChannel ? i : i + 2;
        NSDictionary *item = btnsArr[i];
        [btn setImage:[NSBundle RILC_pngImageWithName:item[@"img"]] forState:UIControlStateNormal];
        [btn setImage:[NSBundle RILC_pngImageWithName:item[@"selectedImg"]] forState:UIControlStateSelected];
        [btn setTitle:item[@"title"] forState:UIControlStateNormal];
        [btn setTitle:item[@"selectedtitle"] forState:UIControlStateSelected];
        [btn addTarget:self action:@selector(BtnClick:) forControlEvents:UIControlEventTouchUpInside];
        
        if (btn.tag == 0) {
            btn.selected = self.me.audioMuted;
        }else if (btn.tag == 1) {
            btn.selected = self.me.videoMuted;
        }else if (btn.tag == 3) {
            btn.selected = self.isJoinChannel;
        }else if (btn.tag == 4) {
            btn.selected = self.isMsgRed;
        }
        
        [self.rightBtnsView addSubview:btn];
    }
}

#pragma mark - uicollectionview delegate & datasource
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.studentArray.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MainRemoterUserCCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    RTCRemoteUserModel *model =  self.studentArray[indexPath.row];
    if ([model.uid isEqualToString:@"me"]) {
        model.displayName = self.userName;
    }
    if (model.displayName.length == 0) {
        model.displayName = [self.rtcManager getDisplayNameWithUid:model.uid];
    }
    cell.userModel = model;
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake(160, 85);
}

#pragma mark - setter & getters
- (AliVideoCanvas *)localCanvas{
    if (!_localCanvas) {
        _localCanvas = [[AliVideoCanvas alloc] init];
        _localCanvas.renderMode = AliRtcRenderModeFill;
        _localCanvas.view = [[UIView alloc] init];
        _localCanvas.backgroundColor = 0xffffff;
        [self.rtcManager setLocalViewConfig:_localCanvas forTrack:AliRtcVideoTrackCamera];
    }
    return _localCanvas;
}

- (RTCRemoteUserModel *)me {
    if (!_me) {
        _me =  [[RTCRemoteUserModel alloc] init];
        _me.uid   = @"me";
        _me.track = AliRtcVideoTrackCamera;
        _me.view  = self.localCanvas.view;
    }
    return _me;
}

- (NSMutableArray *)studentArray {
    if (!_studentArray) {
        _studentArray = [NSMutableArray array];
    }
    return _studentArray;
}

- (NSMutableArray *)onlineArray {
    if (!_onlineArray) {
        _onlineArray = [NSMutableArray array];
    }
    return _onlineArray;
}

- (UIButton *)backBtn {
    if (!_backBtn) {
        _backBtn = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 160, 44)];
        _backBtn.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:14];
        [_backBtn setImage:[NSBundle RILC_pngImageWithName:@"exit"] forState:UIControlStateNormal];
        [_backBtn setTitle:[@"教室码:" stringByAppendingString:self.channel] forState:UIControlStateNormal];
        [_backBtn setTitleColor:[UIColor colorWithHex:0x333333] forState:UIControlStateNormal];
        [_backBtn addTarget:self action:@selector(back) forControlEvents:UIControlEventTouchUpInside];
        _backBtn.titleEdgeInsets = UIEdgeInsetsMake(0, 18, 0, 0);
        _backBtn.imageEdgeInsets = UIEdgeInsetsMake(0, -8, 0, 0);
    }
    return _backBtn;
}

- (UIView *)rightBtnsView {
    if (!_rightBtnsView) {
        _rightBtnsView = [UIView new];
        _rightBtnsView.clipsToBounds = YES;
        _rightBtnsView.layer.cornerRadius = 4;
        _rightBtnsView.backgroundColor = [UIColor colorWithHex:0x555555];
    }
    return _rightBtnsView;
}

-(MinTeacherInfoView *)teacherInfoView {
    if (!_teacherInfoView) {
        _teacherInfoView = [[MinTeacherInfoView alloc] initWithFrame:self.teacherView.bounds];
    }
    return _teacherInfoView;
}

- (UILabel *)speakLbl {
    if (!_speakLbl) {
        _speakLbl = [[UILabel alloc] init];
        _speakLbl.hidden = YES;
        _speakLbl.clipsToBounds = YES;
        _speakLbl.textAlignment = NSTextAlignmentCenter;
        _speakLbl.layer.cornerRadius = 4;
        _speakLbl.backgroundColor = [UIColor colorWithHex:0xEAEEFF];
        _speakLbl.textColor = [UIColor colorWithHex:0x365AFF];
        _speakLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    }
    return _speakLbl;
}

- (UILabel *)nickLbl {
    if (!_nickLbl) {
        _nickLbl = [UILabel new];
        _nickLbl.clipsToBounds = YES;
        _nickLbl.textAlignment = NSTextAlignmentCenter;
        _nickLbl.layer.cornerRadius = 4;
        _nickLbl.backgroundColor = [UIColor colorWithHex:0xFFFFFF alpha:0.6];
        _nickLbl.textColor = [UIColor colorWithHex:0x333333];
        _nickLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    }
    return _nickLbl;
}

- (void)dealloc {
    NSLog(@"mainController destroyed");
}

@end
