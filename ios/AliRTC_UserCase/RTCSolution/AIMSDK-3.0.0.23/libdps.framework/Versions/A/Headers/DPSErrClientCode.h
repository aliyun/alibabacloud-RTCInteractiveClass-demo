// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * 客户端错误嘛
 */
typedef NS_ENUM(NSInteger, DPSErrClientCode) {
  /**
   * [DPS]成功
   */
  DPSErrClientCodeDPSErrSuccess = 0,
  /**
   * [DPS]禁止调用
   */
  DPSErrClientCodeDPSErrNotEnabled,
  /**
   * [DPS]功能不支持
   */
  DPSErrClientCodeDPSErrNotSupport,
  /**
   * [DPS]参数错误
   */
  DPSErrClientCodeDPSErrInvalidArg,
  /**
   * [DPS]DPSEngine实例不存在
   */
  DPSErrClientCodeDPSEngineIsNull = 10,
  /**
   * [DPS]DPSEngine重复创建
   */
  DPSErrClientCodeDPSEngineAlreadyExist,
  /**
   * [DPS]DPSEngine未启动
   */
  DPSErrClientCodeDPSEngineNotStart,
  /**
   * [DPS]DPSSettingService有必填值未填写
   */
  DPSErrClientCodeDPSSettingNotReady,
  /**
   * [DPS]DPSManager创建失败
   */
  DPSErrClientCodeDPSCreateManagerFailed,
  /**
   * [DPS]DPSManager初始化失败
   */
  DPSErrClientCodeDPSManagerInitFailed,
  /**
   * [DPS]DPSManager实例不存在
   */
  DPSErrClientCodeDPSManagerNotExist,
  /**
   * [DPS]DPSAuthService实例不存在
   */
  DPSErrClientCodeDPSAuthIsNull,
  /**
   * [DPS]DPSSyncService实例不存在
   */
  DPSErrClientCodeDPSSyncIsNull,
  /**
   * [DPS]DPSUtService实例不存在
   */
  DPSErrClientCodeDPSUTIsNull,
  /**
   * [DPS]DPSRpcService实例不存在
   */
  DPSErrClientCodeDPSRpcIsNull,
  /**
   * [AUTH]实例不存在
   */
  DPSErrClientCodeAuthAuthIsNull = 50,
  /**
   * [AUTH]网络实例不存在
   */
  DPSErrClientCodeAuthUAIsNull,
  /**
   * [AUTH]AuthTokenCallback回调为空
   */
  DPSErrClientCodeAuthGetTokenCbIsNull,
  /**
   * [AUTH]AuthTokenCallback回调方法返回错误
   */
  DPSErrClientCodeAuthGetTokenFailed,
  /**
   * [AUTH]AuthTokenCallback调用太频繁被流控
   */
  DPSErrClientCodeAuthGetTokenTooFrequently,
  /**
   * [AUTH]token为空
   */
  DPSErrClientCodeAuthTokenEmpty,
  /**
   * [AUTH]token已过期
   */
  DPSErrClientCodeAuthTokenExpired,
  /**
   * [AUTH]未初始化
   */
  DPSErrClientCodeAuthNotInit,
  /**
   * [AUTH]未登录
   */
  DPSErrClientCodeAuthNotAuthYet,
  /**
   * [DB]实例不存在
   */
  DPSErrClientCodeDBManagerNotExist = 100,
  /**
   * [DB]获取数据版本异常
   */
  DPSErrClientCodeDBGetVersionFailed,
  /**
   * [DB]异步执行超时
   */
  DPSErrClientCodeDBAsyncExecTimeout,
  /**
   * [DB]SQL执行失败
   */
  DPSErrClientCodeDBSQLError,
  /**
   * [DB]数据库文件损坏
   */
  DPSErrClientCodeDBOpenMalformed,
  /**
   * [DB]磁盘已满，数据写入失败
   */
  DPSErrClientCodeDBFull,
  /**
   * [DB]数据库损坏且无法自动恢复
   */
  DPSErrClientCodeDBMailformed,
  /**
   * [DB]数据库运行期间内存不足
   */
  DPSErrClientCodeDBNoMemory,
  /**
   *  [DB]数据库密钥错误
   */
  DPSErrClientCodeDBEncryptionKeyError,
  /**
   * [USERDATA]清理用户数据参数错误
   */
  DPSErrClientCodeResetUserDataInvalidParam = 150,
  /**
   * [USERDATA]账号正在使用
   */
  DPSErrClientCodeResetUserDataUserIsRunning,
  /**
   * [USERDATA]用户目录删除失败，可能被占用或无法删除
   */
  DPSErrClientCodeResetUserDataFailedToReset,
  /**
   * [NET]网络参数错误
   */
  DPSErrClientCodeNetErrInvalidParam = 100001,
  /**
   * [NET]网络操作异常
   */
  DPSErrClientCodeNetErrInvalidOperation,
  /**
   * [NET]网络超时
   */
  DPSErrClientCodeNetErrTimeout,
  /**
   * [NET]网络异常
   */
  DPSErrClientCodeNetErrNetworkException,
  /**
   * [NET]找不到token
   */
  DPSErrClientCodeNetErrNoAuthToken,
  /**
   * [NET]网络未连接
   */
  DPSErrClientCodeNetErrNotConnected,
  /**
   * [NET]正在登录
   */
  DPSErrClientCodeNetErrIsAuthing,
  /**
   * [NET]已经登录
   */
  DPSErrClientCodeNetErrIsAuthed,
  /**
   * [NET]token为空
   */
  DPSErrClientCodeNetErrTokenEmpty,
  /**
   * [NET]未知错误
   */
  DPSErrClientCodeNetErrUnknown,
  /**
   * [NET]网络包错误
   */
  DPSErrClientCodeNetErrUnpackException,
  /**
   * [NET]服务端未指定错误原因
   */
  DPSErrClientCodeNetErrCodeReasonNotSet,
  /**
   * [NET]账号已退出
   */
  DPSErrClientCodeNetErrLogout,
  /**
   * [NET]当前网络不可用
   */
  DPSErrClientCodeNetErrNetworkUnavailable,
  /**
   * [NET]发送请求失败
   */
  DPSErrClientCodeNetErrSendError,
  /**
   * [SQLITE] SQL执行成功
   */
  DPSErrClientCodeSqliteErrSqliteOk = 200000,
  /**
   * [SQLITE] SQL错误 或 丢失数据库
   */
  DPSErrClientCodeSqliteErrSqliteError,
  /**
   * [SQLITE] SQLite 内部逻辑错误
   */
  DPSErrClientCodeSqliteErrSqliteInternal,
  /**
   * [SQLITE] 拒绝访问
   */
  DPSErrClientCodeSqliteErrSqlitePerm,
  /**
   * [SQLITE] 回调函数请求取消操作
   */
  DPSErrClientCodeSqliteErrSqliteAbort,
  /**
   * [SQLITE] 数据库文件被锁定
   */
  DPSErrClientCodeSqliteErrSqliteBusy,
  /**
   * [SQLITE] 数据库中的一个表被锁定
   */
  DPSErrClientCodeSqliteErrSqliteLocked,
  /**
   * [SQLITE] 某次 malloc() 函数调用失败
   */
  DPSErrClientCodeSqliteErrSqliteNomem,
  /**
   * [SQLITE] 尝试写入一个只读数据库
   */
  DPSErrClientCodeSqliteErrSqliteReadonly,
  /**
   * [SQLITE] 操作被 sqlite3_interupt() 函数中断
   */
  DPSErrClientCodeSqliteErrSqliteInterrupt,
  /**
   * [SQLITE] 发生某些磁盘 I/O 错误
   */
  DPSErrClientCodeSqliteErrSqliteIOErr,
  /**
   * [SQLITE] 数据库磁盘映像不正确
   */
  DPSErrClientCodeSqliteErrSqliteCorrupt,
  /**
   * [SQLITE] sqlite3_file_control()中出现未知操作数
   */
  DPSErrClientCodeSqliteErrSqliteNotFound,
  /**
   * [SQLITE] 因为数据库满导致插入失败
   */
  DPSErrClientCodeSqliteErrSqliteFull,
  /**
   * [SQLITE] 无法打开数据库文件
   */
  DPSErrClientCodeSqliteErrSqliteCantOpen,
  /**
   * [SQLITE] 数据库锁定协议错误
   */
  DPSErrClientCodeSqliteErrSqliteProtocol,
  /**
   * [SQLITE] 数据库为空
   */
  DPSErrClientCodeSqliteErrSqliteEmpty,
  /**
   * [SQLITE] 数据结构发生改变
   */
  DPSErrClientCodeSqliteErrSqliteSchema,
  /**
   * [SQLITE] 字符串或二进制数据超过大小限制
   */
  DPSErrClientCodeSqliteErrSqliteTooBig,
  /**
   * [SQLITE] 由于约束违例而取消
   */
  DPSErrClientCodeSqliteErrSqliteConstraint,
  /**
   * [SQLITE] 数据类型不匹配
   */
  DPSErrClientCodeSqliteErrSqliteMismatch,
  /**
   * [SQLITE] 不正确的库使用
   */
  DPSErrClientCodeSqliteErrSqliteMisuse,
  /**
   * [SQLITE] 使用了操作系统不支持的功能
   */
  DPSErrClientCodeSqliteErrSqliteNolfs,
  /**
   * [SQLITE] 授权失败
   */
  DPSErrClientCodeSqliteErrSqliteAuth,
  /**
   * [SQLITE] 附加数据库格式错误
   */
  DPSErrClientCodeSqliteErrSqliteFormat,
  /**
   * [SQLITE] 传递给sqlite3_bind()的第二个参数超出范围
   */
  DPSErrClientCodeSqliteErrSqliteRange,
  /**
   * [SQLITE] 被打开的文件不是一个数据库文件
   */
  DPSErrClientCodeSqliteErrSqliteNotADb,
  /**
   * [SQLITE] 来自sqlite3_log()的提示
   */
  DPSErrClientCodeSqliteErrSqliteNotice,
  /**
   * [SQLITE] 来自sqlite3_log()的warning
   */
  DPSErrClientCodeSqliteErrSqliteWarning,
  /**
   * [SQLITE] sqlite3_step() 已经产生一个行结果
   */
  DPSErrClientCodeSqliteErrSqliteRow = 200100,
  /**
   * [SQLITE] sqlite3_step() 已经结束执行
   */
  DPSErrClientCodeSqliteErrSqliteDone = 200101,
};
