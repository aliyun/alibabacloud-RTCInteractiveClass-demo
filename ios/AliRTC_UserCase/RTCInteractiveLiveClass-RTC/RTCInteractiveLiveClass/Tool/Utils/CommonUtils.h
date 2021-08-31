//
//  CommonUtils.h
//  LectureHall
//
//  Created by Aliyun on 2020/5/25.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CommonUtils : NSObject

//+ (UIImage *)imageWithColor:(UIColor *)color;
//
//+ (UIColor *)colorWithHex:(NSInteger)hex;

//+ (void)showHud:(NSString*)msg inView:(UIView*)view;

//获取当前时间戳  精确到毫秒
+ (NSString *)currentTimeStr;

//时间戳转换日期
+ (NSString *)timeWithTimeIntervalString:(long long)time dateFormatter:(NSString *)formatter;


@end

NS_ASSUME_NONNULL_END
