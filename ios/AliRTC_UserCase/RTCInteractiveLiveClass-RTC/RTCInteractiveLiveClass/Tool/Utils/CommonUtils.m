//
//  CommonUtils.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/25.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "CommonUtils.h"
//#import <MBProgressHUD/MBProgressHUD.h>
#import "MBProgressHUD.h"

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

//获取当前时间戳
+ (NSString *)currentTimeStr {
    
    NSDate* date = [NSDate dateWithTimeIntervalSinceNow:0];//获取当前时间0秒后的时间
    NSTimeInterval time=[date timeIntervalSince1970]*1000;// *1000 是精确到毫秒，不乘就是精确到秒
    NSString *timeString = [NSString stringWithFormat:@"%.0f", time];
    return timeString;
}

//时间戳转换日期
+ (NSString *)timeWithTimeIntervalString:(long long)time dateFormatter:(NSString *)formatter {
    
    NSString *timeStr = [NSString stringWithFormat:@"%lld",time];
    
    if (timeStr.length <= 13) {
        time = time / 1000.0;
    }
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:time];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    if (!formatter) {
        formatter = @"yyyy-MM-dd HH:mm:ss";
    }
    [dateFormatter setDateFormat:formatter];
    NSString *destDateString = [dateFormatter stringFromDate:date];
    return destDateString;
}



+ (void)showHud:(NSString*)msg inView:(UIView*)view {
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.label.text = msg;
    [hud hideAnimated:YES afterDelay:1.f];
}
@end
