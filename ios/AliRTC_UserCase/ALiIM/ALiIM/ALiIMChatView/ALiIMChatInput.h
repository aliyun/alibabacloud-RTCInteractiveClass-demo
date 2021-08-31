//
//  ALiIMChatInput.h
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/26.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ALiIMChatInput : UIView
//发送消息
@property (nonatomic, copy) void(^SendMsgClick)( NSString * _Nullable message);

//退出键盘
- (void)resignFirstResponder;

@end

NS_ASSUME_NONNULL_END
