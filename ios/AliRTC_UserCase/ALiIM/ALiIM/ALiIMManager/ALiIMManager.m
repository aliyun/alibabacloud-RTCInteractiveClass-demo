//
//  ALiIMManager.m
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/25.
//

#import "ALiIMManager.h"
#import "NetworkManager.h"
#import "RTCCommon.h"


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


@interface ALiIMManager ()<DPSPubAuthTokenCallback,DPSAuthListener,AIMPubMsgListener,AIMPubGroupMemberChangeListener>

//DPSPubManager
@property (nonatomic, strong) DPSPubManager *dpsManager;
//记录当前用户的id
@property (nonatomic, copy) NSString *user_id;
//频道号
@property (nonatomic, copy) NSString *channel;
//用户名
@property (nonatomic, copy) NSString *nickName;
//群id
@property (nonatomic, copy) NSString *appCid;

@end

static dispatch_once_t onceToken;
static ALiIMManager *manager = nil;


@implementation ALiIMManager

+ (ALiIMManager *)sharedInstance{
    dispatch_once(&onceToken, ^{
        manager = [[super allocWithZone:NULL] init];
    });
    return manager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    return [ALiIMManager sharedInstance];
}

- (id)copyWithZone:(nullable NSZone *)zone {
    return [ALiIMManager sharedInstance];
}

- (id)mutableCopyWithZone:(nullable NSZone *)zone {
    return [ALiIMManager sharedInstance];
}

+ (void)destroySharedInstance{
    
    [[ALiIMManager sharedInstance] removeListeners];
    
    onceToken = 0;
    manager = nil;
}


- (instancetype)init {
    if (self = [super init]) {
        // 创建引擎，仅需创建一次
        [DPSPubEngine createDPSEngine];
    }
    return self;
}

- (void)addListeners {

    AIMPubModule* module = [AIMPubModule getModuleInstance:self.dpsManager.getUserId];
    [[module getMsgService] addMsgListener:self];
    [[module getGroupService] addGroupMemberChangeListener:self];
    [[self.dpsManager getAuthService] addListener:self];
}

- (void)removeListeners {

    AIMPubModule* module = [AIMPubModule getModuleInstance:self.dpsManager.getUserId];
    [[module getMsgService] removeMsgListener:self];
    [[module getGroupService] removeGroupMemberChangeListener:self];
    [[self.dpsManager getAuthService] removeListener:self];
}


/// 登录
/// @param uid 用户id
/// @param channelId 频道号id
/// @param name 用户昵称
- (void)login:(NSString *)uid channel:(NSString *)channelId displayName:(NSString *)name {
    
    self.user_id = uid;
    self.nickName = name;
    self.channel = channelId;
    
    
    // 获取引擎实例
    DPSPubEngine *engine = [DPSPubEngine getDPSEngine];
    
    //获取 DPSPubSettingService
    DPSPubSettingService *service = [engine getSettingService];
    
    //1、设置参数
    [service setAppKey:self.appKey];
    [service setAppID:self.appId];
    //设置本地数据库/数据存储路径, 该路径必须存在，并可有可写权限
    [service setDataPath:self.dataPath];
    // 设备唯一id
    [service setDeviceId:self.deviceId];
    // 构造UA所需的参数
    [service setAppName:[self appName]];
    [service setAppVersion:[self appVersion]];
    [service setAppLocale:[self deviceLocale]];
    [service setOSName:[self osName]];
    [service setOSVersion:[self osVersion]];
    [service setDeviceName:[self deviceName]];
    [service setDeviceType:[self deviceType]];
    [service setDeviceLocale:[self deviceLocale]];
    [service setTimeZone:[self timeZoneName]];
    
    //设置登录token获取回调
    [service setAuthTokenCallback:self];
    
    //注册IM模块
    DPSModuleInfo* info = [AIMPubModule getModuleInfo];
    
    [engine registerModule:info];
    
    //启动引擎，为异步，成功后，将回调listener.onSuccess()
    __weak typeof(self) weakSelf = self;
    [engine startWithBlock:^{
        
        [weakSelf createDPSManagerWithUserId:uid];
    } onFailure:^(DPSError * _Nonnull error) {
        NSLog(@"%@",error);
    }];
}

