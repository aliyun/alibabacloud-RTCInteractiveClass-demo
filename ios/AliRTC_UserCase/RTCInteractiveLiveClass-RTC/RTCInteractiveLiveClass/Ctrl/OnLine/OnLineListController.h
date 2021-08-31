//
//  OnLineListController.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import <UIKit/UIKit.h>
#import "RTCRemoteUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface OnLineListController : UIViewController

/// 连麦用户
@property (nonatomic, strong) NSArray<RTCRemoteUserModel *> *seatArray;

/// 在线用户
@property (nonatomic, strong) NSArray<RTCRemoteUserModel *> *onlineArray;


@end

NS_ASSUME_NONNULL_END
