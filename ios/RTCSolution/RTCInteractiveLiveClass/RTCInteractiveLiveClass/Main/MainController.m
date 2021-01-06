//
//  MainController.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/22.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "MainController.h"
#import "RTCRemoteUserManager.h"
#import "RTCHUD.h"
#import "RTCRemoterUserCell.h"
#import "RTCRemoteUserModel.h"
#import "UIImage+Color.h"
#import "AlertMsgController.h"
#import "NetworkManager.h"
#import "AppConfig.h"
#import "RTCManager.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "UIColor+Hex.h"
#import "RTCHUD.h"

@interface MainController ()<RTCInteractiveClassDelegate,UICollectionViewDelegateFlowLayout>

/**
 @brief SDK管理
 */
@property (nonatomic, strong) RTCManager *rtcManager;

/**
 @brief 远端用户管理
 */
@property(nonatomic, strong) RTCRemoteUserManager *remoteUserManager;

@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *emptyView;

/**
 @brief 主屏视图
 */
@property (weak, nonatomic) IBOutlet UIView *videoView;
/**
@brief 按钮容器视图
*/
@property (weak, nonatomic) IBOutlet UIView *btnsView;
/**
@brief 退出按钮
*/
@property (nonatomic,strong) UIButton *exitBtn;
/**
@brief 静音按钮
*/
@property (nonatomic,weak) UIButton *muteBtn;
/**
@brief 相机按钮
*/
@property (nonatomic,weak) UIButton *cameraBtn;
/**
@brief 连麦&下麦按钮
*/
@property (nonatomic,weak) UIButton *joinBtn;
/**
@brief 翻转相机按钮
*/
@property (nonatomic,weak) UIButton *flipBtn;
/**
@brief 是否正在连麦
*/
@property (nonatomic, assign) BOOL isJoinChannel;
/**
@brief 播放器地址
*/
@property (nonatomic,copy) NSString *playUrl;
/**
@brief 定时器
*/
@property (nonatomic,strong) NSTimer *timer;
/**
@brief 屏幕按钮显示时间倒计时
*/
@property (nonatomic, assign) NSInteger countDown;
/**
@brief 缓冲时间
*/
@property (nonatomic,assign) NSInteger loadingTime;
/**
@brief 是否需要缓冲计时
*/
@property (nonatomic,assign) BOOL shouldStartLoadingCount;
/**
@brief 网络状态显示label
*/
@property (nonatomic,assign) UILabel *networkLabel;

/**
 @brief 自己的网络状态
 */
@property (nonatomic,assign) AliRtcNetworkQuality  selfNetworkQuality;

/**
 @brief 其他人的网络状态
 */
@property (nonatomic,assign) AliRtcNetworkQuality  otherNetworkQuality;

/**
 @brief 小屏collectionView
 */

@property (weak, nonatomic) IBOutlet UICollectionView *remoteUserView;

/**
@brief 主屏显示的用户
*/
@property(nonatomic,strong) RTCRemoteUserModel *remoteUsermodel;

/**
@brief 小屏幕数据源
*/
@property(nonatomic, strong) NSMutableArray *dataArr;
/**
@brief 本地相机预览canvas
*/
@property(nonatomic,strong) AliVideoCanvas *localCanvas;

@end

@implementation MainController


#pragma mark - lifecycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.rtcManager = [RTCManager sharedInstance];
    self.rtcManager.delegate = self;
    
    [self initUI];
    
    self.countDown = 15;
    
    [self login];
    
    [self startTimer];
    
    //防止屏幕锁定
    [UIApplication sharedApplication].idleTimerDisabled = YES;
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    [self onFullScreen:nil];
}

- (void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];

    [self setInterfaceOrientation:UIInterfaceOrientationPortrait];

}

- (void)viewDidLayoutSubviews {
    CGFloat x = self.btnsView.center.x;
    CGFloat y = self.btnsView.center.y - 60;
    self.networkLabel.center = CGPointMake(x, y);
}
- (void)dealloc {
    NSLog(@"mainController destroyed");
        
}

