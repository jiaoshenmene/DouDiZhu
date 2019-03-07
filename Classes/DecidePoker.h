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


class DecidePoker:public Node {
public:
    bool  decidePersonMoreBigSHowPoker(std::vector<std::string> keysOfNextShowArr, std::vector<std::string> keysOfNowShowArr);
    //此函数用来非第二圈判断玩家是否可以打住桌面上的牌
    
    bool decideWhetherHaveSuitablePokers(
                                         std::vector<Sprite *> nowScreenShowPokerArr,
                                         std::vector<std::string> keysOfnowScreenShowPokerArr ,
                                         std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                         std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                         std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                         std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                                         int miPokerID);
    //判断有没有可以压住当前桌面上的牌
    void saveEligibilityPokersAndRelevantKeys(int location,
                                              int length,
                                              std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                              std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                              std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                              std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr);
    //如果存在 记录能压住当前桌面上的牌
    
    bool singleStraight(int length,
                        std::vector<std::string> keysOfnowScreenShowPokerArr,
                        std::vector<Sprite *> nextTimeShouldShowPokerArr,
                        std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                        std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                        std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                        int miPokerID);
    //判断是否能压住顺子
    bool doubleStraight(int length,
                        std::vector<std::string> keysOfnowScreenShowPokerArr,
                        std::vector<Sprite *> nextTimeShouldShowPokerArr,
                        std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                        std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                        std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                        int miPokerID);
    //判断是否能压住拖拉机
    bool threeStraight(int length,
                       std::vector<std::string> keysOfnowScreenShowPokerArr,
                       std::vector<Sprite *> nextTimeShouldShowPokerArr,
                       std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                       std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                       std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                       int miPokerID);
    //判断是否压得住三飞不带翅膀
    bool planeWithSingleWing(int length,
                             std::vector<std::string> keysOfnowScreenShowPokerArr,
                             std::vector<Sprite *> nextTimeShouldShowPokerArr,
                             std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                             std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                             std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                             int miPokerID);
    //判断是否压得住三带一
    bool planeWithDoubleWings(int length,
                              std::vector<std::string> keysOfnowScreenShowPokerArr,
                              std::vector<Sprite *> nextTimeShouldShowPokerArr,
                              std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                              std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                              std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                              int miPokerID);
    
    //判断是否压得住三带一对

public:
    static DecidePoker * sharedDecidePoker();
};
#endif /* defined(__MyGame__DecidePoker__) */
