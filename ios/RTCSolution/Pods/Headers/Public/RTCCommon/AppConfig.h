//
//  AppConfig.h
//  LectureHall
//
//  Created by Aliyun on 2020/5/22.
//  Copyright © 2020 alibaba. All rights reserved.
//

#ifndef AppConfig_h
#define AppConfig_h

//====================================  URL 常量 start =========================================================================

#define kBaseUrl                                @""
//#define kBaseUrl                                @""

#define kProject_1v1Audio                       @"1v1-audio"
#define kProject_InteractiveClass               @"interactive-live-class"
#define kProject_Chatroom                       @"chatroom"
#define kProject_VideoRoom                      @"live-pk"


#define kBaseUrl_1v1Audio                       [NSString stringWithFormat:@"%@%@/",kBaseUrl,kProject_1v1Audio]
#define kBaseUrl_InteractiveClass               [NSString stringWithFormat:@"%@%@/",kBaseUrl,kProject_InteractiveClass]
#define kBaseUrl_Chatroom                       [NSString stringWithFormat:@"%@%@/",kBaseUrl,kProject_Chatroom]
#define kBaseUrl_VideoRoom                      [NSString stringWithFormat:@"%@%@/",kBaseUrl,kProject_VideoRoom]

#define kMP3BaseUrl                             @"https://alivc-demo-cms.alicdn.com/versionProduct/resources/"

#define mp3url(name)                            [NSString stringWithFormat:@"%@%@",kMP3BaseUrl,name]

#define KShareBaseUrl_InteractiveClass          @"https://alivc-demo-cms.alicdn.com/html-demo/play-class/"
                             

//=====================================  URL 常量 end ==========================================================================

#endif /* AppConfig_h */
