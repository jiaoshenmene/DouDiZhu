//
//  DecidePoker.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#include "DecidePoker.h"
#include "TypeEnmu.h"
#include "Tools.h"


static DecidePoker * sh;
DecidePoker * DecidePoker::sharedDecidePoker()
{
    if (sh==NULL) {
        sh=new DecidePoker();
    }
    return sh;
}

#pragma mark ------此函数用来非第二圈判断玩家是否可以打住桌面上的牌
bool DecidePoker:: decidePersonMoreBigSHowPoker(std::vector<std::string> keysOfNextShowArr, std::vector<std::string> keysOfNowShowArr)
{
    int countCompare=0;
    if (keysOfNextShowArr.size()==keysOfNowShowArr.size()) {
        if(keysOfNowShowArr.size()==1)
        {
            if (keysOfNextShowArr.at(0).compare(keysOfNowShowArr.at(0)) > 0) {
                return true;
            }
        }
        else
        {
            for (int i=0; i<keysOfNowShowArr.size()-1; i++) {
                if(keysOfNextShowArr.at(i).compare(keysOfNowShowArr.at(i))==keysOfNextShowArr.at(i+1).compare(keysOfNowShowArr.at(i+1))) {
                    countCompare++;
                }
                if (countCompare==keysOfNowShowArr.size()-1) {
                    //CCLog("%d",countCompare);
                    return true;
                }
                
            }
        }
    }
    return false;
    
}
#pragma mark------判断当前出牌玩家手中是否有压得住桌面上的牌----
bool DecidePoker:: decideWhetherHaveSuitablePokers(
                                                   std::vector<Sprite *> nowScreenShowPokerArr,
                                                   std::vector<std::string> keysOfnowScreenShowPokerArr ,
                                                   std::vector<Sprite *> &nextTimeShouldShowPokerArr,
                                                   std::vector<std::string> &keysOfnextTimeShouldShowPokerArr,
                                                   std::vector<Sprite *> &requireConsiderWhetherOutOfArr,
                                                   std::vector<std::string> &keysOfrequireConsiderWhetherOutOfArr,
                                                 int miPokerTypeID)
{
    int length=keysOfnowScreenShowPokerArr.size();
    int requireLength=keysOfrequireConsiderWhetherOutOfArr.size();
    //one
    if(requireLength>=length){
        if (length==1) {
            for (int i=requireLength-1; i>=0; i--) {
                
                if (keysOfrequireConsiderWhetherOutOfArr.at(i). compare(keysOfnowScreenShowPokerArr.at(0)) >0 )
                {
                    saveEligibilityPokersAndRelevantKeys(i, length,
                                                         nextTimeShouldShowPokerArr,
                                                         keysOfnextTimeShouldShowPokerArr,
                                                         requireConsiderWhetherOutOfArr,
                                                         keysOfrequireConsiderWhetherOutOfArr);
                    return true;
                }
            }
        }
        //two
        if (length==2) {
            for (int i=requireLength-1; i>=1; i--) {
                if (((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfnowScreenShowPokerArr.at(0))))>0
                    &&
                    ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-1))))==0)
                {//
                    saveEligibilityPokersAndRelevantKeys(i-1, length,
                                                         nextTimeShouldShowPokerArr,
                                                         keysOfnextTimeShouldShowPokerArr,
                                                         requireConsiderWhetherOutOfArr,
                                                         keysOfrequireConsiderWhetherOutOfArr);

                    return true;
                }
            }
        }


        //three
        if (length==3) {
            for (int i=requireLength-1; i>=3; i--) {
                if (((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfnowScreenShowPokerArr.at(0))))>0
                    &&
                    ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-1))))==0
                    &&
                    ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-2))))==0
                    &&
                    ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-3))))!=0
                    )
                {
                    saveEligibilityPokersAndRelevantKeys(i-2, length,
                                                         nextTimeShouldShowPokerArr,
                                                         keysOfnextTimeShouldShowPokerArr,
                                                         requireConsiderWhetherOutOfArr,
                                                         keysOfrequireConsiderWhetherOutOfArr);

                    return true;
                }
            }
        }

        //four
        if (length==4) {
            //3-1
            if (miPokerTypeID==POKER_TYPE_FOUR) {
                if (planeWithSingleWing(length-1, keysOfnowScreenShowPokerArr, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
            }
            //4-0
            if (miPokerTypeID==POKER_COMMON_BOOM) {
                for (int i=requireLength-1; i>=3; i--) {
                    if (((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfnowScreenShowPokerArr.at(0))))>0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-1))))==0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-2))))==0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-3))))==0
                        )
                    {
                        saveEligibilityPokersAndRelevantKeys(i-3, length,
                                                             nextTimeShouldShowPokerArr,
                                                             keysOfnextTimeShouldShowPokerArr,
                                                             requireConsiderWhetherOutOfArr,
                                                             keysOfrequireConsiderWhetherOutOfArr);

                        return true;
                    }
                }
            }
        }

        //3-2 five
        if (miPokerTypeID==POKER_TYPE_FIVE_THREE_WITH_TWO) {
            if (planeWithDoubleWings(length-2, keysOfnowScreenShowPokerArr, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
            }

        //顺子 5 6 7 8 ....
        if (miPokerTypeID==POKER_TYPE_STRAIGHT){
            //CCLog("类型顺子");
            if (singleStraight(length,keysOfnowScreenShowPokerArr,
                               nextTimeShouldShowPokerArr,
                               keysOfnextTimeShouldShowPokerArr,
                               requireConsiderWhetherOutOfArr,
                               keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID)==true)
            {
                //CCLog("上家出的是顺子");
                return true;
            }
        }

        //拖拉机 6 8 10 12 ....
        if (miPokerTypeID==POKER_TYPE_DOUBLE_STRAIGHT) {
            if (doubleStraight(length, keysOfnowScreenShowPokerArr, nextTimeShouldShowPokerArr,
                               keysOfnextTimeShouldShowPokerArr,
                               requireConsiderWhetherOutOfArr,
                               keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID)
                )
            {
                return true;
            }
        }
        //三飞不带 6 9 12 ....
        if (miPokerTypeID==POKER_TYPE_THREE_STRAIGHT) {
            if (threeStraight(length, keysOfnowScreenShowPokerArr, nextTimeShouldShowPokerArr,
                              keysOfnextTimeShouldShowPokerArr,
                              requireConsiderWhetherOutOfArr,
                              keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID)
                )
            {
                return true;
            }
        }


        //4-2
        if (miPokerTypeID==POKER_TYPE_SIX_FOUR_WITH_TWO) {
            for (int i=requireLength-1; i>=3; i--) {
                if (((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfnowScreenShowPokerArr.at(0))))>0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-1))))==0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-2))))==0
                        &&
                        ((keysOfrequireConsiderWhetherOutOfArr.at(i))).compare(((keysOfrequireConsiderWhetherOutOfArr.at(i-3))))==0
                        )
                    {
                        saveEligibilityPokersAndRelevantKeys(i-3, length,
                                                             nextTimeShouldShowPokerArr,
                                                             keysOfnextTimeShouldShowPokerArr,
                                                             requireConsiderWhetherOutOfArr,
                                                             keysOfrequireConsiderWhetherOutOfArr);
                        return true;

                    }
                }
            }




        if (length==8) {
            //3-3-1-1
            if (miPokerTypeID==POKER_TYPE_EIGHT_ONE) {

                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=0; i<keysOfnowScreenShowPokerArr.size()-2; i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }

            }
            //1-3-3-1
            if (miPokerTypeID==POKER_TYPE_EIGHT_TWO) {

                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=1; i<keysOfnowScreenShowPokerArr.size()-1; i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }

            }
            //1-1-3-3
            if (miPokerTypeID==POKER_TYPE_EIGHT_THREE) {

                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=2; i<keysOfnowScreenShowPokerArr.size(); i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }

            }
        }




        if (length==10) {

            //3-3-2-2
            if (miPokerTypeID==101) {
                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=0; i<keysOfnowScreenShowPokerArr.size()-4; i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithDoubleWings(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
            }
            //2-3-3-2
            if (miPokerTypeID==102) {

                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=2; i<keysOfnowScreenShowPokerArr.size()-2; i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithDoubleWings(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }

            }
            //2-2-3-3
            if (miPokerTypeID==103) {

                std::vector<std::string> keysOfDecideContainNowShowPokers=std::vector<std::string>();
                for (int i=4; i<keysOfnowScreenShowPokerArr.size(); i++) {
                    keysOfDecideContainNowShowPokers.push_back(keysOfnowScreenShowPokerArr.at(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers.size();
                if (planeWithDoubleWings(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }

            }

        }
    }

    return  false;

}

#pragma mark------如果当前出牌玩家手中有压得住桌面上的牌--保存----
void DecidePoker:: saveEligibilityPokersAndRelevantKeys(int location,
                                                      int length,
                                                      std::vector<Sprite *> &nextTimeShouldShowPokerArr,
                                                      std::vector<std::string> &keysOfnextTimeShouldShowPokerArr,
                                                      std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                                      std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr)
{
    for (int i=location; i<location+length; i++) {
        nextTimeShouldShowPokerArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfnextTimeShouldShowPokerArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }

}
#pragma mark------判断是否有压得住桌面上的顺子----
bool DecidePoker:: singleStraight(int length,
                                std::vector<std::string> keysOfnowScreenShowPokerArr,
                                std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                                int miPokerTypeID)

{
    bool mHaveSuitablePokers=false;
    //成功判断
//    CCLOG("判断是否压得住顺子");
    std::vector<Sprite *> newRequireConsiderArr=std::vector<Sprite *>();    //copy
    std::vector<std::string> keysOfNewRequireConsiderArr=std::vector<std::string>();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr.size(); i++) {
        newRequireConsiderArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfNewRequireConsiderArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }


    std::vector<Sprite *> singleValueArr =std::vector<Sprite *>();
    std::vector<std::string> keysOfSingleArr=std::vector<std::string>();

    std::vector<Sprite *> doubleValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfDoubleValueArr=std::vector<std::string>();
    
    
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfSingleArr.begin(), keysOfSingleArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfSingleArr.end()) {
            singleValueArr.push_back(requireConsiderWhetherOutOfArr.at(i));
            keysOfSingleArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
        }
    }
    newRequireConsiderArr.erase(singleValueArr.begin(), singleValueArr.end());

    keysOfNewRequireConsiderArr.erase(keysOfSingleArr.begin(),keysOfSingleArr.end());

    for (int i=0; i<newRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfDoubleValueArr.begin(), keysOfDoubleValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfSingleArr.end()) {
            doubleValueArr.push_back(requireConsiderWhetherOutOfArr.at(i));
            keysOfDoubleValueArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
        }

    }
        singleValueArr.erase(doubleValueArr.begin(),doubleValueArr.end());
        keysOfSingleArr.erase(keysOfDoubleValueArr.begin(),keysOfDoubleValueArr.end());
    //取 single 若此句不注销 则出顺子时 电脑不会拆牌
    if (keysOfSingleArr.size()>=length) {
        for (int i=keysOfSingleArr.size()-1; i>=length-1; i--) {
            if ((((keysOfSingleArr.at(i)))).compare(((keysOfnowScreenShowPokerArr.at(length-1))))>0
                &&
                (((keysOfSingleArr.at(i)))).compare(((keysOfSingleArr.at(i-length+1))))==-(length-1)) {
                //-(length-1)因为是从后面开始比较所以后面的牌应该比前面的牌小
                saveEligibilityPokersAndRelevantKeys(
                                                     i-length+1,
                                                     length,
                                                     nextTimeShouldShowPokerArr,
                                                     keysOfnextTimeShouldShowPokerArr,
                                                     singleValueArr,
                                                     keysOfSingleArr);
                //CCLog("true");

                mHaveSuitablePokers=true;
                break;
            }
        }
    }
