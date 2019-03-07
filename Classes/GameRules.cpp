//
//  GameRules.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//
#include "GameRules.h"
#include "TypeEnmu.h"
#include "Tools.h"

USING_NS_CC;

static GameRules * sh;
GameRules * GameRules::sharedGameRules()
{

    if (sh==NULL) {
        sh=new GameRules();
    }
    return sh;
}

int GameRules::decideSelectedPokerIfConformToRules(std::vector<Sprite *> selectValueArr,std::vector<std::string> selectKeysArr)//判断选中的牌是否符合规则
{

//    //CCLog("selectArr count =%d,selectKeyArr count =%d",selectValueArr.size(),selectKeysArr.size());
    Tools::sortedForArray(selectValueArr, selectKeysArr);
    if (selectValueArr.size()==1) {
        return POKER_TYPE_SINGLE;
        //单牌可以出
    }
    
    if (selectValueArr.size()==2) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        if (s0.compare(s1) == 0) {
            return POKER_TYPE_DOUBLE;
            //对子可以出
        }
        std::string strT="T";
        std::string strN="N";
        
        if (!s0.compare(strT) && !s1.compare(strN) ) {
            return  POKER_MAX_BOOM;
            //王炸
        }
    }
    
    if (selectValueArr.size()==3) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        if (!s0.compare(s1)&&!s0.compare(s2)) {
            return POKER_TYPE_THREE;
            //三张
        }
    }
    
    if (selectValueArr.size()==4) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        
        if (s0.compare(s1)&&s0.compare(s2)) {
            return POKER_TYPE_FOUR;
            //前三张牌一样
        }
        if (s1.compare(s2)&&s1.compare(s3)) {
            return POKER_TYPE_FOUR;
            //后三张牌一样
        }
        
    }
    if (selectValueArr.size()==5) {
        std::string s0 = (std::string )selectKeysArr.at(0);
        std::string s1 = (std::string )selectKeysArr.at(1);
        std::string s2 = (std::string )selectKeysArr.at(2);
        std::string s3 = (std::string )selectKeysArr.at(3);
        std::string s4 = (std::string )selectKeysArr.at(4);
        
        if (s0.compare(s1)&&s0.compare(s2)
            &&s3.compare(s4)) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //前三张牌一样后两张牌一样 3-2
        }
        if (s2.compare(s3)&&s2.compare(s4)
            &&s0.compare(s1)) {
            return POKER_TYPE_FIVE_THREE_WITH_TWO;
            //后三张牌一样前两张牌一样2-3
        }
        
        if (s0.compare(s1)&&
            s0.compare(s2)&&
            s0.compare(s3)
            ) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        
        if (s1.compare(s2)&&
            s1.compare(s3)&&
            s1.compare(s4)) {
            return POKER_TYPE_FIVE_FOUR_WITH_ONE;
            //四带一
        }
        
        s0.compare( (selectKeysArr.at(selectKeysArr.size() - 1) ) );
        if (s0.compare(s1)&&
            s1.compare(s2)&&
            s2.compare(s3)&&
            s3.compare(s4)
            &&s0.compare(selectKeysArr.at(selectKeysArr.size() - 1)) == 4
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    
    if (selectKeysArr.size()==6) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
       
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s4.compare(s5)
            &&s0.compare(selectKeysArr.at(selectKeysArr.size() - 1)) == 1
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //前三张牌一样后三张牌一样（飞机不带翅膀）
        }
        
        for(int i=0;i<selectKeysArr.size()-3 ;i++){
            std::string si = (std::string )selectKeysArr.at(i);
            if (si.compare(selectKeysArr.at(i+1))
                &&si.compare(selectKeysArr.at(i+2))
                &&si.compare(selectKeysArr.at(i+3))) {

                return POKER_TYPE_SIX_FOUR_WITH_TWO;
                //前四张牌一样（四带二）
            }
        }
        
        if (s0.compare(s1)&&
            s2.compare(s3)
            &&s4.compare(s5)
            &&s0.compare(s2)
            &&!s2.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ){
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)
            &&s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))== 5
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr.size()==7) {
        std::string s0 = (std::string )selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)
