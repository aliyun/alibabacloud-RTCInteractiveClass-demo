//
//  OnlineListTCell.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/22.
//

#import "OnlineListTCell.h"
#import "Masonry.h"
#import "UIColor+Hex.h"
#import "AliRtcInterrativeEngine.h"


@interface OnlineListTCell ()

@property (nonatomic, strong) UILabel *nameLbl;

@property (nonatomic, strong) UILabel *roleLbl;

@end


@implementation OnlineListTCell

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

    _nameLbl = [UILabel new];
    _nameLbl.textColor = [UIColor colorWithHex:0x333333];
    _nameLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
//    _nameLbl.text = @"学生A";
    
    _roleLbl = [UILabel new];
    _roleLbl.hidden = YES;
    _roleLbl.clipsToBounds = YES;
    _roleLbl.textAlignment = NSTextAlignmentCenter;
    _roleLbl.layer.cornerRadius = 4;
    _roleLbl.backgroundColor = [UIColor colorWithHex:0xEAEEFF];
    _roleLbl.textColor = [UIColor colorWithHex:0x365AFF];
    _roleLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:12];
    
    [self.contentView addSubview:_nameLbl];
    [self.contentView addSubview:_roleLbl];

    
    [_nameLbl mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.mas_centerY);
        make.left.equalTo(self.mas_left).mas_offset(16);
    }];
    
    [_roleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.equalTo(_nameLbl.mas_right).mas_offset(12);
        make.centerY.equalTo(self.mas_centerY);
        make.size.mas_equalTo(CGSizeMake(32, 20));
    }];
}


- (void)setModel:(RTCRemoteUserModel *)model {
    _model = model;

    if (!model.displayName.length) {
        _nameLbl.text = [[AliRtcInterrativeEngine sharedInstance] getDisplayNameWithUid:model.uid];
    }else {
        _nameLbl.text = model.displayName;
    }
    
    _roleLbl.hidden = YES;

    if([model.displayName hasSuffix:@"老师"]) {
        _roleLbl.backgroundColor = [UIColor colorWithHex:0xE80320 alpha:0.1];
        _roleLbl.textColor = [UIColor colorWithHex:0xE80320];
        _roleLbl.hidden = NO;
        _roleLbl.text = @"教师";
    }
    
    if ([model.uid isEqualToString:@"me"]) {
        _roleLbl.backgroundColor = [UIColor colorWithHex:0xEAEEFF];
        _roleLbl.textColor = [UIColor colorWithHex:0x365AFF];
        _roleLbl.hidden = NO;
        _roleLbl.text = @"自己";
    }
}


- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
