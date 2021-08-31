互动大班课 app server

## 设计说明
一个课堂会创建一个RTC的Channel，同时会创建Im的一个Group，双方通过Channelid（room）和 Group的Cid进行对应；

## Endpoint
https://alivc-demo.aliyuncs.com/interactive-live-class/

## 接口
### 获取RTC鉴权信息（getRtcAuth）
参数：
- platform=web
- channelId=123asdf
- userId=adsf

返回值：
```json
{
    "result": "true",
    "requestId": "",
    "message": "",
    "code": "200",
    "data": {
        "gslb": [
            "https://rgslb.rtc.aliyuncs.com"
        ],
        "appid": "nqzu6bz8",
        "userid": "1fa11a9d-0431-44ac-8d83-b63fa4416ab7",
        "nonce": "AK-25d9e0d7-dabe-4c48-b696-fc347ae1f617",
        "channelId": "12345",
        "token": "5142ea5beef309aeaa50e6623de5f7*****7f9f661d4be926bed1e",
        "timestamp": 1628243955
    }
}
```


## IM相关接口
### im获取鉴权信息（im/login）
> 获取登录im token，客户端需要有token登录im服务；

参数：
- String appKey：注册im应用是分配的Appkey不同平台不一样
- String deviceId：设备号，由业务方自己生成；
- String appUid：业务用户uid

返回值：
```json
{
    "code": 200,
    "data": {
        "accessToken": "oauth_cloud_key:NtpBiK7Kcm9wmCS/mSe36G/gKUlVFTcDqmdFwrMw17tzBOthv86S/piM2lM9oHDYY+iuo2xVVOo1OCh+eExBXjWOaakbK13m9CtKlOmChbY=",
        "refreshToken": "oauth_cloud_key:vJY16nVs0KSesiVi0GzLYcb/wAZpJlSGXi/ix5K2K6so3ggKGtPa6/lqO6edotQbBlKFZMkH8kHyhbPawitCyQ==",
        "accessTokenExpiredTime": 86400000
    },
    "server": 1627531413545
}
```

### 创建群聊（/im/createGroup）
参数：
- String title：群名
- String appUid：业务用户ID，群主名字
- String room：课堂号，群聊和课堂对应；

返回值：
```json
{
    "code": 200,
    "data": "$2$9500343$EAUNIT",
    "server": 1627291814353
}
```

### 获取群聊信息（/im/getGroup）
> 通过课堂号，获取Group信息；

参数：
- String room：课堂号；

返回值：
```json
{
    "code": 200,
    "data": "$2$9500343$EAUNIT",
    "server": 1627291814353
}
```

### 解散群聊（/im/destoryChannel）
> 课堂结束，解散对应的群聊；

参数：
- String room：课堂号；
- String appUid：业务用户ID，一般来说为老师（群主）

返回值：
```json
{
    "code": 200,
    "data": null,
    "server": 1627291814353
}
```

### 加入群聊（/im/joinChannel）
> 学生进入课堂时调用，加入到课堂对应的群聊里面

参数：
- String appCid：im群聊id
- String appUid：业务用户UID
- Integer role：角色：一般为学生 = 3。1：群主。2：管理员。3：普通。100~127：自定义。
- String nickName：昵称；
- String room：课堂号；

返回值：
```json
{
    "code": 200,
    "data": "加入成功",
    "server": 1627291814353
}
```

### 发送消息（/im/sendMsg）
> 通过服务端发送文本群聊消息

参数：
- String appCid：群聊ID
- String sendUid：发送用户UID
- String content：发送文本内容

返回值：
```json
{
    "code": 200,
    "data": "发送成功",
    "server": 1627291814353
}
```


