//
//  MainRemoterUserCCell.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import "MainRemoterUserCCell.h"
#import "NSBundle+RTCInteractiveLiveClass.h"
#import "Masonry.h"

@interface MainRemoterUserCCell ()

@property (nonatomic, strong) UIView *bgView;

@property (nonatomic, strong) UIImageView *emptyView;
//视频流视图
@property (nonatomic, strong) UIView *viewRemote;
//内容
@property (nonatomic, strong) UIView *contentV;
//角色
@property (strong,nonatomic) UILabel *roleLbl;
//昵称
@property (nonatomic,strong) UILabel *nameLabel;
//音频状态
@property (strong,nonatomic) UIButton *muteBtn;
//视频状态
@property (strong,nonatomic) UIButton *cameraBtn;
/// 举手状态
@property (nonatomic, strong) UIImageView *handView;

@end

@implementation MainRemoterUserCCell

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        [self configUI];
    }
    return self;
}


- (void)configUI {
    
    [self addSubview:self.bgView];
    [self addSubview:self.emptyView];
    [self addSubview:self.viewRemote];
    [self addSubview:self.contentV];
    [self.contentV addSubview:self.handView];
    [self.contentV addSubview:self.roleLbl];
    [self.contentV addSubview:self.nameLabel];
    [self.contentV addSubview:self.muteBtn];
    [self.contentV addSubview:self.cameraBtn];

    
    [_bgView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.edges.mas_equalTo(UIEdgeInsetsMake(4, 12, 4, 12));
    }];
    
    [_emptyView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerX.centerY.equalTo(_bgView);
    }];
    
    
    [_viewRemote mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.edges.mas_equalTo(UIEdgeInsetsMake(4, 12, 4, 12));
    }];
    
    [_contentV mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.edges.mas_equalTo(UIEdgeInsetsMake(4, 12, 4, 12));
    }];
    
    [_handView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerX.equalTo(_muteBtn.mas_centerX);
        make.top.equalTo(_roleLbl.mas_top);
    }];
    
    [_roleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.equalTo(_contentV.mas_left).mas_offset(4);
        make.top.equalTo(_contentV.mas_top).mas_offset(5);
        make.size.mas_equalTo(CGSizeMake(32, 20));
    }];
    
    [_nameLabel mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.equalTo(_roleLbl.mas_left);
        make.bottom.equalTo(_contentV.mas_bottom).mas_offset(-4);
        make.width.equalTo(@(32));
        make.height.equalTo(@(20));
    }];
    
    [_muteBtn mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerY.equalTo(_nameLabel.mas_centerY);
        make.right.equalTo(_contentV.mas_right);
        make.width.height.equalTo(@(30));
    }];
    
    [_cameraBtn mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerY.equalTo(_nameLabel.mas_centerY);
        make.right.equalTo(_muteBtn.mas_left).mas_offset(-5);
        make.width.height.equalTo(@(30));
    }];
}

/// 静音流按钮点击
- (void)MuteBtnClick:(UIButton *)btn {
    
    if ([self.userModel.uid isEqualToString:@"me"] && self.muteBtnClick) {
        self.muteBtnClick(btn);
    }
}

/// 视频流按钮点击
- (void)VideoBtnClick:(UIButton *)btn {
    
    if ([self.userModel.uid isEqualToString:@"me"] && self.videoBtnClick) {
        self.videoBtnClick(btn);
    }
}


#pragma mark - 更新数据 -
- (void)setUserModel:(RTCRemoteUserModel *)userModel {
    _userModel = userModel;
        
    [self updateUserRenderview:userModel.view];
    
    self.nameLabel.text = userModel.displayName;
    
    self.roleLbl.hidden = ![userModel.uid isEqualToString:@"me"];
    self.muteBtn.userInteractionEnabled = [userModel.uid isEqualToString:@"me"];
    self.cameraBtn.userInteractionEnabled = [userModel.uid isEqualToString:@"me"];

    self.handView.hidden = ![userModel.uid isEqualToString:@"me"];
    
    self.muteBtn.selected = userModel.audioMuted;
    
    self.cameraBtn.selected = userModel.videoMuted;

    
   CGFloat w = userModel.displayName.length * 12 + 8;
    if (w >70) {
        w = 70;
    }
    [_nameLabel mas_updateConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.width.equalTo(@(w));
    }];
}

