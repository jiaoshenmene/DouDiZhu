//
//  StartGame.cpp
//  MyGame
//
//  Created by 秦晶 on 14-1-3.
//
//
#include "StartGame.h"
#include "TypeEnmu.h"
#include "DecidePoker.h"
#include "GameRules.h"
#include "PokerInit.h"
#include "GameSetting.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* StartGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartGame *layer = StartGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    layer->setTouchEnabled(true);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          CC_CALLBACK_0(StartGame::menuCloseCallback, this));
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    
    CCMenuItemFont * start=CCMenuItemFont::create("YES",CC_CALLBACK_0(StartGame::outOfTheCards, this));
    start->setPosition( ccp(150, 150) );
    pMenu->addChild(start,1);
    //出牌按钮
    CCMenuItemFont * pass=CCMenuItemFont::create("NO",CC_CALLBACK_0(StartGame::passThisRecycle, this));
    pass->setPosition( ccp(220, 150) );
    pMenu->addChild(pass,1);
    //出牌按钮

    CCSprite * backGround=CCSprite::create("backgroundimage.png");
    backGround->setRotation(-90);
    backGround->setPosition(ccp(240, 160));
//    this->addChild(backGround);
    //添加背景图
    CCSprite * timeBackGround=CCSprite::create("Circle.png");
    timeBackGround->setPosition(ccp(260, 300));
    this->addChild(timeBackGround);
    mpTimerCountDown=CCLabelTTF::create("", "Thonburi", 20);
    mpTimerCountDown->setPosition(ccp(260, 300));
    this->addChild(mpTimerCountDown);
    //person
    
    CCSprite * timeBackGroundOfNext=CCSprite::create("Circle.png");
    timeBackGroundOfNext->setPosition(ccp(400, 160));
    this->addChild(timeBackGroundOfNext);
    mpNextComputertimerCountDown=CCLabelTTF::create("", "Thonburi", 20);
    mpNextComputertimerCountDown->setPosition(ccp(400, 160));
    this->addChild(mpNextComputertimerCountDown);

    //next
    
    CCSprite * timeBackGroundOfUp=CCSprite::create("Circle.png");
    timeBackGroundOfUp->setPosition(ccp(50, 160));
    this->addChild(timeBackGroundOfUp);
    mpUpComputertimerCountDown=CCLabelTTF::create("", "Thonburi", 20);
    mpUpComputertimerCountDown->setPosition(ccp(50, 160));
    this->addChild(mpUpComputertimerCountDown);
    //up
    this->initArraysAndRootDic();//初始化
    srand(time(NULL));
    
    return true;
}
#pragma mark ------洗牌------
void StartGame::adjustPokerOrder()
{
    int i=0;//记录发了多少张
    while (1) {
        int keyRand=rand()%15;
        int valueRand;
        //随机数值为多少的牌
        if (keyRand>12) {
         valueRand=0;
        //大小王只有一张
        }
        else{
         valueRand=rand()%4;
        //1-k各有四张
        }
        CCString * getKeyByKeyRand=(CCString *)mpRootKeys->objectAtIndex(keyRand);
        //随机的key
        CCArray * getArrByValueRand=((CCArray *)(mpRootDic->objectForKey(getKeyByKeyRand->getCString())));
        //随机的数组
        CCSprite * sp=(CCSprite *)(getArrByValueRand->objectAtIndex(valueRand));
        //随机的牌
        if (!mpArrByRand->containsObject(sp)) {
            mpArrByRand->addObject(sp);
            //保存随机后的精灵
            mpKeyArrByRand->addObject(getKeyByKeyRand);
            //保存随机后的精灵对应的key
            i++;
        }
        if (i>=POKERS_COUNT) {
            //牌的顺序随机完成，跳出循环
            break;
        }
    }
    sendPokerOutEveryPlayer();
}