#pragma mark - UI funcions

-(void)initUI{
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    [backBtn setImage:[NSBundle RILC_pngImageWithName:@"back"] forState:UIControlStateNormal];
    [backBtn setTitle:[@"教室编号:" stringByAppendingString:self.channel] forState:UIControlStateNormal];
    [backBtn addTarget:self action:@selector(back) forControlEvents:UIControlEventTouchUpInside];
    [backBtn sizeToFit];
    
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
    self.navigationItem.leftBarButtonItem = leftItem;
    
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    
//    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[NSBundle RILC_pngImageWithName:@"share"] style:UIBarButtonItemStylePlain target:self action:@selector(share)];
    
    [self.remoteUserView registerClass:[RTCRemoterUserCell class] forCellWithReuseIdentifier:@"cell"];
    
    _remoteUserManager = [RTCRemoteUserManager shareManager];
    
    UILabel *label  = [[UILabel alloc] initWithFrame:CGRectMake(200, 100, 150, 40)];
    [self.view addSubview:label];
    self.networkLabel = label;
    self.networkLabel.font = [UIFont systemFontOfSize:18];
    self.networkLabel.textColor = [UIColor whiteColor];
    self.networkLabel.text = @"";
    self.networkLabel.textAlignment = NSTextAlignmentCenter;
    
    self.emptyView.image = [NSBundle RILC_pngImageWithName:@"video_empty"];
}

-(void)buildBtns{
    //先清空一下
    while (self.btnsView.subviews.count) {
        [self.btnsView.subviews.lastObject removeFromSuperview];
    }
    
    NSArray *arr = @[
        @{@"img":@"unmute",@"selectedImg":@"mute_grey",@"title":@"静音",@"selectedtitle":@"取消静音"},
        @{@"img":@"camera",@"selectedImg":@"cameraclosed",@"title":@"摄像头",@"selectedtitle":@"开启摄像头"},
        @{@"img":@"voice",@"selectedImg":@"voice",@"title":@"连麦",@"selectedtitle":@"下麦"},
        @{@"img":@"rotate",@"selectedImg":@"rotate",@"title":@"翻转",@"selectedtitle":@"翻转"},
        @{@"img":@"exit",@"selectedImg":@"exit",@"title":@"退出课程",@"selectedtitle":@"退出课程"},
    ];
    
//    AppDelegate * app = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    int size = 5;
    int paddingLeft = (CGRectGetWidth(self.btnsView.frame) - (60*size+(28*size-1)))/2;
    for (int i=0; i<size; i++) {
        [self buildBtnItem:arr[i] AtIdx:i padding:paddingLeft];
    }
}

-(void)buildBtnItem:(NSDictionary*)item AtIdx:(int)idx padding:(int)padding{
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(idx*(60+28)+padding, 0, 60, 68)];
    btn.tag = idx;
    if (idx == 0) {
        self.muteBtn = btn;
        self.muteBtn.alpha = 0.5;
    }
    if (idx == 1) {
        self.cameraBtn = btn;
        self.cameraBtn.alpha = 0.5;
    }
    if (idx == 2) {
        self.joinBtn = btn;
    }
    if (idx == 3) {
        self.flipBtn = btn;
        self.flipBtn.alpha = 0.5;
    }
    
    
    [btn setImage:[NSBundle RILC_pngImageWithName:item[@"img"]] forState:UIControlStateNormal];
    [btn setImage:[NSBundle RILC_pngImageWithName:item[@"selectedImg"]] forState:UIControlStateSelected];
    [btn setTitle:item[@"title"] forState:UIControlStateNormal];
    [btn setTitle:item[@"selectedtitle"] forState:UIControlStateSelected];
    btn.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(onBtnClick:) forControlEvents:UIControlEventTouchUpInside];
    
    [btn setTitleEdgeInsets:UIEdgeInsetsMake(0, -50, -60, 0)];
    
    [btn setImageEdgeInsets:UIEdgeInsetsMake(-20, 6, 0, 0)];

   
    [self.btnsView addSubview:btn];
    
}

