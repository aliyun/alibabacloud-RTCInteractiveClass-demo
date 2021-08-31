//
//  LCChatController.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import <UIKit/UIKit.h>
#import "LCIMMessage.h"

NS_ASSUME_NONNULL_BEGIN

@interface LCChatController : UIViewController
/// 返回回调
@property (nonatomic, copy) void(^backClick)(void);
///// 发送消息回调
//@property (nonatomic, copy) void(^sendTextMessage)(NSString *msg);

///// 消息更新 包含从服务器拉取消息及新增消息
///// @param messages 消息
- (void)updateMessages:(NSArray<LCIMMessage *> *)messages;

@end

NS_ASSUME_NONNULL_END