#pragma mark ------发牌-------
void StartGame::sendPokerOutEveryPlayer()
{
    for (int i=0; i<POKERS_COUNT/3-1; i++) {
        mpComputerUpArr->addObject(mpArrByRand->objectAtIndex(i));
        mpKeysOfcomputerUpArr->addObject(mpKeyArrByRand->objectAtIndex(i));
        //储存玩家上家的牌及对应的key
    }
    
    for (int i=POKERS_COUNT/3-1; i<2*POKERS_COUNT/3-2; i++) {
        mpPersonArr->addObject(mpArrByRand->objectAtIndex(i));
        mpKeysOfpersonArr->addObject(mpKeyArrByRand->objectAtIndex(i));
         //储存玩家的牌及对应的key
    }
    for (int i=2*POKERS_COUNT/3-2; i<POKERS_COUNT-3; i++) {
        mpComputerNextArr->addObject(mpArrByRand->objectAtIndex(i));
        mpKeysOfcomputerNextArr->addObject(mpKeyArrByRand->objectAtIndex(i));
         //储存玩家吓家的牌及对应的key
    }
    
    for (int i=POKERS_COUNT-3; i<POKERS_COUNT; i++) {
        mpLastThreeArr->addObject(mpArrByRand->objectAtIndex(i));
        mpKeysOflastThreeArr->addObject(mpKeyArrByRand->objectAtIndex(i));
         //储存底牌及对应的key
    }
    int lastThreePokerOwner=rand()%3;
    //随机一个地主
    if (lastThreePokerOwner==0) {
        
        mbUpComputerIsLandlord=true;
        mbNextComputerISLandlord=false;
        mbPersonIsLandlord=false;
        
        mpUpComIdentityLabel->setString("地主");
        mpNextComIdentityLabel->setString("平民");
        mpPersonIdentityLabel->setString("平民");
        
        mpComputerUpArr->addObjectsFromArray(mpLastThreeArr);
        mpKeysOfcomputerUpArr->addObjectsFromArray(mpKeysOflastThreeArr);
    }
    else if(lastThreePokerOwner==1)
    {
        mbUpComputerIsLandlord=false;
        mbNextComputerISLandlord=false;
        mbPersonIsLandlord=true;
        
        mpUpComIdentityLabel->setString("平民");
        mpNextComIdentityLabel->setString("平民");
        mpPersonIdentityLabel->setString("地主");
        
        mpPersonArr->addObjectsFromArray(mpLastThreeArr);
        mpKeysOfpersonArr->addObjectsFromArray(mpKeysOflastThreeArr);
    }
    else
    {
        mbUpComputerIsLandlord=false;
        mbNextComputerISLandlord=true;
        mbPersonIsLandlord=false;
        
        mpUpComIdentityLabel->setString("平民");
        mpNextComIdentityLabel->setString("地主");
        mpPersonIdentityLabel->setString("平民");
        
        mpComputerNextArr->addObjectsFromArray(mpLastThreeArr);
        mpKeysOfcomputerNextArr->addObjectsFromArray(mpKeysOflastThreeArr);
    }
    sortedForArray(mpComputerUpArr, mpKeysOfcomputerUpArr);
    sortedForArray(mpPersonArr, mpKeysOfpersonArr);
    sortedForArray(mpComputerNextArr, mpKeysOfcomputerNextArr);
//    CCLog("发牌");
//    CCLog("upArr count =%d,upKey count = %d",computerUpArr->count(),keysOfcomputerUpArr->count());
//    CCLog("perArr count =%d,perKey count = %d",personArr->count(),keysOfpersonArr->count());
//    CCLog("nextArr count =%d,nextKey count = %d",computerNextArr->count(),keysOfcomputerNextArr->count());
//    CCLog("lastArr count =%d,lastKey count = %d",lastThreeArr->count(),keysOflastThreeArr->count());

    displayPersonPoker();
    
    scheduleUpdate();
}
#pragma mark ------判断输赢------
void StartGame::update(float)
{

    if (mpComputerUpArr->count()==0) {
        mbGameIsOver=true;
        mpGameOverLabel->setString("不要灰心再来一局");
        mpGameOverLabel->setPosition(ccp(240, 160));
        mpGameAgainLabel->setPosition(ccp(240, 230));
        refreshGameOverScreenDisplay(PERSON_LOST_THE_GAME);
        unscheduleInStartGameAllUpdate();
    }
    
    if (mpPersonArr->count()==0) {
        mbGameIsOver=true;
        mpGameOverLabel->setString("恭喜，您赢啦！");
        mpGameOverLabel->setPosition(ccp(240, 160));
        mpGameAgainLabel->setPosition(ccp(240, 230));
        refreshGameOverScreenDisplay(PERSON_WIN_THE_GAME);
        unscheduleInStartGameAllUpdate();
    }
   
    if (mpComputerNextArr->count()==0) {
        mbGameIsOver=true;
        mpGameOverLabel->setString("不要灰心再来一局");
        mpGameOverLabel->setPosition(ccp(240, 160));
        mpGameAgainLabel->setPosition(ccp(240, 230));
        refreshGameOverScreenDisplay(PERSON_LOST_THE_GAME);
        unscheduleInStartGameAllUpdate();
    }
    
}

#pragma mark------游戏结束关闭所有的定时器
void StartGame::unscheduleInStartGameAllUpdate()
{
    unscheduleUpdate();
    unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
    unschedule(schedule_selector(StartGame::nextConsiderTimeCountDown));
    unschedule(schedule_selector(StartGame::upConsiderTimeCountDown));
    
    unschedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider));
    unschedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider));
}

#pragma mark ------游戏结束之后显示每个人拥有的金币------
void StartGame::refreshGameOverScreenDisplay(int decide)
{
    int perValue=CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfPerson");
    int nextComValue=CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfNextComputer");
    int upComValue=CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfUpComputer");

    CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfPerson", perValue+2*miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfNextComputer", nextComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfUpComputer", upComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
    CCUserDefault::sharedUserDefault()->flush();//写入文件
    
    mpPersonHaveCoinsLabel->setString((CCString::createWithFormat("%d",perValue+2*miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS))->getCString());
    mpNextComHaveCoinsLabel->setString((CCString::createWithFormat("%d",nextComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS))->getCString());
    mpUpComHaveCoinsLabel->setString((CCString::createWithFormat("%d",upComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS))->getCString());
    
}
#pragma mark ------显示玩家手中的牌------
void StartGame::displayPersonPoker()
{
    mfWidth=POKER_WIDTH/mpPersonArr->count();
    for (int i=0; i<mpPersonArr->count(); i++) {
        CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
        sp->setAnchorPoint(ccp(0, 0));
        sp->setPosition(ccp(60+i*mfWidth,10));
        sp->setTag(TAG+i);
        this->addChild(sp);
    }
//    if (mbPersonIsLandlord) {
        schedule(schedule_selector(StartGame::personConsiderTimeCountDown), 0.01);
//    }
//    else
//        if (mpNextComIdentityLabel) {
//             nextComputeroutOfTheCards();//下家是地主 下家第一个出牌
//        }
//        else
//        {
//            upComputeroutOfTheCards();//上家是地主 上家第一个出牌
//        }
    //牌显示后开始倒计时
}

#pragma mark ------玩家考虑时间倒计时判断---
float personConsiderTime=0;
int displaytime=0;
void StartGame::personConsiderTimeCountDown(float considerTime)
{
    personConsiderTime+=considerTime;
    if (personConsiderTime>=1) {
        displaytime++;
        CCString * str=CCString::createWithFormat("%d",30-displaytime);
        mpTimerCountDown->setString(str->getCString());
        personConsiderTime=0;
        mbPersonTimeOutOfCards=false;
        if (displaytime>=30) {
            mbPersonTimeOutOfCards=true;//超出限制时间
            mbCanOrCannotOutOfCards=false;//超出限制时间不可出牌
            displaytime=0;//倒计时基数归零
            CCString * str=CCString::create("");
            mpTimerCountDown->setString(str->getCString());//清空显示的倒计时器
            personConsiderTimeRunOutAndRandOneOfPersonPokers();
            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
            //关闭倒计时
            
        }
    }

}
#pragma mark ------发到玩家手中的牌排序-----
void StartGame::sortedForArray(CCArray * valueArr,CCArray * keyArr)
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

