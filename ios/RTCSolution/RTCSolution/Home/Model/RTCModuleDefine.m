//
//  RTC_ModuleDefine.m
//  AliyunVideoClient_Entrance
//
//  Created by Aliyun on 2018/3/22.
//  Copyright © 2018年 Alibaba. All rights reserved.
//

#import "RTCModuleDefine.h"

@implementation RTCModuleDefine

- (instancetype)init{
    self = [self initWithModuleType:RTC_ModuleType_AudioChat1To1];
    return self;
}

- (instancetype)initWithModuleType:(RTC_ModuleType)type{
    self = [super init];
    if (self) {
        _type = type;
        _name = [RTCModuleDefine nameWithModuleType:type];
        _image = [RTCModuleDefine imageWithModuleType:type];
    }
    return self;
}

+ (NSString *)nameWithModuleType:(RTC_ModuleType)type{
    switch (type) {
        case RTC_ModuleType_AudioChat1To1:
            return @"一对一语聊";
            break;
        case RTC_ModuleType_InteractiveClass:
            return @"互动大班课";
            break;
        case RTC_ModuleType_AudioChatRoom:
            return @"语音聊天室";
        case RTC_ModuleType_VideoLiveRoom:
            return @"视频互动直播";
            break;
            
    }
}

+ (UIImage *__nullable)imageWithModuleType:(RTC_ModuleType)type{
    switch (type) {
        case RTC_ModuleType_AudioChat1To1:
            return [UIImage imageNamed:@"1v1"];
            break;
        case RTC_ModuleType_InteractiveClass:
            return [UIImage imageNamed:@"interactiveLiveClass"];
            break;
        case RTC_ModuleType_AudioChatRoom:
            return [UIImage imageNamed:@"chatRoom"];
        case RTC_ModuleType_VideoLiveRoom:
            return [UIImage imageNamed:@"videoliveClass"];
            break;
    }
    
}


+ (NSArray <RTCModuleDefine *>*)allModules{
    NSMutableArray *mArray = [[NSMutableArray alloc]init];
    for (int i = 0; i < 7; i ++) {
        RTC_ModuleType type = (RTC_ModuleType)i;
        RTCModuleDefine *module = [[RTCModuleDefine alloc]initWithModuleType:type];
        [mArray addObject:module];
    }
    return (NSArray *)mArray;
}


+ (NSArray <RTCModuleDefine *>*)allDemos{
    NSMutableArray *mArray = [[NSMutableArray alloc]init];
    for (int i = 7; i < 12; i ++) {
        RTC_ModuleType type = (RTC_ModuleType)i;
        RTCModuleDefine *module = [[RTCModuleDefine alloc]initWithModuleType:type];
        [mArray addObject:module];
    }
    return (NSArray *)mArray;
}

@end