-(void)setupMainRenderView{
    AliRenderView *curView = nil;
    if(_remoteUsermodel){
        [_remoteUsermodel.view setFrame:self.videoView.bounds];
        [_remoteUsermodel.view.subviews.firstObject setFrame:self.videoView.bounds];
        [self.videoView addSubview:_remoteUsermodel.view];
        curView = _remoteUsermodel.view;
        curView.hidden = _remoteUsermodel.videoMuted;
        curView.tag = 100;
    }

    int delTag = 100;
    if(self.videoView.subviews.count>1){
        for (UIView *view in self.videoView.subviews) {
            if(view!=curView && view.tag ==delTag){
                [view removeFromSuperview];
            }
        }
    }

}


#pragma mark - timer function

- (void)startTimer {
    self.timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(count:) userInfo:nil repeats:YES];
    [self.timer fire];
}
- (void)count:(NSTimer *) timer {
    self.countDown--;
    if (self.shouldStartLoadingCount) {
        self.loadingTime++;
        if (self.loadingTime == 30) {
            [self LiveTimeout];
        }
    }
}
- (void)destroyTimer {
    [self.timer invalidate];
    self.timer = nil;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    self.countDown = self.countDown <= 0 ? 15:0;
}

#pragma mark - button actions

- (void)share{
    NSString *shareurl =[NSString stringWithFormat:@"%@index.html#/studentOnly?channel=%@&role=1",KShareBaseUrl_InteractiveClass,self.channel];
    
    //复制到剪切板
    UIPasteboard *board = [UIPasteboard generalPasteboard];
    board.string = shareurl;
    
    [RTCHUD showHud:@"链接已复制" inView:self.view];
}

-(void)back{
    
    [self exitChanel:nil];
}

-(void)exitChanel:(id)sender{
    AlertMsgController *alert =  [[NSBundle RILC_storyboard] instantiateViewControllerWithIdentifier:@"AlertMsgController"];
    alert.modalPresentationStyle = UIModalPresentationOverFullScreen;
    alert.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    __weak typeof(self) weakSelf = self;
    alert.submitblock = ^{
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            [weakSelf logout];
            [weakSelf destroyTimer];
        });
    };
    [self presentViewController:alert animated:YES completion:nil];
}


- (void)onBtnClick:(UIButton*)btn {
    switch (btn.tag) {
        //静音
        case 0:
            if (self.isJoinChannel) {
                [btn setSelected:!btn.isSelected];
                [self.rtcManager muteLocalMic:btn.isSelected];
                [self onUserAudioMuted:@"me" audioMuted:btn.isSelected];
                [RTCHUD showHud:[NSString stringWithFormat:@"已%@静音",btn.isSelected?@"开启":@"关闭"] inView:self.view];
            }else{
                [RTCHUD showHud:@"请在连麦后使用" inView:self.view];
            }
            break;
        //摄像头
        case 1:
            if (self.isJoinChannel) {
                [btn setSelected:!btn.isSelected];
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
                [RTCHUD showHud:[NSString stringWithFormat:@"已%@摄像头",btn.isSelected?@"关闭":@"开启"] inView:self.view];
            }else{
                [RTCHUD showHud:@"请在连麦后使用" inView:self.view];
            }
            break;
        //连麦
        case 2:
            if (!btn.isSelected) {
                [self.rtcManager enterSeat];
                
            }else{
//                [self joinByURL:_authInfo];
                [self.rtcManager leaveSeat];
                self.isJoinChannel = NO;
                [self setupMainRenderView];
                [self.remoteUserView reloadData];
                [RTCHUD showHud:@"听众模式" inView:self.view];
            }
            break;
        //翻转
        case 3:
            if (self.isJoinChannel) {
                [btn setSelected:!btn.isSelected];
                [self.rtcManager switchCamera];
                [RTCHUD showHud:@"已切换摄像头" inView:self.view];
            }else{
                [RTCHUD showHud:@"请在连麦后使用" inView:self.view];
            }
            break;
        //退出课程
        case 4:
            [self exitChanel:nil];
            break;
            
        default:
            break;
    }
}