#pragma mark ------符合条件的出牌------
void StartGame::outOfTheCards()
{
    if(!mbGameIsOver){
    for (int i=0; i<mpUpComputerSelectArr->count(); i++) {
        CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
        sp->removeFromParent();
    }
    if (mpSelectKeysArr->count()==0) {
        return;
    }

    sortedForArray(mpSelectValueArr, mpSelectKeysArr);  //选中的的牌排序
    //    本轮上家电脑有出牌
    if (upcomputerIsOutOfCards) {
        if (DecidePoker::sharedDecidePoker()->decidePersonMoreBigSHowPoker(mpSelectKeysArr, mpKeysOfupComputerSelectArr)) {
            CCLog("more big than up");
            for (int i=0; i<mpSelectValueArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setPosition(ccp(160+mfWidth*i, 150));
            }
            personIsOutOfCards=true;
            //玩家本轮出牌
            mbPersonFirstIsOutOfCards=false;
            mpPersonArr->removeObjectsInArray(mpSelectValueArr);
            //从玩家手中删除出过的牌
            mpKeysOfpersonArr->removeObjectsInArray(mpSelectKeysArr);
            //从玩家手中删除出过的牌及对应的key
            
            mpUpComputerSelectArr->removeAllObjects();
            mpKeysOfupComputerSelectArr->removeAllObjects();
            //清空上家电脑选中的牌
            
            
            for (int i=0; i<mpPersonArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setTag(TAG+i);
                sp->setPosition(ccp(240-mfWidth*(mpPersonArr->count()/2)+mfWidth*i, 10));
            }
            //玩家出牌后调整桌面牌的位置
            
            CCString * str=CCString::create("@");
            for(int i=0;i<20;i++)
            {
                mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str);
                
            }
            
            CCString * str_=CCString::createWithFormat("%d",30);
            mpNextComputertimerCountDown->setString(str_->getCString());
            schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
            schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
            CCString * strPer=CCString::create("");
            mpTimerCountDown->setString(strPer->getCString());//清空显示的倒计时器
            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
        }
        else
        {
            CCLOG("你选的牌不符合规则");
        }
        if (mbPersonTimeOutOfCards) {
            passThisRecycle();//考虑超时
        }
    }

    //本轮上家电脑没有出牌 但是下家出牌了
    if (!upcomputerIsOutOfCards&&nextcomputerIsOutOfCards) {
        if (DecidePoker::sharedDecidePoker()->decidePersonMoreBigSHowPoker(mpSelectKeysArr, mpKeysOfnextComputerSelectArr)) {
            for (int i=0; i<mpSelectValueArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setPosition(ccp(160+mfWidth*i, 150));
            }
            personIsOutOfCards=true;
            mbPersonFirstIsOutOfCards=false;
            //玩家本轮出牌
            mpPersonArr->removeObjectsInArray(mpSelectValueArr);
            //从玩家手中删除出过的牌
            mpKeysOfpersonArr->removeObjectsInArray(mpSelectKeysArr);
            //从玩家手中删除出过的牌及对应的key
            
            mpNextComputerSelectArr->removeAllObjects();
            mpKeysOfnextComputerSelectArr->removeAllObjects();
            //清空下家电脑选中的牌
            
            
            for (int i=0; i<mpPersonArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setTag(TAG+i);
                sp->setPosition(ccp(240-mfWidth*(mpPersonArr->count())/2+mfWidth*i, 10));
            }
            //玩家出牌后调整桌面牌的位置
            
            CCString * str=CCString::create("@");
            for(int i=0;i<20;i++)
            {
                mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str);
                
            }

            
            CCString * str_=CCString::createWithFormat("%d",30);
            mpNextComputertimerCountDown->setString(str_->getCString());
            schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
            schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
            CCString * strPer=CCString::create("");
            mpTimerCountDown->setString(strPer->getCString());//清空显示的倒计时器
            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
        }
        else
        {
            CCLOG("你选的牌不符合规则");
           
        }
        if (mbPersonTimeOutOfCards) {
            passThisRecycle();//考虑超时
        }

    }
    
        
    //    本轮上下家电脑都没有出牌 轮到玩家出牌
    if (!upcomputerIsOutOfCards&&!nextcomputerIsOutOfCards) {
        miPokerTypeID=GameRules::sharedGameRules()->decideSelectedPokerIfConformToRules(mpSelectValueArr, mpSelectKeysArr);
        if (miPokerTypeID&&(!mbPersonTimeOutOfCards)) {
        
        CCString * str=CCString::create("");
        mpTimerCountDown->setString(str->getCString());//清空显示的倒计时器
        unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
        
        for (int i=0; i<mpSelectValueArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
            sp->setAnchorPoint(ccp(0, 0));
            sp->setPosition(ccp(160+i*mfWidth, 150));
        }

        personIsOutOfCards=true;
        //玩家本轮出牌
        mbPersonFirstIsOutOfCards=false;
        mpPersonArr->removeObjectsInArray(mpSelectValueArr);
        //从玩家手中删除出过的牌
        mpKeysOfpersonArr->removeObjectsInArray(mpSelectKeysArr);
         //从玩家手中删除出过的牌及对应的key
        
        
        for (int i=0; i<mpPersonArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
            sp->setAnchorPoint(ccp(0, 0));
            sp->setTag(TAG+i);
            sp->setPosition(ccp(240-mfWidth*(mpPersonArr->count())/2+mfWidth*i, 10));
        }
        //玩家出牌后调整桌面牌的位置
            
        CCString * str1=CCString::create("@");
        for(int i=0;i<20;i++)
        {
            mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str1);
            
        }
            
        CCString * str_=CCString::createWithFormat("%d",30);
        mpNextComputertimerCountDown->setString(str_->getCString());
        schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
        schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
        CCString * strPer=CCString::create("");
        mpTimerCountDown->setString(strPer->getCString());//清空显示的倒计时器
        unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
    }
    
    }
    }
}
#pragma mark ------只应该玩家出牌时玩家托管-----
void StartGame::personConsiderTimeRunOutAndRandOneOfPersonPokers()
{
    if(!mbGameIsOver){
    if (!upcomputerIsOutOfCards&&!nextcomputerIsOutOfCards) {
        for (int i=0; i<mpSelectKeysArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
            sp->removeFromParent();
            //玩家出牌后其他人均为出牌 自己移除桌面上的精灵
        }
        mpSelectValueArr->removeAllObjects();
        mpSelectKeysArr->removeAllObjects();
        
        CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(mpPersonArr->count()-1);
        sp->setAnchorPoint(ccp(0, 0));
        sp->setPosition(ccp(240, 150));
        //即托管状态
        mpSelectValueArr->addObject(sp);
        mpSelectKeysArr->addObject(mpKeysOfpersonArr->objectAtIndex(mpKeysOfpersonArr->count()-1));
        
        mpPersonArr->removeObject(sp);
        mpKeysOfpersonArr->removeObject(mpKeysOfpersonArr->objectAtIndex(mpKeysOfpersonArr->count()-1));
        //移除显示的牌
        
        personIsOutOfCards=true;
        //玩家本轮有出牌
        
        for (int i=0; i<mpPersonArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
            sp->setAnchorPoint(ccp(0, 0));
            sp->setTag(TAG+i);
            sp->setPosition(ccp(160+mfWidth*i, 10));
        }
        //玩家出牌后调整桌面牌的位置
        CCString * str_=CCString::createWithFormat("%d",30);
        mpNextComputertimerCountDown->setString(str_->getCString());
        schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
        
        schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
        CCLOG("玩家托管");
    }
    else
    {
        passThisRecycle();
    }
    }
}

