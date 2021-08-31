//
//  ALiIMChatToolBar.m
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/26.
//

#import "ALiIMChatToolBar.h"

@implementation ALiIMChatToolBar

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        [self configUI];
    }
    return self;
}

- (void)configUI {
    
    self.backgroundColor = [UIColor redColor];
    
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