- (IBAction)onFullScreen:(id)sender {
    [self swithOrientation:UIInterfaceOrientationLandscapeRight];
}

#pragma mark - initializeSDK


-(void)removeRTCSDK{
    _localCanvas = nil;
    _remoteUsermodel = nil;
    [self.remoteUserManager removeAllUser];
    [_dataArr removeAllObjects];
    self.isJoinChannel = NO;
    [RTCManager destroySharedInstance];
}

- (void)logout {
    _localCanvas = nil;
    _remoteUsermodel = nil;
    [self.remoteUserManager removeAllUser];
    [_dataArr removeAllObjects];
    self.isJoinChannel = NO;
    [self.rtcManager logout];
}
- (void)login{
    self.remoteUserView.hidden = NO;
    self.isJoinChannel = NO;
    [self.rtcManager login:self.channel name:self.userName];
    [self setupMainRenderView];
    
}

#pragma mark - orientaiton
- (void)swithOrientation:(UIInterfaceOrientation)orientation{
    [self setInterfaceOrientation:orientation];
    //进来直接横屏，需处理一下
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self buildBtns];
        [self setupMainRenderView];
    });
}

//强制转屏
- (void)setInterfaceOrientation:(UIInterfaceOrientation)orientation{

    if ([[UIDevice currentDevice] respondsToSelector:@selector(setOrientation:)]) {
        SEL selector  = NSSelectorFromString(@"setOrientation:");
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:[UIDevice instanceMethodSignatureForSelector:selector]];
        [invocation setSelector:selector];
        [invocation setTarget:[UIDevice currentDevice]];
        // 从2开始是因为前两个参数已经被selector和target占用
        [invocation setArgument:&orientation atIndex:2];
        [invocation invoke];
    }
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    return  UIInterfaceOrientationMaskLandscapeRight;
}


#pragma mark - alert function

- (void) connectionTimeout {
     __weak typeof(self) weakSelf = self;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"体验时间已到"
                                                                             message:@"您的本次体验时长已满\n如需再次体验，请重新创建通话"
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"我知道了" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
                 [weakSelf removeRTCSDK];
                 [weakSelf destroyTimer];
             });
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf.navigationController popViewControllerAnimated:YES];
        });
        
     
    }];
    [alertController addAction:confirm];
    [self.navigationController presentViewController:alertController animated:YES completion:nil];
    
}

- (void) LiveTimeout {
     __weak typeof(self) weakSelf = self;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"提示"
                                                                             message:@"老师已离开房间"
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
                 [weakSelf removeRTCSDK];
                 [weakSelf destroyTimer];
             });
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf.navigationController popViewControllerAnimated:YES];
        });
    }];
    [alertController addAction:confirm];
    [self.navigationController presentViewController:alertController animated:YES completion:nil];
    
}

- (void)sdkError:(NSString *)errorMsg {
    __weak typeof(self) weakSelf = self;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"错误提示"
                                                                             message:errorMsg
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
                 [weakSelf removeRTCSDK];
                 [weakSelf destroyTimer];
             });
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf.navigationController popViewControllerAnimated:YES];
            
        });
    }];
    [alertController addAction:confirm];
    [self.navigationController presentViewController:alertController animated:YES completion:nil];
}





#pragma mark - alirtcengine delegate
/// 远端用户上麦通知
/// @param errorCode 结果
- (void)onEnterSeatResult:(int)errorCode {
    if (errorCode == 0) {
        self.isJoinChannel = YES;
        [self.rtcManager startPreview];
        [self loadData];
       
    }
}

