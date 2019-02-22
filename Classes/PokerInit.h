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
//    Map<std::string, Vector<Sprite *>> rootDic;
//    //用来存放大小相等的牌
//    Vector<Sprite *> arrA;
//    Vector<Sprite *> arrB;
//    Vector<Sprite *> arrC;
//    Vector<Sprite *> arrD;
//    Vector<Sprite *> arrE;
//    Vector<Sprite *> arrF;
//    Vector<Sprite *> arrG;
//    Vector<Sprite *> arrH;
//    Vector<Sprite *> arrI;
//    Vector<Sprite *> arrJ;
//    Vector<Sprite *> arrK;
//    Vector<Sprite *> arrL;
//    Vector<Sprite *> arrM;
//    Vector<Sprite *> arrN;
//    Vector<Sprite *> arrT;
//    
//    Map<std::string, Vector<Sprite *> > initArraysAndRootDic();//初始化
    
public:
    static PokerInit * sharedPokerInit();
    ~PokerInit();
};
#endif /* defined(__MyGame__PokerInit__) */
