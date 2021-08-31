//
//  AppDelegate.m
//  RTCSolution
//
//  Created by Aliyun on 2020/6/28.
//  Copyright © 2020 Aliyun. All rights reserved.
//

#import "AppDelegate.h"
#import "RTCHomeViewController.h"
#import "RTCNavigationController.h"
#import <AliRTCSdk/AliRTCSdk.h>
#import "RTCCommon.h"
#import "RTCCommonView.h"
@interface AppDelegate () <UIAlertViewDelegate>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window =[[UIWindow alloc]initWithFrame:[UIScreen mainScreen].bounds];
    RTCNavigationController *nav =[[RTCNavigationController alloc]initWithRootViewController:[RTCHomeViewController new]];
    [self.window setRootViewController:nav];
    [self.window makeKeyAndVisible];
    NSString *version = [AliRtcEngine getSdkVersion];
    NSLog(@"%@",version);
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self checkVersion];
    });
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    NSLog(@"\n ===> 程序暂停 !");
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    
}
 
- (void)applicationDidEnterBackground:(UIApplication *)application {
    NSLog(@"\n ===> 进入后台 ！");
}

#pragma mark - 版本更新
- (void)checkVersion{
    
    NSString *plistUrl = @"https://alivc-demo-cms.alicdn.com/versionProduct/installPackage/RTC_Solution/InteractiveLiveClass/InteractiveLiveClass.plist";

    //大班课检测版本更新
    NSString *releaseNoteString = [self releaseNoteStringWithString:plistUrl];
    if (releaseNoteString) {
        UIAlertController *alertC = [UIAlertController alertControllerWithTitle:@"检测到新版本，是否更新？" message:releaseNoteString preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction *confirmAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            if (@available(iOS 10.0, *)) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"itms-services://?action=download-manifest&url=%@",plistUrl]] options:@{} completionHandler:nil];
            } else {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"itms-services://?action=download-manifest&url=%@",plistUrl]]];
            }
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                exit(0);
            });
        }];
        
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleDefault handler:nil];
        
        [alertC addAction:confirmAction];
        [alertC addAction:cancelAction];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.window.rootViewController presentViewController:alertC animated:YES completion:nil];
        });
    }
}

/**
 检查本地版本号与服务器版本号，看下有无更新
 
 @param plistString 服务器版本号所在的url字符串
 @return nil - 无更新， 有值 - 有更新并且返回更新内容
 */
- (NSString *)releaseNoteStringWithString:(NSString *)plistString{
    
    NSDictionary *dic = [NSDictionary dictionaryWithContentsOfURL:[NSURL URLWithString:plistString]];
    NSString *releaseNote = dic[@"items"][0][@"metadata"][@"releaseNote"];
    NSString *onLineVersion = dic[@"items"][0][@"metadata"][@"bundle-version"];
    
    NSString *localVerson = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    
    if([localVerson compare:onLineVersion options:NSNumericSearch] == NSOrderedAscending){
        return releaseNote;
    }
    return nil;
}

@end
