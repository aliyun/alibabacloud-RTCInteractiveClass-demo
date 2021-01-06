//
//  AlertMsgController.m
//  LectureHall
//
//  Created by Aliyun on 2020/5/27.
//  Copyright © 2020 alibaba. All rights reserved.
//

#import "AlertMsgController.h"

@interface AlertMsgController ()

@end

@implementation AlertMsgController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (IBAction)onCancel:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)onSubmit:(id)sender {
    [self onCancel:nil];
    if(self.submitblock){
        self.submitblock();
    }
}

@end
