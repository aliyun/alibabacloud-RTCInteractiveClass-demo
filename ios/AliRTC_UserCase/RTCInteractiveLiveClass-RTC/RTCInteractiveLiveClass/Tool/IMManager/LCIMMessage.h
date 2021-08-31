//
//  LCIMMessage.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCIMMessage : NSObject

/// 发送类型 1:自己发的 2:非自己发的
@property (nonatomic, assign) NSInteger sourceType;
/// 发送消息用户id
@property (nonatomic, copy) NSString *uid;
/// 接收消息用户id （单聊）
@property (nonatomic, copy) NSString *receiverId;
/// 用户昵称
@property (nonatomic, copy) NSString *displayName;
/// 消息
@property (nonatomic, copy) NSString *message;

@end

NS_ASSUME_NONNULL_END
