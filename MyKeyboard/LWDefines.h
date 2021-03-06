//
//  Defines.h
//  MyInputMethod
//
//  Created by luowei on 15/7/1.
//  Copyright (c) 2015 luowei. All rights reserved.
//

#ifndef MyInputMethod_Defines____FILEEXTENSION___
#define MyInputMethod_Defines____FILEEXTENSION___

// -------- 常用宏定义

#ifdef DEBUG
#define Log(format, ...) NSLog(format, ## __VA_ARGS__)
#else
#define Log(format, ...)
#endif


//Localizable Define
#define NSLocalizedString(key, comment) \
        [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
        [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
        [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
        [bundle localizedStringForKey:(key) value:(val) table:(tbl)]


// ----------  类型定义
//键盘类型
typedef NS_OPTIONS(NSUInteger, KeyboardType) {
    //常规键盘
    Keyboard_PingYingFull = 1,              //拼音全键
    keyboard_WuBiFull = 1 << 1,             //全键盘五笔
    Keyboard_ENFull = 1 << 2,               //英文全键
    Keyboard_NumNine = 1 << 3,           //数字九键
    Keyboard_PingYingNine = 1 << 4,     //拼音九键
    keyboard_BiHuaNine = 1 << 5,        //笔画九键
    Keyboard_SymbolCollection = 1 << 6,   //符号方键
    Keyboard_SymbolFull = 1 << 7,        //符号全键

    //特定键盘

};

typedef NS_OPTIONS(NSUInteger, BtnType) {
    ToolbarBtn_UnKnown = 0,           //未知类型
    ToolbarBtn_Logo = 1,              //工具栏logo设置按键
    ToolbarBtn_Emoji = 1 << 2,        //工具栏Emoji按键
    ToolbarBtn_SwitchKB = 1 << 3,        //工具栏选择键盘按键
    ToolbarBtn_Skin = 1 << 4,            //工具栏皮肤设置
    ToolbarBtn_OftenWords = 1 << 5,   //常用语弹窗
    KBBtn_Next = 1 << 6,         //地球键切换键盘弹窗
    KBBtn_FullChar = 1 << 7,     //全键盘字符按键弹窗

    ToolbarBtn_Phrase = 1 << 8,   //工具栏phrase键
    ToolbarBtn_Emoticon = 1 << 9,   //工具栏emoticon键
    ToolbarBtn_Graphic = 1 << 10,   //工具栏graphic键

};

//单手模式类型
typedef NS_OPTIONS(NSUInteger, SingleHandMode) {
    SingleHand_LeftMode = 0,    //左手模式,SingleHandView靠右
    SingleHand_RightMode = 1,   //右手模式,SingleHandView靠左
};

//predictive(双行/单行)
typedef NS_OPTIONS(NSUInteger, PredictiveMode) {
    Predictive_DoubleLine = 0,   //双行模式
    Predictive_SingleLine = 1,    //单行模式
};

//换行键类型
typedef NS_ENUM(NSInteger, ReturnKeyType) {
    ReturnKeyDefault,
    ReturnKeyGo,
    ReturnKeyGoogle,
    ReturnKeyJoin,
    ReturnKeyNext,
    ReturnKeyRoute,
    ReturnKeySearch,
    ReturnKeySend,
    ReturnKeyYahoo,
    ReturnKeyDone,
    ReturnKeyEmergencyCall,
    ReturnKeyOk,
};

// --------- 相关key名

#define GroupId [NSBundle mainBundle].infoDictionary[@"GroupId"]


#define Key_KeyboardSoundSetting @"keyboardSoundSetting"
#define Key_FullAccessControl @"fullaccesscontrol"

#define Key_OftenuseWords @"keyboardOftenuseWords"

//是否中文字符
#define IS_CH_SYMBOL(chr) ((int)(chr)>127)

// ---------  相关参数设置

#define WEAKSELF typeof(self) __weak weakSelf = self;

//屏幕宽度,高度
#define Screen_W ((CGFloat)([UIScreen mainScreen].bounds.size.width))
#define Screen_H ((CGFloat)([UIScreen mainScreen].bounds.size.height))
//竖屏时的屏幕宽度
#define Screen_Protrait_W (Screen_W > Screen_H ? Screen_H : Screen_W)

//InputView横屏、竖屏高度
#define Input_Landscape_H (Screen_Protrait_W == 320.0 ? 202 : 220.0)
#define Input_Protrait_H  (Screen_Protrait_W == 414.0 ? 266.0 : 256.0)
//InputView的高度
#define Input_H ((CGFloat)(Screen_W > Screen_H ? Input_Landscape_H : Input_Protrait_H))

//单手模式下的键盘宽度
#define SINGLEHAND_KEYBOARD_W 320.0


//topView的高度
#define TopView_H  ((CGFloat) ([LWKeyboardConfig predictiveMode] == Predictive_DoubleLine ? 60.0 : 40.0))
//键盘工具栏高度
#define Toolbar_H 40.0
#define Toolbar_Y ((CGFloat) ([LWKeyboardConfig predictiveMode] == Predictive_DoubleLine ? 20.0 : 0.0))


#import "LWThemeManager.h"
#import "UIColor+HexValue.h"

#define FloatValueFromThemeKey(key) (((NSNumber *)[LWThemeManager sharedInstance].theme[(key)]).floatValue)
#define StringValueFromThemeKey(key) ((NSString *)[LWThemeManager sharedInstance].theme[(key)])
#define UIColorValueFromThemeKey(key) ([UIColor colorWithRGBAString:((NSString *)[LWThemeManager sharedInstance].theme[(key)])])
#define CGColorValueFromThemeKey(key) ([UIColor colorWithRGBAString:((NSString *)[LWThemeManager sharedInstance].theme[(key)])].CGColor)

#define FloatValueToThemeFileByKey(fValue,key) ([[LWThemeManager sharedInstance] setThemeValue:(fValue) forKey:(key)])
#define StringValueToThemeFileByKey(strValue,key) ([[LWThemeManager sharedInstance] setThemeValue:(strValue) forKey:(key)])
#define UIColorValueToThemeFileByKey(uicolor,key) ([[LWThemeManager sharedInstance] setThemeValue:([UIColor rgbaStringFromUIColor:uicolor]) forKey:(key)])
#define CGColorValueToThemeFileByKey(cgcolor,key) ([[LWThemeManager sharedInstance] setThemeValue:([UIColor rgbaStringFromUIColor:[[UIColor alloc] initWithCGColor:cgcolor]]) forKey:(key)])

#import "UIKit/UIKit.h"
#define Scr_Scale [UIScreen mainScreen].scale
//窄边框线宽度
//#define NarrowLine_W 1/Scr_Scale
#define NarrowLine_W FloatValueFromThemeKey(@"btn.borderWidth")

//键盘left table 的 Cell 参数
#define Cell_Height 40.0
#define Cell_SeparatorInset UIEdgeInsetsMake(0, 5, 0, 5)

//默认的可选皮肤图片名数组
#define Default_Skins @[@"default",@"moonlight",@"sealight",@"waterglass"]
#define Default_Colors @[[UIColor lightGrayColor],[UIColor grayColor],[UIColor darkGrayColor],\
                        [UIColor whiteColor],[UIColor blackColor],[UIColor redColor],\
                        [UIColor greenColor],[UIColor blueColor],[UIColor cyanColor],\
                        [UIColor yellowColor],[UIColor magentaColor],[UIColor orangeColor],\
                        [UIColor purpleColor],[UIColor brownColor]]

//主题设置的键值
#define Key_Theme @"Key_Theme"

//用户皮肤的键值
#define Key_User_Skins @"Key_User_Skins"
#define Key_User_Colors @"Key_User_Colors"

#define Key_LastEmojiPop_Index @"Key_LastEmojiPop_Index"
#define Key_LastSkinPop_Index @"Key_LastSkinPop_Index"
#define Key_CurrentSymbol_Index @"Key_CurrentSymbol_Index"


//皮肤宫格重用id
#define SkinCell @"SkinCell"

//皮肤宫格padding
#define GridView_Padding 12.0

//皮肤宫格中cell的大小
#define Grid_Cell_W 60.0
#define Grid_Cell_H 80.0

//小x按钮的宽度与高度
#define Cell_DeleteBtn_W 30.0
#define Cell_DeleteBtn_H 30.0

//按键颜色
#define Key_Btn_NormalColor @"Key_Word_NormalColor"
#define Key_Btn_HighColor @"Key_Word_HighColor"

//按键透明度
#define Default_Btn_AlphaDic @{@"Alpha0":@0,@"Alpha1":@0.1,@"Alpha2":@0.4,@"Alpha3":@0.8,@"Alpha4":@1.0}
//按键圆角
#define Default_Btn_CornerRadiusDic @{@"CornerRadiuse0":@0,@"CornerRadiuse1":@5,@"CornerRadiuse2":@10,@"CornerRadiuse3":@16,@"CornerRadiuse4":@20}
//按键边框宽度
#define Default_Btn_BorderWidthDic @{@"BorderWidth0":@0,@"BorderWidth1":@(1/Scr_Scale),@"BorderWidth2":@1,@"BorderWidth3":@2}
//按键阴影宽度
#define Default_Btn_ShadowWidthDic @{@"ShadowWidth0":@0,@"ShadowWidth1":@1.0,@"ShadowWidth2":@2.0,@"ShadowWidth3":@3.0}


//字体名称(http://iosfonts.com/)
#define Default_FontNameDic @[@"Helvetica",@"Helvetica-Bold",@"HelveticaNeue-CondensedBold",@"Helvetica-Light",@"HelveticaNeue-Thin",@"MarkerFelt-Thin",@"Noteworthy-Light",\
    @"Menlo-Regular",@"SavoyeLetPlain",@"SnellRoundhand-Bold",@"Zapfino",@"Papyrus-Condensed"]


//样式宫格重用id
#define StyleCell @"StyleCell"

//第1个Bottom NavItem的Tag
#define Tag_First_NavItem 10000

//pageControll的高度
#define Emoji_Cell_W 40.0
#define Emoji_Cell_H 40.0

//表情键盘弹窗下的bottomNavItems key
#define Key_BottomNavPhraseItems @"Key_BottomNavPhraseItems"
#define Key_BottomNavEmojiItems @"Key_BottomNavEmojiItems"
#define Key_BottomNavEmoticonItems @"Key_BottomNavEmoticonItems"
#define Key_BottomNavGraphicItems @"Key_BottomNavGraphicItems"

//添加键盘皮肤url
#define Url_AddKBImageSkin @"MyInputMethod://addKBImageSkin"

#endif