/// 远端用户下线通知
/// @param errorCode 结果
- (void)onLeaveSeatResult:(int)errorCode {
    if (errorCode == 0) {
        self.isJoinChannel = NO;
        [self.rtcManager stopPreview];
        if ([self.remoteUsermodel.uid isEqual:@"me"]) {
            self.remoteUsermodel =  self.remoteUserManager.allOnlineUsers.firstObject;
        }
        [self loadData];
    }
    
}

/// 房间被销毁通知
- (void)onRoomdestroy {
    [self connectionTimeout];
}

/**
 * @brief 如果engine出现error，通过这个回调通知app
 * @param error  Error type
 */
- (void)onOccurError:(int)error {
    NSString *errorMsg = [NSString stringWithFormat:@"errorCode:%d",error];
    [RTCHUD showHud:errorMsg inView:self.view];
}
/**
* @brief 如果engine出现warning，通过这个回调通知app
* @param warn  Warning type
*/
- (void)onOccurWarning:(int)warn {
    
}
/**
* @brief 如果engine出现严重error，通过这个回调通知app
* @param error  错误类型
*/
- (void)onSDKError:(int)error {
    NSString *errMsg = @"";
       if (error == AliRtcErrSdkInvalidState) {
           errMsg = @"sdk 状态错误";
      }else if (error == AliRtcErrIceConnectionHeartbeatTimeout) {
           errMsg = @"信令心跳超时";
      }else if (error == AliRtcErrSessionRemoved) {
           errMsg = @"Session 已经被移除，Session 不存在";
      }
    [self sdkError:errMsg];
}

/**
* @brief 加入频道结果
* @param result 加入频道结果，成功返回0，失败返回错误码
* @note 此回调等同于joinChannel接口的block，二者择一处理即可
*/
- (void)onJoinChannelResult:(int)result authInfo:(AliRtcAuthInfo *)authInfo {
    if (result != 0) {
        [RTCHUD showHud:@"加入房间失败" inView:self.view];
        dispatch_after(2, dispatch_get_main_queue(), ^{
            [self.navigationController popViewControllerAnimated:YES];
        });
    } else {
        [self loadData];
        [self setupMainRenderView];
    }
}

/**
* @brief 离开频道结果
* @param result 离开频道结果，成功返回0，失败返回错误码
* @note 调用leaveChannel接口后返回，如果leaveChannel后直接调用destroy，将不会收到此回调
*/
- (void)onLeaveChannelResult:(int)result {
    if (result == 0) {
        [self removeRTCSDK];
        [self.navigationController popViewControllerAnimated:YES];
       
    } else {
        [RTCHUD showHud:@"离会失败" inView:self.view];
    }
    
}

/**
* @brief 当远端用户的流发生变化时，返回这个消息
* @note 远方用户停止推流，也会发送这个消息
*/
- (void)onRemoteTrackAvailableNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
    //在这里订阅流 数组里有对象 订阅小流 第一个对象订阅大流
    if (audioTrack !=AliRtcAudioTrackNo && videoTrack != AliRtcVideoTrackNo) {
        [self.rtcManager configRemoteTrack:uid preferMaster:!self.dataArr.count enable:YES];
        [self.rtcManager subscribe:uid onResult:^(NSString * _Nonnull uid, AliRtcVideoTrack vt, AliRtcAudioTrack at) {
            
        }];
    }
}

/**
 * @brief 当订阅情况发生变化时，返回这个消息
 */
