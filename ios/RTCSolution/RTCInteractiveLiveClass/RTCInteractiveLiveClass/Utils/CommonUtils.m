//
//  CommonUtils.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/25.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "CommonUtils.h"
#import <MBProgressHUD/MBProgressHUD.h>

@implementation CommonUtils
//
//+ (UIImage *)imageWithColor:(UIColor *)color {
//    CGRect rect = CGRectMake(0, 0, 1, 1);
//    UIGraphicsBeginImageContext(rect.size);
//    CGContextRef context = UIGraphicsGetCurrentContext();
//    [color setFill];
//    CGContextFillRect(context, rect);
//    UIImage *imgae = UIGraphicsGetImageFromCurrentImageContext();
//    UIGraphicsEndImageContext();
//    return imgae;
//}

//+ (UIColor *)colorWithHex:(NSInteger)hex {
//    return [UIColor colorWithRed:((float)((hex & 0xff0000) >> 16))/255.0 green:((float)((hex & 0x00ff00) >> 8))/255.0 blue:((float)(hex & 0x0000ff))/255.0 alpha:1.0];
//}

+ (void)showHud:(NSString*)msg inView:(UIView*)view {
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.label.text = msg;
    [hud hideAnimated:YES afterDelay:1.f];
}
@end