#pragma mark ------玩家过牌-----
void StartGame::passThisRecycle()
{
    if(!mbGameIsOver){
    if(!mbPersonFirstIsOutOfCards&&(nextcomputerIsOutOfCards||upcomputerIsOutOfCards)){
    CCString * str=CCString::create("");
    mpTimerCountDown->setString(str->getCString());//清空显示的倒计时器
    unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
    //玩家计时器清零
    personIsOutOfCards=false;
    //玩家本轮没有出牌
    mpPersonLabel->setString("不出");
    mpPersonLabel->setPosition(ccp(320, 160));

    CCString * str_=CCString::createWithFormat("%d",30);
    mpNextComputertimerCountDown->setString(str_->getCString());
    schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
    
    schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
    }
    }
}

#pragma mark ------玩家出牌几秒后下家电脑考虑出牌---
float sumTime=0;
void StartGame::personOutOfCardsManyTimeNextStartConsider(float t)
{
    sumTime+=t;
   
    mpComputerNextLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);

    if (sumTime>=PERSON_INTERVAL_TIME_TO_NEXT_COMPUTER) {
        nextComputeroutOfTheCards();
        //下家电脑开始考虑出牌
        sumTime=0;
        unschedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider));
    }
}
#pragma mark ------下家电脑考虑时间倒计时判断---
float nextComputerConsiderTime=0;
int nextdisplaytime=0;
void StartGame::nextConsiderTimeCountDown(float considerTime)
{
    nextComputerConsiderTime+=considerTime;
    if (nextComputerConsiderTime>=1) {
        nextdisplaytime++;
        CCString * str=CCString::createWithFormat("%d",30-nextdisplaytime);
        mpNextComputertimerCountDown->setString(str->getCString());
        nextComputerConsiderTime=0;
        if (nextdisplaytime>=PERSON_INTERVAL_TIME_TO_NEXT_COMPUTER) {
            nextdisplaytime=0;//倒计时基数归零
            CCString * str=CCString::create("");
            mpNextComputertimerCountDown->setString(str->getCString());//清空显示的倒计时器
            unschedule(schedule_selector(StartGame::nextConsiderTimeCountDown));
            //关闭倒计时
            
        }
    }
    
}

