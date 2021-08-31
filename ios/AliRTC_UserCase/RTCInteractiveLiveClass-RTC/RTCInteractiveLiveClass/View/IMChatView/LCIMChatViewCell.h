//
//  LCIMChatViewCell.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/10.
//

#import <UIKit/UIKit.h>
#import "LCIMMessage.h"
//#import <libaim/aim-Bridging-Header.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCIMChatViewCell : UITableViewCell

//@property(nonatomic, nonnull) NSString *uid;

@property (nonatomic, strong) LCIMMessage *model;

@end

NS_ASSUME_NONNULL_END
