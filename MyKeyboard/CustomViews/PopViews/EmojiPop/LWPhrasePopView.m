//
//  LWPhrasePopView.m
//  MyInputMethod
//
//  Created by luowei on 16/2/18.
//  Copyright © 2016年 luowei. All rights reserved.
//

#import "LWPhrasePopView.h"
#import "LWDefines.h"
#import "LWBottomNavBar.h"
#import "Categories.h"
#import "MyKeyboardViewController.h"
#import "LWDataConfig.h"
#import "LWBottomSeparatorLayer.h"

@implementation LWPhrasePopView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        self.backgroundColor = [LWDataConfig getPopViewBackGroundColor];


        self.phrasesDict = [LWDataConfig getPhraseDictionary];
        NSArray *bottomNavItems = [LWDataConfig getArrByKey:Key_BottomNavPhraseItems withDefaultArr:_phrasesDict.allKeys];
        self.bottomNavBar = [[LWBottomNavBar alloc]initWithFrame:CGRectMake(0, (CGFloat) (frame.size.height-Toolbar_H),frame.size.width,Toolbar_H)
                                                     andNavItems:bottomNavItems andShowAdd:YES];
        self.bottomNavBar.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        [self addSubview:self.bottomNavBar];

        __weak typeof(self) weakSelf = self;
        self.bottomNavBar.bottomNavScrollview.updateTableDatasouce=^(){
            [weakSelf.tableView reloadData];
        };


        self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0,0,frame.size.width,frame.size.height-Toolbar_H)
                                                        style:UITableViewStylePlain];
        self.tableView.dataSource = self;
        self.tableView.delegate = self;
    
        self.tableView.tableFooterView = [[UIView alloc] init];
        self.tableView.separatorColor = UIColorValueFromThemeKey(@"btn.borderColor");
        self.tableView.layoutMargins = UIEdgeInsetsZero;
        self.tableView.backgroundColor = [UIColor clearColor];
        self.tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [self addSubview:self.tableView];

        self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    }

    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    _bottomNavBar.frame = CGRectMake(0, (CGFloat) (self.frame.size.height-Toolbar_H),self.frame.size.width,Toolbar_H);

    //刷新,更新分隔线
    [self.tableView reloadData];
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSUInteger idx = (NSUInteger) (_bottomNavBar.bottomNavScrollview->currentBtn.tag - Tag_First_NavItem);
    
    NSString *key = _phrasesDict.allKeys[idx];
    return ((NSDictionary *)_phrasesDict[key]).count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    static NSString *ID = @"cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ID];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:ID];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    CGSize tableViewSize = tableView.frame.size;
    UILabel *textLabel = (UILabel *) [cell.contentView viewWithTag:10];
    if (!textLabel) {
        textLabel = [[UILabel alloc] init];
        textLabel.tag = 10;
        [cell.contentView addSubview:textLabel];
    }


    textLabel.font = [UIFont fontWithName:StringValueFromThemeKey(@"font.name") size:FloatValueFromThemeKey(@"btn.mainLabel.fontSize")];
    textLabel.textColor = UIColorValueFromThemeKey(@"font.color");

    NSUInteger idx = (NSUInteger) (_bottomNavBar.bottomNavScrollview->currentBtn.tag - Tag_First_NavItem);
    NSString *key = _phrasesDict.allKeys[idx];
    NSString *value = _phrasesDict[key][(NSUInteger) indexPath.item];
    textLabel.text = value;

    [textLabel sizeToFit];
    CGFloat textWidth = textLabel.frame.size.width;
    if (textWidth >= (tableViewSize.width - 12)) {
        textLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        textWidth = tableViewSize.width - 12;
    }
    textLabel.frame = CGRectMake(6, 0, textWidth, Cell_Height);

    //添加分隔线
    CALayer *line = nil;
    for(CALayer *layer1 in cell.contentView.layer.sublayers){
        if([line isKindOfClass:[LWBottomSeparatorLayer class]]){
            line = layer1;
            line.frame = CGRectMake(6,Cell_Height-NarrowLine_W,tableViewSize.width-12,NarrowLine_W);
        }
    }
    if(!line){
        LWBottomSeparatorLayer *bottomLine = [LWBottomSeparatorLayer layer];
        bottomLine.backgroundColor = CGColorValueFromThemeKey(@"btn.borderColor");
        bottomLine.frame = CGRectMake(6,Cell_Height-NarrowLine_W,tableViewSize.width-12,NarrowLine_W);
        [cell.contentView.layer addSublayer:bottomLine];
    }

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {

    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    NSString *text = nil;
    UILabel *textLabel = (UILabel *) [cell.contentView viewWithTag:10];
    if (textLabel) {
        text = textLabel.text;
    }

    MyKeyboardViewController *kbVC = [self responderKBViewController];
    if(kbVC){
        [kbVC insertText:text];
    }

    [tableView deselectRowAtIndexPath:indexPath animated:NO];

}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return Cell_Height;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    cell.backgroundColor = [UIColor clearColor];
}

- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    UILabel *textLabel = (UILabel *)[cell viewWithTag:10];
    if (textLabel) {
        textLabel.textColor = UIColorValueFromThemeKey(@"font.highlightColor");
    }
    cell.contentView.backgroundColor = [UIColor clearColor];
}


- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    UILabel *textLabel = (UILabel *)[cell viewWithTag:10];
    if (textLabel) {
        textLabel.textColor = UIColorValueFromThemeKey(@"font.color");
    }
    cell.contentView.backgroundColor = [UIColor clearColor];
}

@end
