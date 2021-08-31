//
//  LCClassEndController.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/13.
//

#import "LCClassEndController.h"
#import "UIImage+Color.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "CommonUtils.h"
#import "NetworkManager.h"
#import "AppConfig.h"

@interface LCClassEndController ()
@property (unsafe_unretained, nonatomic) IBOutlet UIImageView *topBgIcon;
@property (weak, nonatomic) IBOutlet UILabel *teacherNameLabel;
@property (weak, nonatomic) IBOutlet UILabel *startTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *classDurationLabel;
@property (weak, nonatomic) IBOutlet UILabel *onlineUsersLabel;
@property (weak, nonatomic) IBOutlet UILabel *connecUsersLabel;

@end

@implementation LCClassEndController

- (instancetype)init {
    return [[NSBundle RILC_storyboard] instantiateViewControllerWithIdentifier:@"LCClassEndController"];
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


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithImage:[NSBundle RILC_pngImageWithName:@"angle_left"] style:UIBarButtonItemStylePlain target:self action:@selector(back)];
    self.navigationItem.leftBarButtonItem = leftItem;
     
    UIImage *image = [UIImage imageWithColor:[[UIColor whiteColor]colorWithAlphaComponent:0]];
    [self.navigationController.navigationBar setBackgroundImage:image forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:image];
    
    self.topBgIcon.image = [NSBundle RILC_pngImageWithName:@"classEnd"];
}

- (void)classEAndWithTeacherName:(NSString *)teacherName startTime:(NSTimeInterval)startTime onlineUsers:(NSInteger)users connectUsers:(NSInteger)connectUsers {
    
    NSTimeInterval end = [[CommonUtils currentTimeStr] longLongValue];
    
    NSInteger seconds = (end - startTime) / 1000;
    //hour
    NSString *str_hour = [NSString stringWithFormat:@"%02d",(int)(seconds/3600)];
    //minute
    NSString *str_minute = [NSString stringWithFormat:@"%02d",(int)((seconds%3600)/60)];
    //second
    NSString *str_second = [NSString stringWithFormat:@"%02d",(int)(seconds%60)];
    NSString *onlineTime = [NSString stringWithFormat:@"%@:%@:%@",str_hour,str_minute,str_second];
    
    //教师名称
    NSString *teacherString = [NSString stringWithFormat:@"教师:%@",teacherName];
    self.teacherNameLabel.text = teacherString;
    
    //开始时间
    self.startTimeLabel.text = [CommonUtils timeWithTimeIntervalString:startTime dateFormatter:@"MM-dd HH:mm"];
    
    //课程时长
    self.classDurationLabel.text = onlineTime;
    
    //在线人数
    self.onlineUsersLabel.text = [NSString stringWithFormat:@"%ld",(long)users];
    
    //连麦人数
    self.connecUsersLabel.text = [NSString stringWithFormat:@"%ld",(long)connectUsers];
}


- (void)back {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self respondsToSelector:@selector(presentingViewController)]) {
            [self.presentingViewController.presentingViewController dismissViewControllerAnimated:YES completion:nil];
        }
    });
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
