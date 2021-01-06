//
//  AlertMsgController.h
//  LectureHall
//
//  Created by Aliyun on 2020/5/27.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface AlertMsgController : UIViewController

@property(nonatomic,copy) void(^submitblock)(void);

@end

NS_ASSUME_NONNULL_END
