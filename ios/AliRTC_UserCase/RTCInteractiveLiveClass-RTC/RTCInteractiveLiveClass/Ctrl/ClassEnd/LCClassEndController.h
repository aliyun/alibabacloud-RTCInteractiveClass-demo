//
//  LCClassEndController.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/13.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCClassEndController : UIViewController

/// 展示信息
/// @param teacherName 教师名称
/// @param startTime 开始时间
/// @param users 在线人数
/// @param connectUsers 连麦人数
- (void)classEAndWithTeacherName:(NSString *)teacherName startTime:(NSTimeInterval)startTime onlineUsers:(NSInteger)users connectUsers:(NSInteger)connectUsers;

@end

NS_ASSUME_NONNULL_END
