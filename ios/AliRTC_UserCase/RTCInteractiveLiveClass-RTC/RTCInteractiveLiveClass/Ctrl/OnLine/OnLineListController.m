//
//  OnLineListController.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import "OnLineListController.h"
#import "OnlineListTCell.h"
#import "Masonry.h"
#import "AliRtcInterrativeEngine.h"


@interface OnLineListController () <UITableViewDelegate, UITableViewDataSource>


@property (nonatomic, strong) UIView *emptyView;


@property (nonatomic, strong) UIView *contentView;
//标题
@property (nonatomic, strong) UILabel *titleLbl;
//在线人数
@property (nonatomic, strong) UILabel *onlineLbl;
//连麦人数
@property (nonatomic, strong) UILabel *micLbl;
//列表
@property (nonatomic, strong) UITableView *tableView;


@end

static NSString * const OnlineListTCellId = @"OnlineListTCellId";

@implementation OnLineListController

//支持旋转
-(BOOL)shouldAutorotate{
    return NO;
}

//支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscapeRight;
}

//一开始的方向  很重要
-(UIInterfaceOrientation)preferredInterfaceOrientationForPresentation{
    return UIInterfaceOrientationLandscapeRight;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = [UIColor clearColor];
    
    [self configUI];
}


- (void)setSeatArray:(NSArray<RTCRemoteUserModel *> *)seatArray {
    _seatArray = seatArray;
    
    NSInteger onlineCount = seatArray.count;
    for (RTCRemoteUserModel *Mo in seatArray) {
        if([[[AliRtcInterrativeEngine sharedInstance] getDisplayNameWithUid:Mo.uid] hasSuffix:@"老师"]) {
            onlineCount -= 1;
            break;
        }
    }
    
    //    self.onlineLbl.text = [NSString stringWithFormat:@"当前在线：%ld人",onlineArray.count];
    
    self.micLbl.text = [NSString stringWithFormat:@"连麦学生：%ld人",(long)onlineCount];
    
    //    [_tableView reloadData];
    
}

- (void)setOnlineArray:(NSArray<RTCRemoteUserModel *> *)onlineArray {
    _onlineArray = onlineArray;
    
    self.onlineLbl.text = [NSString stringWithFormat:@"当前在线：%lu人",(unsigned long)onlineArray.count];
    
    [_tableView reloadData];
}


#pragma mark - UITableViewDataSource -
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.onlineArray.count;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    return [UIView new];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    OnlineListTCell *cell = [tableView dequeueReusableCellWithIdentifier:OnlineListTCellId forIndexPath:indexPath];
    cell.model = [self.onlineArray objectAtIndex:indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0.01;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return 0.01;
}


#pragma mark - 配置UI -
- (void)configUI {
    
    _emptyView = [UIView new];
    
    _contentView = [UIView new];
    _contentView.backgroundColor = [UIColor whiteColor];
    
    _titleLbl = [UILabel new];
    _titleLbl.textColor = [UIColor colorWithHex:0x2F2F2F];
    _titleLbl.font = [UIFont fontWithName:@"PingFangSC-Regular" size:14];
    _titleLbl.text = @"在线列表";
    
    UIView *Line = [UIView new];
    Line.backgroundColor = [UIColor colorWithHex:0xEDEDED];
    
    
    [self.view addSubview:_emptyView];
    [self.view addSubview:_contentView];
    [_contentView addSubview:_titleLbl];
    [_contentView addSubview:Line];
    [_contentView addSubview:self.onlineLbl];
    [_contentView addSubview:self.micLbl];
    [_contentView addSubview:self.tableView];
    
    
    [_emptyView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.bottom.top.equalTo(self.view);
        make.right.equalTo(_contentView.mas_left);
    }];
    
    [_contentView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.top.bottom.right.equalTo(self.view);
        make.width.equalTo(@(320));
    }];
    
    [_titleLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerX.equalTo(_contentView.mas_centerX);
        make.top.equalTo(_contentView.mas_top);
        make.height.equalTo(@(36));
    }];
    
    [Line mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.left.right.equalTo(_contentView);
        make.top.equalTo(_titleLbl.mas_bottom);
        make.height.equalTo(@(1));
    }];
    
    [_onlineLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.top.equalTo(Line.mas_bottom).mas_offset(4);
        make.left.equalTo(_contentView.mas_left).mas_offset(16);
        make.height.equalTo(@(44));
    }];
    
    [_micLbl mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.centerY.equalTo(_onlineLbl.mas_centerY);
        make.left.equalTo(_onlineLbl.mas_right).mas_offset(48);
    }];
    
    [_tableView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.bottom.left.right.equalTo(_contentView);
        make.top.equalTo(_onlineLbl.mas_bottom);
    }];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(closeSelf)];
    tap.numberOfTapsRequired = 1;
    [_emptyView addGestureRecognizer:tap];
}

- (void)closeSelf {
    [self dismissViewControllerAnimated:NO completion:nil];
}


- (UITableView *)tableView {
    if (!_tableView) {
        _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
        _tableView.backgroundColor = [UIColor clearColor];
        _tableView.dataSource = self;
        _tableView.delegate = self;
        _tableView.showsVerticalScrollIndicator = NO;
        _tableView.delaysContentTouches = NO;
        _tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        [_tableView registerClass:[OnlineListTCell class] forCellReuseIdentifier:OnlineListTCellId];
        _tableView.tableFooterView = [[UIView alloc] init];
    }
    return _tableView;
}

- (UILabel *)onlineLbl {
    if (!_onlineLbl) {
        _onlineLbl = [UILabel new];
        _onlineLbl.textColor = [UIColor colorWithHex:0x333333];
        _onlineLbl.font = [UIFont fontWithName:@"PingFangSC-Medium" size:12];
        _onlineLbl.text = @"当前在线：0人";
    }
    return _onlineLbl;;
}

- (UILabel *)micLbl {
    if (!_micLbl) {
        _micLbl = [UILabel new];
        _micLbl.textColor = [UIColor colorWithHex:0x333333];
        _micLbl.font = [UIFont fontWithName:@"PingFangSC-Medium" size:12];
        _micLbl.text = @"连麦学生：0人";
    }
    return _micLbl;
}


- (void)viewDidLayoutSubviews {
    
    _contentView.layer.shadowColor = [UIColor colorWithHex:0x000000 alpha:0.21].CGColor;
    _contentView.layer.shadowOffset = CGSizeMake(0,3);
    _contentView.layer.shadowOpacity = 0.5;
    _contentView.layer.shadowRadius = 5;
    // 单边阴影 左边
    CGRect shadowRect = CGRectMake(-4, -4, 8, _contentView.bounds.size.height);
    UIBezierPath *path = [UIBezierPath bezierPathWithRect:shadowRect];
    _contentView.layer.shadowPath = path.CGPath;
}


/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

@end