//            &&
//            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))
//            .compare((selectKeysArr.at(selectKeysArr.size()-1)))==6
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
    }
    if (selectKeysArr.size()==8) {
        
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        std::string s7 = selectKeysArr.at(7);
        
        
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s3.compare(s5)
            && s0.compare(s3)==1
            ) {
            return POKER_TYPE_EIGHT_ONE;
            //前六张牌出现飞机（飞机带翅膀）
        }
        
        if (s1.compare(s2)
            &&s1.compare(s3)
            &&s4.compare(s5)
            &&s4.compare(s6)
            &&s1.compare(s4)
            ) {
            return POKER_TYPE_EIGHT_TWO;
            //中间六张牌出现飞机（飞机带翅膀）
        }
        
        if (s2.compare(s3)
            &&s2.compare(s4)
            &&s5.compare(s6)
            &&s5.compare(s7)
            &&s2.compare(s5)
            ) {
            return POKER_TYPE_EIGHT_THREE;
            //后六张牌出现飞机（飞机带翅膀）
        }
        
        if (s0.compare(s1)&&
            s2.compare(s3)
            &&s4.compare(s5)
            &&
            s6.compare(s7)
            &&s0.compare(s2)
            &&s2.compare(s4)
            &&s4.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)&&
            !s6.compare(s7)&&
            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr.size()==9) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        std::string s7 = selectKeysArr.at(7);
        std::string s8 = selectKeysArr.at(8);
        
        
        
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s3.compare(s5)
            &&s6.compare(s7)
            &&s6.compare(s8)
            &&s0.compare(s3)
            &&s3.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //三飞不带翅膀
        }
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)&&
            !s6.compare(s7)&&
            !s7.compare(s8)&&
            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
        
    }
    if (selectKeysArr.size()==10) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        std::string s7 = selectKeysArr.at(7);
        std::string s8 = selectKeysArr.at(8);
        std::string s9 = selectKeysArr.at(9);
        
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s3.compare(s5)
            &&s0.compare(s3)
            &&s6.compare(s7)
            &&s8.compare(s9)
            ) {
            return POKER_TYPE_TEN;
            //前六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s2.compare(s3)
            &&s2.compare(s4)
            &&s5.compare(s6)
            &&s5.compare(s7)
            &&s2.compare(s5)
            &&s0.compare(s1)
            &&s8.compare(s9)
            ) {
            return POKER_TYPE_TEN;
            //中间六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s4.compare(s5)
            &&s4.compare(s6)
            &&s7.compare(s8)
            &&s7.compare(s9)
            &&s4.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            &&s0.compare(s1)
            &&s2.compare(s3)
            ) {
            return POKER_TYPE_TEN;
            //后六张出现飞机（飞机带双翅膀）
        }
        
        
        if (s0.compare(s1)&&
            s2.compare(s3)
            &&s4.compare(s5)
            &&
            s6.compare(s7)
            &&
            s8.compare(s9)
            &&s0.compare(s2)
            &&s2.compare(s4)
            &&s4.compare(s6)
            &&s6.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)&&
            !s6.compare(s7)&&
            !s7.compare(s8)&&
            !s8.compare(s9)&&
            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1)) ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    if (selectKeysArr.size()==11) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        std::string s7 = selectKeysArr.at(7);
        std::string s8 = selectKeysArr.at(8);
        std::string s9 = selectKeysArr.at(9);
        std::string s10 = selectKeysArr.at(10);
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)&&
            !s6.compare(s7)&&
            !s7.compare(s8)&&
            !s8.compare(s9)&&
            !s9.compare(s10)&&
            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    
    if (selectKeysArr.size()==12) {
        std::string s0 = selectKeysArr.at(0);
        std::string s1 = selectKeysArr.at(1);
        std::string s2 = selectKeysArr.at(2);
        std::string s3 = selectKeysArr.at(3);
        std::string s4 = selectKeysArr.at(4);
        std::string s5 = selectKeysArr.at(5);
        std::string s6 = selectKeysArr.at(6);
        std::string s7 = selectKeysArr.at(7);
        std::string s8 = selectKeysArr.at(8);
        std::string s9 = selectKeysArr.at(9);
        std::string s10 = selectKeysArr.at(10);
        std::string s11 = selectKeysArr.at(11);
        
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s3.compare(s5)
            &&s6.compare(s7)
            &&s6.compare(s8)
            &&s9.compare(s10)
            &&s9.compare(s11)
            &&s0.compare(s3)
            &&s3.compare(s6)
            &&s6.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ) {
            return POKER_TYPE_THREE_STRAIGHT;
            //四飞不带翅膀
        }
        if (s0.compare(s1)
            &&s0.compare(s2)
            &&s3.compare(s4)
            &&s3.compare(s5)
            &&s6.compare(s7)
            &&s6.compare(s8)
            &&s0.compare(s3)
            &&s3.compare(s6)
            ) {
            return 122;
            //前面出现三飞带单翅膀
        }
        if (s1.compare(s2)
            &&s1.compare(s3)
            &&s4.compare(s5)
            &&s4.compare(s6)
            &&s7.compare(s8)
            &&s7.compare(s9)
            &&s1.compare(s4)
            &&s4.compare(s7)
            ) {
            return 123;
            //中间出现三飞带单翅膀
        }
        
        if (s2.compare(s3)
            &&s2.compare(s4)
            &&s5.compare(s6)
            &&s5.compare(s7)
            &&s8.compare(s9)
            &&s8.compare(s10)
            &&s2.compare(s5)
            &&s5.compare(s8)
            ) {
            return 124;
            //中间出现三飞带单翅膀
        }
        
        if (s3.compare(s4)
            &&s3.compare(s5)
            &&s6.compare(s7)
            &&s6.compare(s8)
            &&s9.compare(s10)
            &&s9.compare(s11)
            &&s3.compare(s6)
            &&s6.compare(s9)
            ) {
            return 125;
            //后面出现三飞带单翅膀
        }
        
        
        
        if (s0.compare(s1)&&
            s2.compare(s3)
            &&s4.compare(s5)
            &&
            s6.compare(s7)
            &&
            s8.compare(s9)
            &&
            s10.compare(s11)
            &&s0.compare(s2)
            
            &&s2.compare(s4)
            &&s4.compare(s6)
            &&s6.compare(s8)
            &&s8.compare(selectKeysArr.at(selectKeysArr.size() - 1)) ) {
            return POKER_TYPE_DOUBLE_STRAIGHT;
            //拖拉机
        }
        
        
        if (!s0.compare(s1)&&
            !s1.compare(s2)&&
            !s2.compare(s3)&&
            !s3.compare(s4)&&
            !s4.compare(s5)&&
            !s5.compare(s6)&&
            !s6.compare(s7)&&
            !s7.compare(s8)&&
            !s8.compare(s9)&&
            !s9.compare(s10)&&
            !s10.compare(s11)&&
            s0.compare(selectKeysArr.at(selectKeysArr.size() - 1))
            ){
            return POKER_TYPE_STRAIGHT;
            //顺子
        }
        
    }
    return 0;

}
