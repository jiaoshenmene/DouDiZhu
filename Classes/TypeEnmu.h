//
//  Type Enmu.h
//  MyGame
//
//  Created by user on 14-4-14.
//
//

#ifndef MyGame_Type_Enmu_h
#define MyGame_Type_Enmu_h

#define TAG 100
#define SELECTED_TAG 200
#define POKER_WIDTH 300

#define PERSON_INTERVAL_TIME_TO_NEXT_COMPUTER 1
#define NEXT_INTERVAL_TIME_TO_UP_COMPUTER 1

#define POKERS_COUNT                        54//牌的数目


#pragma mark--------poker type----
#define POKER_TYPE_SINGLE 1                  //单牌
#define POKER_TYPE_DOUBLE 2                  //对子
#define POKER_TYPE_THREE  3                  //三张

#define POKER_TYPE_FOUR 31                   //三带一

#define POKER_TYPE_FIVE_THREE_WITH_TWO 32    //三带二
#define POKER_TYPE_FIVE_FOUR_WITH_ONE  41    //四带一

#define POKER_TYPE_SIX_FOUR_WITH_TWO   42    //四带二

#define POKER_TYPE_EIGHT_ONE 3311            //双飞带单
#define POKER_TYPE_EIGHT_TWO 1331
#define POKER_TYPE_EIGHT_THREE 1133

#define POKER_TYPE_TEN  3322                 //双飞带对子

#define POKER_TYPE_STRAIGHT 12345            //顺子
#define POKER_TYPE_DOUBLE_STRAIGHT 112233    //拖拉机
#define POKER_TYPE_THREE_STRAIGHT  111222    //三飞不带
#define POKER_COMMON_BOOM  4000              //一般炸弹
#define POKER_MAX_BOOM  2000                 //王炸


#define EVERY_PLAYER_COINS_NUMBER    300     //默认玩家和电脑开始时拥有300金币
#define EVERY_ROUND_PLAYER_COST_MINI_COINS  5//默认不加倍的情况 每局最少消耗五个金币

#define GAME_MUSIC_OPEN                     1//游戏背景音乐、音效打开
#define GAME_MUSIC_CLOSE                    0//游戏背景音乐，音效关闭

#define START_GAME_LABEL_SIZE               15//游戏界面字体大小
#define PERSON_WIN_THE_GAME                 1//玩家赢了
#define PERSON_LOST_THE_GAME                -1//玩家输了

#define OUT_OF_SCREEN_POINT_Y               2000
#endif
