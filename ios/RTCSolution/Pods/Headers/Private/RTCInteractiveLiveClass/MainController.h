//
//  MainController.h
//  LectureHall
//
//  Created by Aliyun on 2020/5/22.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
 

@class AliRtcAuthInfo;

@interface MainController : UIViewController

//@property(nonatomic,strong) AliRtcAuthInfo *authInfo;

@property(nonatomic,copy) NSString *userName;

@property(nonatomic,copy) NSString *channel;


@end

NS_ASSUME_NONNULL_END
