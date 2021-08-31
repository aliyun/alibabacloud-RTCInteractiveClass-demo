//
//  ALiIMManager.h
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/25.
//

#import <Foundation/Foundation.h>
#import "ALiIMManagerDelegate.h"


#import <libaim/aim-Bridging-Header.h>
#import <libdps/DPS-Bridging-Header.h>




NS_ASSUME_NONNULL_BEGIN


@interface ALiIMManager : NSObject

// 请使用 +sharedIntance 方法
+ (instancetype)new  __attribute__((unavailable("Use +sharedInstance instead")));
- (instancetype)init __attribute__((unavailable("Use +sharedInstance instead")));


/// 获取IM管理类单例
+ (ALiIMManager *)sharedInstance;

/// 销毁IM管理类
+ (void)destroySharedInstance;

// 代理
@property (nonatomic, weak) id<ALiIMManagerDelegate> delegate;

/// 登录
/// @param uid 用户id
/// @param channelId 频道号id
/// @param name 用户昵称
- (void)login:(NSString *)uid channel:(NSString *)channelId displayName:(NSString *)name;

/// 退出登录
- (void)logout;

/// 创建群聊
/// @param channelId 频道id
- (void)createGroupConversation:(NSString *)channelId;

/// 获取群聊appCid
/// @param channel 频道号
/// @param onSuccess 成功回调
/// @param onFailure 失败回调
- (void)getGroupWithChannel:(NSString *)channel
                    success:(void (^)(NSString *appCid))onSuccess
                    failure:(void (^)(NSString *error))onFailure;

/// 加入群聊
/// @param channelId 频道id
- (void)addGroupConversationMember:(NSString *)channelId;

/// 发送群组文本消息
/// @param msg 频道id
- (void)sendGroupTextMessage:(NSString *)msg;

/// 发送单聊文本消息
/// @param msg 频道id
- (void)sendSingleTextMessage:(NSString *)msg;

/// 发送自定义信令消息
/// @param signal 信令
- (void)sendCustomSignal:(NSString *)signal;


/// 拉取群成员（通过onGroupMembersChanged回调）
- (void)getGroupMembers;


@end

NS_ASSUME_NONNULL_END
