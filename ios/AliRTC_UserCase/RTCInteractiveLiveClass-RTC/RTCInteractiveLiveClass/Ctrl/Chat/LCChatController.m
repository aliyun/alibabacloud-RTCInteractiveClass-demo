//
//  LCChatController.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import "LCChatController.h"
#import "Masonry.h"
#import "UIColor+Hex.h"
#import "LCIMChatView.h"
#import "RTCHUD.h"
#import "AliImInterrativeEngine.h"


@interface LCChatController ()

@property (nonatomic, strong) UIView *emptyView;

@property (nonatomic, strong) UIView *contentView;
//标题
@property (nonatomic, strong) UILabel *titleLbl;
// 聊天视图
@property(nonatomic,strong) LCIMChatView *chatView;

@end

@implementation LCChatController

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

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor clearColor];
    
    [self configUI];
}

#pragma mark - 发送消息 -
- (void)chatInputSendMsgClick:(NSString *)msg {
    
    msg = [msg stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    if (msg.length == 0) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [RTCHUD showHud:@"不能发送空消息" inView:self.view];
        });
        return;
    }
    
    [[AliImInterrativeEngine sharedInstance] sendTextMessage:msg];
    
//    if (self.sendTextMessage) {
//        self.sendTextMessage(msg);
//    }
}


#pragma mark - 消息信令相关(接收) -
- (void)updateMessages:(NSArray<LCIMMessage *> *)messages {
    
    [self.chatView updateMessages:messages];
}



#pragma mark - 配置UI -
- (void)configUI {
    
    _emptyView = [UIView new];
    
    _contentView = [UIView new];
    _contentView.backgroundColor = [UIColor whiteColor];
    
    _titleLbl = [UILabel new];
    _titleLbl.textColor = [UIColor colorWithHex:0x2F2F2F];
    _titleLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:14];
    _titleLbl.text = @"实时互动";
    
    UIView *Line = [UIView new];
    Line.backgroundColor = [UIColor colorWithHex:0xEDEDED];
            
    
    [self.view addSubview:_emptyView];
    [self.view addSubview:_contentView];
    [_contentView addSubview:_titleLbl];
    [_contentView addSubview:Line];
    [_contentView addSubview:self.chatView];

    
    
    [_emptyView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.bottom.top.equalTo(self.view);
        make.right.equalTo(_contentView.mas_left);
    }];
    
    [_contentView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.top.bottom.right.equalTo(self.view);
        make.width.equalTo(@(320));
    }];
    
    [_titleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerX.equalTo(_contentView.mas_centerX);
        make.top.equalTo(_contentView.mas_top);
        make.height.equalTo(@(36));
    }];
    
    [Line mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.right.equalTo(_contentView);
        make.top.equalTo(_titleLbl.mas_bottom);
        make.height.equalTo(@(1));
    }];
    
    [_chatView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.bottom.right.equalTo(_contentView);
        make.top.equalTo(Line.mas_bottom).mas_offset(11);
    }];
    
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(closeSelf)];
    tap.numberOfTapsRequired = 1;
    [_emptyView addGestureRecognizer:tap];
}

- (void)closeSelf {
    
    if (self.backClick) {
        self.backClick();
    }
    [self dismissViewControllerAnimated:NO completion:nil];
}




- (void)viewDidLayoutSubviews {
    
    _contentView.layer.shadowColor = [UIColor colorWithHex:0x000000 alpha:0.21].CGColor;
    _contentView.layer.shadowOffset = CGSizeMake(0,3);
    _contentView.layer.shadowOpacity = 0.5;
    _contentView.layer.shadowRadius = 5;
    // 单边阴影 左边
    CGRect shadowRect = CGRectMake(-4, -4, 8, _contentView.bounds.size.height);
    UIBezierPath *path = [UIBezierPath bezierPathWithRect:shadowRect];
    _contentView.layer.shadowPath = path.CGPath;
}


- (LCIMChatView *)chatView {
    if (!_chatView) {
        _chatView = [[LCIMChatView alloc] init];
        __weak typeof(self) weakSelf = self;
        _chatView.SendMsgClick = ^(NSString * _Nullable message) {
            [weakSelf chatInputSendMsgClick:message];
        };
    }
    return _chatView;
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
