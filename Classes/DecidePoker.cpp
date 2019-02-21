//
//  DecidePoker.cpp
//  MyGame
//
//  Created by user on 14-4-1.
//
//

#include "cocos2d.h"

static DecidePoker * sh;
DecidePoker * DecidePoker::sharedDecidePoker()
{
    if (sh==NULL) {
        sh=new DecidePoker();
    }
    return sh;
}

#pragma mark ------此函数用来非第二圈判断玩家是否可以打住桌面上的牌
bool DecidePoker:: decidePersonMoreBigSHowPoker(CCArray * keysOfNextShowArr, CCArray * keysOfNowShowArr)
{
    int countCompare=0;
    if (keysOfNextShowArr->count()==keysOfNowShowArr->count()) {
        if(keysOfNowShowArr->count()==1)
        {
            if (((CCString *)(keysOfNextShowArr->objectAtIndex(0)))->compare(((CCString *)(keysOfNowShowArr->objectAtIndex(0)))->getCString())>0) {
                return true;
            }
            
        }
        else
        {
            for (int i=0; i<keysOfNowShowArr->count()-1; i++) {
                if (((CCString *)(keysOfNextShowArr->objectAtIndex(i)))->compare(((CCString *)(keysOfNowShowArr->objectAtIndex(i)))->getCString())==((CCString *)(keysOfNextShowArr->objectAtIndex(i+1)))->compare(((CCString *)(keysOfNowShowArr->objectAtIndex(i+1)))->getCString())) {
                    countCompare++;
                }
                if (countCompare==keysOfNowShowArr->count()-1) {
                    CCLOG("%d",countCompare);
                    return true;
                }
                
            }
        }
    }
    return false;
    
}
#pragma mark------判断当前出牌玩家手中是否有压得住桌面上的牌----
bool DecidePoker:: decideWhetherHaveSuitablePokers(
                                                 CCArray *nowScreenShowPokerArr,
                                                 CCArray *keysOfnowScreenShowPokerArr,
                                                 CCArray *nextTimeShouldShowPokerArr,
                                                 CCArray *keysOfnextTimeShouldShowPokerArr,
                                                 CCArray *requireConsiderWhetherOutOfArr,
                                                 CCArray *keysOfrequireConsiderWhetherOutOfArr,
                                                 int miPokerTypeID)
{
    int length=keysOfnowScreenShowPokerArr->count();
    int requireLength=keysOfrequireConsiderWhetherOutOfArr->count();
    //one
    if(requireLength>=length){
        if (length==1) {
            for (int i=requireLength-1; i>=0; i--) {
                if (((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(0)))->getCString())>0)
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
                if (((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(0)))->getCString())>0
                    &&
                    ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-1)))->getCString())==0)
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
                if (((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(0)))->getCString())>0
                    &&
                    ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-1)))->getCString())==0
                    &&
                    ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-2)))->getCString())==0
                    &&
                    ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-3)))->getCString())!=0
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
                    if (((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(0)))->getCString())>0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-1)))->getCString())==0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-2)))->getCString())==0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-3)))->getCString())==0
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
            CCLOG("类型顺子");
            if (singleStraight(length,keysOfnowScreenShowPokerArr,
                               nextTimeShouldShowPokerArr,
                               keysOfnextTimeShouldShowPokerArr,
                               requireConsiderWhetherOutOfArr,
                               keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID)==true)
            {
                CCLOG("上家出的是顺子");
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
                if (((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(0)))->getCString())>0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-1)))->getCString())==0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-2)))->getCString())==0
                        &&
                        ((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i)))->compare(((CCString *)(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i-3)))->getCString())==0
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
                
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=0; i<keysOfnowScreenShowPokerArr->count()-2; i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
                
            }
            //1-3-3-1
            if (miPokerTypeID==POKER_TYPE_EIGHT_TWO) {
                
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=1; i<keysOfnowScreenShowPokerArr->count()-1; i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
                
            }
            //1-1-3-3
            if (miPokerTypeID==POKER_TYPE_EIGHT_THREE) {
                
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=2; i<keysOfnowScreenShowPokerArr->count(); i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
                if (planeWithSingleWing(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
                
            }
        }
        
        
        
        
        if (length==10) {
            
            //3-3-2-2
            if (miPokerTypeID==101) {
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=0; i<keysOfnowScreenShowPokerArr->count()-4; i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
                if (planeWithDoubleWings(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
            }
            //2-3-3-2
            if (miPokerTypeID==102) {
                
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=2; i<keysOfnowScreenShowPokerArr->count()-2; i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
                if (planeWithDoubleWings(newlength, keysOfDecideContainNowShowPokers, nextTimeShouldShowPokerArr, keysOfnextTimeShouldShowPokerArr, requireConsiderWhetherOutOfArr, keysOfrequireConsiderWhetherOutOfArr,miPokerTypeID))
                {
                    return true;
                }
                
            }
            //2-2-3-3
            if (miPokerTypeID==103) {
                
                CCArray * keysOfDecideContainNowShowPokers=new CCArray();
                for (int i=4; i<keysOfnowScreenShowPokerArr->count(); i++) {
                    keysOfDecideContainNowShowPokers->addObject(keysOfnowScreenShowPokerArr->objectAtIndex(i));
                }
                //只需判断相同的三张是否可以压住
                int newlength=keysOfDecideContainNowShowPokers->count();
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
                                                      CCArray * nextTimeShouldShowPokerArr,
                                                      CCArray * keysOfnextTimeShouldShowPokerArr,
                                                      CCArray * requireConsiderWhetherOutOfArr,
                                                      CCArray *keysOfrequireConsiderWhetherOutOfArr)
{
    for (int i=location; i<location+length; i++) {
        nextTimeShouldShowPokerArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfnextTimeShouldShowPokerArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
}
#pragma mark------判断是否有压得住桌面上的顺子----
bool DecidePoker:: singleStraight(int length,
                                CCArray * keysOfnowScreenShowPokerArr,
                                CCArray * nextTimeShouldShowPokerArr,
                                CCArray * keysOfnextTimeShouldShowPokerArr,
                                CCArray * requireConsiderWhetherOutOfArr,
                                CCArray * keysOfrequireConsiderWhetherOutOfArr,
                                int miPokerTypeID)

{
    bool mHaveSuitablePokers=false;
    //成功判断
    CCLOG("判断是否压得住顺子");
    CCArray * newRequireConsiderArr=new CCArray();    //copy
    CCArray * keysOfNewRequireConsiderArr=new CCArray();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr->count(); i++) {
        newRequireConsiderArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfNewRequireConsiderArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
    
    CCArray * singleValueArr =new CCArray();
    CCArray * keysOfSingleArr=new CCArray();
    
    CCArray * doubleValueArr=new CCArray();
    CCArray * keysOfDoubleValueArr=new CCArray();
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfSingleArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            singleValueArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
            keysOfSingleArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
        }
    }
    
    newRequireConsiderArr->removeObjectsInArray(singleValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfSingleArr);
    
    for (int i=0; i<newRequireConsiderArr->count(); i++) {
        if (!(keysOfDoubleValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            doubleValueArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
            keysOfDoubleValueArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
        }
        
    }
    //    singleValueArr->removeObjectsInArray(doubleValueArr);
    //    keysOfSingleArr->removeObjectsInArray(keysOfDoubleValueArr);
    //取 single 若此句不注销 则出顺子时 电脑不会拆牌
    if (keysOfSingleArr->count()>=length) {
        for (int i=keysOfSingleArr->count()-1; i>=length-1; i--) {
            if ((((CCString *)(keysOfSingleArr->objectAtIndex(i))))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(length-1)))->getCString())>0
                &&
                (((CCString *)(keysOfSingleArr->objectAtIndex(i))))->compare(((CCString *)(keysOfSingleArr->objectAtIndex(i-length+1)))->getCString())==-(length-1)) {
                //-(length-1)因为是从后面开始比较所以后面的牌应该比前面的牌小
                saveEligibilityPokersAndRelevantKeys(
                                                     i-length+1,
                                                     length,
                                                     nextTimeShouldShowPokerArr,
                                                     keysOfnextTimeShouldShowPokerArr,
                                                     singleValueArr,
                                                     keysOfSingleArr);
                CCLOG("true");
                
                mHaveSuitablePokers=true;
                break;
            }
        }
    }
    CC_SAFE_DELETE(newRequireConsiderArr);
    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
    CC_SAFE_DELETE(singleValueArr);
    CC_SAFE_DELETE(keysOfSingleArr);
    CC_SAFE_DELETE(doubleValueArr);
    CC_SAFE_DELETE(keysOfDoubleValueArr);
    //判断如果存在符合条件 保存输出
    return mHaveSuitablePokers;
}
#pragma mark------判断是否有压得住桌面上的拖拉机----
bool DecidePoker:: doubleStraight(int length,
                                CCArray * keysOfnowScreenShowPokerArr,
                                CCArray * nextTimeShouldShowPokerArr,
                                CCArray * keysOfnextTimeShouldShowPokerArr,
                                CCArray * requireConsiderWhetherOutOfArr,
                                CCArray * keysOfrequireConsiderWhetherOutOfArr,
                                int miPokerTypeID)
{
    bool mHaveSuitablePokers=false;
    //判断成功
    CCLOG("判断是否压得住拖拉机");
    CCArray * newRequireConsiderArr=new CCArray();    //copy
    CCArray * keysOfNewRequireConsiderArr=new CCArray();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr->count(); i++) {
        newRequireConsiderArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfNewRequireConsiderArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
    
    
    CCArray * firstDoubleValueArr=new CCArray();
    CCArray * keysOfFirstDoubleValueArr=new CCArray();
    
    
    CCArray * secondDoubleValueArr=new CCArray();
    CCArray * keysOfSecondDoubleValueArr=new CCArray();
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        CCLog("first %s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
        if (!(keysOfFirstDoubleValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            firstDoubleValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfFirstDoubleValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr->removeObjectsInArray(firstDoubleValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfFirstDoubleValueArr);
    //
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        CCLog("second %s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
        if (!(keysOfSecondDoubleValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            secondDoubleValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfSecondDoubleValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时secondDoubleValueArr keysOfSecondDoubleValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    
    CCArray * threeDoubleValueArr=new CCArray();
    CCArray * keysOfThreeDoubleValueArr=new CCArray();
    threeDoubleValueArr->addObjectsFromArray(secondDoubleValueArr);
    keysOfThreeDoubleValueArr->addObjectsFromArray(keysOfSecondDoubleValueArr);
    
    for (int i=0; i<keysOfFirstDoubleValueArr->count(); i++) {
        for (int j=0; j<keysOfSecondDoubleValueArr->count(); j++) {
            if (((CCString *)(keysOfFirstDoubleValueArr->objectAtIndex(i)))->isEqual((CCString *)(keysOfSecondDoubleValueArr->objectAtIndex(j)))) {
                threeDoubleValueArr->addObject(firstDoubleValueArr->objectAtIndex(i));
                keysOfThreeDoubleValueArr->addObject(keysOfFirstDoubleValueArr->objectAtIndex(i));
                CCLog("d sec %s",((CCString *)(keysOfSecondDoubleValueArr->objectAtIndex(j)))->getCString());
                
            }
        }
    }
    CCLog("decide count %d",threeDoubleValueArr->count());
    //在此处重新排序方便显示
    if (keysOfThreeDoubleValueArr->count()>0) {
        sortedForArray(threeDoubleValueArr, keysOfThreeDoubleValueArr);
    }
    if (keysOfThreeDoubleValueArr->count()>=length) {
        for (int i=keysOfThreeDoubleValueArr->count()-1; i>=length-1; i--) {
            if ((((CCString *)(keysOfThreeDoubleValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(length-1)))->getCString())>0
                &&
                (((CCString *)(keysOfThreeDoubleValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfThreeDoubleValueArr->objectAtIndex(i-length+1)))->getCString())==-(length/2-1)) {
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
    CC_SAFE_DELETE(newRequireConsiderArr);
    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
    CC_SAFE_DELETE(firstDoubleValueArr);
    CC_SAFE_DELETE(keysOfFirstDoubleValueArr);
    CC_SAFE_DELETE(secondDoubleValueArr);
    CC_SAFE_DELETE(keysOfSecondDoubleValueArr);
    CC_SAFE_DELETE(threeDoubleValueArr);
    CC_SAFE_DELETE(keysOfThreeDoubleValueArr);
    return mHaveSuitablePokers;
    
}
#pragma mark------判断是否有压得住桌面上的三飞不带----
bool DecidePoker:: threeStraight(int length,
                               CCArray * keysOfnowScreenShowPokerArr,
                               CCArray * nextTimeShouldShowPokerArr,
                               CCArray * keysOfnextTimeShouldShowPokerArr,
                               CCArray * requireConsiderWhetherOutOfArr,
                               CCArray *keysOfrequireConsiderWhetherOutOfArr,
                               int miPokerTypeID)
{
    bool mHaveSuitablePokers=false;
    CCLOG("判断是否有压得住桌面上的三飞不带");
    CCArray * newRequireConsiderArr=new CCArray();    //copy
    CCArray * keysOfNewRequireConsiderArr=new CCArray();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr->count(); i++) {
        newRequireConsiderArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfNewRequireConsiderArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
    
    CCArray * firstThreeValueArr=new CCArray();
    CCArray * keysOfFirstThreeValueArr=new CCArray();
    
    
    CCArray * secondThreeValueArr=new CCArray();
    CCArray * keysOfSecondThreeValueArr=new CCArray();
    
    CCArray * thirdThreeValueArr=new CCArray();
    CCArray * keysOfThirdThreeValueArr=new CCArray();
    
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfFirstThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            firstThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfFirstThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr->removeObjectsInArray(firstThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfFirstThreeValueArr);
    //
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfSecondThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            secondThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfSecondThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr->removeObjectsInArray(secondThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfSecondThreeValueArr);
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfThirdThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            thirdThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfThirdThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }
    
    CCArray * decideValueArr=new CCArray();
    CCArray * keysOfDecideValueArr=new CCArray();
    decideValueArr->addObjectsFromArray(thirdThreeValueArr);
    keysOfDecideValueArr->addObjectsFromArray(keysOfThirdThreeValueArr);
    
    decideValueArr->addObjectsFromArray(thirdThreeValueArr);
    keysOfDecideValueArr->addObjectsFromArray(keysOfThirdThreeValueArr);
    
    decideValueArr->addObjectsFromArray(thirdThreeValueArr);
    keysOfDecideValueArr->addObjectsFromArray(keysOfThirdThreeValueArr);
    
    //在此处重新排序方便显示
    if (keysOfDecideValueArr->count()>=length) {
        for (int i=keysOfDecideValueArr->count()-1; i>=length-1; i--) {
            if ((((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(length-1)))->getCString())>0
                &&
                (((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfDecideValueArr->objectAtIndex(i-length+1)))->getCString())==-(length-1)) {
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
    CC_SAFE_DELETE(newRequireConsiderArr);
    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
    CC_SAFE_DELETE(firstThreeValueArr);
    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
    CC_SAFE_DELETE(secondThreeValueArr);
    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
    CC_SAFE_DELETE(thirdThreeValueArr);
    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
    CC_SAFE_DELETE(decideValueArr);
    CC_SAFE_DELETE(keysOfDecideValueArr);
    return mHaveSuitablePokers;
}

#pragma mark------判断是否有压得住桌面上的三带一----
bool DecidePoker:: planeWithSingleWing(int length,
                                     CCArray * keysOfnowScreenShowPokerArr,
                                     CCArray * nextTimeShouldShowPokerArr,
                                     CCArray * keysOfnextTimeShouldShowPokerArr,
                                     CCArray * requireConsiderWhetherOutOfArr,
                                     CCArray * keysOfrequireConsiderWhetherOutOfArr,
                                     int miPokerTypeID)
{
    bool mHaveSuitable=false;
    //成功判断
    CCLOG("判断是否压得住三带一");
    CCArray * newRequireConsiderArr=new CCArray();    //copy
    CCArray * keysOfNewRequireConsiderArr=new CCArray();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr->count(); i++) {
        newRequireConsiderArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfNewRequireConsiderArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
    
    CCArray * firstThreeValueArr=new CCArray();
    CCArray * keysOfFirstThreeValueArr=new CCArray();
    
    
    CCArray * secondThreeValueArr=new CCArray();
    CCArray * keysOfSecondThreeValueArr=new CCArray();
    
    CCArray * thirdThreeValueArr=new CCArray();
    CCArray * keysOfThirdThreeValueArr=new CCArray();
    
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        CCLOG("first%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
        if (!(keysOfFirstThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            firstThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfFirstThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr->removeObjectsInArray(firstThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfFirstThreeValueArr);
    
    //
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        CCLOG("second%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
        if (!(keysOfSecondThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            secondThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfSecondThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr->removeObjectsInArray(secondThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfSecondThreeValueArr);
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        CCLOG("third%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
        if (!(keysOfThirdThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            thirdThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfThirdThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }
    
    CCArray * decideValueArr=new CCArray();
    CCArray * keysOfDecideValueArr=new CCArray();
    decideValueArr->addObjectsFromArray(thirdThreeValueArr);
    keysOfDecideValueArr->addObjectsFromArray(keysOfThirdThreeValueArr);
    
    for (int i=0; i<keysOfFirstThreeValueArr->count(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr->count();j++){
            if (((CCString *)(keysOfThirdThreeValueArr->objectAtIndex(j)))->isEqual((CCString *)(keysOfFirstThreeValueArr->objectAtIndex(i)))) {
                decideValueArr->addObject(firstThreeValueArr->objectAtIndex(i));
                keysOfDecideValueArr->addObject(keysOfFirstThreeValueArr->objectAtIndex(i));
            }
        }
    }
    //此时decideValueArr中存放的是对子
    for (int i=0; i<keysOfSecondThreeValueArr->count(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr->count();j++){
            if (((CCString *)(keysOfThirdThreeValueArr->objectAtIndex(j)))->isEqual((CCString *)(keysOfSecondThreeValueArr->objectAtIndex(i)))) {
                decideValueArr->addObject(secondThreeValueArr->objectAtIndex(i));
                keysOfDecideValueArr->addObject(keysOfSecondThreeValueArr->objectAtIndex(i));
            }
        }
    }
    //此时decideValueArr中存放的是三个
    firstThreeValueArr->removeObjectsInArray(secondThreeValueArr);
    keysOfFirstThreeValueArr->removeObjectsInArray(keysOfSecondThreeValueArr);
    //此时firstThreeValueArr中存放的仅是单牌
    CCLOG("%d",keysOfDecideValueArr->count());
    
    //在此处重新排序方便显示
    if (decideValueArr->count()>0) {
        sortedForArray(decideValueArr, keysOfDecideValueArr);
    }
    if (keysOfDecideValueArr->count()>=length&&keysOfFirstThreeValueArr->count()>0) {
        for (int i=keysOfDecideValueArr->count()-1; i>=length-1; i--) {
            if ((((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(1)))->getCString())>0
                &&
                (((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfDecideValueArr->objectAtIndex(i-length+1)))->getCString())==0) {
                {
                    for (int j=0; j<keysOfnowScreenShowPokerArr->count()/3; j++) {
                        decideValueArr->insertObject(firstThreeValueArr->objectAtIndex(firstThreeValueArr->count()-1), i+1);
                        keysOfDecideValueArr->insertObject(keysOfFirstThreeValueArr->objectAtIndex(keysOfFirstThreeValueArr->count()-1),i+1);
                    }
                    
                    saveEligibilityPokersAndRelevantKeys(
                                                         i-length+1,
                                                         length+length/3,
                                                         nextTimeShouldShowPokerArr,
                                                         keysOfnextTimeShouldShowPokerArr,
                                                         decideValueArr,
                                                         keysOfDecideValueArr);
                    CCLOG("三带一true");
                    mHaveSuitable=true;
                    break;
                }
            }
            
        }
    }
    CC_SAFE_DELETE(newRequireConsiderArr);
    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
    CC_SAFE_DELETE(firstThreeValueArr);
    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
    CC_SAFE_DELETE(secondThreeValueArr);
    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
    CC_SAFE_DELETE(thirdThreeValueArr);
    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
    CC_SAFE_DELETE(decideValueArr);
    CC_SAFE_DELETE(keysOfDecideValueArr);
    return mHaveSuitable;
    
    
}
#pragma mark------判断是否有压得住桌面上的三带二----
bool DecidePoker:: planeWithDoubleWings(int length,
                                      CCArray * keysOfnowScreenShowPokerArr,
                                      CCArray * nextTimeShouldShowPokerArr,
                                      CCArray * keysOfnextTimeShouldShowPokerArr,
                                      CCArray * requireConsiderWhetherOutOfArr,
                                      CCArray * keysOfrequireConsiderWhetherOutOfArr,
                                      int miPokerTypeID)
{
    bool mHaveSuitable=false;
    //成功判断
    CCLOG("判断是否压得住三带二");
    CCArray * newRequireConsiderArr=new CCArray();    //copy
    CCArray * keysOfNewRequireConsiderArr=new CCArray();//copy
    for (int i=0; i<requireConsiderWhetherOutOfArr->count(); i++) {
        newRequireConsiderArr->addObject(requireConsiderWhetherOutOfArr->objectAtIndex(i));
        keysOfNewRequireConsiderArr->addObject(keysOfrequireConsiderWhetherOutOfArr->objectAtIndex(i));
    }
    
    
    CCArray * firstThreeValueArr=new CCArray();
    CCArray * keysOfFirstThreeValueArr=new CCArray();
    
    
    CCArray * secondThreeValueArr=new CCArray();
    CCArray * keysOfSecondThreeValueArr=new CCArray();
    
    CCArray * thirdThreeValueArr=new CCArray();
    CCArray * keysOfThirdThreeValueArr=new CCArray();
    
    
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfFirstThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            CCLog("first%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
            firstThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfFirstThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //first singe key and value
        }
    }
    newRequireConsiderArr->removeObjectsInArray(firstThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfFirstThreeValueArr);
    //在copy的数组中移除single
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfSecondThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            CCLog("second%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
            secondThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfSecondThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时secondThreeValueArr keysOfSecondThreeValueArr包含的value
            //和key在原数组中至少有两个
        }
    }
    newRequireConsiderArr->removeObjectsInArray(secondThreeValueArr);
    keysOfNewRequireConsiderArr->removeObjectsInArray(keysOfSecondThreeValueArr);
    for (int i=0; i<keysOfNewRequireConsiderArr->count(); i++) {
        if (!(keysOfThirdThreeValueArr->containsObject(keysOfNewRequireConsiderArr->objectAtIndex(i)))) {
            CCLog("third%s",((CCString *)(keysOfNewRequireConsiderArr->objectAtIndex(i)))->getCString());
            thirdThreeValueArr->addObject(newRequireConsiderArr->objectAtIndex(i));
            keysOfThirdThreeValueArr->addObject(keysOfNewRequireConsiderArr->objectAtIndex(i));
            //此时thirdThreeValueArr keysOfThirdThreeValueArr包含的value
            //和key在原数组中至少有三个
        }
    }
    
    CCArray * decideValueArr=new CCArray();
    CCArray * keysOfDecideValueArr=new CCArray();
    decideValueArr->addObjectsFromArray(thirdThreeValueArr);
    keysOfDecideValueArr->addObjectsFromArray(keysOfThirdThreeValueArr);
    
    for (int i=0; i<keysOfFirstThreeValueArr->count(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr->count();j++){
            if (((CCString *)(keysOfThirdThreeValueArr->objectAtIndex(j)))->isEqual((CCString *)(keysOfFirstThreeValueArr->objectAtIndex(i)))) {
                decideValueArr->addObject(firstThreeValueArr->objectAtIndex(i));
                keysOfDecideValueArr->addObject(keysOfFirstThreeValueArr->objectAtIndex(i));
            }
        }
    }
    //此时decideValueArr中存放的是对子
    for (int i=0; i<keysOfSecondThreeValueArr->count(); i++) {
        for(int j=0;j<keysOfThirdThreeValueArr->count();j++){
            if (((CCString *)(keysOfThirdThreeValueArr->objectAtIndex(j)))->isEqual((CCString *)(keysOfSecondThreeValueArr->objectAtIndex(i)))) {
                decideValueArr->addObject(secondThreeValueArr->objectAtIndex(i));
                keysOfDecideValueArr->addObject(keysOfSecondThreeValueArr->objectAtIndex(i));
            }
        }
    }
    //此时decideValueArr中存放的是三个
    CCLog("decide third =%d",decideValueArr->count());
    
    
    CCArray * temArr=new CCArray();
    CCArray * keysOfTemArr=new CCArray();
    
    for (int i=0; i<keysOfThirdThreeValueArr->count(); i++){
        for (int j=0; j<keysOfSecondThreeValueArr->count(); j++) {
            if (((CCString *)(keysOfThirdThreeValueArr->objectAtIndex(i)))->isEqual((CCString *)(keysOfSecondThreeValueArr->objectAtIndex(j)))){
                temArr->addObject(secondThreeValueArr->objectAtIndex(j));
                keysOfTemArr->addObject(keysOfSecondThreeValueArr->objectAtIndex(j));
            }
        }
    }
    secondThreeValueArr->removeObjectsInArray(temArr);
    keysOfSecondThreeValueArr->removeObjectsInArray(keysOfTemArr);
    //此时secondThreeValueArr keysOfSecondThreeValueArr保存的时double
    int countSec=secondThreeValueArr->count();
    CCLog("single second%d",countSec);
    for (int i=0; i<keysOfFirstThreeValueArr->count(); i++) {
        for(int j=0;j<countSec;j++){
            if (((CCString *)(keysOfSecondThreeValueArr->objectAtIndex(j)))->isEqual((CCString *)(keysOfFirstThreeValueArr->objectAtIndex(i)))) {
                secondThreeValueArr->addObject(firstThreeValueArr->objectAtIndex(i));
                keysOfSecondThreeValueArr->addObject(keysOfFirstThreeValueArr->objectAtIndex(i));
            }
        }
    }
    //此时secondThreeValueArr中存放的仅是对子
    CCLog("only second =%d",secondThreeValueArr->count());
    
    //在此处重新排序方便显示
    if (secondThreeValueArr->count()>0&&decideValueArr->count()>0) {
        sortedForArray(secondThreeValueArr, keysOfSecondThreeValueArr);
        sortedForArray(decideValueArr, keysOfDecideValueArr);
    }
    if (keysOfDecideValueArr->count()>=length&&keysOfSecondThreeValueArr->count()>0) {
        for (int i=keysOfDecideValueArr->count()-1; i>=length-1; i--) {
            if ((((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfnowScreenShowPokerArr->objectAtIndex(2)))->getCString())>0
                &&
                (((CCString *)(keysOfDecideValueArr->objectAtIndex(i))))->compare(((CCString *)(keysOfDecideValueArr->objectAtIndex(i-length+1)))->getCString())==0) {
                
                for (int j=0; j<2*length/3; j++) {
                    decideValueArr->insertObject(secondThreeValueArr->objectAtIndex(j), i+1);
                    keysOfDecideValueArr->insertObject(keysOfSecondThreeValueArr->objectAtIndex(j), i+1);
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
    CC_SAFE_DELETE(newRequireConsiderArr);
    CC_SAFE_DELETE(keysOfNewRequireConsiderArr);
    CC_SAFE_DELETE(firstThreeValueArr);
    CC_SAFE_DELETE(keysOfFirstThreeValueArr);
    CC_SAFE_DELETE(secondThreeValueArr);
    CC_SAFE_DELETE(keysOfSecondThreeValueArr);
    CC_SAFE_DELETE(thirdThreeValueArr);
    CC_SAFE_DELETE(keysOfThirdThreeValueArr);
    CC_SAFE_DELETE(decideValueArr);
    CC_SAFE_DELETE(keysOfDecideValueArr);
    CC_SAFE_DELETE(temArr);
    CC_SAFE_DELETE(keysOfTemArr);
    return mHaveSuitable;
    
    
}
void DecidePoker::sortedForArray(CCArray * valueArr,CCArray * keyArr)
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