/// 创建消息管理对象
/// @param uid 用户id
- (void)createDPSManagerWithUserId:(NSString *)uid {
    
    // 获取DPSEngine
    DPSPubEngine *engine = [DPSPubEngine getDPSEngine];
    
    // 创建用户manager
    __weak typeof(self) weakSelf = self;
    [engine createDPSManagerWithBlock:uid onSuccess:^(DPSPubManager * _Nullable manager) {
        weakSelf.dpsManager = manager;
    } onFailure:^(DPSError * _Nonnull error) {
        NSLog(@"%@",error);
    }];
}

- (void)setDpsManager:(DPSPubManager *)dpsManager {
    
    if (_dpsManager != dpsManager) {
        // 先清理历史
        [self removeListeners];
        
        _dpsManager = dpsManager;
        
        //登录
        [[dpsManager getAuthService] login];
        
        //设置监听
        [self addListeners];
    }
}

#pragma mark - DPSAuthTokenCallback 设置登录token获取回调
- (void)onCallback:(NSString *)userId onGot:(DPSAuthTokenGotCallback *)onGot reason:(DPSAuthTokenExpiredReason)reason {
    
    // 当App调用authService.login()时触发该回调
    // 回调内，App向AppServer发起RPC请求，AppServer从IMPaaS服务端获取AuthToken
    // 应用无需缓存该token，SDK内部会进行缓存管理
    
    
    [self requestTokenWithUid:self.user_id completion:^(NSDictionary *dict, NSString *errString) {
        
        if (!errString) {
            
            if ([[dict allKeys] containsObject:@"accessToken"] && [[dict allKeys] containsObject:@"refreshToken"]) {
                DPSAuthToken *authToken = [[DPSAuthToken alloc] init];
                authToken.accessToken = dict[@"accessToken"];
                authToken.refreshToken = dict[@"refreshToken"];
                [onGot onSuccess:authToken];
            }else {
                [onGot onFailure:-1 errorMsg:@"请检查 accessToken,refreshToken 是否有值，或检查 requestToken 是否阻塞"];
            }
        }else {
            NSLog(@"%@",errString);
        }
    }];
}


/// 退出登录
- (void)logout {
   
//    AIMPubModule* module = [AIMPubModule getModuleInstance:self.dpsManager.getUserId];
//    AIMPubGroupLeave *leave = [[AIMPubGroupLeave alloc] initWithAppCid:self.appCid];
//
//    [[module getGroupService] leaveWithBlock:leave onSuccess:^{
//
//    } onFailure:^(DPSError * _Nonnull error) {
//        NSLog(@"%@",error.developerMessage);
//    }];
    
    [[self.dpsManager getAuthService] logoutWithBlock:^{
    } onFailure:^(DPSError * _Nonnull error) {
    }];
    
    [self removeListeners];
}

/// 创建群聊
/// @param channelId 频道id
- (void)createGroupConversation:(NSString *)channelId {
    
    __weak typeof(self) weakSelf = self;
    [self createGroupWithChannel:channelId userId:self.user_id success:^(NSString * _Nonnull appCid) {
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(createGroupSuccess)]) {
                [weakSelf.delegate createGroupSuccess];
            }
        });
    } failure:^(NSString * _Nonnull error) {
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(createGroupFailure:)]) {
                [weakSelf.delegate createGroupFailure:error];
            }
        });
    }];
}

/// 加入群聊
/// @param channelId 频道id
- (void)addGroupConversationMember:(NSString *)channelId {
    
    //加入群聊聊天 1、获取群号  2、加入群聊
    __weak typeof(self) weakSelf = self;
    [self getGroupWithChannel:channelId success:^(NSString * _Nonnull appCid) {
        [weakSelf joinGroupWithAppCid:appCid channel:channelId];
    } failure:^(NSString * _Nonnull error) {
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(joinGroupFailure:)]) {
                [weakSelf.delegate joinGroupFailure:error];
            }
        });
    }];
}

/// 加入群聊
- (void)joinGroupWithAppCid:(NSString *)appCid channel:(NSString *)channelId {

    self.appCid = appCid;
    
    __weak typeof(self) weakSelf = self;
    [self joinGroupWithAppCid:appCid userId:self.user_id nickName:self.nickName channel:channelId success:^{
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(joinGroupSuccess)]) {
                [weakSelf.delegate joinGroupSuccess];
            }
        });
    } failure:^(NSString * _Nonnull error) {
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(joinGroupFailure:)]) {
                [weakSelf.delegate joinGroupFailure:error];
            }
        });
    }];
}

- (void)getGroupMembers {
    [self UpdatedGroupMembers];
}


/// 发送群组文本消息
/// @param msg 频道id
- (void)sendGroupTextMessage:(NSString *)msg {
    [self sendNetworkTextMessage:msg];
}