//    CC_SAFE_DELETE(newRequireConsiderArr);
//    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
//    CC_SAFE_DELETE(singleValueArr);
//    CC_SAFE_DELETE(keysOfSingleArr);
//    CC_SAFE_DELETE(doubleValueArr);
//    CC_SAFE_DELETE(keysOfDoubleValueArr);
    //判断如果存在符合条件 保存输出
    return mHaveSuitablePokers;
}
#pragma mark------判断是否有压得住桌面上的拖拉机----
bool DecidePoker:: doubleStraight(int length,
                                std::vector<std::string> keysOfnowScreenShowPokerArr,
                                std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                                int miPokerTypeID)
{
    bool mHaveSuitablePokers=false;
    //判断成功
    //CCLog("判断是否压得住拖拉机");
    std::vector<Sprite *> newRequireConsiderArr=std::vector<Sprite *>();    //copy
    std::vector<std::string> keysOfNewRequireConsiderArr=std::vector<std::string>();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr.size(); i++) {
        newRequireConsiderArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfNewRequireConsiderArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }



    std::vector<Sprite *> firstDoubleValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfFirstDoubleValueArr=std::vector<std::string>();


    std::vector<Sprite *> secondDoubleValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfSecondDoubleValueArr=std::vector<std::string>();

    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfFirstDoubleValueArr.begin(), keysOfFirstDoubleValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfFirstDoubleValueArr.end()) {
            firstDoubleValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfFirstDoubleValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr.erase(firstDoubleValueArr.begin(),firstDoubleValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfFirstDoubleValueArr.begin(),keysOfFirstDoubleValueArr.end());
    //
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfSecondDoubleValueArr.begin(), keysOfSecondDoubleValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfFirstDoubleValueArr.end()) {
            secondDoubleValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfSecondDoubleValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时secondDoubleValueArr keysOfSecondDoubleValueArr包含的value
            //和key在原数组中至少有两个
        }
    }

    std::vector<Sprite *> threeDoubleValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfThreeDoubleValueArr=std::vector<std::string>();
    
    for (auto v: secondDoubleValueArr) {
        threeDoubleValueArr.push_back(v);
    }
    for (auto v: keysOfSecondDoubleValueArr) {
        keysOfThreeDoubleValueArr.push_back(v);
    }
    
    for (int i=0; i<keysOfFirstDoubleValueArr.size(); i++) {
        for (int j=0; j<keysOfSecondDoubleValueArr.size(); j++) {
            std::vector<std::string>::iterator it = std::find(keysOfFirstDoubleValueArr.begin(), keysOfFirstDoubleValueArr.end(), keysOfSecondDoubleValueArr.at(i));
            if (it != keysOfFirstDoubleValueArr.end()) {
                threeDoubleValueArr.push_back(firstDoubleValueArr.at(i));
                keysOfThreeDoubleValueArr.push_back(keysOfFirstDoubleValueArr.at(i));
                
            }
        }
    }
