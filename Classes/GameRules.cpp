//
//  GameRules.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#include "MyGameHeader.h"
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
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))) {
            return POKER_TYPE_DOUBLE;
            //对子可以出
        }
        CCString * strT=CCString::create("T");
        CCString * strN=CCString::create("N");
        if (selectKeysArr->objectAtIndex(0)->isEqual(strT)&&selectKeysArr->objectAtIndex(1)->isEqual(strN)) {
            return  POKER_MAX_BOOM;
            //王炸
        }
    }
    
    if (selectValueArr->count()==3) {
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))) {
            return POKER_TYPE_THREE;
            //三张
        }
    }
    
    if (selectValueArr->count()==4) {
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))) {
            return POKER_TYPE_FOUR;
            //前三张牌一样
        }
        if (selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(3))) {
            return POKER_TYPE_FOUR;
            //后三张牌一样
        }
        
    }
    if (selectValueArr->count()==5) {
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(selectKeysArr->count()-2)->isEqual(selectKeysArr->objectAtIndex(selectKeysArr->count()-1))) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //前三张牌一样后两张牌一样 3-2
        }
        if (selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //后三张牌一样前两张牌一样2-3
        }
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))&&
            selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(3))
            ) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        
        if (selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(3))&&
            selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(4))) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==4){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    
    if (selectKeysArr->count()==6) {
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(selectKeysArr->count()-3)->isEqual(selectKeysArr->objectAtIndex(selectKeysArr->count()-2))
            &&selectKeysArr->objectAtIndex(selectKeysArr->count()-2)->isEqual(selectKeysArr->objectAtIndex(selectKeysArr->count()-1))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //前三张牌一样后三张牌一样（飞机不带翅膀）
        }
        for(int i=0;i<selectKeysArr->count()-3 ;i++){
        if (selectKeysArr->objectAtIndex(i)->isEqual(selectKeysArr->objectAtIndex(i+1))
            &&selectKeysArr->objectAtIndex(i)->isEqual(selectKeysArr->objectAtIndex(i+2))
            &&selectKeysArr->objectAtIndex(i)->isEqual(selectKeysArr->objectAtIndex(i+3))) {

            return POKER_TYPE_SIX_FOUR_WITH_TWO;
            //前四张牌一样（四带二）
        }
        }
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(2))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==5){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==7) {
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==6){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    if (selectKeysArr->count()==8) {
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(3))->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_ONE;
            //前六张牌出现飞机（飞机带翅膀）
        }
        
        if (selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(6))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(1)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(4))->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_TWO;
            //中间六张牌出现飞机（飞机带翅膀）
        }
        
        if (selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(7))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(5))->getCString())==1
            ) {
            return POKER_TYPE_EIGHT_THREE;
            //后六张牌出现飞机（飞机带翅膀）
        }
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(2))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(4))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(4)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            !selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==7){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==9) {
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(8))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(3))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(3)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //三飞不带翅膀
        }
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            !selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))&&
            !selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==8){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
        
    }
    if (selectKeysArr->count()==10) {
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(3))->getCString())==1
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))
            ) {
            return POKER_TYPE_TEN;
            //前六张出现飞机（飞机带双翅膀）
        }
        
        
        if (selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(7))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(5))->getCString())==1
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))
            ) {
            return POKER_TYPE_TEN;
            //中间六张出现飞机（飞机带双翅膀）
        }
        
        
        if (selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(6))
            &&selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))
            &&selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(9))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(4)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            ) {
            return POKER_TYPE_TEN;
            //后六张出现飞机（飞机带双翅膀）
        }
        
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&
            selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(2))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(4))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(4)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(6))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(6)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            !selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))&&
            !selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))&&
            !selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==9){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr->count()==11) {
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            !selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))&&
            !selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))&&
            !selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))&&
            !selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(10))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==10){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    
    if (selectKeysArr->count()==12) {
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(8))
            &&selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(10))
            &&selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(11))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(3))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(3)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(6))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(6)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //四飞不带翅膀
        }
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))
            &&selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(8))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(3))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(3)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(6))->getCString())==1
            ) {
            return 122;
            //前面出现三飞带单翅膀
        }
        if (selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))
            &&selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(6))
            &&selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))
            &&selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(9))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(1)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(4))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(4)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(7))->getCString())==1
            ) {
            return 123;
            //中间出现三飞带单翅膀
        }
        
        if (selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))
            &&selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))
            &&selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(10))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(5))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(5)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(8))->getCString())==1
            ) {
            return 124;
            //中间出现三飞带单翅膀
        }
        
        if (selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))
            &&selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(5))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(8))
            &&selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(10))
            &&selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(11))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(3)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(6))->getCString())==1
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(6)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(9))->getCString())==1
            ) {
            return 125;
            //后面出现三飞带单翅膀
        }
        
        
        
        if (selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))
            &&selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))
            &&
            selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))
            &&
            selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))
            &&
            selectKeysArr->objectAtIndex(10)->isEqual(selectKeysArr->objectAtIndex(11))
            &&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(2))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(2)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(4))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(4)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(6))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(6)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(8))->getCString())==1
            &&((CCString *)(selectKeysArr->objectAtIndex(8)))
            ->compare(((CCString *)selectKeysArr->objectAtIndex(selectKeysArr->count()-1))->getCString())==1) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        
        if (!selectKeysArr->objectAtIndex(0)->isEqual(selectKeysArr->objectAtIndex(1))&&
            !selectKeysArr->objectAtIndex(1)->isEqual(selectKeysArr->objectAtIndex(2))&&
            !selectKeysArr->objectAtIndex(2)->isEqual(selectKeysArr->objectAtIndex(3))&&
            !selectKeysArr->objectAtIndex(3)->isEqual(selectKeysArr->objectAtIndex(4))&&
            !selectKeysArr->objectAtIndex(4)->isEqual(selectKeysArr->objectAtIndex(5))&&
            !selectKeysArr->objectAtIndex(5)->isEqual(selectKeysArr->objectAtIndex(6))&&
            !selectKeysArr->objectAtIndex(6)->isEqual(selectKeysArr->objectAtIndex(7))&&
            !selectKeysArr->objectAtIndex(7)->isEqual(selectKeysArr->objectAtIndex(8))&&
            !selectKeysArr->objectAtIndex(8)->isEqual(selectKeysArr->objectAtIndex(9))&&
            !selectKeysArr->objectAtIndex(9)->isEqual(selectKeysArr->objectAtIndex(10))&&
            !selectKeysArr->objectAtIndex(10)->isEqual(selectKeysArr->objectAtIndex(11))&&
            ((CCString *)(selectKeysArr->objectAtIndex(0)))
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