/// 发送单聊文本消息
/// @param msg 频道id
- (void)sendSingleTextMessage:(NSString *)msg {
    [self sendNetworkTextMessage:msg];
}

/// 发送自定义信令消息
/// @param signal 信令
- (void)sendCustomSignal:(NSString *)signal {
    __weak typeof(self) weakSelf = self;
    [self sendNetworkTextMessageWithAppCid:self.appCid userId:self.user_id message:signal success:^{
        
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(sendSignalSuccess)]) {
                [weakSelf.delegate sendSignalSuccess];
            }
        });
    } failure:^(NSString *error) {
        
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(sendSignalFailure:)]) {
                [weakSelf.delegate sendSignalFailure:error];
            }
        });
    }];
}


//发送消息
- (void)sendNetworkTextMessage:(NSString *)message {
    
    __weak typeof(self) weakSelf = self;
    [self sendNetworkTextMessageWithAppCid:self.appCid userId:self.user_id message:message success:^{
        
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(sendMessageSuccess)]) {
                [weakSelf.delegate sendMessageSuccess];
            }
        });
    } failure:^(NSString *error) {
        
        dispatch_async_on_main_queue(^{
            if (weakSelf.delegate && [self.delegate respondsToSelector:@selector(sendMessageFailure:)]) {
                [weakSelf.delegate sendMessageFailure:error];
            }
        });
    }];
}


#pragma mark - DPSPubAuthListener -
/**
 * 连接状态事件
 * @param status      连接状态
 */
- (void)onConnectionStatusChanged:(DPSConnectionStatus)status {
    
}
/**
 * 登录token获取失败事件
 * @param errorCode  获取登录token失败错误值
 * @param errorMsg   获取登录token失败错误信息
 */
- (void)onGetAuthCodeFailed:(int32_t)errorCode errorMsg:(nonnull NSString *)errorMsg {
    
    
}

/**
 * 本地登录事件
 * 如果本地已有登录信息，创建账号后会立即回调；反之会等待网络登录成功之后回调
 */
- (void)onLocalLogin {
    dispatch_async_on_main_queue(^{
        if ([self.delegate respondsToSelector:@selector(onLocalLogin)]) {
            [self.delegate onLocalLogin];
        }
    });
}
/**
 * 被踢事件
 * @param message     被踢下线时附带的消息
 */
- (void)onKickout:(nonnull NSString *)message {
    
}

/**
 * 其他端设备在（离）线情况
 * @param type        事件类型（1：事件通知，包括上下线，2：状态通知，在线状态）
 * @param deviceType 设备类型
 * （0:default,1:web,2:Android,3:iOS,4:Mac,5:Windows,6:iPad）
 * @param status      设备状态（1：上线或在线，2：下线或离线）
 * @param time        时间（上线或下线时间）
 */
- (void)onDeviceStatus:(int32_t)type deviceType:(int32_t)deviceType status:(int32_t)status time:(int64_t)time {
    
}
/**
 * 下载资源cookie变更事件
 * @param cookie      新cookie
 */
- (void)onMainServerCookieRefresh:(nonnull NSString *)cookie {

    NSLog(@"onMainServerCookieRefresh");

}


#pragma mark - AIMPubGroupMemberChangeListener -
/**
 * 新增成员
 * @param members 成员
 */
- (void)onAddedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members {
    
    [self UpdatedGroupMembers];
}

/**
 * 删除成员
 * @param members 成员
 */
- (void)onRemovedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members {
    [self UpdatedGroupMembers];
}

/**
 * 成员变更
 * @param members 成员
 */
- (void)onUpdatedMembers:(nonnull NSArray<AIMPubGroupMember *> *)members {
    
}


/// 群成员加入离开变化更新
- (void)UpdatedGroupMembers {
    
    AIMPubModule* module = [AIMPubModule getModuleInstance:self.dpsManager.getUserId];
    __weak typeof(self) weakSelf = self;
    [[module getGroupService] listAllMembersWithBlock:self.appCid onLocal:^(NSArray<AIMPubGroupMember *> * _Nonnull members) {
        
    } onRefresh:^(NSArray<AIMPubGroupMember *> * _Nonnull members) {
        
        dispatch_async_on_main_queue(^{
            if ([weakSelf.delegate respondsToSelector:@selector(onGroupMembersChanged:)]) {
                [weakSelf.delegate onGroupMembersChanged:members];
            }
        });
    } onFailure:^(DPSError * _Nonnull error) {
        NSLog(@"%@",error);
    }];
}


