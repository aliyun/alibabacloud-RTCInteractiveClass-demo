//
//  OnlineListTCell.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/22.
//

#import <UIKit/UIKit.h>
#import "RTCRemoteUserModel.h"


NS_ASSUME_NONNULL_BEGIN

@interface OnlineListTCell : UITableViewCell

@property (nonatomic, strong) RTCRemoteUserModel *model;

@end

NS_ASSUME_NONNULL_END
