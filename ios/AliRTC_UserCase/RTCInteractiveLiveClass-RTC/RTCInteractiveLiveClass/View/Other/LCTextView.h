//
//  LCTextView.h
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/12.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface LCTextView : UITextView

/** 占位文字 */
@property (weak, nonatomic) NSString *placeholder;
/** 占位文字颜色 */
@property (nonatomic, strong) UIColor *placeholderColor;
/** 占位文字大小 */
@property (nonatomic, assign) CGFloat placeholderFont;


@end

NS_ASSUME_NONNULL_END
