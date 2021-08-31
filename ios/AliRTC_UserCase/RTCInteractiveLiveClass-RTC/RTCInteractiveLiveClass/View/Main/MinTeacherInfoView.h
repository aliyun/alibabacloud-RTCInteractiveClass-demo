//
//  MinTeacherInfoView.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/22.
//

#import <UIKit/UIKit.h>
#import "RTCRemoteUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface MinTeacherInfoView : UIView

@property (nonatomic, strong) UIView *renderview;

@property (nonatomic, strong) RTCRemoteUserModel *userModel;

@end

NS_ASSUME_NONNULL_END
