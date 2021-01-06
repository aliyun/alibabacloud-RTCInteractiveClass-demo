//
//  RTCRemoterUserCell.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/25.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "RTCRemoterUserCell.h"
#import "NSBundle+RTCInteractiveLiveClass.h"

#define RTCRemoterUserCellWidth 120

#define RTCRemoterUserCellHeight 90
@interface RTCRemoterUserCell()

@property (weak,nonatomic) UIImageView *muteIcon;

@property (nonatomic,weak) UILabel *nameLabel;

@property (nonatomic, assign) BOOL muted;

@property (nonatomic, weak) AliRenderView *viewRemote;


@end
 
@implementation RTCRemoterUserCell


- (instancetype)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        //设置远端流界面 
        self.backgroundColor = [UIColor blackColor];
        //1.添加摄像头关闭ICON
        CGFloat imageW = 26;
        CGFloat imageH = 26;
        CGFloat imageX = (RTCRemoterUserCellWidth - imageW) * 0.5;
        CGFloat imageY = 20;
        UIImageView *imageView = [[UIImageView alloc]initWithFrame:CGRectMake(imageX, imageY, imageW, imageH)];
        imageView.image = [NSBundle RILC_pngImageWithName:@"camera_off"];
        [self addSubview:imageView];
        
        UILabel *label = [[ UILabel alloc] initWithFrame:CGRectMake(0, 50, RTCRemoterUserCellWidth, 16)];
        label.text = @"摄像头已关闭";
        label.textColor = [UIColor whiteColor];
        label.font = [UIFont systemFontOfSize:12];
        label.textAlignment = NSTextAlignmentCenter;
        [self addSubview:label];
        
        UILabel *nameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 70, RTCRemoterUserCellWidth, 20)];
        self.nameLabel = nameLabel;
        self.nameLabel.font = [UIFont systemFontOfSize:14];
        self.nameLabel.textColor = [UIColor whiteColor];
        nameLabel.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0.4];
        [self addSubview: nameLabel];
        
        UIImageView *micMuteView = [[UIImageView alloc] initWithFrame:CGRectMake(RTCRemoterUserCellWidth - 25, 0, 20, 20)];
        micMuteView.image = [NSBundle RILC_pngImageWithName:@"unmute"];
        [nameLabel addSubview:micMuteView];
        _muteIcon = micMuteView;
        
        
    }
    return self;
}

- (void)updateUserRenderview:(AliRenderView *)view {
     
    
    view.backgroundColor = [UIColor clearColor];
    view.frame = CGRectMake(0, 0, RTCRemoterUserCellWidth, RTCRemoterUserCellHeight);
    view.subviews.firstObject.frame = CGRectMake(0, 0, RTCRemoterUserCellWidth, RTCRemoterUserCellHeight);
    self.viewRemote = view;
    for (UIView *view in self.subviews) {
        if ([view isKindOfClass:[AliRenderView class]]) {
            [view removeFromSuperview];
        }
    }
    [self addSubview:self.viewRemote];
    [self bringSubviewToFront:self.nameLabel]; 
}

- (void)setMuted:(BOOL)muted {
    if (muted) {
        _muteIcon.image = [NSBundle RILC_pngImageWithName:@"mute_red"];
    } else {
        _muteIcon.image = [NSBundle RILC_pngImageWithName:@"unmute"];
    }
}

- (void)setUserModel:(RTCRemoteUserModel *)userModel {
    _userModel = userModel;
    if (_userModel) {
        //1.设置renderView
        [self updateUserRenderview:userModel.view];
        //2.mic muted
        [self setMuted:userModel.audioMuted];
        //3.displayName
        self.nameLabel.text = userModel.displayName;
        //3.videoMute
        self.viewRemote.hidden = userModel.videoMuted;
    }
}
@end