- (void)updateUserRenderview:(UIView *)view {

    for (UIView *v in self.viewRemote.subviews) {
        [v removeFromSuperview];
    }
    
    view.backgroundColor = [UIColor clearColor];
    view.frame = CGRectMake(0, 0, 137, 77);
    view.hidden = self.userModel.videoMuted;

    [self.viewRemote addSubview:view];
}

#pragma mark - setter && getter -
- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [UIView new];
        _bgView.layer.cornerRadius = 4;
        _bgView.backgroundColor = [UIColor colorWithHex:0xF7F7F7];
        _bgView.layer.borderColor = [UIColor colorWithHex:0xEBEBEB].CGColor;
        _bgView.layer.shadowColor = [UIColor colorWithHex:0xD9D9D9 alpha:0.5].CGColor;
        _bgView.layer.shadowOffset = CGSizeMake(0,8);// 阴影偏移
        _bgView.layer.shadowOpacity = 0.5;// 阴影透明度
        _bgView.layer.shadowRadius = 16;// 阴影半径
    }
    return _bgView;
}

- (UIImageView *)emptyView {
    if (!_emptyView) {
        _emptyView = [UIImageView new];
        _emptyView.contentMode = UIViewContentModeScaleAspectFit;
        _emptyView.image = [NSBundle RILC_pngImageWithName:@"student"];
    }
    return _emptyView;
}


- (UIView *)contentV {
    if (!_contentV) {
        _contentV = [UIView new];
        _contentV.backgroundColor = [UIColor clearColor];
    }
    return _contentV;
}

- (UIView *)viewRemote {
    if (!_viewRemote) {
        _viewRemote = [UIView new];
    }
    return _viewRemote;
}

- (UILabel *)roleLbl {
    if (!_roleLbl) {
        _roleLbl = [UILabel new];
        _roleLbl.clipsToBounds = YES;
        _roleLbl.textAlignment = NSTextAlignmentCenter;
        _roleLbl.layer.cornerRadius = 4;
        _roleLbl.backgroundColor = [UIColor colorWithHex:0xEAEEFF];
        _roleLbl.textColor = [UIColor colorWithHex:0x365AFF];
        _roleLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
        _roleLbl.text = @"自己";
    }
    return _roleLbl;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [UILabel new];
        _nameLabel.clipsToBounds = YES;
        _nameLabel.textAlignment = NSTextAlignmentCenter;
        _nameLabel.layer.cornerRadius = 4;
        _nameLabel.backgroundColor = [UIColor colorWithHex:0xFFFFFF alpha:0.6];
        _nameLabel.textColor = [UIColor colorWithHex:0x333333];
        _nameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    }
    return _nameLabel;
}

- (UIButton *)muteBtn {
    if (!_muteBtn) {
        _muteBtn = [UIButton new];
        _muteBtn.tag = 0;
        [_muteBtn setImage:[NSBundle RILC_pngImageWithName:@"mute"] forState:UIControlStateNormal];
        [_muteBtn setImage:[NSBundle RILC_pngImageWithName:@"mute_no"] forState:UIControlStateSelected];
        [_muteBtn addTarget:self action:@selector(MuteBtnClick:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _muteBtn;
}

- (UIButton *)cameraBtn {
    if (!_cameraBtn) {
        _cameraBtn = [UIButton new];
        _cameraBtn.tag = 1;
        [_cameraBtn setImage:[NSBundle RILC_pngImageWithName:@"camera"] forState:UIControlStateNormal];
        [_cameraBtn setImage:[NSBundle RILC_pngImageWithName:@"camera_off"] forState:UIControlStateSelected];
        [_cameraBtn addTarget:self action:@selector(VideoBtnClick:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _cameraBtn;
}

- (UIImageView *)handView {
    if (!_handView) {
        _handView = [UIImageView new];
        _handView.hidden = YES;
        _handView.image = [NSBundle RILC_pngImageWithName:@"endMate"];
    }
    return _handView;
}


@end