//    //CCLog("decide count %d",threeDoubleValueArr.size());
    //在此处重新排序方便显示
    if (keysOfThreeDoubleValueArr.size()>0) {
        Tools::sortedForArray(threeDoubleValueArr, keysOfThreeDoubleValueArr);
    }
    if (keysOfThreeDoubleValueArr.size()>=length) {
        for (int i=keysOfThreeDoubleValueArr.size()-1; i>=length-1; i--) {
            if ((((keysOfThreeDoubleValueArr.at(i)))).compare(((keysOfnowScreenShowPokerArr.at(length-1))))>0
                &&
                (((keysOfThreeDoubleValueArr.at(i)))).compare(((keysOfThreeDoubleValueArr.at(i-length+1))))==-(length/2-1)) {
                //-(length-1)因为是从后面开始比较所以后面的牌应该比前面的牌小
                saveEligibilityPokersAndRelevantKeys(
                                                     i-length+1,
                                                     length,
                                                     nextTimeShouldShowPokerArr,
                                                     keysOfnextTimeShouldShowPokerArr,
                                                     threeDoubleValueArr,
                                                     keysOfThreeDoubleValueArr);
                mHaveSuitablePokers=true;
                break;
            }

        }
    }
//    CC_SAFE_DELETE(newRequireConsiderArr);
//    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
//    CC_SAFE_DELETE(firstDoubleValueArr);
//    CC_SAFE_DELETE(keysOfFirstDoubleValueArr);
//    CC_SAFE_DELETE(secondDoubleValueArr);
//    CC_SAFE_DELETE(keysOfSecondDoubleValueArr);
//    CC_SAFE_DELETE(threeDoubleValueArr);
//    CC_SAFE_DELETE(keysOfThreeDoubleValueArr);
    return mHaveSuitablePokers;

}
#pragma mark------判断是否有压得住桌面上的三飞不带----
bool DecidePoker:: threeStraight(int length,
                               std::vector<std::string> keysOfnowScreenShowPokerArr,
                               std::vector<Sprite *> nextTimeShouldShowPokerArr,
                               std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                               std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                               std::vector<std::string>keysOfrequireConsiderWhetherOutOfArr,
                               int miPokerTypeID)
{
    bool mHaveSuitablePokers=false;
    //CCLog("判断是否有压得住桌面上的三飞不带");
    std::vector<Sprite *> newRequireConsiderArr=std::vector<Sprite *>();    //copy
    std::vector<std::string> keysOfNewRequireConsiderArr=std::vector<std::string>();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr.size(); i++) {
        newRequireConsiderArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfNewRequireConsiderArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }


    std::vector<Sprite *> firstThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfFirstThreeValueArr=std::vector<std::string>();


    std::vector<Sprite *> secondThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfSecondThreeValueArr=std::vector<std::string>();

    std::vector<Sprite *> thirdThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfThirdThreeValueArr=std::vector<std::string>();


    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfFirstThreeValueArr.begin(), keysOfFirstThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfFirstThreeValueArr.end()) {
            firstThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfFirstThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr.erase(firstThreeValueArr.begin(),firstThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfFirstThreeValueArr.begin(),keysOfFirstThreeValueArr.end());
    //
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfSecondThreeValueArr.begin(), keysOfSecondThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfThirdThreeValueArr.end()) {
            secondThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfSecondThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr.erase(secondThreeValueArr.begin(),secondThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfSecondThreeValueArr.begin(),keysOfSecondThreeValueArr.end());

    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfThirdThreeValueArr.begin(), keysOfThirdThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfThirdThreeValueArr.end()) {
            thirdThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfThirdThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }

    std::vector<Sprite *> decideValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfDecideValueArr=std::vector<std::string>();
    
    for (auto v : thirdThreeValueArr) {
        decideValueArr.push_back(v);
    }
    
    for (auto v : keysOfThirdThreeValueArr) {
        keysOfDecideValueArr.push_back(v);
    }
    
    for (auto v : thirdThreeValueArr) {
        decideValueArr.push_back(v);
    }
    
    for (auto v : keysOfThirdThreeValueArr) {
        keysOfDecideValueArr.push_back(v);
    }
   
    for (auto v : thirdThreeValueArr) {
        decideValueArr.push_back(v);
    }
    
    for (auto v : keysOfThirdThreeValueArr) {
        keysOfDecideValueArr.push_back(v);
    }
    
    //在此处重新排序方便显示
    if (keysOfDecideValueArr.size()>=length) {
        for (int i=keysOfDecideValueArr.size()-1; i>=length-1; i--) {
            if ((((keysOfDecideValueArr.at(i)))).compare(((keysOfnowScreenShowPokerArr.at(length-1))))>0
                &&
                (((keysOfDecideValueArr.at(i)))).compare(((keysOfDecideValueArr.at(i-length+1))))==-(length-1)) {
                saveEligibilityPokersAndRelevantKeys(
                                                     i-length+1,
                                                     length,
                                                     nextTimeShouldShowPokerArr,
                                                     keysOfnextTimeShouldShowPokerArr,
                                                     decideValueArr,
                                                     keysOfDecideValueArr);
                mHaveSuitablePokers=true;
                break;
            }

        }
    }
