//
//  PokerInit.h
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#ifndef __MyGame__PokerInit__
#define __MyGame__PokerInit__

#include "cocos2d.h"
USING_NS_CC;
class PokerInit:public Node {
public:
    //用来存放所有的牌
    std::map<std::string, std::vector<Sprite *>> rootDic;
    //用来存放大小相等的牌
    std::vector<Sprite *> arrA;
    std::vector<Sprite *> arrB;
    std::vector<Sprite *> arrC;
    std::vector<Sprite *> arrD;
    std::vector<Sprite *> arrE;
    std::vector<Sprite *> arrF;
    std::vector<Sprite *> arrG;
    std::vector<Sprite *> arrH;
    std::vector<Sprite *> arrI;
    std::vector<Sprite *> arrJ;
    std::vector<Sprite *> arrK;
    std::vector<Sprite *> arrL;
    std::vector<Sprite *> arrM;
    std::vector<Sprite *> arrN;
    std::vector<Sprite *> arrT;
//
    std::map<std::string, std::vector<Sprite *>> initArraysAndRootDic();//初始化
    
public:
    static PokerInit * sharedPokerInit();
    ~PokerInit();
};
#endif /* defined(__MyGame__PokerInit__) */
