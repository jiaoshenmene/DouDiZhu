//
//  PublicItem.cpp
//  DouDiZhu-mobile
//
//  Created by 杜甲 on 2019/2/22.
//

#include "PublicItem.h"
USING_NS_CC;



Sprite* PublicItem::backgroundSprite() {
    Size size = Director::getInstance()->getWinSize();
    
    Sprite* pSprite = Sprite::create("bk.png");
    float winw = size.width;
    float winh = size.height;
    float spx = pSprite->getTextureRect().getMaxX();
    float spy = pSprite->getTextureRect().getMaxY();
    pSprite->setScale(winw / spx, winh / spy);
    pSprite->setPosition( Vec2(size.width/2, size.height/2) );
    
    return pSprite;
}

