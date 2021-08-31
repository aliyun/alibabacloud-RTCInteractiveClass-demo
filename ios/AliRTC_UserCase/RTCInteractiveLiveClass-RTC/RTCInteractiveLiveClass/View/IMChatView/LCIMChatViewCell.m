//
//  LCIMChatViewCell.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/10.
//

#import "LCIMChatViewCell.h"
#import "Masonry.h"
#import "AliRtcInterrativeEngine.h"
#import "UIColor+Hex.h"
#import "NSBundle+RTCInteractiveLiveClass.h"

//#import "MJExtension.h"

@interface LCIMChatViewCell ()

@property (nonatomic, strong) UILabel *roleLbl;

@property (nonatomic, strong) UILabel *nameLbl;

@property (nonatomic, strong) UIImageView *bgIcon;

@property (nonatomic, strong) UILabel *messageLbl;

@end

@implementation LCIMChatViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        [self configUI];
    }
    return self;
}

//配置UI
- (void)configUI {
    
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    self.backgroundColor = [UIColor clearColor];

    [self.contentView addSubview:self.roleLbl];
    [self.contentView addSubview:self.nameLbl];
    [self.contentView addSubview:self.bgIcon];
    [self.contentView addSubview:self.messageLbl];

}

//设置数据 & 更新布局
- (void)setModel:(LCIMMessage *)model {
    _model = model;
    
    //1:自己发的 2:非自己发的
    if (model.sourceType == 1) { //自己发的
        
        _roleLbl.hidden = NO;
        _roleLbl.text = @"自己";
        _roleLbl.backgroundColor = [UIColor colorWithHex:0xEAEEFF];
        _roleLbl.textColor = [UIColor colorWithHex:0x365AFF];
        _messageLbl.textColor = [UIColor whiteColor];

        _bgIcon.image = [[NSBundle RILC_pngImageWithName:@"bg_bubble_blue"] resizableImageWithCapInsets:UIEdgeInsetsMake(30, 28, 85, 28) resizingMode:UIImageResizingModeStretch];
        
        
        [_roleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.centerY.equalTo(_nameLbl.mas_centerY);
            make.right.equalTo(self.contentView.mas_right).mas_offset(-16);
            make.size.mas_equalTo(CGSizeMake(28, 18));
        }];
        
        [_nameLbl mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(_roleLbl.mas_left).mas_offset(-4);
            make.top.equalTo(self.contentView.mas_top).mas_offset(11);
        }];
        
        [_bgIcon mas_remakeConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.edges.equalTo(_messageLbl).mas_equalTo(UIEdgeInsetsMake(-5, -8, -5, -8));
        }];
        
        [_messageLbl mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(self.contentView.mas_right).mas_offset(-21);
            make.top.equalTo(_nameLbl.mas_bottom).mas_offset(11);
            make.width.mas_lessThanOrEqualTo(320-48);
        }];
        
    }else { //其他人发的
        
        _roleLbl.text = @"教师";
        _roleLbl.hidden = ![model.displayName containsString:@"教师"];
        _roleLbl.backgroundColor = [UIColor colorWithHex:0xFFEDF0];
        _roleLbl.textColor = [UIColor colorWithHex:0xE80320];
        _messageLbl.textColor = [UIColor colorWithHex:0x333333];
        _bgIcon.image = [[NSBundle RILC_pngImageWithName:@"bg_bubble_white"] resizableImageWithCapInsets:UIEdgeInsetsMake(30, 28, 85, 28) resizingMode:UIImageResizingModeStretch];

        
        [_roleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.centerY.equalTo(_nameLbl.mas_centerY);
            make.left.equalTo(_nameLbl.mas_right).mas_offset(4);
            make.size.mas_equalTo(CGSizeMake(28, 18));
        }];

        [_nameLbl mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self.contentView.mas_left).mas_offset(16);
            make.top.equalTo(self.contentView.mas_top).mas_offset(11);
        }];

        
        [_bgIcon mas_remakeConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.edges.equalTo(_messageLbl).mas_equalTo(UIEdgeInsetsMake(-5, -8, -5, -8));
        }];
        
        [_messageLbl mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self.contentView.mas_left).mas_offset(21);
            make.top.equalTo(_nameLbl.mas_bottom).mas_offset(11);
            make.width.mas_lessThanOrEqualTo(320-48);
        }];
        
        [_roleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
            make.centerY.equalTo(_nameLbl.mas_centerY);
            make.left.equalTo(_nameLbl.mas_right).mas_offset(4);
            make.size.mas_equalTo(CGSizeMake(28, 18));
        }];
    }
    
    _messageLbl.text = model.message;

    _nameLbl.text = model.displayName;
}


- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}


#pragma mark - getter && setter -
- (UILabel *)roleLbl {
    if (!_roleLbl) {
        _roleLbl = [[UILabel alloc] init];
        _roleLbl.hidden = YES;
        _roleLbl.clipsToBounds = YES;
        _roleLbl.textAlignment = NSTextAlignmentCenter;
        _roleLbl.layer.cornerRadius = 4;
        _roleLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:10];
    }
    return _roleLbl;
}

- (UILabel *)nameLbl {
    if (!_nameLbl) {
        _nameLbl = [UILabel new];
        _nameLbl.textColor = [UIColor colorWithHex:0x888888];
        _nameLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:10];
    }
    return _nameLbl;
}

- (UIImageView *)bgIcon {
    if (!_bgIcon) {
        _bgIcon = [UIImageView new];
    }
    return _bgIcon;
}

- (UILabel *)messageLbl {
    if (!_messageLbl) {
        _messageLbl = [UILabel new];
        _messageLbl.numberOfLines = 0;
        _messageLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    }
    return _messageLbl;
}

@end
