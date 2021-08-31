//
//  LCIMChatView.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/6/10.
//

#import "LCIMChatView.h"
#import "LCIMChatViewCell.h"
#import "LCIMChatInput.h"

#import "Masonry.h"
#import "RTCHUD.h"
#import "RTCCommon.h"
#import "ALiIMHeader.h"


@interface LCIMChatView ()<ALiIMChatViewDelegate>

//聊天视图
@property (nonatomic, strong) ALiIMChatView *chatView;
//文本输入框
@property (nonatomic, strong)LCIMChatInput *chatInput;
//消息列表
@property (nonatomic, strong)NSMutableArray<LCIMMessage *> *dataArrM;

@end

@implementation LCIMChatView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self configUI];
    }
    return self;
}

#pragma mark - 配置UI
- (void)configUI {
    
    self.backgroundColor = [UIColor whiteColor];
    
    [self addSubview:self.chatView];
    
    [_chatView mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.edges.equalTo(self);
    }];

    [_chatView chatViewCustomInputToolbar:self.chatInput];
}


#pragma mark - 消息相关 -
///// 消息更新 包含从服务器拉取消息及新增消息
///// @param messages 消息
- (void)updateMessages:(NSArray<LCIMMessage *> *)messages {

//    NSLog(@"消息更新 = %@",messages);

    [self.dataArrM removeAllObjects];

    [self.dataArrM addObjectsFromArray:messages];

    [self.chatView reloadData];

    if ([self.chatView isBottom]) {
        [self.chatView scrollToBottomAnimated:YES];
    }
}



#pragma mark - ALiIMChatViewDataSource -
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataArrM.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    LCIMChatViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"LCIMChatViewCell"];
    cell.model = [self.dataArrM objectAtIndex:indexPath.row];
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    LCIMMessage *model = [self.dataArrM objectAtIndex:indexPath.row];

    CGFloat maxWith = self.frame.size.width - 48;
    CGSize size = [self labelAutoCalculateRectWith:model.message Font:[UIFont fontWithName:@"PingFangSC-Regular" size:12] MaxSize:CGSizeMake(maxWith, MAXFLOAT)];
    return 50 + size.height;
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [self.chatInput resignFirstResponder];
}

- (CGSize)labelAutoCalculateRectWith:(NSString *)text Font:(UIFont *)textFont MaxSize:(CGSize)maxSize {
    NSDictionary *attributes = @{NSFontAttributeName: textFont};
    CGRect rect = [text boundingRectWithSize:maxSize
                                     options:NSStringDrawingUsesLineFragmentOrigin
                                  attributes:attributes
                                     context:nil];
    return rect.size;
}



#pragma mark - setter & getter -
- (ALiIMChatView *)chatView {
    if (!_chatView) {
        _chatView = [ALiIMChatView new];
        _chatView.delegate = self;
        [_chatView registerClass:[LCIMChatViewCell class] forCellReuseIdentifier:@"LCIMChatViewCell"];
    }
    return _chatView;
}

- (LCIMChatInput *)chatInput {
    if (!_chatInput) {
        _chatInput = [[LCIMChatInput alloc] initWithFrame:CGRectMake(0, 0, 320, 50)];
        __weak typeof(self) weakSelf = self;
        _chatInput.SendMsgClick = ^(NSString * _Nullable message) {
            if (weakSelf.SendMsgClick) {
                weakSelf.SendMsgClick(message);
            }
        };
    }
    return _chatInput;
}

- (NSMutableArray *)dataArrM {
    if (!_dataArrM) {
        _dataArrM = [NSMutableArray array];
    }
    return _dataArrM;
}




- (void)dealloc {
        
    NSLog(@"LCIMChatView - dealloc");
}

/*
 // Only override drawRect: if you perform custom drawing.
 // An empty implementation adversely affects performance during animation.
 - (void)drawRect:(CGRect)rect {
 // Drawing code
 }
 */

@end