//    CC_SAFE_DELETE(newRequireConsiderArr);
//    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
//    CC_SAFE_DELETE(firstThreeValueArr);
//    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
//    CC_SAFE_DELETE(secondThreeValueArr);
//    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
//    CC_SAFE_DELETE(thirdThreeValueArr);
//    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
//    CC_SAFE_DELETE(decideValueArr);
//    CC_SAFE_DELETE(keysOfDecideValueArr);
    return mHaveSuitablePokers;
}

#pragma mark------判断是否有压得住桌面上的三带一----
bool DecidePoker:: planeWithSingleWing(int length,
                                     std::vector<std::string> keysOfnowScreenShowPokerArr,
                                     std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                     std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                     std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                     std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                                     int miPokerTypeID)
{
    bool mHaveSuitable=false;
    //成功判断
    //CCLog("判断是否压得住三带一");
    std::vector<Sprite *> newRequireConsiderArr=std::vector<Sprite *>();    //copy
    std::vector<std::string> keysOfNewRequireConsiderArr=std::vector<std::string>();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr.size(); i++) {
        newRequireConsiderArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfNewRequireConsiderArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }


    std::vector<Sprite *> firstThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfFirstThreeValueArr=std::vector<std::string>();


    std::vector<Sprite *> secondThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfSecondThreeValueArr=std::vector<std::string>();

    std::vector<Sprite *> thirdThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfThirdThreeValueArr=std::vector<std::string>();


    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfThirdThreeValueArr.begin(), keysOfThirdThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfThirdThreeValueArr.end()) {
            firstThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfFirstThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr.erase(firstThreeValueArr.begin(),firstThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfFirstThreeValueArr.begin(),keysOfFirstThreeValueArr.end());

    //
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfSecondThreeValueArr.begin(), keysOfSecondThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfNewRequireConsiderArr.end()) {
            secondThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfSecondThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr.erase(secondThreeValueArr.begin(),secondThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfSecondThreeValueArr.begin(),keysOfSecondThreeValueArr.end());

    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfThirdThreeValueArr.begin(), keysOfThirdThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfThirdThreeValueArr.end()) {
            thirdThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfThirdThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }

    std::vector<Sprite *> decideValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfDecideValueArr=std::vector<std::string>();
    
    for (auto v : thirdThreeValueArr) {
        decideValueArr.push_back(v);
    }
    
    for (auto v : keysOfThirdThreeValueArr) {
        keysOfDecideValueArr.push_back(v);
    }
   
    for (int i=0; i<keysOfFirstThreeValueArr.size(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr.size();j++){
            if (keysOfThirdThreeValueArr.at(j).compare(keysOfFirstThreeValueArr.at(i))) {
                decideValueArr.push_back(firstThreeValueArr.at(i));
                keysOfDecideValueArr.push_back(keysOfFirstThreeValueArr.at(i));
            }
        }
    }
    //此时decideValueArr中存放的是对子
    for (int i=0; i<keysOfSecondThreeValueArr.size(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr.size();j++){
            if (((keysOfThirdThreeValueArr.at(j))).compare((keysOfSecondThreeValueArr.at(i)))) {
                decideValueArr.push_back(secondThreeValueArr.at(i));
                keysOfDecideValueArr.push_back(keysOfSecondThreeValueArr.at(i));
            }
        }
    }
    //此时decideValueArr中存放的是三个
    firstThreeValueArr.erase(secondThreeValueArr.begin(),secondThreeValueArr.end());
    keysOfFirstThreeValueArr.erase(keysOfSecondThreeValueArr.begin(),keysOfSecondThreeValueArr.end());
    //此时firstThreeValueArr中存放的仅是单牌
    
    //在此处重新排序方便显示
    if (decideValueArr.size()>0) {
        Tools::sortedForArray(decideValueArr, keysOfDecideValueArr);
    }
    if (keysOfDecideValueArr.size()>=length&&keysOfFirstThreeValueArr.size()>0) {
        for (int i=keysOfDecideValueArr.size()-1; i>=length-1; i--) {
            if ((((keysOfDecideValueArr.at(i)))).compare(((keysOfnowScreenShowPokerArr.at(1))))>0
                &&
                (((keysOfDecideValueArr.at(i)))).compare(((keysOfDecideValueArr.at(i-length+1))))==0) {
                {
                    for (int j=0; j<keysOfnowScreenShowPokerArr.size()/3; j++) {
                        decideValueArr.insert(decideValueArr.begin() + i + 1, firstThreeValueArr.at(firstThreeValueArr.size()-1));
                        
                        keysOfDecideValueArr.insert(keysOfDecideValueArr.begin() + i + 1, keysOfFirstThreeValueArr.at(keysOfFirstThreeValueArr.size()-1));
                        
                    }

                    saveEligibilityPokersAndRelevantKeys(
                                                         i-length+1,
                                                         length+length/3,
                                                         nextTimeShouldShowPokerArr,
                                                         keysOfnextTimeShouldShowPokerArr,
                                                         decideValueArr,
                                                         keysOfDecideValueArr);
                    //CCLog("三带一true");
                    mHaveSuitable=true;
                    break;
                }
            }

        }
    }
