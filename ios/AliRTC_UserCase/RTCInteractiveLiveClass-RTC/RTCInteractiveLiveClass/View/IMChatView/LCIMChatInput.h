//
//  LCIMChatInput.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/28.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCIMChatInput : UIView
//发送消息
@property (nonatomic, copy) void(^SendMsgClick)( NSString * _Nullable message);

//退出键盘
- (void)resignFirstResponder;

@end

NS_ASSUME_NONNULL_END
