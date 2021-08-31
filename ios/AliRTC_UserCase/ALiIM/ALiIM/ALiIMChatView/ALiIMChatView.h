//
//  ALiIMChatView.h
//  RTCWatchTogether
//
//  Created by RTCTeam on 2021/6/25.
//

#import <UIKit/UIKit.h>
#import "ALiIMChatToolBar.h"
NS_ASSUME_NONNULL_BEGIN


@protocol ALiIMChatViewDelegate <NSObject>

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;


- (void)testSendMsg:(NSString *)msg;


@end



@interface ALiIMChatView : UIView


@property (nonatomic, weak, nullable) id <ALiIMChatViewDelegate> delegate;

- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier;

- (void)chatViewCustomInputToolbar:(UIView *)input;

- (BOOL)isBottom;

- (void)scrollToBottomAnimated:(BOOL)animated;

- (void)reloadData;


@end

NS_ASSUME_NONNULL_END
