//
//  AliRtcEngine+Plugin.h
//  PluginAudio
//
//  Created by mt on 2021/2/5.
//  Copyright © 2021 mt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliRtcEngine.h"
/// @addtogroup AliRtcDef_ios Mac关键类型定义
/// AliRTC功能的插件扩展
/// @{

/**
 * @brief 插件错误码
 */
enum AliRtcPluginErrorCode{
    /** 成功 */
    AliRtcPluginErrorCodeSuccess = 0,
    /** 未知错误 */
    AliRtcPluginErrorCodeFailed = -1,
    /** 未找到对应插件 */
    AliRtcPluginErrorNoFindPlugin = -2,
    /** 参数错误 */
    AliRtcPluginErrorParameterError = -3,
    /** 插件库加载错误 */
    AliRtcPluginErrorLoadError = -4,
    /** 插件对象创建错误 */
    AliRtcPluginErrorCreateError = -5,
    /** 插件初始化失败 */
    AliRtcPluginErrorInitError = -6,
    /** 插件鉴权失败，使用非官网下载插件 */
    AliRtcPluginErrorInitTokenError = -7,
};


/**
 * @brief 插件类型
 */
enum AliRtcPluginDataType{
    /** 共享型 */
    AliRtcPluginDataTypeShared = 0,
    /** 视频处理型 */
    AliRtcPluginDataTypeVideo,
    /** 音频处理型 */
    AliRtcPluginDataTypeAudio,
    /** 加密型 */
    AliRtcPluginDataTypeEncryption,
    /** 占位符，无含义 */
    AliRtcPluginDataTypeMax,
};

/**
 * @brief 插件操作类型
 */
enum AliRtcPluginOperationType{
    /** 共享插件 */
    AliRtcPluginShared = 0,
    /** 推流前处理 */
    AliRtcPluginPreOperation,
    /** 拉流后处理 */
    AliRtcPluginPostOperation,
    /** 编码器 */
    AliRtcPluginEncodeOperation,
    /** 解码器 */
    AliRtcPluginDecodeOperation,
    /** 采集 */
    AliRtcPluginRecord,
    /** 渲染 */
    AliRtcPluginRender,
};
/** @} */

#pragma mark - 接口主类
/// @addtogroup AliRtc_ios AliRtcEngine
/// AliRTC功能的插件扩展
/// @{
@interface AliRtcEngine(Plugin)

/**
 * @brief 开启音视频处理算法插件
 * @details RTC采用插件件形式提供音视频增强及特效能力，可通过[官网组件文档](https://help.aliyun.com/document_detail/261183.html?spm=a2c4g.11186623.6.792.1bd4313f5c9nfe) 进行组件下载，参考插件集成文档集成进RTC引擎；
 * @param moduleName 插件库包名，组件文档中会有对应描述，包名中不包含插件后缀名如：iOS/Mac平台使用虚拟背景插件bokeh.framework，则包名为bokeh，Windows平台插件库名为：bokeh.dll，则moduleName 为bokeh；
 * @param pluginName 插件类名，根据下载的插件库中头文件中描述进行设置 如：虚拟背景插件头文件中描述了 pluginName 为 PluginBokeh；
 * @param pluginType 插件类型，值为AliRtcPluginDataType 与AliRtcPluginOperationType组合，
 * 如：视频前处理插件 pluginType  = (AliRtcPluginDataTypeVideo << 16)|AliRtcPluginPreOperation;
 * 如果需要修改已开启插件的pluginType，需要先进行插件关闭，再次开启；
 * @param opType 插件初始化参数类型，请阅读插件库接入文档，参考各个插件头文件中描述进行设置；
 * @param option 插件初始化参数值，请阅读插件库接入文档，参考各个插件头文件中描述进行设置；
 * @return
 * - >0: 返回注册的插件ID，插件移除及插件设置和插件信息获取需要使用此返回值；
 * - 非0: 详见{@link AliRtcPluginErrorCode}；
 *   - AliRtcPluginErrorLoadError：插件库库加载失败，插件库未添加到工程中，可参考[官网组件文档](https://help.aliyun.com/document_detail/261183.html?spm=a2c4g.11186623.6.792.1bd4313f5c9nfe) 按照集成文档进行集成；
 *
 *   - AliRtcPluginErrorInitError： 插件初始化失败，插件类型，参数类型或参数为非法值，可参考插件集成文档检查pluginType,opType,option初始值是否符合要求；
 *
 * @note
 * - 入会前入会后均可调用；
 * - 如果重复调用会返回之前已经注册插件ID；
 * - 如果需要修改已开启插件的pluginType，需要先进行插件关闭，再次开启；
*/
- (int)enablePlugin:(NSString *_Nullable)moduleName pluginName:(NSString *_Nullable)pluginName pluginType:(int)pluginType  opType:(uint32_t)opType option:(const void*_Nullable)option;