#pragma mark ------下家电脑出牌-----
void StartGame::nextComputeroutOfTheCards()
{
    if(!mbGameIsOver){
    if(personIsOutOfCards)//本轮玩家出牌了
    {
        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpSelectValueArr, mpSelectKeysArr, mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpComputerNextArr, mpKeysOfcomputerNextArr,miPokerTypeID)) {
        for (int i=0; i<mpSelectKeysArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
            sp->removeFromParent();
        }

        for (int i=0; i<mpNextComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpNextComputerSelectArr->objectAtIndex(i);
            sp->setAnchorPoint(ccp(0, 0));
            sp->setPosition(ccp(200+i*20, 150));
            this->addChild(sp);
        };
        nextcomputerIsOutOfCards=true;
        //本轮下家电脑有出牌
        mpComputerNextArr->removeObjectsInArray(mpNextComputerSelectArr);
        //从下家电脑手中删除出过的牌
        mpKeysOfcomputerNextArr->removeObjectsInArray(mpKeysOfnextComputerSelectArr);
        //从下家电脑手中删除出过的牌
        mpSelectValueArr->removeAllObjects();
            //出完牌记录选中person牌的数组清零
        mpSelectKeysArr->removeAllObjects();
            //出完牌记录选中person牌的数组及对应的key清零
    }else
    {
        nextcomputerIsOutOfCards=false;
        //本轮下家电脑有出牌
        mpComputerNextLabel->setString("不出");
        mpComputerNextLabel->setPosition(ccp(400, 200));
    }
    }
    
    if(!personIsOutOfCards&&upcomputerIsOutOfCards)//本轮玩家没出牌但玩家上家出牌了
    {
        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpComputerNextArr, mpKeysOfcomputerNextArr,miPokerTypeID)) {
            for (int i=0; i<mpUpComputerSelectArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
                sp->removeFromParent();
            }
            
            for (int i=0; i<mpNextComputerSelectArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpNextComputerSelectArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setPosition(ccp(200+i*20, 150));
                this->addChild(sp);
            };
            
            nextcomputerIsOutOfCards=true;
            //本轮下家电脑有出牌
            mpComputerNextArr->removeObjectsInArray(mpNextComputerSelectArr);
            //从下家电脑手中删除出过的牌
            mpKeysOfcomputerNextArr->removeObjectsInArray(mpKeysOfnextComputerSelectArr);
            //从下家电脑手中删除出过的牌
            
            mpUpComputerSelectArr->removeAllObjects();
            //出完牌记录选中upcomputer牌的数组清零
            mpKeysOfupComputerSelectArr->removeAllObjects();
            //出完牌记录选中upcomputer牌的数组及对应的key清零
        }else
        {
            nextcomputerIsOutOfCards=false;
            //本轮下家电脑没有出牌
            mpComputerNextLabel->setString("不出");
            mpComputerNextLabel->setPosition(ccp(400, 200));
        }
    }
    if(!personIsOutOfCards&&!upcomputerIsOutOfCards)//本轮玩家和玩家上家都没有出牌
    {
        
        for (int i=0; i<mpKeysOfnextComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpNextComputerSelectArr->objectAtIndex(i);
            sp->removeFromParent();
            //下家出牌后无人出牌 自己移除桌面上的精灵
        }
        
        mpNextComputerSelectArr->removeAllObjects();
        mpKeysOfnextComputerSelectArr->removeAllObjects();
        //存放选中的精灵的数组清空
        
        nextcomputerIsOutOfCards=true;
        //本轮下家电脑有出牌
        CCSprite * sp=(CCSprite *)mpComputerNextArr->objectAtIndex(mpComputerNextArr->count()-1);
        sp->setAnchorPoint(ccp(0, 0));
        sp->setPosition(ccp(200, 150));
        this->addChild(sp);
        
        mpNextComputerSelectArr->addObject(sp);
        mpKeysOfnextComputerSelectArr->addObject(mpKeysOfcomputerNextArr->objectAtIndex(mpKeysOfcomputerNextArr->count()-1));
        //添加下家电脑选中的牌
        mpComputerNextArr->removeObject(sp);
        mpKeysOfcomputerNextArr->removeObject(mpKeysOfcomputerNextArr->objectAtIndex(mpKeysOfcomputerNextArr->count()-1));
        
        clearSelectedPokersType();
        //清空出牌类型
    }
    schedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider), 0.01);
    //下家电脑出完牌几秒后上家电脑出牌
    CCString * str=CCString::createWithFormat("%d",30);
    mpUpComputertimerCountDown->setString(str->getCString());
    schedule(schedule_selector(StartGame::upConsiderTimeCountDown), 0.01);
    }
}
#pragma mark ------next出牌几秒后up电脑考虑出牌-----
float nextToUpSumTime=0;
void StartGame::nextComputerOutOfCardsManyTimeUpStartConsider(float t)
{
    mpComputerUpLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);
    nextToUpSumTime+=t;
    if (nextToUpSumTime>=NEXT_INTERVAL_TIME_TO_UP_COMPUTER) {
        upComputeroutOfTheCards();
        nextToUpSumTime=0;
        unschedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider));
    }

}

#pragma mark ------上家电脑考虑时间倒计时判断---
float upComputerConsiderTime=0;
int updisplaytime=0;
void StartGame::upConsiderTimeCountDown(float considerTime)
{
    upComputerConsiderTime+=considerTime;
    if (upComputerConsiderTime>=1) {
        updisplaytime++;
        CCString * str=CCString::createWithFormat("%d",30-updisplaytime);
        mpUpComputertimerCountDown->setString(str->getCString());
        upComputerConsiderTime=0;
        if (updisplaytime>=NEXT_INTERVAL_TIME_TO_UP_COMPUTER) {
            updisplaytime=0;//倒计时基数归零
            CCString * str=CCString::create("");
            mpUpComputertimerCountDown->setString(str->getCString());//清空显示的倒计时器
            unschedule(schedule_selector(StartGame::upConsiderTimeCountDown));
            //关闭倒计时
            
        }
    }
    
}