//    CC_SAFE_DELETE(newRequireConsiderArr);
//    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
//    CC_SAFE_DELETE(firstThreeValueArr);
//    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
//    CC_SAFE_DELETE(secondThreeValueArr);
//    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
//    CC_SAFE_DELETE(thirdThreeValueArr);
//    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
//    CC_SAFE_DELETE(decideValueArr);
//    CC_SAFE_DELETE(keysOfDecideValueArr);
    return mHaveSuitable;


}
#pragma mark------判断是否有压得住桌面上的三带二----
bool DecidePoker:: planeWithDoubleWings(int length,
                                      std::vector<std::string> keysOfnowScreenShowPokerArr,
                                      std::vector<Sprite *> nextTimeShouldShowPokerArr,
                                      std::vector<std::string> keysOfnextTimeShouldShowPokerArr,
                                      std::vector<Sprite *> requireConsiderWhetherOutOfArr,
                                      std::vector<std::string> keysOfrequireConsiderWhetherOutOfArr,
                                      int miPokerTypeID)
{
    bool mHaveSuitable=false;
    //成功判断
    //CCLog("判断是否压得住三带二");
    std::vector<Sprite *> newRequireConsiderArr=std::vector<Sprite *>();    //copy
    std::vector<std::string> keysOfNewRequireConsiderArr=std::vector<std::string>();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr.size(); i++) {
        newRequireConsiderArr.push_back(requireConsiderWhetherOutOfArr.at(i));
        keysOfNewRequireConsiderArr.push_back(keysOfrequireConsiderWhetherOutOfArr.at(i));
    }


    std::vector<Sprite *> firstThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfFirstThreeValueArr=std::vector<std::string>();


    std::vector<Sprite *> secondThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfSecondThreeValueArr=std::vector<std::string>();

    std::vector<Sprite *> thirdThreeValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfThirdThreeValueArr=std::vector<std::string>();


    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfFirstThreeValueArr.begin(), keysOfFirstThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it != keysOfFirstThreeValueArr.end()) {
            firstThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfFirstThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr.erase(firstThreeValueArr.begin(),firstThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfFirstThreeValueArr.begin(),keysOfFirstThreeValueArr.end());
    //在copy的数组中移除single
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfSecondThreeValueArr.begin(), keysOfSecondThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfSecondThreeValueArr.end()) {
            
            secondThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfSecondThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr.erase(secondThreeValueArr.begin(),secondThreeValueArr.end());
    keysOfNewRequireConsiderArr.erase(keysOfSecondThreeValueArr.begin(),keysOfSecondThreeValueArr.end());
    for (int i=0; i<keysOfNewRequireConsiderArr.size(); i++) {
        std::vector<std::string>::iterator it = std::find(keysOfThirdThreeValueArr.begin(), keysOfThirdThreeValueArr.end(), keysOfNewRequireConsiderArr.at(i));
        if (it == keysOfThirdThreeValueArr.end()) {
            
            thirdThreeValueArr.push_back(newRequireConsiderArr.at(i));
            keysOfThirdThreeValueArr.push_back(keysOfNewRequireConsiderArr.at(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }

    std::vector<Sprite *> decideValueArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfDecideValueArr=std::vector<std::string>();
    
    for (auto v : thirdThreeValueArr) {
        decideValueArr.push_back(v);
    }
    
    for (auto v : keysOfThirdThreeValueArr) {
        keysOfDecideValueArr.push_back(v);
    }
    for (int i=0; i<keysOfFirstThreeValueArr.size(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr.size();j++){
            if (((keysOfThirdThreeValueArr.at(j))).compare((keysOfFirstThreeValueArr.at(i)))) {
                decideValueArr.push_back(firstThreeValueArr.at(i));
                keysOfDecideValueArr.push_back(keysOfFirstThreeValueArr.at(i));
            }
        }
    }
    //此时decideValueArr中存放的是对子
    for (int i=0; i<keysOfSecondThreeValueArr.size(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr.size();j++){
            if (((keysOfThirdThreeValueArr.at(j))).compare((keysOfSecondThreeValueArr.at(i)))) {
                decideValueArr.push_back(secondThreeValueArr.at(i));
                keysOfDecideValueArr.push_back(keysOfSecondThreeValueArr.at(i));
            }
        }
    }
    //此时decideValueArr中存放的是三个
//    //CCLog("decide third =%d",decideValueArr.size());


    std::vector<Sprite *> temArr=std::vector<Sprite *>();
    std::vector<std::string> keysOfTemArr=std::vector<std::string>();

    for (int i=0; i<keysOfThirdThreeValueArr.size(); i++){
        for (int j=0; j<keysOfSecondThreeValueArr.size(); j++) {
            if (((keysOfThirdThreeValueArr.at(i))).compare((keysOfSecondThreeValueArr.at(j)))){
                temArr.push_back(secondThreeValueArr.at(j));
                keysOfTemArr.push_back(keysOfSecondThreeValueArr.at(j));
            }
        }
    }
    secondThreeValueArr.erase(temArr.begin(),temArr.end());
    keysOfSecondThreeValueArr.erase(keysOfTemArr.begin(),keysOfTemArr.end());
    //此时secondThreeValueArr keysOfSecondThreeValueArr保存的时double
    int countSec=secondThreeValueArr.size();
//    CCLog("single second%d",countSec);
    for (int i=0; i<keysOfFirstThreeValueArr.size(); i++) {
        for(int j=0;j<countSec;j++){
            if (((keysOfSecondThreeValueArr.at(j))).compare((keysOfFirstThreeValueArr.at(i)))) {
                secondThreeValueArr.push_back(firstThreeValueArr.at(i));
                keysOfSecondThreeValueArr.push_back(keysOfFirstThreeValueArr.at(i));
            }
        }
    }
    //此时secondThreeValueArr中存放的仅是对子
//    CCLog("only second =%d",secondThreeValueArr.size());

    //在此处重新排序方便显示
    if (secondThreeValueArr.size()>0&&decideValueArr.size()>0) {
        Tools::sortedForArray(secondThreeValueArr, keysOfSecondThreeValueArr);
        Tools::sortedForArray(decideValueArr, keysOfDecideValueArr);
    }
    if (keysOfDecideValueArr.size()>=length&&keysOfSecondThreeValueArr.size()>0) {
        for (int i=keysOfDecideValueArr.size()-1; i>=length-1; i--) {
            if ((((keysOfDecideValueArr.at(i)))).compare(((keysOfnowScreenShowPokerArr.at(2))))>0
                &&
                (((keysOfDecideValueArr.at(i)))).compare(((keysOfDecideValueArr.at(i-length+1))))==0) {

                for (int j=0; j<2*length/3; j++) {
                    decideValueArr.insert(decideValueArr.begin() + i + 1, secondThreeValueArr.at(j));
                    keysOfDecideValueArr.insert(keysOfDecideValueArr.begin() + i + 1, keysOfSecondThreeValueArr.at(j));
                }
                saveEligibilityPokersAndRelevantKeys(
                                                     i-length+1,
                                                     length+2*length/3,
                                                     nextTimeShouldShowPokerArr,
                                                     keysOfnextTimeShouldShowPokerArr,
                                                     decideValueArr,
                                                     keysOfDecideValueArr);
                mHaveSuitable=true;
                break;
            }

        }
    }
//    CC_SAFE_DELETE(newRequireConsiderArr);
//    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
//    CC_SAFE_DELETE(firstThreeValueArr);
//    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
//    CC_SAFE_DELETE(secondThreeValueArr);
//    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
//    CC_SAFE_DELETE(thirdThreeValueArr);
//    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
//    CC_SAFE_DELETE(decideValueArr);
//    CC_SAFE_DELETE(keysOfDecideValueArr);
//    CC_SAFE_DELETE(temArr);
//    CC_SAFE_DELETE(keysOfTemArr);
    return mHaveSuitable;


}
