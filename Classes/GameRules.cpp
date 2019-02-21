//
//  GameRules.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//
#include "GameRules.h"
#include "TypeEnmu.h"

USING_NS_CC;

static GameRules * sh;
GameRules * GameRules::sharedGameRules()
{

    if (sh==NULL) {
        sh=new GameRules();
    }
    return sh;
}

int GameRules::decideSelectedPokerIfConformToRules(CCArray * selectValueArr,CCArray * selectKeysArr)//判断选中的牌是否符合规则
{

    CCLOG("selectArr count =%d,selectKeyArr count =%d",selectValueArr->count(),selectKeysArr->count());
    sortedForArray(selectValueArr, selectKeysArr);
    if (selectValueArr->count()==1) {
        return POKER_TYPE_SINGLE;
        //单牌可以出
    }
    
    if (selectValueArr->count()==2) {
        CCString *s0 = (CCString *)s0;
        CCString *s1 = (CCString *)s1;
        if (s0->isEqual(s1)) {
            return POKER_TYPE_DOUBLE;
            //对子可以出
        }
        CCString * strT=CCString::create("T");
        CCString * strN=CCString::create("N");
        
        if (s0->isEqual(strT)&&s1->isEqual(strN)) {
            return  POKER_MAX_BOOM;
            //王炸
        }
    }
    
    if (selectValueArr->count()==3) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        if (s0->isEqual(s1)&&s0->isEqual(s2)) {
            return POKER_TYPE_THREE;
            //三张
        }
    }
    
    if (selectValueArr->count()==4) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        
        if (s0->isEqual(s1)&&s0->isEqual(s2)) {
            return POKER_TYPE_FOUR;
            //前三张牌一样
        }
        if (s1->isEqual(s2)&&s1->isEqual(s3)) {
            return POKER_TYPE_FOUR;
            //后三张牌一样
        }
        
    }
    if (selectValueArr->count()==5) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        
        if (s0->isEqual(s1)&&s0->isEqual(s2)
            &&s3->isEqual(s4)) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //前三张牌一样后两张牌一样 3-2
        }
        if (s2->isEqual(s3)&&s2->isEqual(s4)
            &&s0->isEqual(s1)) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //后三张牌一样前两张牌一样2-3
        }
        
        if (s0->isEqual(s1)&&
            s0->isEqual(s2)&&
            s0->isEqual(s3)
            ) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        
        if (s1->isEqual(s2)&&
            s1->isEqual(s3)&&
            s1->isEqual(s4)) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==4){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    
    if (selectKeysArr->count()==6) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
       
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s4->isEqual(s5)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //前三张牌一样后三张牌一样（飞机不带翅膀）
        }
        
        for(int i=0;i<selectKeysArr->count()-3 ;i++){
            CCString *si = (CCString *)selectKeysArr->objectAtIndex(i);
            if (si->isEqual(selectKeysArr->objectAtIndex(i+1))
                &&si->isEqual(selectKeysArr->objectAtIndex(i+2))
                &&si->isEqual(selectKeysArr->objectAtIndex(i+3))) {

                return POKER_TYPE_SIX_FOUR_WITH_TWO;
                //前四张牌一样（四带二）
            }
        }
        
        if (s0->isEqual(s1)&&
            s2->isEqual(s3)
            &&s4->isEqual(s5)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s2)->getCString())==1
            &&((CCString *)(s2))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==5){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==7) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==6){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    if (selectKeysArr->count()==8) {
        
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        CCString *s7 = (CCString *)selectKeysArr->objectAtIndex(7);
        
        
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s3)->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_ONE;
            //前六张牌出现飞机（飞机带翅膀）
        }
        
        if (s1->isEqual(s2)
            &&s1->isEqual(s3)
            &&s4->isEqual(s5)
            &&s4->isEqual(s6)
            &&
            ((CCString *)(s1))
            ->compare(((CCString *)s4)->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_TWO;
            //中间六张牌出现飞机（飞机带翅膀）
        }
        
        if (s2->isEqual(s3)
            &&s2->isEqual(s4)
            &&s5->isEqual(s6)
            &&s5->isEqual(s7)
            &&
            ((CCString *)(s2))
            ->compare(((CCString *)s5)->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_THREE;
            //后六张牌出现飞机（飞机带翅膀）
        }
        
        if (s0->isEqual(s1)&&
            s2->isEqual(s3)
            &&s4->isEqual(s5)
            &&
            s6->isEqual(s7)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s2)->getCString())==1
            &&((CCString *)(s2))
            ->compare(((CCString *)s4)->getCString())==1
            &&((CCString *)(s4))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            !s6->isEqual(s7)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==7){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==9) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        CCString *s7 = (CCString *)selectKeysArr->objectAtIndex(7);
        CCString *s8 = (CCString *)selectKeysArr->objectAtIndex(8);
        
        
        
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&s6->isEqual(s7)
            &&s6->isEqual(s8)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s3)->getCString())==1
            &&
            ((CCString *)(s3))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //三飞不带翅膀
        }
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            !s6->isEqual(s7)&&
            !s7->isEqual(s8)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==8){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
        
    }
    if (selectKeysArr->count()==10) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        CCString *s7 = (CCString *)selectKeysArr->objectAtIndex(7);
        CCString *s8 = (CCString *)selectKeysArr->objectAtIndex(8);
        CCString *s9 = (CCString *)selectKeysArr->objectAtIndex(9);
        
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s3)->getCString())==1
            &&s6->isEqual(s7)
            &&s8->isEqual(s9)
            ) {
            return POKER_TYPE_TEN;
            //前六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s2->isEqual(s3)
            &&s2->isEqual(s4)
            &&s5->isEqual(s6)
            &&s5->isEqual(s7)
            &&
            ((CCString *)(s2))
            ->compare(((CCString *)s5)->getCString())==1
            &&s0->isEqual(s1)
            &&s8->isEqual(s9)
            ) {
            return POKER_TYPE_TEN;
            //中间六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s4->isEqual(s5)
            &&s4->isEqual(s6)
            &&s7->isEqual(s8)
            &&s7->isEqual(s9)
            &&
            ((CCString *)(s4))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            &&s0->isEqual(s1)
            &&s2->isEqual(s3)
            ) {
            return POKER_TYPE_TEN;
            //后六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s0->isEqual(s1)&&
            s2->isEqual(s3)
            &&s4->isEqual(s5)
            &&
            s6->isEqual(s7)
            &&
            s8->isEqual(s9)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s2)->getCString())==1
            &&((CCString *)(s2))
            ->compare(((CCString *)s4)->getCString())==1
            &&((CCString *)(s4))
            ->compare(((CCString *)s6)->getCString())==1
            &&((CCString *)(s6))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            !s6->isEqual(s7)&&
            !s7->isEqual(s8)&&
            !s8->isEqual(s9)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==9){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==11) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        CCString *s7 = (CCString *)selectKeysArr->objectAtIndex(7);
        CCString *s8 = (CCString *)selectKeysArr->objectAtIndex(8);
        CCString *s9 = (CCString *)selectKeysArr->objectAtIndex(9);
        CCString *s10 = (CCString *)selectKeysArr->objectAtIndex(10);
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            !s6->isEqual(s7)&&
            !s7->isEqual(s8)&&
            !s8->isEqual(s9)&&
            !s9->isEqual(s10)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==10){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    
    if (selectKeysArr->count()==12) {
        CCString *s0 = (CCString *)selectKeysArr->objectAtIndex(0);
        CCString *s1 = (CCString *)selectKeysArr->objectAtIndex(1);
        CCString *s2 = (CCString *)selectKeysArr->objectAtIndex(2);
        CCString *s3 = (CCString *)selectKeysArr->objectAtIndex(3);
        CCString *s4 = (CCString *)selectKeysArr->objectAtIndex(4);
        CCString *s5 = (CCString *)selectKeysArr->objectAtIndex(5);
        CCString *s6 = (CCString *)selectKeysArr->objectAtIndex(6);
        CCString *s7 = (CCString *)selectKeysArr->objectAtIndex(7);
        CCString *s8 = (CCString *)selectKeysArr->objectAtIndex(8);
        CCString *s9 = (CCString *)selectKeysArr->objectAtIndex(9);
        CCString *s10 = (CCString *)selectKeysArr->objectAtIndex(10);
        CCString *s11 = (CCString *)selectKeysArr->objectAtIndex(11);
        
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&s6->isEqual(s7)
            &&s6->isEqual(s8)
            &&s9->isEqual(s10)
            &&s9->isEqual(s11)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s3)->getCString())==1
            &&
            ((CCString *)(s3))
            ->compare(((CCString *)s6)->getCString())==1
            &&
            ((CCString *)(s6))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //四飞不带翅膀
        }
        if (s0->isEqual(s1)
            &&s0->isEqual(s2)
            &&s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&s6->isEqual(s7)
            &&s6->isEqual(s8)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s3)->getCString())==1
            &&
            ((CCString *)(s3))
            ->compare(((CCString *)s6)->getCString())==1
            ) {
            return 122;
            //前面出现三飞带单翅膀
        }
        if (s1->isEqual(s2)
            &&s1->isEqual(s3)
            &&s4->isEqual(s5)
            &&s4->isEqual(s6)
            &&s7->isEqual(s8)
            &&s7->isEqual(s9)
            &&
            ((CCString *)(s1))
            ->compare(((CCString *)s4)->getCString())==1
            &&
            ((CCString *)(s4))
            ->compare(((CCString *)s7)->getCString())==1
            ) {
            return 123;
            //中间出现三飞带单翅膀
        }
        
        if (s2->isEqual(s3)
            &&s2->isEqual(s4)
            &&s5->isEqual(s6)
            &&s5->isEqual(s7)
            &&s8->isEqual(s9)
            &&s8->isEqual(s10)
            &&
            ((CCString *)(s2))
            ->compare(((CCString *)s5)->getCString())==1
            &&
            ((CCString *)(s5))
            ->compare(((CCString *)s8)->getCString())==1
            ) {
            return 124;
            //中间出现三飞带单翅膀
        }
        
        if (s3->isEqual(s4)
            &&s3->isEqual(s5)
            &&s6->isEqual(s7)
            &&s6->isEqual(s8)
            &&s9->isEqual(s10)
            &&s9->isEqual(s11)
            &&
            ((CCString *)(s3))
            ->compare(((CCString *)s6)->getCString())==1
            &&
            ((CCString *)(s6))
            ->compare(((CCString *)s9)->getCString())==1
            ) {
            return 125;
            //后面出现三飞带单翅膀
        }
        
        
        
        if (s0->isEqual(s1)&&
            s2->isEqual(s3)
            &&s4->isEqual(s5)
            &&
            s6->isEqual(s7)
            &&
            s8->isEqual(s9)
            &&
            s10->isEqual(s11)
            &&
            ((CCString *)(s0))
            ->compare(((CCString *)s2)->getCString())==1
            &&((CCString *)(s2))
            ->compare(((CCString *)s4)->getCString())==1
            &&((CCString *)(s4))
            ->compare(((CCString *)s6)->getCString())==1
            &&((CCString *)(s6))
            ->compare(((CCString *)s8)->getCString())==1
            &&((CCString *)(s8))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        
        if (!s0->isEqual(s1)&&
            !s1->isEqual(s2)&&
            !s2->isEqual(s3)&&
            !s3->isEqual(s4)&&
            !s4->isEqual(s5)&&
            !s5->isEqual(s6)&&
            !s6->isEqual(s7)&&
            !s7->isEqual(s8)&&
            !s8->isEqual(s9)&&
            !s9->isEqual(s10)&&
            !s10->isEqual(s11)&&
            ((CCString *)(s0))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==11){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    return 0;

}

void GameRules::sortedForArray(CCArray * valueArr,CCArray * keyArr)
{
    for (int i=0; i<keyArr->count()-1; i++){
        for (int j=keyArr->count()-1; j>i; j--) {
            CCString * key=(CCString *)keyArr->objectAtIndex(j);
            CCString * upkey=(CCString *)keyArr->objectAtIndex(j-1);
            if (key->compare(upkey->getCString())>0) {
                keyArr->exchangeObjectAtIndex(j, j-1);
                valueArr->exchangeObjectAtIndex(j, j-1);
            }
        }
        
    }
}
