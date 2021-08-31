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
#import "RTCCommonView.h"
#import "ALiIMManager.h"
#import "NavigationController.h"

@interface LoginController () <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet LoadingButton *loginBtn;
@property (weak, nonatomic) IBOutlet UITextField *nameTextField;
@property (weak, nonatomic) IBOutlet UITextField *roomTextField;
@property (weak, nonatomic) IBOutlet UIView *codeView;
@property (nonatomic,strong) NSMutableArray *codeArr;
@property (weak, nonatomic) IBOutlet UILabel *studentNameLabel;
@property (weak, nonatomic) IBOutlet UILabel *classroomLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *sdkVersionLbl;

@end

@implementation LoginController

- (instancetype)init {
    UIStoryboard *storyboard = [NSBundle RILC_storyboard];
    return [storyboard instantiateViewControllerWithIdentifier:@"LoginController"];
}


//支持旋转
-(BOOL)shouldAutorotate{
    return NO;
}

//支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

//一开始的方向  很重要
-(UIInterfaceOrientation)preferredInterfaceOrientationForPresentation{
    return UIInterfaceOrientationPortrait;
}

- (UIStatusBarStyle) preferredStatusBarStyle {
    if (@available(iOS 13.0, *)) {
        return UIStatusBarStyleDarkContent;
    } else {
        return UIStatusBarStyleDefault;
    }
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBar.tintColor = [UIColor blackColor];
    [self checkLoginButtonStatus];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
        
    
    [self initUI];
    
    [self registNotification];
}

- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}

-(void)initUI {

    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithImage:[NSBundle RILC_pngImageWithName:@"angle_left"] style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    self.navigationItem.leftBarButtonItem = leftItem;
     
    UIImage *image = [UIImage imageWithColor:[[UIColor whiteColor]colorWithAlphaComponent:0]];
    [self.navigationController.navigationBar setBackgroundImage:image forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:image];

    //loginButton
    [_loginBtn setBackgroundColor:[UIColor colorWithRed:1/255.0 green:62/255.0 blue:190/255.0 alpha:1/1.0] forState:UIControlStateNormal];
    [_loginBtn setBackgroundColor:[UIColor colorWithRed:182/255.0 green:197/255.0 blue:233/255.0 alpha:1/1.0] forState:UIControlStateDisabled];
    _loginBtn.enabled = NO;
    
    
    [_roomTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    [_nameTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    
    NSAttributedString *roomPlaceHolder = [[NSAttributedString alloc] initWithString:@"教室码（6位数字）" attributes:
                                           @{NSForegroundColorAttributeName:[UIColor colorWithHex:0x262626],
                                             NSFontAttributeName:_roomTextField.font
                                           }];
    
    _roomTextField.attributedPlaceholder = roomPlaceHolder;
    
    
    NSAttributedString *namePlaceHolder = [[NSAttributedString alloc] initWithString:@"学生姓名" attributes:
                                           @{NSForegroundColorAttributeName:[UIColor colorWithHex:0x262626],
                                             NSFontAttributeName:_nameTextField.font
                                           }];
    
    _nameTextField.attributedPlaceholder = namePlaceHolder;
    
    
    [self fillCodeView];
    
        
    self.sdkVersionLbl.text = [NSString stringWithFormat:@"rtc version:%@\naim version:%@",[AliRtcEngine getSdkVersion],@"3.0.0.23"];
    
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

- (IBAction)onLogin:(LoadingButton *)sender {
    if (_nameTextField.text.length<=0) {
        [RTCHUD showHud:@"请输入用户名" inView:self.view];
        return;
    }
    if (_roomTextField.text.length != 6) {
        [RTCHUD showHud:@"请输入6位房间号" inView:self.view];
        return;
    }
    
    [sender startLoading];
    
    __weak typeof(self)weakSelf = self;
    [[ALiIMManager sharedInstance] getGroupWithChannel:self.roomTextField.text success:^(NSString * _Nonnull appCid) {
        
        [sender stopLoading];
        
        if ([appCid isKindOfClass:[NSNull class]] || [appCid isEqual:[NSNull null]] || appCid == nil) {
            
            [RTCHUD showHud:@"请确认老师是否已经创建教室,\n仅可通过PC端老师创建教室" inView:weakSelf.view];
        }else {
            MainController *vc = [[NSBundle RILC_storyboard] instantiateViewControllerWithIdentifier:@"MainController"];
            vc.userName = weakSelf.nameTextField.text;
            vc.channel = weakSelf.roomTextField.text;
            
            NavigationController *nav = [[NavigationController alloc] initWithRootViewController:vc];
            nav.modalPresentationStyle = UIModalPresentationFullScreen;
            [weakSelf presentViewController:nav animated:YES completion:^{
                [weakSelf resetInputFields];
            }];
        }
    } failure:^(NSString * _Nonnull error) {
        [sender stopLoading];
        [RTCHUD showHud:error inView:weakSelf.view];
    }];
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
    
    [self checkLoginButtonStatus];
}

- (void)checkLoginButtonStatus
{
    if (_roomTextField.text.length==6 && _nameTextField.text.length>0)
    {
        self.loginBtn.enabled = YES;
    } else {
        self.loginBtn.enabled = NO;
    }
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
