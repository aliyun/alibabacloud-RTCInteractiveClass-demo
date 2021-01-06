//
//  LoginController.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/22.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "LoginController.h"
#import "CommonUtils.h"
#import "MainController.h"
#import <AliRTCSdk/AliRTCSdk.h>
#import "NetworkManager.h"
#import "AppConfig.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "UIImage+Color.h"
#import "UIColor+Hex.h"
#import "RTCHUD.h"



@interface LoginController () <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UIButton *loginBtn;
@property (weak, nonatomic) IBOutlet UITextField *nameTextField;
@property (weak, nonatomic) IBOutlet UITextField *roomTextField;
@property (weak, nonatomic) IBOutlet UIView *codeView;
@property (nonatomic,strong) NSMutableArray *codeArr;
@property (weak, nonatomic) IBOutlet UILabel *studentNameLabel;
@property (weak, nonatomic) IBOutlet UILabel *classroomLabel;

@end

@implementation LoginController

- (instancetype)init {
    UIStoryboard *storyboard = [NSBundle RILC_storyboard];
    return [storyboard instantiateViewControllerWithIdentifier:@"LoginController"];
}
 
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initUI];
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBar.tintColor = [UIColor blackColor];
}

-(void)initUI {
//    AppDelegate * app = (AppDelegate *)[[UIApplication sharedApplication] delegate];
//    app.isLandscape = NO;
//    self.navigationController.navigationBar.topItem.title = @"";
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithImage:[NSBundle RILC_pngImageWithName:@"angle_left"] style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    self.navigationItem.leftBarButtonItem = leftItem;
     
    UIImage *image = [UIImage imageWithColor:[[UIColor whiteColor]colorWithAlphaComponent:0]];
    [self.navigationController.navigationBar setBackgroundImage:image forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:image];
    
    [_loginBtn setBackgroundImage:[UIImage imageWithColor:[UIColor colorWithHex:0x013EBE]] forState:UIControlStateNormal];
    
    [_loginBtn setBackgroundImage:[UIImage imageWithColor:[UIColor colorWithHex:0xB6C5E9]] forState:UIControlStateDisabled];
    
    [_loginBtn setEnabled:NO];
    
    [self registNotification];
    
    [_roomTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    [_nameTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    
    NSAttributedString *roomPlaceHolder = [[NSAttributedString alloc] initWithString:@"请输入教室编号" attributes:
                                           @{NSForegroundColorAttributeName:[UIColor colorWithHex:0x262626],
                                             NSFontAttributeName:_roomTextField.font
                                           }];
    
    _roomTextField.attributedPlaceholder = roomPlaceHolder;
    
    
    NSAttributedString *namePlaceHolder = [[NSAttributedString alloc] initWithString:@"请输入学生姓名" attributes:
                                           @{NSForegroundColorAttributeName:[UIColor colorWithHex:0x262626],
                                             NSFontAttributeName:_nameTextField.font
                                           }];
    
    _nameTextField.attributedPlaceholder = namePlaceHolder;
    
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.4 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self fillCodeView];
    });
}

- (UIStatusBarStyle) preferredStatusBarStyle {
    if (@available(iOS 13.0, *)) {
        return UIStatusBarStyleDarkContent;
    } else {
        return UIStatusBarStyleDefault;
    }
}

#pragma mark - codeView
-(void)fillCodeView{
    while (self.codeView.subviews.count) {
        [self.codeView.subviews.lastObject removeFromSuperview];
    }
    
    _codeArr = @[].mutableCopy;
    CGFloat itemWidth = (CGRectGetWidth(self.view.frame)-72)/6;
    for (int i=0; i<6; i++) {
        [self buildCodeAtIdx:i width:itemWidth];
    }
}

-(void)buildCodeAtIdx:(int)idx width:(int)itemWidth{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(idx*itemWidth, 0, itemWidth, CGRectGetHeight(self.codeView.frame))];
    [label setFont:[UIFont fontWithName:@"PingFangSC-Medium" size:20]];
    [label setTextColor:[UIColor blackColor]];
    [label setTextAlignment:NSTextAlignmentCenter];
    [self.codeView addSubview:label];
    [_codeArr addObject:label];
    
    //画断线
    UIView *line = [[UIView alloc] initWithFrame:CGRectMake(CGRectGetMinX(label.frame)+4, CGRectGetMaxY(label.frame)+2, CGRectGetWidth(label.frame)-8, 1)];
    [line setBackgroundColor:[UIColor blackColor]];
    [self.codeView addSubview:line];
}

#pragma mark - notification 通知管理
- (void)registNotification
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
}

#pragma mark --键盘弹出收起管理
-(void)keyboardWillShow:(NSNotification *)note{
    [UIView animateWithDuration:0.1 animations:^{
        self.view.frame = CGRectMake(0, -80, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame));
    }];
}

-(void)keyboardWillHide:(NSNotification *)note{
    [UIView animateWithDuration:0.1 animations:^{
        self.view.frame = CGRectMake(0, 0, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame));
    }];
}

