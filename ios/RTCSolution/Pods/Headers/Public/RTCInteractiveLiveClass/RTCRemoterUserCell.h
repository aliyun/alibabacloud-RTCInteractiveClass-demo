//
//  RTCRemoterUserCell.h
//  LectureHall
//
//  Created by Aliyun on 2020/5/25.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import <AliRTCSdk/AliRTCSdk.h>
#import "RTCRemoteUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RTCRemoterUserCell : UICollectionViewCell


@property (strong, nonatomic) RTCRemoteUserModel *userModel;



@end

NS_ASSUME_NONNULL_END
