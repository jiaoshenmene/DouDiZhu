//
//  DecidePoker.h
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#ifndef __MyGame__DecidePoker__
#define __MyGame__DecidePoker__

#include "cocos2d.h"
USING_NS_CC;


class DecidePoker:public CCObject {
public:
    bool  decidePersonMoreBigSHowPoker(CCArray * keysOfNextShowArr, CCArray * keysOfNowShowArr);
    //此函数用来非第二圈判断玩家是否可以打住桌面上的牌
    
    bool decideWhetherHaveSuitablePokers(
                                         CCArray * nowScreenShowPokerArr,
                                         CCArray * keysOfnowScreenShowPokerArr ,
                                         CCArray * nextTimeShouldShowPokerArr,
                                         CCArray * keysOfnextTimeShouldShowPokerArr,
                                         CCArray * requireConsiderWhetherOutOfArr,
                                         CCArray *keysOfrequireConsiderWhetherOutOfArr,
                                         int miPokerID);
    //判断有没有可以压住当前桌面上的牌
    void saveEligibilityPokersAndRelevantKeys(int location,
                                              int length,
                                              CCArray * nextTimeShouldShowPokerArr,
                                              CCArray * keysOfnextTimeShouldShowPokerArr,
                                              CCArray * requireConsiderWhetherOutOfArr,
                                              CCArray * keysOfrequireConsiderWhetherOutOfArr);
    //如果存在 记录能压住当前桌面上的牌
    
    bool singleStraight(int length,
                        CCArray * keysOfnowScreenShowPokerArr,
                        CCArray * nextTimeShouldShowPokerArr,
                        CCArray * keysOfnextTimeShouldShowPokerArr,
                        CCArray * requireConsiderWhetherOutOfArr,
                        CCArray * keysOfrequireConsiderWhetherOutOfArr,
                        int miPokerID);
    //判断是否能压住顺子
    bool doubleStraight(int length,
                        CCArray * keysOfnowScreenShowPokerArr,
                        CCArray * nextTimeShouldShowPokerArr,
                        CCArray * keysOfnextTimeShouldShowPokerArr,
                        CCArray * requireConsiderWhetherOutOfArr,
                        CCArray * keysOfrequireConsiderWhetherOutOfArr,
                        int miPokerID);
    //判断是否能压住拖拉机
    bool threeStraight(int length,
                       CCArray * keysOfnowScreenShowPokerArr,
                       CCArray * nextTimeShouldShowPokerArr,
                       CCArray * keysOfnextTimeShouldShowPokerArr,
                       CCArray * requireConsiderWhetherOutOfArr,
                       CCArray * keysOfrequireConsiderWhetherOutOfArr,
                       int miPokerID);
    //判断是否压得住三飞不带翅膀
    bool planeWithSingleWing(int length,
                             CCArray * keysOfnowScreenShowPokerArr,
                             CCArray * nextTimeShouldShowPokerArr,
                             CCArray * keysOfnextTimeShouldShowPokerArr,
                             CCArray * requireConsiderWhetherOutOfArr,
                             CCArray * keysOfrequireConsiderWhetherOutOfArr,
                             int miPokerID);
    //判断是否压得住三带一
    bool planeWithDoubleWings(int length,
                              CCArray * keysOfnowScreenShowPokerArr,
                              CCArray * nextTimeShouldShowPokerArr,
                              CCArray * keysOfnextTimeShouldShowPokerArr,
                              CCArray * requireConsiderWhetherOutOfArr,
                              CCArray * keysOfrequireConsiderWhetherOutOfArr,
                              int miPokerID);
    
    //判断是否压得住三带一对

public:
    void sortedForArray(CCArray * valueArr,CCArray * keyArr);
    static DecidePoker * sharedDecidePoker();
};
#endif /* defined(__MyGame__DecidePoker__) */
