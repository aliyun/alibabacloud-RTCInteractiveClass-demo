//
//  AliImInterrativeEngine.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/28.
//

#import <Foundation/Foundation.h>
#import "LCIMMessage.h"
#import "ALiIMHeader.h"
#import "AliImInterrativeEngineDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface AliImInterrativeEngine : NSObject


/// 获取单例
+ (AliImInterrativeEngine *)sharedInstance;

/// 销毁IM管理类
+ (void)destroySharedInstance;

// 代理
@property (nonatomic, weak) id<AliImInterrativeEngineDelegate> delegate;

/// 登录
/// @param uid 用户id
/// @param channelId 频道号id
/// @param name 用户昵称
- (void)login:(NSString *)uid channel:(NSString *)channelId displayName:(NSString *)name;

/// 退出登录
- (void)logout;

/// 发送文本消息
/// @param message 发送文本
- (void)sendTextMessage:(NSString *)message;


/// 发送举手
/// @param mute 是否举手(YES:举手,目前仅支持YES)
- (void)sendHandUp:(BOOL)mute;


/// 获取群消息
- (NSArray *)getGroupMessages;


@end

NS_ASSUME_NONNULL_END