- (void)onSubscribeChangedNotify:(NSString *)uid audioTrack:(AliRtcAudioTrack)audioTrack videoTrack:(AliRtcVideoTrack)videoTrack {
       //收到远端订阅回调
       dispatch_async(dispatch_get_main_queue(), ^{
           [self.remoteUserManager updateRemoteUser:uid forTrack:videoTrack];
           
           if (videoTrack == AliRtcVideoTrackCamera) {
               AliVideoCanvas *canvas = [[AliVideoCanvas alloc] init];
               canvas.renderMode = AliRtcRenderModeFill;
               canvas.view = [self.remoteUserManager cameraView:uid];
               [self.rtcManager setRemoteViewConfig:canvas uid:uid forTrack:AliRtcVideoTrackCamera];
           }else if (videoTrack == AliRtcVideoTrackScreen) {
               AliVideoCanvas *canvas2 = [[AliVideoCanvas alloc] init];
               canvas2.renderMode = AliRtcRenderModeFill;
               canvas2.view = [self.remoteUserManager screenView:uid];
               [self.rtcManager setRemoteViewConfig:canvas2 uid:uid forTrack:AliRtcVideoTrackScreen];
           }else if (videoTrack == AliRtcVideoTrackBoth) {
               AliVideoCanvas *canvas2 = [[AliVideoCanvas alloc] init];
               canvas2.renderMode = AliRtcRenderModeFill;
               canvas2.view = [self.remoteUserManager screenView:uid];
               [self.rtcManager setRemoteViewConfig:canvas2 uid:uid forTrack:AliRtcVideoTrackScreen];
           }
           
           if([self.remoteUserManager allOnlineUsers].count>0){
               //如果视频流有流 并且是老师 则放到主屏幕
               if(videoTrack != AliRtcVideoTrackNo){
                   if([[self.rtcManager displayName:uid] hasSuffix:@"老师"]) {
                       RTCRemoteUserModel *teacherCamera = [self.remoteUserManager findUser:uid forTrack:AliRtcVideoTrackCamera];
                       RTCRemoteUserModel *teacherScreen = [self.remoteUserManager findUser:uid forTrack:AliRtcVideoTrackScreen];
                       if (teacherScreen) {
                           self.remoteUsermodel = teacherScreen;
                       } else {
                           self.remoteUsermodel = teacherCamera;
                       }
                   }
               } else {
                   //停止推流
                   if([self.remoteUsermodel.uid isEqual:uid]) {
                       self.remoteUsermodel =  self.dataArr.firstObject;
                   }
               }
           }
          
           [self loadData];
       });
}

/**
 * @brief 用户muteAudio通知
 * @param uid 执行muteAudio的用户
 * @param isMute YES:静音 NO:未静音
 */
- (void)onUserAudioMuted:(NSString *)uid audioMuted:(BOOL)isMute {
    [self.remoteUserManager updateRemoteUer:uid forAudioMuted:isMute];
    [self.remoteUserView reloadData];
}

/**
 * @brief 用户muteVideo通知
 * @param uid 执行muteVideo的用户
 * @param isMute YES:推流黑帧 NO:正常推流
 */
- (void)onUserVideoMuted:(NSString *)uid videoMuted:(BOOL)isMute {
    [self.remoteUserManager updateRemoteUer:uid forVideoMuted:isMute];
    [self loadData];
    [self setupMainRenderView];
}

/**
 * @brief 网络质量变化时发出的消息
 * @param uid 网络质量发生变化的uid
 * @param upQuality  上行网络质量
 * @param downQuality  下行网络质量
 * @note 当网络质量发生变化时触发，uid为@""时代表self的网络质量变化
 */
- (void)onNetworkQualityChanged:(NSString *)uid
               upNetworkQuality:(AliRtcNetworkQuality)upQuality
             downNetworkQuality:(AliRtcNetworkQuality)downQuality {
//    if([uid isEqualToString:@""] || [uid isEqualToString:_authInfo.user_id]||[uid isEqualToString:@"0"]) {
//              //自己的网络状态
//              self.selfNetworkQuality = upQuality;
//          } else {
//               self.otherNetworkQuality = upQuality;
//          }
}

/**
 * @brief 当用户角色发生变化化时通知
 * @param oldRole 变化前角色类型
 * @param newRole 变化后角色类型
 * @note 调用setClientRole方法切换角色成功时触发此回调
 */
