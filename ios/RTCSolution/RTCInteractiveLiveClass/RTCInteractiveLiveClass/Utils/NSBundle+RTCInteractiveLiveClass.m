//
//  NSBundle+RTCInteractiveLiveClass.m
//  RTCInteractiveLiveClass
//
//  Created by Aliyun on 2020/6/28.
//

#import "NSBundle+RTCInteractiveLiveClass.h"
#import "LoginController.h"
#import "NSBundle+RTCCommonView.h"

@implementation NSBundle (RTCInteractiveLiveClass)

+ (instancetype)RTC_InteractiveLiveClassBundle{
    static NSBundle *VoiceCall = nil;
    if (VoiceCall == nil) {
        NSString *bundlePath = [[NSBundle bundleForClass:[LoginController class]] pathForResource:@"RTCInteractiveLiveClass" ofType:@"bundle"];
        VoiceCall = [NSBundle bundleWithPath:bundlePath];
    }
    return VoiceCall;
}

+ (UIImage *)RILC_imageWithName:(NSString *)name type:(NSString *)type{
    int scale = [[UIScreen mainScreen] scale] <= 2 ? 2 : 3;
    NSString *fullName = [NSString stringWithFormat:@"%@@%dx",name,scale];
    NSString *path =  [[NSBundle RTC_InteractiveLiveClassBundle] pathForResource:fullName ofType:type];
    UIImage *image = [UIImage imageNamed:path];
    //如果不存在 则直接加载name.type
    if (!image) {
        path =  [[NSBundle RTCCommonViewBundle] pathForResource:name ofType:type];
        image = [UIImage imageNamed:path];
    }
    return image;
}

+ (UIImage *)RILC_pngImageWithName:(NSString *)name{
    UIImage *image = [NSBundle  RILC_imageWithName:name type:@"png"];
    //从commonView中查找
    if (!image) {
        image = [NSBundle RCV_pngImageWithName:name];
    }
    return image;
}


+ (UIStoryboard *)RILC_storyboard {
    return [UIStoryboard storyboardWithName:@"RTCInteractiveLiveClass" bundle:[NSBundle bundleForClass:[LoginController class]]];
}

+ (NSString *)RILC_musicPathForResource:(NSString *)name {
    return [NSBundle RCV_pathForResource:name];
}
@end
