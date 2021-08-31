//
//  LCTipsInfoAlert.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/12.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCTipsInfoAlert : UIView

/// 创建一个提示框
/// @param icon 顶部图片
/// @param msg 提示信息
/// @param sureName 确认按钮名称
/// @param cancelName 取消按钮名称
- (instancetype)initWithIcon:(NSString *)icon
                     message:(NSString *)msg
                       sureName:(NSString *)sureName
                     cancelName:(NSString *)cancelName;

/// 点击确认按钮回调
@property(nonatomic,copy) void(^submitblock)(void);

/// 显示
-(void)show;

/// 隐藏
-(void)hide;


@end

NS_ASSUME_NONNULL_END
