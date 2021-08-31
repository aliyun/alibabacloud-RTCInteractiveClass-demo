//
//  MainRemoterUserCCell.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import <UIKit/UIKit.h>
#import "RTCRemoteUserModel.h"


NS_ASSUME_NONNULL_BEGIN

@interface MainRemoterUserCCell : UICollectionViewCell

@property (strong, nonatomic) RTCRemoteUserModel *userModel;
//音频
@property (strong,nonatomic,readonly) UIButton *muteBtn;
//相机
@property (strong,nonatomic,readonly) UIButton *cameraBtn;

/// 静音流按钮点击回调
@property (nonatomic, copy) void(^muteBtnClick)(UIButton *btn);
/// 视频流按钮点击回调
@property (nonatomic, copy) void(^videoBtnClick)(UIButton *btn);

@end

NS_ASSUME_NONNULL_END