#pragma mark ------上家电脑出牌-----
void StartGame::upComputeroutOfTheCards()
{
    if(!mbGameIsOver){
       //本轮下家电脑出牌了
    if (nextcomputerIsOutOfCards) {
    if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpComputerUpArr, mpKeysOfcomputerUpArr,miPokerTypeID)) {
        for (int i=0; i<mpNextComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpNextComputerSelectArr->objectAtIndex(i);
            sp->removeFromParent();
        }
        
        for (int i=0; i<mpUpComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
            sp->setAnchorPoint(ccp(0, 0));
            sp->setPosition(ccp(200+i*20, 150));
            this->addChild(sp);
        };
        upcomputerIsOutOfCards=true;
        //本轮玩家电脑出牌了
        mpComputerUpArr->removeObjectsInArray(mpUpComputerSelectArr);
        mpKeysOfcomputerUpArr->removeObjectsInArray(mpKeysOfupComputerSelectArr);
        //上家电脑出过的牌从手中删除
        
        mpNextComputerSelectArr->removeAllObjects();
        //出完牌记录选中nextcomputer牌的数组清零
        mpKeysOfnextComputerSelectArr->removeAllObjects();
        //出完牌记录选中nextcomputer牌的数组及对应的key清零
    }else
    {
        upcomputerIsOutOfCards=false;
        //本轮玩家电脑没有出牌
        mpComputerUpLabel->setString("不出");
        mpComputerUpLabel->setPosition(ccp(100, 200));
        }
    }
    
    //本轮下家电脑没有出牌但是玩家出牌了
    if (!nextcomputerIsOutOfCards&&personIsOutOfCards) {
        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpSelectValueArr, mpSelectKeysArr, mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpComputerUpArr, mpKeysOfcomputerUpArr,miPokerTypeID)) {
            for (int i=0; i<mpSelectValueArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
                sp->removeFromParent();
            }
            
            for (int i=0; i<mpUpComputerSelectArr->count(); i++) {
                CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
                sp->setAnchorPoint(ccp(0, 0));
                sp->setPosition(ccp(200+i*20, 150));
                this->addChild(sp);
            };
            upcomputerIsOutOfCards=true;
            //本轮上家电脑出牌了
            mpComputerUpArr->removeObjectsInArray(mpUpComputerSelectArr);
            mpKeysOfcomputerUpArr->removeObjectsInArray(mpKeysOfupComputerSelectArr);
            //上家电脑出过的牌从手中删除
            
            mpSelectValueArr->removeAllObjects();
            //出完牌记录选中nextcomputer牌的数组清零
            mpSelectKeysArr->removeAllObjects();
            //出完牌记录选中nextcomputer牌的数组及对应的key清零
        }else
        {
            upcomputerIsOutOfCards=false;
            //本轮上家电脑没有出牌
            mpComputerUpLabel->setString("不出");
            mpComputerUpLabel->setPosition(ccp(100, 200));
            schedule(schedule_selector(StartGame::upclearPersonShowPokers),0.01);

        }
    }
    
    //玩家和下家电脑都没有出牌
    if(!personIsOutOfCards&&!nextcomputerIsOutOfCards)//本轮玩家和玩家上家都没有出牌
    {
        
        
        for (int i=0; i<mpKeysOfupComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
            sp->removeFromParent();
            //上家出牌后无人出牌 自己移除桌面上的精灵
        }
        mpUpComputerSelectArr->removeAllObjects();
        mpKeysOfupComputerSelectArr->removeAllObjects();
        
        nextcomputerIsOutOfCards=true;
        //本轮下家电脑有出牌
        CCSprite * sp=(CCSprite *)mpComputerUpArr->objectAtIndex(mpComputerUpArr->count()-1);
        sp->setAnchorPoint(ccp(0, 0));
        sp->setPosition(ccp(200, 150));
        this->addChild(sp);
        mpUpComputerSelectArr->addObject(sp);
        mpKeysOfupComputerSelectArr->addObject(mpKeysOfcomputerUpArr->objectAtIndex(mpKeysOfcomputerUpArr->count()-1));
        
        mpComputerUpArr->removeObject(sp);
        mpKeysOfcomputerUpArr->removeObject(mpKeysOfcomputerUpArr->objectAtIndex(mpKeysOfcomputerUpArr->count()-1));
    
        clearSelectedPokersType();
        //清空出牌类型
    }
    displaytime=0;//person倒计时基数归零
    schedule(schedule_selector(StartGame::personConsiderTimeCountDown), 0.01);
    clearSelectedPokersType();
    //清空出牌类型
    //上家电脑出完牌 玩家可以出牌
        mpPersonLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);
    
    }

}
#pragma mark ------如果本轮只有玩家出牌，上家过牌后，定时删除----
float upClearPerson=0;
void StartGame::upclearPersonShowPokers(float t)
{
    upClearPerson+=t;
    if (upClearPerson>=2) {
        for (int i=0; i<mpSelectValueArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
            sp->removeFromParent();
        }
        mpSelectValueArr->removeAllObjects();
        //出完牌记录选中nextcomputer牌的数组清零
        mpSelectKeysArr->removeAllObjects();
        //出完牌记录选中nextcomputer牌的数组及对应的key清零
        CCLOG("value c=%d,keys c=%d",mpSelectValueArr->count(),mpSelectKeysArr->count());
        upClearPerson=0;
        unschedule(schedule_selector(StartGame::upclearPersonShowPokers));
    }
}
#pragma mark ------清空出牌的类型----
void StartGame::clearSelectedPokersType()
{
    
}

#pragma mark ------初始化-----
void StartGame::initArraysAndRootDic()
{
    mpPokerWhetherMoveArr=CCArray::createWithCapacity(20);
    //记录每个排当前的状态
    mpPokerIsSlectArr=CCArray::createWithCapacity(20);
    //记录选中的牌
    mpSelectValueArr=new CCArray();
    mpSelectKeysArr=new CCArray();
    
    mpArrByRand=new CCArray();
    mpKeyArrByRand=new CCArray();
    //储存随机后的牌
    
    mpComputerUpArr=new CCArray();
    mpPersonArr=new CCArray();
    mpComputerNextArr=new CCArray();
    mpLastThreeArr=new CCArray();
    
    mpKeysOfcomputerUpArr=new CCArray();
    mpKeysOfpersonArr=new CCArray();
    mpKeysOfcomputerNextArr=new CCArray();
    mpKeysOflastThreeArr=new CCArray();
    //储存玩家，上家电脑，下家电脑，底牌及相应的key
    
    mpNextComputerSelectArr=new CCArray();
    mpKeysOfnextComputerSelectArr=new CCArray();
    //记录下家电脑应该出得牌
    
    mpUpComputerSelectArr=new CCArray();
    mpKeysOfupComputerSelectArr=new CCArray();
    //记录上家电脑应该出的牌
    
    mpNextComIdentityLabel=CCLabelTTF::create("","",START_GAME_LABEL_SIZE);
    mpUpComIdentityLabel=CCLabelTTF::create("","",START_GAME_LABEL_SIZE);
    mpPersonIdentityLabel=CCLabelTTF::create("","",START_GAME_LABEL_SIZE);
    
    mpNextComIdentityLabel->setPosition(ccp(430, 230));
    mpNextComIdentityLabel->setColor(ccc3(0, 255, 255));
    addChild(mpNextComIdentityLabel);
    
    mpUpComIdentityLabel->setPosition(ccp(50, 230));
    mpUpComIdentityLabel->setColor(ccc3(255, 255, 0));
    addChild(mpUpComIdentityLabel);
    
    mpPersonIdentityLabel->setPosition(ccp(450, 80));
    mpPersonIdentityLabel->setColor(ccc3(255, 0, 255));
    addChild(mpPersonIdentityLabel);
    //显示玩家的身份
    
    CCString * pNextStr=CCString::createWithFormat("%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfNextComputer"));
    CCString * pUpStr=CCString::createWithFormat("%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfUpComputer"));
    CCString * pPerStr=CCString::createWithFormat("%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinsOfPerson"));
    
    mpPersonHaveCoinsLabel=CCLabelTTF::create(pPerStr->getCString(), "", START_GAME_LABEL_SIZE);
    mpNextComHaveCoinsLabel=CCLabelTTF::create(pNextStr->getCString(),"", START_GAME_LABEL_SIZE);
    mpUpComHaveCoinsLabel=CCLabelTTF::create(pUpStr->getCString(), "", START_GAME_LABEL_SIZE);
    
    mpNextComHaveCoinsLabel->setPosition(ccp(430, 255));
    mpNextComHaveCoinsLabel->setColor(ccc3(0, 255, 255));
    addChild(mpNextComHaveCoinsLabel);
    
    mpUpComHaveCoinsLabel->setPosition(ccp(50, 255));
    mpUpComHaveCoinsLabel->setColor(ccc3(255, 255, 0));
    addChild(mpUpComHaveCoinsLabel);
    
    mpPersonHaveCoinsLabel->setPosition(ccp(450, 105));
    mpPersonHaveCoinsLabel->setColor(ccc3(255, 0, 255));
    addChild(mpPersonHaveCoinsLabel);
    //显示每个玩家拥有多少金币
    
    mpComputerNextLabel=CCLabelTTF::create("", "", 20);
    mpComputerNextLabel->setColor(ccc3(255, 255, 0));
    addChild(mpComputerNextLabel);
    
    mpComputerUpLabel=CCLabelTTF::create("", "", 20);
    mpComputerUpLabel->setColor(ccc3(255, 255, 0));
    addChild(mpComputerUpLabel);
    
    mpPersonLabel=CCLabelTTF::create("", "", 20);
    mpPersonLabel->setColor(ccc3(255, 255, 0));
    addChild(mpPersonLabel);
    //创建不出 label
    
    mpGameAgainLabel=CCLabelTTF::create("继续游戏", "", 30);
    mpGameAgainLabel->setPosition(ccp(OUT_OF_SCREEN_POINT_Y, OUT_OF_SCREEN_POINT_Y));
    mpGameAgainLabel->setColor(ccc3(255, 255, 0));
    addChild(mpGameAgainLabel,10);
    //创建继续游戏 label
    
    mpGameOverLabel=CCLabelTTF::create("", "", 30);
    mpGameOverLabel->setPosition(ccp(OUT_OF_SCREEN_POINT_Y, OUT_OF_SCREEN_POINT_Y));
    mpGameOverLabel->setColor(ccc3(0, 255, 255));
    addChild(mpGameOverLabel,10);
    //游戏结束显示胜负
    
    GameStart();//开始游戏
    
}