#pragma mark - AIMPubMsgListener -
/// 消息新增 发送消息或收到推送消息时，触发该回调 当从服务端拉取历史消息时，不会触发该回调
/// @param msgs 新增消息
- (void)onAddedMessages:(nonnull NSArray<AIMPubNewMessage *> *)msgs {

    dispatch_async_on_main_queue(^{
        if ([self.delegate respondsToSelector:@selector(onAddedMessages:)]) {
            [self.delegate onAddedMessages:msgs];
        }
    });
}

/// 消息删除
/// @param msgs 变更消息
- (void)onRemovedMessages:(nonnull NSArray<AIMPubMessage *> *)msgs {

    
}

/// 当消息数据库内有消息添加时，触发该回调
/// 包括发送，推送及拉取历史消息
/// 注意： 1. 不保证传入消息 msgs 的顺序 2. onStored 回调的顺序也不保证消息组间的顺序
/// @param msgs 变更消息
- (void)onStoredMessages:(nonnull NSArray<AIMPubMessage *> *)msgs {


}




#pragma mark - Service -
/// AppServer从IMPaaS服务端获取AuthToken
/// @param completion 返回信息
/// @param uid 用户id
- (void)requestTokenWithUid:(NSString *)uid
                 completion:(void (^)(NSDictionary *dict,NSString *errString))completion {
    
    NSString *api = [kBaseUrl_InteractiveClass stringByAppendingString:@"im/login"];
        
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"appKey"] = self.appKey;
    parms[@"appId"] = self.appId;
    parms[@"deviceId"] = self.deviceId;
    parms[@"appUid"] = uid;
    
    [NetworkManager GET:api parameters:parms completionHandler:^(NSString * _Nullable errString, id  _Nullable result) {
        completion(result,errString);
    }];
}

/// 创建群聊
/// @param channel 频道号
/// @param uid 业务用户id
/// @param onSuccess 成功回调
/// @param onFailure 失败回调
- (void)createGroupWithChannel:(NSString *)channel
                        userId:(NSString *)uid
                    success:(void (^)(NSString *appCid))onSuccess
                    failure:(void (^)(NSString *error))onFailure {
    
    NSString *api = [kBaseUrl_InteractiveClass stringByAppendingString:@"im/createGroup"];
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"appId"] = self.appId;
    parms[@"appUid"] = uid;
    parms[@"room"] = channel;
    
    [NetworkManager GET:api parameters:parms completionHandler:^(NSString * _Nullable errString, id  _Nullable result) {
        
        if (!errString) {
            if (onSuccess) {
                onSuccess(result);
            }
        }else {
            
            if (onFailure) {
                onFailure(errString);
            }
        }
    }];
}

/// 获取群聊appCid
/// @param channel 频道号
/// @param onSuccess 成功回调
/// @param onFailure 失败回调
- (void)getGroupWithChannel:(NSString *)channel
                    success:(void (^)(NSString *appCid))onSuccess
                    failure:(void (^)(NSString *error))onFailure {
    
    NSString *api = [kBaseUrl_InteractiveClass stringByAppendingString:@"im/getGroup"];
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"appId"] = self.appId;
    parms[@"room"] = channel;
    
    [NetworkManager GET:api parameters:parms completionHandler:^(NSString * _Nullable errString, id  _Nullable result) {
        
        if (!errString) {
            if (onSuccess) {
                onSuccess(result);
            }
        }else {
            
            if (onFailure) {
                onFailure(errString);
            }
        }
    }];
}

/// 加入群聊
/// @param appCid 群id
/// @param uid 用户id
/// @param nickName 昵称
/// @param channelId 频道号
/// @param onSuccess 成功回调
/// @param onFailure 失败回调
- (void)joinGroupWithAppCid:(NSString *)appCid
                     userId:(NSString *)uid
                   nickName:(NSString *)nickName
                    channel:(NSString *)channelId
                    success:(void (^)(void))onSuccess
                     failure:(void (^)(NSString * error))onFailure {
    
    NSString *api = [kBaseUrl_InteractiveClass stringByAppendingString:@"im/joinChannel"];
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"appId"] = self.appId;
    parms[@"appCid"] = appCid;
    parms[@"appUid"] = uid;
    parms[@"role"] = @(3);
    parms[@"nickName"] = nickName;
    parms[@"room"] = channelId;

    [NetworkManager GET:api parameters:parms completionHandler:^(NSString * _Nullable errString, id  _Nullable result) {
        if (!errString) {
            //加入群聊
            if (onSuccess) {
                onSuccess();
            }
        }else {
            
            if (onFailure) {
                onFailure(errString);
            }
        }
    }];
}

