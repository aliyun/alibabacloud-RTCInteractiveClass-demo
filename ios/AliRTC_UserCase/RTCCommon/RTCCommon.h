//
//  RTCCommon.h
//  RTCCommon
//
//  Created by Aliyun on 2020/7/1.
//

#ifndef RTCCommon_h
#define RTCCommon_h

#import "RTCMacro.h"
#import "AppConfig.h"
#import "NetworkManager.h"

#if TARGET_OS_IOS
    #import "UIColor+Hex.h"
    #import "UIImage+Color.h"
   
#endif


#if TARGET_OS_IOS
    #define RenderView UIView
#else
    #define RenderView NSView
#endif



#endif /* RTCCommon_h */
