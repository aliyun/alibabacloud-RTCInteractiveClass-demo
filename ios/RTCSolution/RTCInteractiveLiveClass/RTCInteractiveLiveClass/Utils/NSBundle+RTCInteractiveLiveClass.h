//
//  NSBundle+RTCInteractiveLiveClass.h
//  RTCInteractiveLiveClass
//
//  Created by Aliyun on 2020/6/28.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSBundle (RTCInteractiveLiveClass)

+ (instancetype)RTC_InteractiveLiveClassBundle;

+ (UIImage *)RILC_imageWithName:(NSString *)name type:(NSString *)type;

+ (UIImage *)RILC_pngImageWithName:(NSString *)name;
 
+ (UIStoryboard *)RILC_storyboard;

+ (NSString *)RILC_musicPathForResource:(NSString *)name;
@end

NS_ASSUME_NONNULL_END