/// 发送文本消息/信令消息
/// @param appCid 群id
/// @param uid 用户id
/// @param message 文本消息
/// @param onSuccess 成功回调
/// @param onFailure 失败回调
- (void)sendNetworkTextMessageWithAppCid:(NSString *)appCid
                                  userId:(NSString *)uid
                                 message:(NSString *)message
                                 success:(void (^)(void))onSuccess
                                 failure:(void (^)(NSString *error))onFailure {
    
    NSString *api = [kBaseUrl_InteractiveClass stringByAppendingString:@"im/sendMsg"];
    
    NSMutableDictionary *parms = [NSMutableDictionary dictionary];
    parms[@"appId"] = self.appId;
    parms[@"appCid"] = appCid;
    parms[@"sendUid"] = uid;
    parms[@"content"] = message;
    
    [NetworkManager GET:api parameters:parms completionHandler:^(NSString * _Nullable errString, id  _Nullable result) {
        if (!errString) {
            if (onSuccess) {
                onSuccess();
            }
        }else {
            if (onFailure) {
                onFailure(errString);
            }
        }
    }];
}


#pragma mark - getter && setter -

- (NSString *)dataPath {
    static NSString *dataDirectory = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        @autoreleasepool
        {
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *documentsDirectory = [paths objectAtIndex:0];
            dataDirectory = [documentsDirectory stringByAppendingPathComponent:@"AIMData"];
            
            // 若目录不存在，则创建
            if (![[NSFileManager defaultManager] fileExistsAtPath:dataDirectory]) {
                [[NSFileManager defaultManager] createDirectoryAtPath:dataDirectory withIntermediateDirectories:YES attributes:nil error:nil];
            }
        }
    });
    return dataDirectory;
}

- (NSString *)deviceId {
    static NSString *deviceId = nil;
    NSString *key = @"MockDeviceId";
    
    deviceId = [[NSUserDefaults standardUserDefaults] stringForKey:key];
    if (deviceId.length == 0) {
        deviceId = [NSUUID UUID].UUIDString;
        
        NSString *prefix = nil;
#if TARGET_IPHONE_SIMULATOR//模拟器
        prefix = @"iOS_Simulator_";
#elif TARGET_OS_IPHONE//真机
        prefix = @"iOS_Device_";
#endif
        deviceId = [prefix stringByAppendingString:deviceId];
        [[NSUserDefaults standardUserDefaults] setObject:deviceId forKey:key];
    }
    return deviceId;
}

//appKey和appID从控制台的 直播互动>功能配置 页面获取
//https://live.console.aliyun.com/?spm=a2c4g.11186623.2.4.320d76b4TgWusU#/overview
- (NSString *)appId {
#warning "请在ALiIM/ALiIMManager.m中配置appKey和appID"
    NSLog(@"appKey和appID从控制台的 直播互动>功能配置 页面获取");
    return @"";
}

- (NSString *)appKey {
#warning "请在ALiIM/ALiIMManager.m中配置appKey和appID"
    NSLog(@"appKey和appID从控制台的 直播互动>功能配置 页面获取");
    return @"";
}

- (NSString *)appName {
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *displayName = infoDictionary[@"CFBundleDisplayName"];
    if (displayName.length > 0) {
        return displayName;
    }
    return infoDictionary[@"CFBundleName"];
}

- (NSString *)appVersion {
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *versionString = infoDictionary[@"CFBundleShortVersionString"];
    if (versionString.length == 0) {
        versionString = infoDictionary[@"CFBundleVersion"];
    }
    return versionString;
}

- (NSString *)osName {
    return [UIDevice currentDevice].systemName;
}

- (NSString *)osVersion {
    return [UIDevice currentDevice].systemVersion;
}

- (NSString *)deviceName {
    return [UIDevice currentDevice].name;
}
    
- (NSString *)deviceType {
    return [UIDevice currentDevice].model;
}
    
- (NSString *)deviceLocale {
    return NSLocale.preferredLanguages.firstObject;
//    return [NSLocale currentLocale].localeIdentifier;
}

- (NSString *)timeZoneName {
    // 暂时使用系统时区
    return [NSTimeZone systemTimeZone].name;
}




@end