#pragma mark------开始游戏
void StartGame::GameStart()
{
    
    mpRootDic=PokerInit::sharedPokerInit()->initArraysAndRootDic();
    mpRootKeys=mpRootDic->allKeys();
    
    CCString * str=CCString::create("@");
    for(int i=0;i<20;i++)
    {
        mpPokerWhetherMoveArr->addObject(str);//初始化牌的状态
        mpPokerIsSlectArr->addObject(str);//初始化选中的牌
        
    }
    mpPokerWhetherMoveArr->retain();
    mpPokerIsSlectArr->retain();
    
    
    mbPersonTimeOutOfCards=false;
    //玩家考虑时间
    mbCanOrCannotOutOfCards=true;
    //初始时玩家是否可以出牌
    mbPersonFirstIsOutOfCards=true;
    //用来记录玩家以他为起点开始新的一轮的时候是否出牌
    personIsOutOfCards=false;
    //玩家是否出牌
    upcomputerIsOutOfCards=false;
    //up是否出牌
    nextcomputerIsOutOfCards=false;
    //next是否出牌
    mbPersonIsWin=false;
    mbUpComputerIsWin=false;
    mbNextComputerIsWin=false;
    //判断谁先出完牌
    miPokerTypeID=-1;
    miBaseTime=1;
    
    mbNextComputerISLandlord=false;
    mbPersonIsLandlord=false;
    mbUpComputerIsLandlord=false;
    mbGameIsOver=false;
    
    srand(time(NULL));
    
    this->adjustPokerOrder();//洗牌
}

//void StartGame:: registerWithTouchDispatcher(void)
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate
//    (this,-1,false);
//}
//#pragma mark ------点击判断-----
//bool StartGame:: ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//    if (mpGameAgainLabel->boundingBox().containsPoint(pTouch->getLocation())) {
//        mbGameIsOver=false;
//        gameAgain();
//        return false;
//    }
//
//
//
//
//    for (int i=0; i<mpPersonArr->count(); i++) {
//        CCSprite * sp=(CCSprite *)getChildByTag(TAG+i);
//        CCRect rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),mfWidth,sp->boundingBox().size.height);
//        //重新划分触摸响应区域
//        if (i==mpPersonArr->count()-1) {
//            rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),sp->boundingBox().size.width,sp->boundingBox().size.height);
//            //最后一张牌划分单独区域
//        }
//        if (rectForTouch.containsPoint(pTouch->getLocation())) {
//            CCString * decide=CCString::createWithFormat("%d",1);
//            if ((mpPokerWhetherMoveArr->objectAtIndex(i))->isEqual(decide)) {
//                CCString * strIsMove=CCString::createWithFormat("%d",0);
//                mpPokerWhetherMoveArr->replaceObjectAtIndex(i,strIsMove);
//            }
//            else{
//                CCString * strIsNotMove=CCString::createWithFormat("%d",1);
//                mpPokerWhetherMoveArr->replaceObjectAtIndex(i,strIsNotMove);
//            }
//
//            return  true;
//        }
//    }
//    return false;
//}
//void StartGame:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//}

//#pragma mark ------点击判断结束后做一定操作-----
//void StartGame:: ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//    if(!mbGameIsOver){
//    CCString * decide=CCString::createWithFormat("%d",1);
//    for (int i=0; i<mpPersonArr->count(); i++) {
//        CCSprite * sp=(CCSprite *)getChildByTag(TAG+i);
//        CCRect rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),mfWidth,sp->boundingBox().size.height);
//        //重新划分触摸响应区域
//        if (i==mpPersonArr->count()-1) {
//            rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),sp->boundingBox().size.width,sp->boundingBox().size.height);
//            //最后一张牌划分单独区域
//        }
//        if (rectForTouch.containsPoint(pTouch->getLocation()))
//        {
//            if ((mpPokerWhetherMoveArr->objectAtIndex(i))->isEqual(decide))
//            {
//                sp->setPositionY(sp->getPositionY()+20);
//                CCString * strIsSelect=CCString::createWithFormat("%d",1);
//                mpPokerIsSlectArr->replaceObjectAtIndex(i,strIsSelect);
//                mpSelectValueArr->addObject(sp);
//                //保存选中的牌
//                mpSelectKeysArr->addObject(mpKeysOfpersonArr->objectAtIndex(i));
//                //保存选中的牌对应的key
//
//            }
//            else
//            {
//                sp->setPositionY(sp->getPositionY()-20);
//                CCString * strIsNotSelect=CCString::createWithFormat("%d",0);
//                mpPokerIsSlectArr->replaceObjectAtIndex(i,strIsNotSelect);
//                mpSelectValueArr->removeObject(sp);
//                //删除取消选中的牌
//                mpSelectKeysArr->removeObject(mpKeysOfpersonArr->objectAtIndex(i));
//                //删除取消选中的牌的key
//            }
//
//        }
//    }
//    }
//}

