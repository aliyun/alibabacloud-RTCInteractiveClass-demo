//
//  LCIMChatView.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/10.
//

#import <UIKit/UIKit.h>

#import "LCIMMessage.h"

NS_ASSUME_NONNULL_BEGIN

@interface LCIMChatView : UIView

//发送消息
@property (nonatomic, copy) void(^SendMsgClick)( NSString * _Nullable message);

/// 消息更新 包含从服务器拉取消息及新增消息
/// @param messages 消息（全部）
- (void)updateMessages:(NSArray<LCIMMessage *> *)messages;


@end

NS_ASSUME_NONNULL_END
