//
//  AliImInterrativeEngine.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/28.
//

#import "AliImInterrativeEngine.h"

#import "ALiIMManager.h"

#import "RTCHUD.h"
#import "NetworkManager.h"
#import "AppConfig.h"


NSString * const kCLMessageSortKey = @"createdAt";


static inline void dispatch_async_on_main_queue(void (^block)(void)) {
    if (block == nil) {
        return;
    }
    if (NSThread.isMainThread) {
        block();
    } else {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}


@interface AliImInterrativeEngine () <ALiIMManagerDelegate>

@property (weak, nonatomic) ALiIMManager *manager;
//记录当前用户的id
@property (nonatomic, copy) NSString *user_id;
//频道号
@property (nonatomic, copy) NSString *channel;
//用户名
@property (nonatomic, copy) NSString *nickName;
//消息列表
@property (nonatomic, strong) NSMutableArray<LCIMMessage*> *messagesArray;

@end

static dispatch_once_t onceToken;
static AliImInterrativeEngine *manager = nil;
@implementation AliImInterrativeEngine

+ (AliImInterrativeEngine *)sharedInstance{
    dispatch_once(&onceToken, ^{
        manager = [[super allocWithZone:NULL] init];
    });
    return manager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    return [AliImInterrativeEngine sharedInstance];
}

- (id)copyWithZone:(nullable NSZone *)zone {
    return [AliImInterrativeEngine sharedInstance];
}

- (id)mutableCopyWithZone:(nullable NSZone *)zone {
    return [AliImInterrativeEngine sharedInstance];
}



+ (void)destroySharedInstance{
    
    [[AliImInterrativeEngine sharedInstance] logout];
    [ALiIMManager destroySharedInstance];
    onceToken = 0;
    manager = nil;
}

/// 登录
/// @param uid 用户id
/// @param channelId 频道号id
/// @param name 用户昵称
- (void)login:(NSString *)uid channel:(NSString *)channelId displayName:(NSString *)name {
    
    self.manager = [ALiIMManager sharedInstance];
    self.manager.delegate = self;
    self.user_id = uid;
    self.nickName = name;
    self.channel = channelId;
    
    //初始化消息列表
    self.messagesArray = [NSMutableArray array];
    
    [self.manager login:uid channel:channelId displayName:name];
}

/// 退出登录
- (void)logout  {
    [self.manager logout];
}

#pragma mark - 发送消息及信令 -
/// 发送文本消息
/// @param message 发送文本
- (void)sendTextMessage:(NSString *)message {
    
    message = [message stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    if (message.length == 0) {
        return;
    }
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"type"] = @(0);
    parms[@"isTeacher"] = @(NO);
    parms[@"displayName"] = self.nickName;
    parms[@"message"] = message;
    
    [self.manager sendGroupTextMessage:[self jsonStringWithDictionary:parms]];
}


/// 发送举手
/// @param mute 是否举手(YES:举手,目前仅支持YES)
- (void)sendHandUp:(BOOL)mute {
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"type"] = @(1);
    parms[@"isTeacher"] = @(NO);
    parms[@"displayName"] = self.nickName;
    parms[@"handUp"] = @(mute);
    parms[@"message"] = @"";
    
    [self.manager sendCustomSignal:[self jsonStringWithDictionary:parms]];
}

/// 获取群消息
- (NSArray *)getGroupMessages {
    return self.messagesArray;
}

#pragma mark - ALiIMManagerDelegate -

/// 加入群聊成功通知
- (void)joinGroupSuccess {
    //拉取群成员
    [self.manager getGroupMembers];
}

/// 加入群聊失败通知
- (void)joinGroupFailure:(NSString *)error {
    NSLog(@"%@",error);
}

/// 本地登录成功通知
- (void)onLocalLogin {
    [self.manager addGroupConversationMember:self.channel];
}

/// 发送消息成功通知
- (void)sendMessageSuccess {
    
}

/// 发送消息失败通知
- (void)sendMessageFailure:(NSString *)error {
    dispatch_async_on_main_queue(^{
        if ([self.delegate respondsToSelector:@selector(imSendMessageFailure:)]) {
            [self.delegate imSendMessageFailure:error];
        }
    });
    
}

/// 发送信令成功通知
- (void)sendSignalSuccess {
    
}

/// 发送信令失败通知
- (void)sendSignalFailure:(NSString *)error {
    NSLog(@"%@",error);
}

- (void)onGroupMembersChanged:(NSArray<AIMPubGroupMember *> *)members {
    
    dispatch_async_on_main_queue(^{
        if ([self.delegate respondsToSelector:@selector(imGroupMembersChanged:)]) {
            [self.delegate imGroupMembersChanged:members];
        }
    });    
}