#pragma mark------重新开始游戏
void StartGame::gameAgain()
{
    clearScreenAndManyArr();
}

#pragma mark------清理桌面 清空数组
void StartGame::clearScreenAndManyArr()
{
    if (mpPersonArr->count()>0) {
        for (int i=0; i<mpPersonArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpPersonArr->objectAtIndex(i);
            if (sp->getParent()) {
                sp->removeFromParentAndCleanup(true);
            }
        }
    }
    
    if (mpSelectValueArr->count()>0) {
        for (int i=0; i<mpSelectValueArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpSelectValueArr->objectAtIndex(i);
            if (sp->getParent()) {
                sp->removeFromParentAndCleanup(true);
            }
        }
    }
    
    if (mpNextComputerSelectArr->count()>0) {
        for (int i=0; i<mpNextComputerSelectArr->count(); i++) {
            CCSprite * sp=(CCSprite *)mpNextComputerSelectArr->objectAtIndex(i);
            if (sp->getParent()) {
                sp->removeFromParentAndCleanup(true);
            }
        }
    }
    
    if (mpUpComputerSelectArr->count()>0) {
        for (int i=0; i<mpUpComputerSelectArr->count();i++) {
            CCSprite * sp=(CCSprite *)mpUpComputerSelectArr->objectAtIndex(i);
            if (sp->getParent()) {
                sp->removeFromParentAndCleanup(true);
            }
        }
    }
    
    mpRootDic->removeAllObjects();
    mpArrByRand->removeAllObjects();
    mpKeyArrByRand->removeAllObjects();
    
    mpPersonArr->removeAllObjects();
    mpKeysOfpersonArr->removeAllObjects();
    
    mpComputerNextArr->removeAllObjects();
    mpKeysOfcomputerNextArr->removeAllObjects();
    mpComputerUpArr->removeAllObjects();
    mpKeysOfcomputerUpArr->removeAllObjects();
    
    mpLastThreeArr->removeAllObjects();
    mpKeysOflastThreeArr->removeAllObjects();
    
    mpPokerWhetherMoveArr->removeAllObjects();
    mpPokerIsSlectArr->removeAllObjects();
    
    mpSelectKeysArr->removeAllObjects();
    mpSelectValueArr->removeAllObjects();
    
    mpNextComputerSelectArr->removeAllObjects();
    mpKeysOfnextComputerSelectArr->removeAllObjects();
    mpUpComputerSelectArr->removeAllObjects();
    mpKeysOfupComputerSelectArr->removeAllObjects();
    
    mpUpComIdentityLabel->setString("");
    mpPersonIdentityLabel->setString("");
    mpNextComIdentityLabel->setString("");
    //身份清空
    mpComputerUpLabel->setString("");
    mpComputerNextLabel->setString("");
    mpPersonLabel->setString("");
    
    mpGameAgainLabel->setPositionX(OUT_OF_SCREEN_POINT_Y);
    mpGameOverLabel->setPositionX(OUT_OF_SCREEN_POINT_Y);
    
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    GameStart();//重新开始游戏
    
}

StartGame::~StartGame()
{
    CC_SAFE_RELEASE(mpRootDic);
    
    CC_SAFE_DELETE(mpArrByRand);
    CC_SAFE_DELETE(mpKeyArrByRand);
    
    CC_SAFE_DELETE(mpPersonArr);
    CC_SAFE_DELETE(mpKeysOfpersonArr);
    CC_SAFE_DELETE(mpComputerNextArr);
    CC_SAFE_DELETE(mpKeysOfcomputerNextArr);
    CC_SAFE_DELETE(mpComputerUpArr);
    CC_SAFE_DELETE(mpKeysOfcomputerUpArr);
    CC_SAFE_DELETE(mpLastThreeArr);
    CC_SAFE_DELETE(mpKeysOflastThreeArr);
    
    CC_SAFE_RELEASE(mpPokerWhetherMoveArr);
    CC_SAFE_RELEASE(mpPokerIsSlectArr);
    
    CC_SAFE_DELETE(mpSelectValueArr);
    CC_SAFE_DELETE(mpSelectKeysArr);
    
    CC_SAFE_DELETE(mpNextComputerSelectArr);
    CC_SAFE_DELETE(mpKeysOfnextComputerSelectArr);
    CC_SAFE_DELETE(mpUpComputerSelectArr);
    CC_SAFE_DELETE(mpKeysOfupComputerSelectArr);
}

CCScene * StartGame::creatWithSenceTarget(TargetPlayScence target)
{
    StartGame * start=StartGame::create();
    if (start&&start->initWithSenceTarget(target)) {
        CCScene * sence=CCScene::create();
        sence->addChild(start);
        return sence;
    }
    return NULL;
}
bool StartGame::initWithSenceTarget(TargetPlayScence target)
{
    if (!this->init()) {
        return false;
    }
    targetPlayScence=target;
    this->schedule(schedule_selector(StartGame::reolaceScenceUpdate), 1.0f);
    return true;
    
}
void StartGame::reolaceScenceUpdate(float t)
{
    
}
void StartGame:: onEnter()
{
    CCLayer::onEnter();
}
void StartGame:: onExit()
{
    CCLayer::onExit();
    unscheduleInStartGameAllUpdate();
    displaytime=0;
}
void StartGame:: onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void StartGame::menuCloseCallback()
{
    //CCTransitionSplitRows
    
    CCTransitionSplitRows * transition=CCTransitionSplitRows::create(1.0f,
                                                                   HelloWorld::createScene());
    CCDirector::sharedDirector()->replaceScene(transition);
    
}