- (void)onUpdateRoleNotifyWithOldRole:(AliRtcClientRole)oldRole newRole:(AliRtcClientRole)newRole {
    
}

/// 远端用户上线
/// @param uid 用户id
- (void)onRemoteUserOnLineNotify:(NSString *)uid {
    [self.remoteUserManager  updateRemoteUser:uid forTrack:AliRtcVideoTrackNo];
}

/// 用户下线通知
/// @param uid 用户id
- (void)onRemoteUserOffLineNotify:(NSString *)uid;{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.remoteUserManager remoteUserOffLine:uid];
        [self loadData];
        if([self->_remoteUsermodel.uid isEqualToString:uid]) {
              //点击自己头像
              [self collectionView:self.remoteUserView didSelectItemAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]];
        }
    });
}



#pragma mark - uicollectionview delegate & datasource

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return _dataArr.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    RTCRemoterUserCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    RTCRemoteUserModel *model =  _dataArr[indexPath.row];
     
    if ([model.uid isEqualToString:@"me"]) {
        model.audioMuted = self.muteBtn.selected;
        model.videoMuted = self.cameraBtn.selected;
        model.displayName = @"我";
    }
    
    if (model.displayName.length == 0) {
        model.displayName = [self.rtcManager displayName:model.uid];
    }
    
    cell.userModel = model;
     
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath{
    RTCRemoteUserModel *model =  _dataArr[indexPath.row];
    
    //remoteUserModel 订阅小流
    //不能是自己
//    NSString *uid = self.remoteUsermodel.uid;
//    if (uid.length > 0 && ![uid isEqualToString:@"me"]) {
//        [self.rtcManager configRemoteTrack:self.remoteUsermodel.uid preferMaster:NO enable:YES];
//        [self.rtcManager subscribe:self.remoteUsermodel.uid onResult:^(NSString * _Nonnull uid, AliRtcVideoTrack vt, AliRtcAudioTrack at) {
//
//        }];
//    }
    //点击的对象订阅大流
    self.remoteUsermodel = model;
    //不能是自己
//    if (model.uid.length > 0 && ![model.uid isEqualToString:@"me"]) {
//        [self.rtcManager configRemoteTrack:model.uid preferMaster:YES enable:YES];
//        [self.rtcManager subscribe:model.uid onResult:^(NSString * _Nonnull uid, AliRtcVideoTrack vt, AliRtcAudioTrack at) {
//        }];
//    }
    
    [self setupMainRenderView];
    [self loadData];
 
}
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake(120, 90);
}
- (void)loadData{
    _dataArr = @[].mutableCopy;
    
    //上麦后才预览自己
   
    if(self.isJoinChannel && ![self.remoteUsermodel.uid isEqual:@"me"]) {
        RTCRemoteUserModel *model = [[RTCRemoteUserModel alloc] init];
        model.uid   = @"me";
        model.track = AliRtcVideoTrackCamera;
        model.view  = self.localCanvas.view;
        [_dataArr addObject:model];
    }
   
    
    for (RTCRemoteUserModel *userModel in [self.remoteUserManager allOnlineUsers]) {
        if(userModel.track > AliRtcVideoTrackNo) {
            [_dataArr addObject:userModel];
        }
    } 
    
    [_dataArr removeObject:self.remoteUsermodel];
    
    [self.remoteUserView reloadData];
}

#pragma mark - setter & getters
- (UIButton *)exitBtn{
    if (!_exitBtn) {
        _exitBtn = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 58, 27)];
       [_exitBtn setTitle:@" 退出课程 " forState:UIControlStateNormal];
       [_exitBtn addTarget:self action:@selector(exitChanel:) forControlEvents:UIControlEventTouchUpInside];
       [_exitBtn setBackgroundImage:[UIImage imageWithColor:[UIColor colorWithHex:0xFC4448]] forState:UIControlStateNormal];
       _exitBtn.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:13];
       _exitBtn.layer.cornerRadius = 2;
       _exitBtn.layer.masksToBounds = YES;
    }
    return _exitBtn;;
}

