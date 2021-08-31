//
//  LCTipsInfoAlert.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/12.
//

#import "LCTipsInfoAlert.h"
#import "Masonry.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "UIColor+Hex.h"



@interface LCTipsInfoAlert ()

/** 弹窗 */
@property(nonatomic,strong) UIView *alertView;
/** 图标*/
@property(nonatomic,strong) UIImageView *imageView;

/** 消息内容*/
@property(nonatomic,retain) UILabel *msgLbl;

/** 确认按钮 */
@property(nonatomic,strong) UIButton *sureBtn;
/** 取消按钮 */
@property(nonatomic,strong) UIButton *cancleBtn;
/** 横线 */
@property (nonatomic, strong) UIView *hLine;
/** 竖线 */
@property (nonatomic, strong) UIView *vLine;

@end

@implementation LCTipsInfoAlert

/// 创建一个提示框
/// @param icon 顶部图片
/// @param msg 提示信息
/// @param sureName 确认按钮名称
/// @param cancelName 取消按钮名称
- (instancetype)initWithIcon:(NSString *)icon
                     message:(NSString *)msg
                       sureName:(NSString *)sureName
                  cancelName:(NSString *)cancelName {
    if (self = [super init]) {
        
        self.frame = [UIScreen mainScreen].bounds;
        self.backgroundColor = [UIColor clearColor];
        
        _alertView = [UIView new];
        _alertView.backgroundColor = [UIColor whiteColor];
        _alertView.layer.shadowColor = [UIColor colorWithHex:0x000000 alpha:0.11].CGColor;
        _alertView.layer.shadowOffset = CGSizeMake(0,0);
        _alertView.layer.shadowOpacity = 0.5;
        _alertView.layer.shadowRadius = 5;

        
        
        _imageView = [UIImageView new];
        _imageView.image = [NSBundle RILC_pngImageWithName:icon];
        
        _msgLbl = [UILabel new];
        _msgLbl.textAlignment = NSTextAlignmentCenter;
        _msgLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:16];
        _msgLbl.textColor = [UIColor colorWithHex:0x333333];
        _msgLbl.text = msg;
        
        _hLine = [UIView new];
        _hLine.backgroundColor = [UIColor colorWithHex:0xE2E2E2];;
        
        _cancleBtn = [UIButton new];
        _cancleBtn.tag = 1;
        _cancleBtn.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:18];
        [_cancleBtn setTitle:cancelName forState:UIControlStateNormal];
        [_cancleBtn setTitleColor:[UIColor colorWithHex:0x9B9B9B] forState:UIControlStateNormal];
        [_cancleBtn addTarget:self action:@selector(buttonEvent:) forControlEvents:UIControlEventTouchUpInside];
                
        _vLine = [UIView new];
        _vLine.backgroundColor = [UIColor colorWithHex:0xE2E2E2];;

        _sureBtn = [UIButton new];
        _sureBtn.tag = 2;
        _sureBtn.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:18];
        [_sureBtn setTitle:sureName forState:UIControlStateNormal];
        [_sureBtn setTitleColor:[UIColor colorWithHex:0x365AFF] forState:UIControlStateNormal];
        [_sureBtn addTarget:self action:@selector(buttonEvent:) forControlEvents:UIControlEventTouchUpInside];

        
        [self addSubview:_alertView];
        [_alertView addSubview:_imageView];
        [_alertView addSubview:_msgLbl];
        
        [_alertView addSubview:_hLine];

        [_alertView addSubview:_sureBtn];
        [_alertView addSubview:_vLine];
        [_alertView addSubview:_cancleBtn];

        
        [_alertView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.equalTo(@(160));
            make.width.equalTo(@(295));
            make.centerY.centerX.equalTo(self);
        }];
        
        [_imageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(_alertView.mas_centerX);
            make.top.equalTo(_alertView.mas_top).mas_offset(24);
            make.width.height.equalTo(@(24));
        }];
        
        [_msgLbl mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_alertView.mas_left).mas_offset(24);
            make.right.equalTo(_alertView.mas_right).mas_offset(-24);
            make.top.equalTo(_imageView.mas_bottom).mas_offset(20);
        }];
        
        [_hLine mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_alertView.mas_left);
            make.right.equalTo(_alertView.mas_right);
            make.bottom.equalTo(_sureBtn.mas_top);
            make.height.equalTo(@(1));
        }];
        
        CGFloat W = 294.0 / 2.0;
        [_cancleBtn mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_alertView.mas_left);
            make.bottom.equalTo(_alertView.mas_bottom);
            make.width.equalTo(@(W));
            make.height.equalTo(@(50));
        }];
        
        [_vLine mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.top.equalTo(_cancleBtn);
            make.left.equalTo(_cancleBtn.mas_right);
            make.width.equalTo(@(1));
        }];
        
        [_sureBtn mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_vLine.mas_right);
            make.top.width.height.equalTo(_cancleBtn);
        }];
    }
    return self;
}

#pragma mark - 回调 只设置2 -- > 确定才回调
- (void)buttonEvent:(UIButton *)sender {
    if (sender.tag == 2) {
        if (self.submitblock) {
            self.submitblock();
        }
    }
    [self removeFromSuperview];
}

/// 显示
-(void)show {
    UIWindow *rootWindow = [UIApplication sharedApplication].keyWindow;
    [rootWindow addSubview:self];
    [self creatShowAnimation];
}

/// 隐藏
-(void)hide {
    [self removeFromSuperview];
}


#pragma mark - 弹出
-(void)showAlertView {

}

-(void)creatShowAnimation {
    self.alertView.layer.position = self.center;
    self.alertView.transform = CGAffineTransformMakeScale(0.90, 0.90);
    [UIView animateWithDuration:0.25 delay:0 usingSpringWithDamping:0.8 initialSpringVelocity:1 options:UIViewAnimationOptionCurveLinear animations:^{
        self.alertView.transform = CGAffineTransformMakeScale(1.0, 1.0);
    } completion:^(BOOL finished) {
        
    }];
    
}

#pragma mark - 关闭按钮点击才回调
- (void)CloseBtnClick {
    
    [self removeFromSuperview];
}




/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