/**
 * @brief 关闭音视频处理算法插件
 * @param pluginId 开启音视频处理算法插件接口调用成功后返回值；
 * @return
 * - >0: 返回删除插件ID 即pluginId；
 * - 非0: 详见{@link AliRtcPluginErrorCode}；
 *   - AliRtcPluginErrorNoFindPlugin：pluginId为非法值或重复调用关闭接口，请检查pluginId值是否为开启插件接口调用成功后返回值；
 *
 * @note
 *  - 入会前入会后均可调用；
 *  - 重复调用返回 AliRtcPluginErrorNoFindPlugin 错误码；
*/
- (int)removePlugin:(uint32_t)pluginId;

/**
 * @brief 根据插件ID设置插件
 * @param pluginId 插件开启接口调用成功后返回值；
 * @param opType 设置插件参数类型，请阅读插件库接入文档，参考各个插件头文件中描述进行设置；
 * @param option 设置插件参数值，请阅读插件库接入文档，参考各个插件头文件中描述进行设置；
 * @return
 * - 0: 参数设置成功；
 * - 非0: 详见{@link AliRtcPluginErrorCode}；
 *  - AliRtcPluginErrorNoFindPlugin： 未找到对应插件，pluginId 为非法值，请检查pluginId值是否为开启插件接口调用成功后返回值；
 *  - AliRtcPluginErrorCodeFailed：opType或option为非法值，请阅读插件库接入文档，参考各个插件头文件中设置接口描述进行设置；
 *
 * @note
 *  - 入会前入会后均可调用；
 *  - opType及option 取值及范围要准守已开启插件头文件接口描述；
*/
- (int)setPluginOption:(uint32_t)pluginId opType:(uint32_t)opType option:(const void* _Nullable )option;

/**
 * @brief 根据插件ID获取插件内部信息
 * @param pluginId 开启插件接口调用成功后返回值；
 * @param opType 获取信息类型，请阅读插件库接入文档，参考各个插件头文件中描述进行设置；
 * @param option 返回的信息写入地址，插件会根据opType类型将返回的信息重写入option，需要进行内存初始化，长度请参考接入文档及插件头文件描述；
 * @return
 * - 0: 参数设置成功
 * - 非0: 详见{@link AliRtcPluginErrorCode}；
 *  - AliRtcPluginErrorNoFindPlugin： 未找到对应插件，pluginId 为非法值，请检查pluginId值是否为开启插件接口调用成功后返回值；
 *  - AliRtcPluginErrorCodeFailed：opType或option为非法值，请阅读插件库接入文档，参考插件接入文档及头文件中获取插件信息接口描述进行设置；
 *
 * @note
 *  - 入会前入会后均可调用；
 *  - AliRtcPluginErrorNoFindPlugin： 未找到对应插件，pluginId 为非法值，请检查pluginId值是否为开启插件接口调用成功后返回值；
 *  - AliRtcPluginErrorCodeFailed：opType或option为非法值，请阅读插件库接入文档，参考各个插件头文件中设置接口描述进行设置；
*/
- (int)getPluginOption:(uint32_t)pluginId opType:(uint32_t)opType option:(void* _Nonnull )option;

@end

/** @} */
