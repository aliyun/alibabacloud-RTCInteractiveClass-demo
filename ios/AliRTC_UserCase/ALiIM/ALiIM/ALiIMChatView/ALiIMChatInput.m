//
//  ALiIMChatInput.m
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/26.
//

#import "ALiIMChatInput.h"
#import "Masonry.h"

@interface ALiIMChatInput ()<UITextViewDelegate>

@property (nonatomic, strong) UITextView *textView;

@property (nonatomic, strong) UIButton *sendButton;

@end


@implementation ALiIMChatInput


- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        [self configUI];
    }
    return self;
}

//配置UI
- (void)configUI {
    
    self.backgroundColor = [UIColor whiteColor];
    
    _textView = [UITextView new];
    _textView.clipsToBounds = YES;
    _textView.layer.cornerRadius = 5;
    _textView.layer.borderWidth = 1;
    _textView.layer.borderColor = [UIColor colorWithWhite:0.4 alpha:0.3].CGColor;
    _textView.textColor = [UIColor blackColor];
    _textView.font = [UIFont systemFontOfSize:15];
    _textView.returnKeyType = UIReturnKeySend;
    _textView.delegate = self;

    _sendButton = [UIButton new];
    _sendButton.enabled = NO;
    _sendButton.titleLabel.font = [UIFont systemFontOfSize:15];
    _sendButton.layer.cornerRadius = 5;
    _sendButton.backgroundColor = [UIColor cyanColor];
    [_sendButton setTitle:@"发送" forState:UIControlStateNormal];
    [_sendButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_sendButton addTarget:self action:@selector(SendButtonClick) forControlEvents:UIControlEventTouchUpInside];
    
    
    [self addSubview:_textView];
    [self addSubview:_sendButton];

    [_textView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.mas_equalTo(UIEdgeInsetsMake(5, 5, 5, 65));
    }];
    
    [_sendButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.mas_centerY);
        make.right.equalTo(self.mas_right).mas_offset(-10);
        make.size.mas_equalTo(CGSizeMake(50, 35));
    }];
    
}

//退出键盘
- (void)resignFirstResponder {
    
    [_textView resignFirstResponder];
}


- (void)textViewDidChange:(UITextView *)textView {
    _sendButton.enabled = textView.text.length;

    UITextRange *selectedRange = [textView markedTextRange];
    //获取高亮部分
    UITextPosition *pos = [textView positionFromPosition:selectedRange.start offset:0];
    //如果在变化中是高亮部分在变，就不要计算字符了
    if(selectedRange && pos) {return;}
    if(textView.text.length>30) {
        // 对超出的部分进行剪切
        textView.text= [textView.text substringToIndex:30];
    }
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    if ([text isEqualToString:@"\n"])
    {
        if (textView.text.length == 0)
        {
            return NO;
        }
        //发送消息
        [self SendButtonClick];

        return NO;
    }
    return YES;
}


- (void)SendButtonClick {
    
    NSString *message = self.textView.text;
    
    if (self.SendMsgClick && message.length) {
        self.textView.text = @"";
        self.sendButton.enabled = NO;
        self.SendMsgClick(message);
    }
}



/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
