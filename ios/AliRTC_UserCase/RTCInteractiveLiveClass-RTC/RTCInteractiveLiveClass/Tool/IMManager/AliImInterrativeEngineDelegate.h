//
//  AliImInterrativeEngineDelegate.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AliImInterrativeEngineDelegate <NSObject>

@optional
/// 消息更新 包含从服务器拉取消息及新增消息
/// @param messages 消息（全部）
- (void)imUpdateMessages:(NSArray<LCIMMessage *> *)messages;

/// 更新单条消息
/// @param msg 新消息
- (void)imUpdateSingleMessage:(LCIMMessage *)msg;

/// 群成员加入离开变化更新
/// @param members 成员
- (void)imGroupMembersChanged:(NSArray<AIMPubGroupMember *> *)members;



/// --- 信令相关 ---

/// 收到老师反馈举手信令
/// @param mute 是否同意举手(YES:同意举手,NO:拒绝举手)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteBackHandUpCommand:(BOOL)mute userId:(NSString *)uid;

/// 收到静音指令
/// @param mute 是否静音 (YES:关闭麦克风，NO:打开麦克风)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteMuteMicCommand:(BOOL)mute userId:(NSString *)uid;

/// 收到相机流指令
/// @param mute 是否关闭相机流 (YES:关闭相机流，NO:打开相机流)
/// @param uid 需执行的用户id
- (void)imReceiveRemoteMuteCameraCommand:(BOOL)mute userId:(NSString *)uid;

/// 收到全员静音指令
/// @param mute 是否全员静音 (YES:全员静音，NO:解除全员静音)
- (void)imReceiveRemoteMuteAllMicCommand:(BOOL)mute;

/// 发送消息失败通知
- (void)imSendMessageFailure:(NSString *)error;


@end

NS_ASSUME_NONNULL_END