- (AliVideoCanvas *)localCanvas{
    if (!_localCanvas) {
        _localCanvas = [[AliVideoCanvas alloc] init];
        _localCanvas.renderMode = AliRtcRenderModeFill;
        _localCanvas.view = [[AliRenderView alloc] init];
        [self.rtcManager setLocalViewConfig:_localCanvas forTrack:AliRtcVideoTrackCamera];
    }
    return _localCanvas;
}


- (void)setCountDown:(NSInteger)countDown {
    _countDown = countDown;
     self.btnsView.hidden = countDown <= 0;
     self.navigationController.navigationBar.hidden =  countDown <= 0;
  
}

- (void)setSelfNetworkQuality:(AliRtcNetworkQuality)selfNetworkQuality {
    if (_selfNetworkQuality != selfNetworkQuality) {
        _selfNetworkQuality = selfNetworkQuality;
        
        //更新Label
        dispatch_async(dispatch_get_main_queue(), ^{
            if (selfNetworkQuality >= AlivcRtcNetworkQualityBad) {
                self.networkLabel.text = @"当前网络不佳";
            }else{
                self.networkLabel.text = @"";
            }
        });
    }
    
}

- (void)setOtherNetworkQuality:(AliRtcNetworkQuality)otherNetworkQuality {
    if (_otherNetworkQuality != otherNetworkQuality) {
        _otherNetworkQuality = otherNetworkQuality;
        //更新Label
        dispatch_async(dispatch_get_main_queue(), ^{
            if (otherNetworkQuality >= AlivcRtcNetworkQualityBad) {
                 self.networkLabel.text = @"对方网络不佳";
            }else{
                 self.networkLabel.text = @"";
            }
        });
    }
}

- (void)setIsJoinChannel:(BOOL)isJoinChannel {
    _isJoinChannel = isJoinChannel;
     __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if (weakSelf.isJoinChannel) {
            weakSelf.muteBtn.alpha = 1;
            weakSelf.cameraBtn.alpha = 1;
            weakSelf.flipBtn.alpha = 1;
            weakSelf.joinBtn.selected = YES;
        }else{
            weakSelf.joinBtn.selected = NO;
            weakSelf.muteBtn.selected = NO;
            weakSelf.cameraBtn.selected = NO;
            weakSelf.flipBtn.selected = NO;
            weakSelf.cameraBtn.alpha = 0.5;
            weakSelf.muteBtn.alpha = 0.5;
            weakSelf.flipBtn.alpha = 0.5;
        }
    });
}

- (void)setRemoteUsermodel:(RTCRemoteUserModel *)remoteUsermodel {
    if (remoteUsermodel) {
        //原来的订阅小流
        if (_remoteUsermodel.uid.length > 0 && ![_remoteUsermodel.uid isEqualToString:@"me"]) {
            [self.rtcManager configRemoteTrack:_remoteUsermodel.uid preferMaster:NO enable:YES];
            [self.rtcManager subscribe:_remoteUsermodel.uid onResult:^(NSString * _Nonnull uid, AliRtcVideoTrack vt, AliRtcAudioTrack at) {
                
            }];
        }
        //新的订阅大流
        if (remoteUsermodel.uid.length > 0 && ![remoteUsermodel.uid isEqualToString:@"me"]) {
            [self.rtcManager configRemoteTrack:remoteUsermodel.uid preferMaster:YES enable:YES];
            [self.rtcManager subscribe:remoteUsermodel.uid onResult:^(NSString * _Nonnull uid, AliRtcVideoTrack vt, AliRtcAudioTrack at) {
                
            }];
        }
    }
    
    _remoteUsermodel = remoteUsermodel;
           
    [self setupMainRenderView];
}
@end
