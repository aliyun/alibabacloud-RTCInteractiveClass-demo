//
//  UIColor+Hex.h
//  Pods
//
//  Created by Aliyun on 2020/6/30.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (Hex)

+ (UIColor *)colorWithHex:(NSInteger)hex;

+ (UIColor *)colorWithHex:(NSInteger)hex alpha:(CGFloat)alpha;

@end

NS_ASSUME_NONNULL_END
