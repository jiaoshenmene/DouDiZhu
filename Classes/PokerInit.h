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
class PokerInit:public CCObject {
public:
    //用来存放所有的牌
    CCDictionary * rootDic;
    //用来存放大小相等的牌
    CCArray * arrA;
    CCArray * arrB;
    CCArray * arrC;
    CCArray * arrD;
    CCArray * arrE;
    CCArray * arrF;
    CCArray * arrG;
    CCArray * arrH;
    CCArray * arrI;
    CCArray * arrJ;
    CCArray * arrK;
    CCArray * arrL;
    CCArray * arrM;
    CCArray * arrN;
    CCArray * arrT;
    
    CCDictionary * initArraysAndRootDic();//初始化
    
public:
    static PokerInit * sharedPokerInit();
    ~PokerInit();
};
#endif /* defined(__MyGame__PokerInit__) */