/// 收到新消息的回调，可通过newMsg.type 区分是自己发送的，或在线/离线状态收到的消息
/// @param msgs 新收到的消息列表
- (void)onAddedMessages:(NSArray<AIMPubNewMessage *> *)msgs {
    
    @synchronized (self) {
        
        [msgs enumerateObjectsUsingBlock:^(AIMPubNewMessage * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            
            NSDictionary *dict = [self dictionaryWithJsonString:obj.msg.content.textContent.text];
            
            if (dict && [[dict allKeys] containsObject:@"type"]) {
                //type 消息类型 0:群聊消息 1:发送信令
                switch ([dict[@"type"] intValue]) {
                    case 0: { [self detailChatMessage:obj.msg]; } break;
                    case 1: { [self detailAddedIMCommandMessage:obj.msg]; } break;
                    default:
                        break;
                }
            }
        }];
    }
}

#pragma mark - 消息处理 -
/// 处理群聊消息
/// @param message 接收的新消息
- (void)detailChatMessage:(AIMPubMessage *)message {
    
    @synchronized (self) {
        
        NSDictionary *dict = [self dictionaryWithJsonString:message.content.textContent.text];
        
        LCIMMessage *msg = [[LCIMMessage alloc] init];
        msg.uid = message.sender;
        
        if ([[dict allKeys] containsObject:@"receiverId"]) {
            msg.receiverId = dict[@"receiverId"];
        }
        
        if ([[dict allKeys] containsObject:@"displayName"]) {
            msg.displayName = dict[@"displayName"];
        }
        
        if ([[dict allKeys] containsObject:@"message"]) {
            msg.message = dict[@"message"];
        }
        
        if ([msg.uid isEqualToString:self.user_id]) {
            msg.sourceType = 1;
        }else {
            msg.sourceType = 2;
        }
        
        [self.messagesArray addObject:msg];
        
//        NSLog(@" -----delegate----- %@",self.delegate);
        
        dispatch_async_on_main_queue(^{
            if (self.delegate && [self.delegate respondsToSelector:@selector(imUpdateMessages:)]) {
                [self.delegate imUpdateMessages:self.messagesArray];
            }
            if (self.delegate && [self.delegate respondsToSelector:@selector(imUpdateSingleMessage:)]) {
                [self.delegate imUpdateSingleMessage:msg];
            }
        });
    }   
}


- (void)detailAddedIMCommandMessage:(AIMPubMessage *)message {
    
    NSDictionary *dict = [self dictionaryWithJsonString:message.content.textContent.text];
    
    //接收消息的userId
    NSString *re_userId = @"";
    if ([[dict allKeys] containsObject:@"uid"]) {
        re_userId = dict[@"uid"];
    }
    
    BOOL  isTeacher = NO;
    if ([[dict allKeys] containsObject:@"isTeacher"]) {
        isTeacher = [dict[@"isTeacher"] boolValue];
    }
        
    dispatch_async_on_main_queue(^{
        
        if (isTeacher) { //收到信令 是 老师发送的
            
            if ([re_userId isEqualToString:self.user_id]) {
                
                //判断是否是当前用户，只有是当前用户才执行以下信令操作
                if ([[dict allKeys] containsObject:@"muteMic"]) { //静音
                    
                    BOOL mute = [dict[@"muteMic"] boolValue];
                    if ([self.delegate respondsToSelector:@selector(imReceiveRemoteMuteMicCommand:userId:)]) {
                        [self.delegate imReceiveRemoteMuteMicCommand:mute userId:re_userId];
                    }
                }else if ([[dict allKeys] containsObject:@"muteCamera"]) { //相机流
                    
                    BOOL mute = [dict[@"muteCamera"] boolValue];
                    if ([self.delegate respondsToSelector:@selector(imReceiveRemoteMuteCameraCommand:userId:)]) {
                        [self.delegate imReceiveRemoteMuteCameraCommand:mute userId:re_userId];
                    }
                }else if ([[dict allKeys] containsObject:@"backHandUp"]) { //老师反馈学生举手
                    
                    BOOL mute = [dict[@"backHandUp"] boolValue];
                    if ([self.delegate respondsToSelector:@selector(imReceiveRemoteBackHandUpCommand:userId:)]) {
                        [self.delegate imReceiveRemoteBackHandUpCommand:mute userId:re_userId];
                    }
                }
            }else {
                
                //不是当前用户，需判断是否是全员静音信令，若是则执行此操作
                if ([[dict allKeys] containsObject:@"muteAllMic"]) { //全员静音
                    
                    BOOL mute = [dict[@"muteAllMic"] boolValue];
                    if ([self.delegate respondsToSelector:@selector(imReceiveRemoteMuteAllMicCommand:)]) {
                        [self.delegate imReceiveRemoteMuteAllMicCommand:mute];
                    }
                }
            }
        }
    });
}

#pragma mark - Other -
//字典转JSON
- (NSString *)jsonStringWithDictionary:(NSDictionary *)dic{
    NSError *err;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic options:NSJSONWritingPrettyPrinted error:&err];
    
    NSString *jsonString;
    if (!jsonData) {
        NSLog(@"%@",err);
    }else{
        jsonString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    NSLog(@"%@",jsonString);
    return jsonString;
}

//JSON转字典
- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString {
    if (jsonString == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err) {
        NSLog(@"json解析失败：%@",err);
        return nil;
    }
    return dic;
}


- (void)dealloc {
    [ALiIMManager destroySharedInstance];
}


@end
