//
//  MainViewRightButton.m
//  RTCInteractiveLiveClass
//
//  Created by RTCTeam on 2021/7/10.
//

#import "MainViewRightButton.h"

@implementation MainViewRightButton

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        self.titleLabel.textAlignment = NSTextAlignmentCenter;
        self.titleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:10];
        [self setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    CGFloat w = self.frame.size.width;

    CGFloat x = (w - 20) / 2.0;
    
    self.imageView.frame = CGRectMake(x, 14, 20, 20);
    self.titleLabel.frame = CGRectMake(0, 37, w, 18);
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
