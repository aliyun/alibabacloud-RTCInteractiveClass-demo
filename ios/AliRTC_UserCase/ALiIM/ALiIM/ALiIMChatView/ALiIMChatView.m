//
//  ALiIMChatView.m
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/25.
//

#import "ALiIMChatView.h"
#import "ALiIMChatInput.h"
#import "Masonry.h"


@interface ALiIMChatView ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong)UITableView *tableView;

@property (nonatomic, strong)ALiIMChatToolBar *bottomToolbar;

@property (nonatomic, strong)ALiIMChatInput *chatInput;



@end

@implementation ALiIMChatView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self configUI];
    }
    return self;
}

- (void)chatInputSendMsgClick:(NSString *)msg {
    
    if ([self.delegate respondsToSelector:@selector(testSendMsg:)]) {
        [self.delegate testSendMsg:msg];
    }
    
}


#pragma mark - 配置UI
- (void)configUI {
    
    self.backgroundColor = [UIColor clearColor];
    
    [self addSubview:self.tableView];
    [self addSubview:self.bottomToolbar];
    [self.bottomToolbar addSubview:self.chatInput];
    
    [_tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.equalTo(self);
        make.bottom.equalTo(_bottomToolbar.mas_top);
    }];
    
    [_bottomToolbar mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self);
        make.bottom.equalTo(self);
        make.height.equalTo(@(50));
    }];
        
    [_chatInput mas_makeConstraints:^(MASConstraintMaker * _Nonnull make) {
        make.edges.equalTo(_bottomToolbar);
    }];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardWillChangeFrame:) name:UIKeyboardWillChangeFrameNotification object:nil];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self scrollToBottomAnimated:NO];
    });
}

- (void)chatViewCustomInputToolbar:(UIView *)input {
    
    if (input) {
        
        [self.chatInput removeFromSuperview];
        [self.bottomToolbar addSubview:input];
        
        [_bottomToolbar mas_updateConstraints:^(MASConstraintMaker *make) {
            make.height.equalTo(@(input.bounds.size.height));
        }];
    }
}

- (void)reloadData {
    [self.tableView reloadData];
}

#pragma mark - UITableViewDataSource -
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.delegate tableView:tableView numberOfRowsInSection:section];
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    return [UIView new];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    return [self.delegate tableView:tableView cellForRowAtIndexPath:indexPath];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return [self.delegate tableView:tableView heightForRowAtIndexPath:indexPath];
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0.01;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return 0.01;
}


- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    if ([self.delegate respondsToSelector:@selector(scrollViewWillBeginDragging:)]) {
        [self.delegate scrollViewWillBeginDragging:scrollView];
    }
    [self.chatInput resignFirstResponder];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesBegan:touches withEvent:event];
    [self.chatInput resignFirstResponder];
}


- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier {
    [self.tableView registerClass:cellClass forCellReuseIdentifier:identifier];
}

#pragma mark - 监听键盘frame改变 -
- (void)keyBoardWillChangeFrame:(NSNotification*)notification {
    
    // 键盘显示\隐藏完毕的frame
    CGRect frame = [notification.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    
    //    _keyboardHeight = frame.size.height;
    
    // 动画时间
    CGFloat duration = [notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    CGFloat offSetY = 0;
            
    if (frame.origin.y == [UIScreen mainScreen].bounds.size.height) { // 没有弹出键盘 (横屏)
        
        offSetY = 0;
    }else{ // 弹出键盘
        
        offSetY = -frame.size.height;
    }
    
    
    [_bottomToolbar mas_updateConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self).mas_offset(offSetY);
    }];
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView reloadData];
    });

    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(duration * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        [self scrollToBottomAnimated:NO];
    });
}




- (BOOL)isBottom {
    CGFloat bottomHeight = 5;
    BOOL isBottom = (self.tableView.contentSize.height - self.tableView.contentOffset.y - self.tableView.bounds.size.height < bottomHeight);
    return isBottom;
}


- (void)scrollToBottomAnimated:(BOOL)animated {
    if ([self.tableView numberOfSections] == 0) {
        return;
    }

    NSIndexPath *lastCell = [NSIndexPath indexPathForRow:([self.tableView numberOfRowsInSection:0] - 1) inSection:0];

    [self scrollToIndexPath:lastCell animated:animated];
}


- (void)scrollToIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated
{
    if ([self.tableView numberOfSections] <= indexPath.section) {
        return;
    }

    NSInteger numberOfItems = [self.tableView numberOfRowsInSection:indexPath.section];

    if (numberOfItems == 0) {
        return;
    }

    CGFloat tableViewContentHeight = self.tableView.contentSize.height;
    BOOL isContentTooSmall = (tableViewContentHeight < CGRectGetHeight(self.tableView.bounds));

    
    if (isContentTooSmall) {
        //  workaround for the first few messages not scrolling
        //  when the collection view content size is too small, `scrollToItemAtIndexPath:` doesn't work properly
        //  this seems to be a UIKit bug, see #256 on GitHub
        [self.tableView scrollRectToVisible:CGRectMake(0.0, tableViewContentHeight - 1.0f, 1.0f, 1.0f)
                                        animated:animated];
        return;
    }

    NSInteger item = MAX(MIN(indexPath.row, numberOfItems - 1), 0);
    indexPath = [NSIndexPath indexPathForItem:item inSection:0];
    
    [self.tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionBottom animated:animated];
}



#pragma mark - setter & getters
- (UITableView *)tableView {
    if (!_tableView) {
        _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
        _tableView.backgroundColor = [UIColor clearColor];
        _tableView.dataSource = self;
        _tableView.delegate = self;
        _tableView.showsVerticalScrollIndicator = NO;
        _tableView.delaysContentTouches = NO;
        _tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
//        [_tableView registerClass:[ALiIMChatBaseCell class] forCellReuseIdentifier:@"ALiIMChatBaseCell"];
        _tableView.tableFooterView = [[UIView alloc] init];
    }
    return _tableView;
}

- (ALiIMChatToolBar *)bottomToolbar {
    if (!_bottomToolbar) {
        _bottomToolbar = [ALiIMChatToolBar new];
    }
    return _bottomToolbar;
}

- (ALiIMChatInput *)chatInput {
    if (!_chatInput) {
        _chatInput = [ALiIMChatInput new];
        __weak typeof(self) weakSelf = self;
        _chatInput.SendMsgClick = ^(NSString * _Nullable message) {
            [weakSelf chatInputSendMsgClick:message];
        };
    }
    return _chatInput;
}


- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
