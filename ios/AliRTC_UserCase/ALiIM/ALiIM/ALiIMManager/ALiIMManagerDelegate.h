//
//  ALiIMManagerDelegate.h
//  ALiIM
//
//  Created by RTCTeam on 2021/7/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AIMPubNewMessage,AIMPubGroupMember;

@protocol ALiIMManagerDelegate <NSObject>

@optional

/// 创建群聊成功通知
- (void)createGroupSuccess;

/// 创建群聊失败通知
- (void)createGroupFailure:(NSString *)error;

/// 加入群聊成功通知
- (void)joinGroupSuccess;

/// 加入群聊失败通知
- (void)joinGroupFailure:(NSString *)error;

/// 本地登录成功通知
- (void)onLocalLogin;

/// 发送消息成功通知
- (void)sendMessageSuccess;

/// 发送消息失败通知
- (void)sendMessageFailure:(NSString *)error;

/// 发送信令成功通知
- (void)sendSignalSuccess;

/// 发送信令失败通知
- (void)sendSignalFailure:(NSString *)error;

/// 收到新消息的回调，可通过newMsg.type 区分是自己发送的，或在线/离线状态收到的消息
/// @param msgs 新收到的消息列表
- (void)onAddedMessages:(NSArray<AIMPubNewMessage *> *)msgs;

/// 群成员加入离开变化更新
/// @param members 成员
- (void)onGroupMembersChanged:(NSArray<AIMPubGroupMember *> *)members;


@end

NS_ASSUME_NONNULL_END