#pragma mark - Navigation
//-(void)requestToken:(NSString *)channel{
//    __weak typeof(self)weakSelf = self;
//    [NetworkManager GET:kRouteAppToken parameters:@{@"channelId":channel} completionHandler:^(NSString * _Nullable errString, NSDictionary * _Nullable resultDic) {
//        if(!errString){
//            AliRtcAuthInfo *authInfo = [[AliRtcAuthInfo alloc] init];
//            authInfo.appid = resultDic[@"appid"];
//            authInfo.user_id = resultDic[@"userid"];
//            authInfo.channel = channel;
//            authInfo.nonce = resultDic[@"nonce"];
//            authInfo.timestamp = [resultDic[@"timestamp"] longLongValue];
//            authInfo.token = resultDic[@"token"];
//            authInfo.gslb = resultDic[@"gslb"];
//            authInfo.agent = @[@""];
//
//            MainController *vc = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"MainController"];
//            vc.authInfo = authInfo;
//            [weakSelf.navigationController pushViewController:vc animated:YES];
//        }
//    }];
//
//}

-(void)requestToken:(NSString *)channel{
    __weak typeof(self)weakSelf = self;
    //判断房间人数
//    [NetworkManager GET:[kBaseUrl_InteractiveClass stringByAppendingString:@"describeChannelUsers"] parameters:@{@"channelId":channel} completionHandler:^(NSString * _Nullable errString, NSDictionary * _Nullable resultDic) {
//        NSInteger num = [resultDic[@"commTotalNum"] integerValue];
//        if (num > 0) {
            
    
    MainController *vc = [[NSBundle RILC_storyboard] instantiateViewControllerWithIdentifier:@"MainController"];
    vc.userName = weakSelf.nameTextField.text;
    vc.channel = channel;
    [weakSelf.navigationController pushViewController:vc animated:YES];
    [self resetInputFields];
    weakSelf.loginBtn.enabled = YES;
    
    
  
            
//        } else {
//            [self showAlert:@"教室码不存在,若未创建教室,请先从电脑端创建"];
//             weakSelf.loginBtn.enabled = YES;
//
//        }
//    }];
 
    
}

- (void)showAlert:(NSString *)msg {
      UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"提示"
                                                                               message:msg
                                                                        preferredStyle:UIAlertControllerStyleAlert];
      UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
      }];
      [alertController addAction:confirm];
      [self.navigationController presentViewController:alertController animated:YES completion:nil];
}
- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}
- (IBAction)onLogin:(UIButton *)sender {
    if (_nameTextField.text.length<=0) {
        [RTCHUD showHud:@"请输入用户名" inView:self.view];
        return;
    }
    if (_roomTextField.text.length != 6) {
        [RTCHUD showHud:@"请输入6位房间号" inView:self.view];
        return;
    }
    sender.enabled = NO;
    [self requestToken:_roomTextField.text];
}

- (IBAction)onTap:(id)sender {
    [self.view endEditing:YES];
}

- (IBAction)onCodeViewTap:(id)sender {
    [_roomTextField becomeFirstResponder];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField{
    if(textField==_roomTextField){
        _codeView.hidden = NO;
        _classroomLabel.hidden = NO;
    }
    if (textField == _nameTextField) {
        _studentNameLabel.hidden = NO;
    }
    return YES;
}


- (void)textFieldDidEndEditing:(UITextField *)textField{
    if(textField==_roomTextField){
        _codeView.hidden = !textField.text.length;;
        _classroomLabel.hidden = !textField.text.length;
    }
    
    if (textField == _nameTextField) {
         _studentNameLabel.hidden = !textField.text.length;
    }
   
}

-(UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

-(void)textFieldDidChange :(UITextField *)textField{
    NSLog( @"text changed: %@", textField.text);
    if (textField==_roomTextField) {
        if (textField.text.length>6) {
            textField.text = [textField.text substringToIndex:6];
        }
        for (UILabel *lab in _codeArr) {
            [lab setText:@""];
        }
        for (int i=0; i<MIN(textField.text.length, _codeArr.count); i++) {
            NSString *code = [textField.text substringWithRange:NSMakeRange(i, 1)];
            [_codeArr[i] setText:code];
        }
    }
    if (_roomTextField.text.length==6 && _nameTextField.text.length>0) {
        [_loginBtn setEnabled:YES];
    }else{
        [_loginBtn setEnabled:NO];
    }
}

- (void)resetInputFields {
    self.nameTextField.text = nil;
    self.roomTextField.text = nil;
    self.studentNameLabel.hidden = YES;
    self.classroomLabel.hidden = YES;
    
    [self textFieldDidChange:self.nameTextField];
    [self textFieldDidChange:self.roomTextField];
    
    [self onTap:nil];
    
    [self textFieldDidEndEditing:self.nameTextField];
    [self textFieldDidEndEditing:self.roomTextField];
}
@end
