// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AIMErrClientCode) {
  /**
   * [DPS]AIMConvService实例不存在
   */
  AIMErrClientCodeAIMConvIsNull = 300,
  /**
   * [DPS]AIMSearchService实例不存在
   */
  AIMErrClientCodeAIMSEARCHISNULL,
  /**
   * [DPS]AIMMsgService实例不存在
   */
  AIMErrClientCodeAIMMsgIsNull,
  /**
   * [DPS]AIMTraceService实例不存在
   */
  AIMErrClientCodeAIMTraceIsNull,
  /**
   * [IM]消息实例不存在
   */
  AIMErrClientCodeIMMsgIsNull,
  /**
   * [IM]拉取消息失败
   */
  AIMErrClientCodeIMListMsgFailed,
  /**
   * [IM]消息已读状态写入失败
   */
  AIMErrClientCodeIMSyncReadFailed,
  /**
   * [IM]写入消息扩展失败
   */
  AIMErrClientCodeIMSyncExtFailed,
  /**
   * [IM]合并消息失败
   */
  AIMErrClientCodeIMMsgMergeFailed,
  /**
   * [IM]消息内容为空
   */
  AIMErrClientCodeIMMsgTextEmpty,
  /**
   * [IM]会话实例不存在
   */
  AIMErrClientCodeIMConvIsNull,
  /**
   * [IM]找不到会话
   */
  AIMErrClientCodeIMGetConvFailed,
  /**
   * [IM]撤回消息失败
   */
  AIMErrClientCodeIMRecallMsgFailed,
  /**
   * [IM]外部消息Hook回调发生错误
   */
  AIMErrClientCodeIMMsgHookFailed,
  /**
   * [IM]数据unpack失败
   */
  AIMErrClientCodeIMUnpcakFailed,
  /**
   * [SEARCH]搜索数据库操作失败
   */
  AIMErrClientCodeSearchDBFailed = 500,
  /**
   * [SEARCH]FTS引擎操作失败
   */
  AIMErrClientCodeSearchFTSFailed,
  /**
   * [SEARCH]搜索参数错误
   */
  AIMErrClientCodeSearchParamsFailed,
  /**
   * [SEARCH]FTS引擎未初始化
   */
  AIMErrClientCodeSearchFTSNotInitialized,
};
