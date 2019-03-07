//
//  GameRules.h
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#ifndef __MyGame__GameRules__
#define __MyGame__GameRules__

#include "cocos2d.h"
USING_NS_CC;

class GameRules:public Node
{
public:
    int decideSelectedPokerIfConformToRules(std::vector<Sprite *> selectValueArr,std::vector<std::string> selectKeysArr);//判断选中的牌是否符合规则
public:
    static  GameRules * sharedGameRules();

};
#endif /* defined(__MyGame__GameRules__) */
