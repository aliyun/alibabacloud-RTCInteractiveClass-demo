// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import <Foundation/Foundation.h>

@protocol DPSUtListener

/**
 * 成功打点上报
 * @param module    模块
 * @param monitorPoint    打点名称
 * @param extensions      附加参数
 */
- (void)onSuccessReport:(nonnull NSString *)module
           monitorPoint:(nonnull NSString *)monitorPoint
             extensions:(nonnull NSDictionary<NSString *, NSString *> *)extensions;

/**
 * 失败打点上报
 * @param module    模块
 * @param monitorPoint    打点名称
 * @param errorCode     错误码
 * @param errorMsg     错误信息
 * @param extensions      附加参数
 */
- (void)onFailReport:(nonnull NSString *)module
        monitorPoint:(nonnull NSString *)monitorPoint
           errorCode:(int32_t)errorCode
            errorMsg:(nonnull NSString *)errorMsg
          extensions:(nonnull NSDictionary<NSString *, NSString *> *)extensions;

/**
 * 计数打点上报
 * @param module    模块
 * @param monitorPoint    打点名称
 * @param count     计数值
 * @param extensions      附加参数
 */
- (void)onCountReport:(nonnull NSString *)module
         monitorPoint:(nonnull NSString *)monitorPoint
                count:(double)count
           extensions:(nonnull NSDictionary<NSString *, NSString *> *)extensions;

/**
 * 性能打点注册
 * @param module    模块
 * @param monitorPoint    打点名称
 * @param dimensions 维度
 * @param measures 测量数据
 */
- (void)onStatRegister:(nonnull NSString *)module
          monitorPoint:(nonnull NSString *)monitorPoint
            dimensions:(nonnull NSArray<NSString *> *)dimensions
              measures:(nonnull NSArray<NSString *> *)measures;

/**
 * 性能打点上报
 * @param module    模块
 * @param monitorPoint    打点名称
 * @param dimensionValues 维度
 * @param measureValues 测量数据
 */
- (void)onStatReport:(nonnull NSString *)module
        monitorPoint:(nonnull NSString *)monitorPoint
     dimensionValues:(nonnull NSDictionary<NSString *, NSString *> *)dimensionValues
       measureValues:(nonnull NSDictionary<NSString *, NSNumber *> *)measureValues;

@end
