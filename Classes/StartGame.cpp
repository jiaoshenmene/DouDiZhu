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
#include "PublicItem.h"

USING_NS_CC;

Scene* StartGame::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    StartGame *layer = StartGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
//    layer->setTouchEnabled(true);
    // return the scene
    return scene;
}

StartGame *StartGame::create() {
    StartGame *pRet = new StartGame();
    
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}


// on "init" you need to initialize your instance
bool StartGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          CC_CALLBACK_0(StartGame::menuCloseCallback, this));
    pCloseItem->setPosition( Vec2(Director::getInstance()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition( Vec2::ZERO );
    this->addChild(pMenu, 1);


//    CCMenuItemFont * start=CCMenuItemFont::create("YES",CC_CALLBACK_0(StartGame::outOfTheCards, this));
//    start->setPosition( Vec2(150, 150) );
//    pMenu->addChild(start,1);
//    //出牌按钮
//    CCMenuItemFont * pass=CCMenuItemFont::create("NO",CC_CALLBACK_0(StartGame::passThisRecycle, this));
//    pass->setPosition( Vec2(220, 150) );
//    pMenu->addChild(pass,1);
    //出牌按钮

    Sprite * backGround= PublicItem::backgroundSprite();
    this->addChild(backGround);
    //添加背景图
    Sprite * timeBackGround=Sprite::create("Circle.png");
    timeBackGround->setPosition(Vec2(260, 300));
    this->addChild(timeBackGround);
    mpTimerCountDown = Label::create();
    mpTimerCountDown->setSystemFontSize(20);
    mpTimerCountDown->setPosition(Vec2(260, 300));
    this->addChild(mpTimerCountDown);
    //person

    Sprite * timeBackGroundOfNext=Sprite::create("Circle.png");
    timeBackGroundOfNext->setPosition(Vec2(400, 160));
    this->addChild(timeBackGroundOfNext);
    
    mpNextComputertimerCountDown = Label::create();
    mpNextComputertimerCountDown->setSystemFontSize(20);
    
    mpNextComputertimerCountDown->setPosition(Vec2(400, 160));
    this->addChild(mpNextComputertimerCountDown);

    //next

    Sprite * timeBackGroundOfUp=Sprite::create("Circle.png");
    timeBackGroundOfUp->setPosition(Vec2(50, 160));
    this->addChild(timeBackGroundOfUp);
    
    mpUpComputertimerCountDown = Label::create();
    mpUpComputertimerCountDown->setSystemFontSize(20);
    mpUpComputertimerCountDown->setPosition(Vec2(50, 160));
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
        std::string getKeyByKeyRand=mpRootKeys.at(keyRand);
        //随机的key
        std::vector<Sprite *> getArrByValueRand= mpRootDic.at(getKeyByKeyRand);
        //随机的数组
        Sprite * sp=(Sprite *)(getArrByValueRand.at(valueRand));
        //随机的牌
        std::vector<Sprite *>::iterator it = std::find(mpArrByRand.begin(), mpArrByRand.end(), sp);
        if (it == mpArrByRand.end()) {
            mpArrByRand.push_back(sp);
            //保存随机后的精灵
            mpKeyArrByRand.push_back(getKeyByKeyRand);
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

//#pragma mark ------发牌-------
//void StartGame::sendPokerOutEveryPlayer()
//{
//    for (int i=0; i<POKERS_COUNT/3-1; i++) {
//        mpComputerUpArr.push_back(mpArrByRand.at(i));
//        mpKeysOfcomputerUpArr.push_back(mpKeyArrByRand.at(i));
//        //储存玩家上家的牌及对应的key
//    }
//
//    for (int i=POKERS_COUNT/3-1; i<2*POKERS_COUNT/3-2; i++) {
//        mpPersonArr.push_back(mpArrByRand.at(i));
//        mpKeysOfpersonArr.push_back(mpKeyArrByRand.at(i));
//         //储存玩家的牌及对应的key
//    }
//    for (int i=2*POKERS_COUNT/3-2; i<POKERS_COUNT-3; i++) {
//        mpComputerNextArr.push_back(mpArrByRand.at(i));
//        mpKeysOfcomputerNextArr.push_back(mpKeyArrByRand.at(i));
//         //储存玩家吓家的牌及对应的key
//    }
//
//    for (int i=POKERS_COUNT-3; i<POKERS_COUNT; i++) {
//        mpLastThreeArr.push_back(mpArrByRand.at(i));
//        mpKeysOflastThreeArr.push_back(mpKeyArrByRand.at(i));
//         //储存底牌及对应的key
//    }
//    int lastThreePokerOwner=rand()%3;
//    //随机一个地主
//    if (lastThreePokerOwner==0) {
//
//        mbUpComputerIsLandlord=true;
//        mbNextComputerISLandlord=false;
//        mbPersonIsLandlord=false;
//
//        mpUpComIdentityLabel->setString("地主");
//        mpNextComIdentityLabel->setString("平民");
//        mpPersonIdentityLabel->setString("平民");
//
//        mpComputerUpArr.push_backsFromArray(mpLastThreeArr);
//        mpKeysOfcomputerUpArr.push_backsFromArray(mpKeysOflastThreeArr);
//    }
//    else if(lastThreePokerOwner==1)
//    {
//        mbUpComputerIsLandlord=false;
//        mbNextComputerISLandlord=false;
//        mbPersonIsLandlord=true;
//
//        mpUpComIdentityLabel->setString("平民");
//        mpNextComIdentityLabel->setString("平民");
//        mpPersonIdentityLabel->setString("地主");
//
//        mpPersonArr.push_backsFromArray(mpLastThreeArr);
//        mpKeysOfpersonArr.push_backsFromArray(mpKeysOflastThreeArr);
//    }
//    else
//    {
//        mbUpComputerIsLandlord=false;
//        mbNextComputerISLandlord=true;
//        mbPersonIsLandlord=false;
//
//        mpUpComIdentityLabel->setString("平民");
//        mpNextComIdentityLabel->setString("地主");
//        mpPersonIdentityLabel->setString("平民");
//
//        mpComputerNextArr.push_backsFromArray(mpLastThreeArr);
//        mpKeysOfcomputerNextArr.push_backsFromArray(mpKeysOflastThreeArr);
//    }
//    sortedForArray(mpComputerUpArr, mpKeysOfcomputerUpArr);
//    sortedForArray(mpPersonArr, mpKeysOfpersonArr);
//    sortedForArray(mpComputerNextArr, mpKeysOfcomputerNextArr);
////    CCLog("发牌");
////    CCLog("upArr count =%d,upKey count = %d",computerUpArr.size(),keysOfcomputerUpArr.size());
////    CCLog("perArr count =%d,perKey count = %d",personArr.size(),keysOfpersonArr.size());
////    CCLog("nextArr count =%d,nextKey count = %d",computerNextArr.size(),keysOfcomputerNextArr.size());
////    CCLog("lastArr count =%d,lastKey count = %d",lastThreeArr.size(),keysOflastThreeArr.size());
//
//    displayPersonPoker();
//
//    scheduleUpdate();
//}
//#pragma mark ------判断输赢------
//void StartGame::update(float)
//{
//
//    if (mpComputerUpArr.size()==0) {
//        mbGameIsOver=true;
//        mpGameOverLabel->setString("不要灰心再来一局");
//        mpGameOverLabel->setPosition(Vec2(240, 160));
//        mpGameAgainLabel->setPosition(Vec2(240, 230));
//        refreshGameOverScreenDisplay(PERSON_LOST_THE_GAME);
//        unscheduleInStartGameAllUpdate();
//    }
//
//    if (mpPersonArr.size()==0) {
//        mbGameIsOver=true;
//        mpGameOverLabel->setString("恭喜，您赢啦！");
//        mpGameOverLabel->setPosition(Vec2(240, 160));
//        mpGameAgainLabel->setPosition(Vec2(240, 230));
//        refreshGameOverScreenDisplay(PERSON_WIN_THE_GAME);
//        unscheduleInStartGameAllUpdate();
//    }
//
//    if (mpComputerNextArr.size()==0) {
//        mbGameIsOver=true;
//        mpGameOverLabel->setString("不要灰心再来一局");
//        mpGameOverLabel->setPosition(Vec2(240, 160));
//        mpGameAgainLabel->setPosition(Vec2(240, 230));
//        refreshGameOverScreenDisplay(PERSON_LOST_THE_GAME);
//        unscheduleInStartGameAllUpdate();
//    }
//
//}
//
//#pragma mark------游戏结束关闭所有的定时器
//void StartGame::unscheduleInStartGameAllUpdate()
//{
//    unscheduleUpdate();
//    unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//    unschedule(schedule_selector(StartGame::nextConsiderTimeCountDown));
//    unschedule(schedule_selector(StartGame::upConsiderTimeCountDown));
//
//    unschedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider));
//    unschedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider));
//}
//
//#pragma mark ------游戏结束之后显示每个人拥有的金币------
//void StartGame::refreshGameOverScreenDisplay(int decide)
//{
//    int perValue=UserDefault::getInstance()->getIntegerForKey("CoinsOfPerson");
//    int nextComValue=UserDefault::getInstance()->getIntegerForKey("CoinsOfNextComputer");
//    int upComValue=UserDefault::getInstance()->getIntegerForKey("CoinsOfUpComputer");
//
//    UserDefault::getInstance()->setIntegerForKey("CoinsOfPerson", perValue+2*miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
//    UserDefault::getInstance()->setIntegerForKey("CoinsOfNextComputer", nextComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
//    UserDefault::getInstance()->setIntegerForKey("CoinsOfUpComputer", upComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS);
//    UserDefault::getInstance()->flush();//写入文件
//
//    mpPersonHaveCoinsLabel->setString((CCString::createWithFormat("%d",perValue+2*miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS)));
//    mpNextComHaveCoinsLabel->setString((CCString::createWithFormat("%d",nextComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS)));
//    mpUpComHaveCoinsLabel->setString((CCString::createWithFormat("%d",upComValue-miBaseTime*decide*EVERY_ROUND_PLAYER_COST_MINI_COINS)));
//
//}
//#pragma mark ------显示玩家手中的牌------
//void StartGame::displayPersonPoker()
//{
//    mfWidth=POKER_WIDTH/mpPersonArr.size();
//    for (int i=0; i<mpPersonArr.size(); i++) {
//        Sprite * sp=(Sprite *)mpPersonArr.at(i);
//        sp->setAnchorPoint(Vec2(0, 0));
//        sp->setPosition(Vec2(60+i*mfWidth,10));
//        sp->setTag(TAG+i);
//        this->addChild(sp);
//    }
////    if (mbPersonIsLandlord) {
//        schedule(schedule_selector(StartGame::personConsiderTimeCountDown), 0.01);
////    }
////    else
////        if (mpNextComIdentityLabel) {
////             nextComputeroutOfTheCards();//下家是地主 下家第一个出牌
////        }
////        else
////        {
////            upComputeroutOfTheCards();//上家是地主 上家第一个出牌
////        }
//    //牌显示后开始倒计时
//}
//
//#pragma mark ------玩家考虑时间倒计时判断---
//float personConsiderTime=0;
//int displaytime=0;
//void StartGame::personConsiderTimeCountDown(float considerTime)
//{
//    personConsiderTime+=considerTime;
//    if (personConsiderTime>=1) {
//        displaytime++;
//        std::string str=CCString::createWithFormat("%d",30-displaytime);
//        mpTimerCountDown->setString(str);
//        personConsiderTime=0;
//        mbPersonTimeOutOfCards=false;
//        if (displaytime>=30) {
//            mbPersonTimeOutOfCards=true;//超出限制时间
//            mbCanOrCannotOutOfCards=false;//超出限制时间不可出牌
//            displaytime=0;//倒计时基数归零
//            std::string str=CCString::create("");
//            mpTimerCountDown->setString(str);//清空显示的倒计时器
//            personConsiderTimeRunOutAndRandOneOfPersonPokers();
//            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//            //关闭倒计时
//
//        }
//    }
//
//}
//#pragma mark ------发到玩家手中的牌排序-----
//void StartGame::sortedForArray(CCArray * valueArr,CCArray * keyArr)
//{
//    for (int i=0; i<keyArr.size()-1; i++){
//        for (int j=keyArr.size()-1; j>i; j--) {
//            std::string key=keyArr.at(j);
//            std::string upkey=keyArr.at(j-1);
//            if (key.compare(upkey)>0) {
//                keyArr->exchangeObjectAtIndex(j, j-1);
//                valueArr->exchangeObjectAtIndex(j, j-1);
//            }
//        }
//
//    }
//}
//
//#pragma mark ------符合条件的出牌------
//void StartGame::outOfTheCards()
//{
//    if(!mbGameIsOver){
//    for (int i=0; i<mpUpComputerSelectArr.size(); i++) {
//        Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//        sp->removeFromParent();
//    }
//    if (mpSelectKeysArr.size()==0) {
//        return;
//    }
//
//    sortedForArray(mpSelectValueArr, mpSelectKeysArr);  //选中的的牌排序
//    //    本轮上家电脑有出牌
//    if (upcomputerIsOutOfCards) {
//        if (DecidePoker::sharedDecidePoker()->decidePersonMoreBigSHowPoker(mpSelectKeysArr, mpKeysOfupComputerSelectArr)) {
//            CCLog("more big than up");
//            for (int i=0; i<mpSelectValueArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setPosition(Vec2(160+mfWidth*i, 150));
//            }
//            personIsOutOfCards=true;
//            //玩家本轮出牌
//            mbPersonFirstIsOutOfCards=false;
//            mpPersonArr.erase(mpSelectValueArr);
//            //从玩家手中删除出过的牌
//            mpKeysOfpersonArr.erase(mpSelectKeysArr);
//            //从玩家手中删除出过的牌及对应的key
//
//            mpUpComputerSelectArr->removeAllObjects();
//            mpKeysOfupComputerSelectArr->removeAllObjects();
//            //清空上家电脑选中的牌
//
//
//            for (int i=0; i<mpPersonArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpPersonArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setTag(TAG+i);
//                sp->setPosition(Vec2(240-mfWidth*(mpPersonArr.size()/2)+mfWidth*i, 10));
//            }
//            //玩家出牌后调整桌面牌的位置
//
//            std::string str=CCString::create("@");
//            for(int i=0;i<20;i++)
//            {
//                mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str);
//
//            }
//
//            std::string str_=CCString::createWithFormat("%d",30);
//            mpNextComputertimerCountDown->setString(str_);
//            schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
//            schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
//            std::string strPer=CCString::create("");
//            mpTimerCountDown->setString(strPer);//清空显示的倒计时器
//            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//        }
//        else
//        {
//            CCLOG("你选的牌不符合规则");
//        }
//        if (mbPersonTimeOutOfCards) {
//            passThisRecycle();//考虑超时
//        }
//    }
//
//    //本轮上家电脑没有出牌 但是下家出牌了
//    if (!upcomputerIsOutOfCards&&nextcomputerIsOutOfCards) {
//        if (DecidePoker::sharedDecidePoker()->decidePersonMoreBigSHowPoker(mpSelectKeysArr, mpKeysOfnextComputerSelectArr)) {
//            for (int i=0; i<mpSelectValueArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setPosition(Vec2(160+mfWidth*i, 150));
//            }
//            personIsOutOfCards=true;
//            mbPersonFirstIsOutOfCards=false;
//            //玩家本轮出牌
//            mpPersonArr.erase(mpSelectValueArr);
//            //从玩家手中删除出过的牌
//            mpKeysOfpersonArr.erase(mpSelectKeysArr);
//            //从玩家手中删除出过的牌及对应的key
//
//            mpNextComputerSelectArr->removeAllObjects();
//            mpKeysOfnextComputerSelectArr->removeAllObjects();
//            //清空下家电脑选中的牌
//
//
//            for (int i=0; i<mpPersonArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpPersonArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setTag(TAG+i);
//                sp->setPosition(Vec2(240-mfWidth*(mpPersonArr.size())/2+mfWidth*i, 10));
//            }
//            //玩家出牌后调整桌面牌的位置
//
//            std::string str=CCString::create("@");
//            for(int i=0;i<20;i++)
//            {
//                mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str);
//
//            }
//
//
//            std::string str_=CCString::createWithFormat("%d",30);
//            mpNextComputertimerCountDown->setString(str_);
//            schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
//            schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
//            std::string strPer=CCString::create("");
//            mpTimerCountDown->setString(strPer);//清空显示的倒计时器
//            unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//        }
//        else
//        {
//            CCLOG("你选的牌不符合规则");
//
//        }
//        if (mbPersonTimeOutOfCards) {
//            passThisRecycle();//考虑超时
//        }
//
//    }
//
//
//    //    本轮上下家电脑都没有出牌 轮到玩家出牌
//    if (!upcomputerIsOutOfCards&&!nextcomputerIsOutOfCards) {
//        miPokerTypeID=GameRules::sharedGameRules()->decideSelectedPokerIfConformToRules(mpSelectValueArr, mpSelectKeysArr);
//        if (miPokerTypeID&&(!mbPersonTimeOutOfCards)) {
//
//        std::string str=CCString::create("");
//        mpTimerCountDown->setString(str);//清空显示的倒计时器
//        unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//
//        for (int i=0; i<mpSelectValueArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//            sp->setAnchorPoint(Vec2(0, 0));
//            sp->setPosition(Vec2(160+i*mfWidth, 150));
//        }
//
//        personIsOutOfCards=true;
//        //玩家本轮出牌
//        mbPersonFirstIsOutOfCards=false;
//        mpPersonArr.erase(mpSelectValueArr);
//        //从玩家手中删除出过的牌
//        mpKeysOfpersonArr.erase(mpSelectKeysArr);
//         //从玩家手中删除出过的牌及对应的key
//
//
//        for (int i=0; i<mpPersonArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpPersonArr.at(i);
//            sp->setAnchorPoint(Vec2(0, 0));
//            sp->setTag(TAG+i);
//            sp->setPosition(Vec2(240-mfWidth*(mpPersonArr.size())/2+mfWidth*i, 10));
//        }
//        //玩家出牌后调整桌面牌的位置
//
//        std::string str1=CCString::create("@");
//        for(int i=0;i<20;i++)
//        {
//            mpPokerWhetherMoveArr->replaceObjectAtIndex(i, str1);
//
//        }
//
//        std::string str_=CCString::createWithFormat("%d",30);
//        mpNextComputertimerCountDown->setString(str_);
//        schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
//        schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
//        std::string strPer=CCString::create("");
//        mpTimerCountDown->setString(strPer);//清空显示的倒计时器
//        unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//    }
//
//    }
//    }
//}
//#pragma mark ------只应该玩家出牌时玩家托管-----
//void StartGame::personConsiderTimeRunOutAndRandOneOfPersonPokers()
//{
//    if(!mbGameIsOver){
//    if (!upcomputerIsOutOfCards&&!nextcomputerIsOutOfCards) {
//        for (int i=0; i<mpSelectKeysArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//            sp->removeFromParent();
//            //玩家出牌后其他人均为出牌 自己移除桌面上的精灵
//        }
//        mpSelectValueArr->removeAllObjects();
//        mpSelectKeysArr->removeAllObjects();
//
//        Sprite * sp=(Sprite *)mpPersonArr.at(mpPersonArr.size()-1);
//        sp->setAnchorPoint(Vec2(0, 0));
//        sp->setPosition(Vec2(240, 150));
//        //即托管状态
//        mpSelectValueArr.push_back(sp);
//        mpSelectKeysArr.push_back(mpKeysOfpersonArr.at(mpKeysOfpersonArr.size()-1));
//
//        mpPersonArr->removeObject(sp);
//        mpKeysOfpersonArr->removeObject(mpKeysOfpersonArr.at(mpKeysOfpersonArr.size()-1));
//        //移除显示的牌
//
//        personIsOutOfCards=true;
//        //玩家本轮有出牌
//
//        for (int i=0; i<mpPersonArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpPersonArr.at(i);
//            sp->setAnchorPoint(Vec2(0, 0));
//            sp->setTag(TAG+i);
//            sp->setPosition(Vec2(160+mfWidth*i, 10));
//        }
//        //玩家出牌后调整桌面牌的位置
//        std::string str_=CCString::createWithFormat("%d",30);
//        mpNextComputertimerCountDown->setString(str_);
//        schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
//
//        schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
//        CCLOG("玩家托管");
//    }
//    else
//    {
//        passThisRecycle();
//    }
//    }
//}
//
//#pragma mark ------玩家过牌-----
//void StartGame::passThisRecycle()
//{
//    if(!mbGameIsOver){
//    if(!mbPersonFirstIsOutOfCards&&(nextcomputerIsOutOfCards||upcomputerIsOutOfCards)){
//    std::string str=CCString::create("");
//    mpTimerCountDown->setString(str);//清空显示的倒计时器
//    unschedule(schedule_selector(StartGame::personConsiderTimeCountDown));
//    //玩家计时器清零
//    personIsOutOfCards=false;
//    //玩家本轮没有出牌
//    mpPersonLabel->setString("不出");
//    mpPersonLabel->setPosition(Vec2(320, 160));
//
//    std::string str_=CCString::createWithFormat("%d",30);
//    mpNextComputertimerCountDown->setString(str_);
//    schedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider), 0.01f);
//
//    schedule(schedule_selector(StartGame::nextConsiderTimeCountDown), 0.01);
//    }
//    }
//}
//
//#pragma mark ------玩家出牌几秒后下家电脑考虑出牌---
//float sumTime=0;
//void StartGame::personOutOfCardsManyTimeNextStartConsider(float t)
//{
//    sumTime+=t;
//
//    mpComputerNextLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);
//
//    if (sumTime>=PERSON_INTERVAL_TIME_TO_NEXT_COMPUTER) {
//        nextComputeroutOfTheCards();
//        //下家电脑开始考虑出牌
//        sumTime=0;
//        unschedule(schedule_selector(StartGame::personOutOfCardsManyTimeNextStartConsider));
//    }
//}
//#pragma mark ------下家电脑考虑时间倒计时判断---
//float nextComputerConsiderTime=0;
//int nextdisplaytime=0;
//void StartGame::nextConsiderTimeCountDown(float considerTime)
//{
//    nextComputerConsiderTime+=considerTime;
//    if (nextComputerConsiderTime>=1) {
//        nextdisplaytime++;
//        std::string str=CCString::createWithFormat("%d",30-nextdisplaytime);
//        mpNextComputertimerCountDown->setString(str);
//        nextComputerConsiderTime=0;
//        if (nextdisplaytime>=PERSON_INTERVAL_TIME_TO_NEXT_COMPUTER) {
//            nextdisplaytime=0;//倒计时基数归零
//            std::string str=CCString::create("");
//            mpNextComputertimerCountDown->setString(str);//清空显示的倒计时器
//            unschedule(schedule_selector(StartGame::nextConsiderTimeCountDown));
//            //关闭倒计时
//
//        }
//    }
//
//}

//#pragma mark ------下家电脑出牌-----
//void StartGame::nextComputeroutOfTheCards()
//{
//    if(!mbGameIsOver){
//    if(personIsOutOfCards)//本轮玩家出牌了
//    {
//        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpSelectValueArr, mpSelectKeysArr, mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpComputerNextArr, mpKeysOfcomputerNextArr,miPokerTypeID)) {
//        for (int i=0; i<mpSelectKeysArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//            sp->removeFromParent();
//        }
//
//        for (int i=0; i<mpNextComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpNextComputerSelectArr.at(i);
//            sp->setAnchorPoint(Vec2(0, 0));
//            sp->setPosition(Vec2(200+i*20, 150));
//            this->addChild(sp);
//        };
//        nextcomputerIsOutOfCards=true;
//        //本轮下家电脑有出牌
//        mpComputerNextArr.erase(mpNextComputerSelectArr);
//        //从下家电脑手中删除出过的牌
//        mpKeysOfcomputerNextArr.erase(mpKeysOfnextComputerSelectArr);
//        //从下家电脑手中删除出过的牌
//        mpSelectValueArr->removeAllObjects();
//            //出完牌记录选中person牌的数组清零
//        mpSelectKeysArr->removeAllObjects();
//            //出完牌记录选中person牌的数组及对应的key清零
//    }else
//    {
//        nextcomputerIsOutOfCards=false;
//        //本轮下家电脑有出牌
//        mpComputerNextLabel->setString("不出");
//        mpComputerNextLabel->setPosition(Vec2(400, 200));
//    }
//    }
//
//    if(!personIsOutOfCards&&upcomputerIsOutOfCards)//本轮玩家没出牌但玩家上家出牌了
//    {
//        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpComputerNextArr, mpKeysOfcomputerNextArr,miPokerTypeID)) {
//            for (int i=0; i<mpUpComputerSelectArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//                sp->removeFromParent();
//            }
//
//            for (int i=0; i<mpNextComputerSelectArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpNextComputerSelectArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setPosition(Vec2(200+i*20, 150));
//                this->addChild(sp);
//            };
//
//            nextcomputerIsOutOfCards=true;
//            //本轮下家电脑有出牌
//            mpComputerNextArr.erase(mpNextComputerSelectArr);
//            //从下家电脑手中删除出过的牌
//            mpKeysOfcomputerNextArr.erase(mpKeysOfnextComputerSelectArr);
//            //从下家电脑手中删除出过的牌
//
//            mpUpComputerSelectArr->removeAllObjects();
//            //出完牌记录选中upcomputer牌的数组清零
//            mpKeysOfupComputerSelectArr->removeAllObjects();
//            //出完牌记录选中upcomputer牌的数组及对应的key清零
//        }else
//        {
//            nextcomputerIsOutOfCards=false;
//            //本轮下家电脑没有出牌
//            mpComputerNextLabel->setString("不出");
//            mpComputerNextLabel->setPosition(Vec2(400, 200));
//        }
//    }
//    if(!personIsOutOfCards&&!upcomputerIsOutOfCards)//本轮玩家和玩家上家都没有出牌
//    {
//
//        for (int i=0; i<mpKeysOfnextComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpNextComputerSelectArr.at(i);
//            sp->removeFromParent();
//            //下家出牌后无人出牌 自己移除桌面上的精灵
//        }
//
//        mpNextComputerSelectArr->removeAllObjects();
//        mpKeysOfnextComputerSelectArr->removeAllObjects();
//        //存放选中的精灵的数组清空
//
//        nextcomputerIsOutOfCards=true;
//        //本轮下家电脑有出牌
//        Sprite * sp=(Sprite *)mpComputerNextArr.at(mpComputerNextArr.size()-1);
//        sp->setAnchorPoint(Vec2(0, 0));
//        sp->setPosition(Vec2(200, 150));
//        this->addChild(sp);
//
//        mpNextComputerSelectArr.push_back(sp);
//        mpKeysOfnextComputerSelectArr.push_back(mpKeysOfcomputerNextArr.at(mpKeysOfcomputerNextArr.size()-1));
//        //添加下家电脑选中的牌
//        mpComputerNextArr->removeObject(sp);
//        mpKeysOfcomputerNextArr->removeObject(mpKeysOfcomputerNextArr.at(mpKeysOfcomputerNextArr.size()-1));
//
//        clearSelectedPokersType();
//        //清空出牌类型
//    }
//    schedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider), 0.01);
//    //下家电脑出完牌几秒后上家电脑出牌
//    std::string str=CCString::createWithFormat("%d",30);
//    mpUpComputertimerCountDown->setString(str);
//    schedule(schedule_selector(StartGame::upConsiderTimeCountDown), 0.01);
//    }
//}
//#pragma mark ------next出牌几秒后up电脑考虑出牌-----
//float nextToUpSumTime=0;
//void StartGame::nextComputerOutOfCardsManyTimeUpStartConsider(float t)
//{
//    mpComputerUpLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);
//    nextToUpSumTime+=t;
//    if (nextToUpSumTime>=NEXT_INTERVAL_TIME_TO_UP_COMPUTER) {
//        upComputeroutOfTheCards();
//        nextToUpSumTime=0;
//        unschedule(schedule_selector(StartGame::nextComputerOutOfCardsManyTimeUpStartConsider));
//    }
//
//}
//
//#pragma mark ------上家电脑考虑时间倒计时判断---
//float upComputerConsiderTime=0;
//int updisplaytime=0;
//void StartGame::upConsiderTimeCountDown(float considerTime)
//{
//    upComputerConsiderTime+=considerTime;
//    if (upComputerConsiderTime>=1) {
//        updisplaytime++;
//        std::string str=CCString::createWithFormat("%d",30-updisplaytime);
//        mpUpComputertimerCountDown->setString(str);
//        upComputerConsiderTime=0;
//        if (updisplaytime>=NEXT_INTERVAL_TIME_TO_UP_COMPUTER) {
//            updisplaytime=0;//倒计时基数归零
//            std::string str=CCString::create("");
//            mpUpComputertimerCountDown->setString(str);//清空显示的倒计时器
//            unschedule(schedule_selector(StartGame::upConsiderTimeCountDown));
//            //关闭倒计时
//
//        }
//    }
//
//}
//
//
//#pragma mark ------上家电脑出牌-----
//void StartGame::upComputeroutOfTheCards()
//{
//    if(!mbGameIsOver){
//       //本轮下家电脑出牌了
//    if (nextcomputerIsOutOfCards) {
//    if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpNextComputerSelectArr, mpKeysOfnextComputerSelectArr, mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpComputerUpArr, mpKeysOfcomputerUpArr,miPokerTypeID)) {
//        for (int i=0; i<mpNextComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpNextComputerSelectArr.at(i);
//            sp->removeFromParent();
//        }
//
//        for (int i=0; i<mpUpComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//            sp->setAnchorPoint(Vec2(0, 0));
//            sp->setPosition(Vec2(200+i*20, 150));
//            this->addChild(sp);
//        };
//        upcomputerIsOutOfCards=true;
//        //本轮玩家电脑出牌了
//        mpComputerUpArr.erase(mpUpComputerSelectArr);
//        mpKeysOfcomputerUpArr.erase(mpKeysOfupComputerSelectArr);
//        //上家电脑出过的牌从手中删除
//
//        mpNextComputerSelectArr->removeAllObjects();
//        //出完牌记录选中nextcomputer牌的数组清零
//        mpKeysOfnextComputerSelectArr->removeAllObjects();
//        //出完牌记录选中nextcomputer牌的数组及对应的key清零
//    }else
//    {
//        upcomputerIsOutOfCards=false;
//        //本轮玩家电脑没有出牌
//        mpComputerUpLabel->setString("不出");
//        mpComputerUpLabel->setPosition(Vec2(100, 200));
//        }
//    }
//
//    //本轮下家电脑没有出牌但是玩家出牌了
//    if (!nextcomputerIsOutOfCards&&personIsOutOfCards) {
//        if (DecidePoker::sharedDecidePoker()->decideWhetherHaveSuitablePokers(mpSelectValueArr, mpSelectKeysArr, mpUpComputerSelectArr, mpKeysOfupComputerSelectArr, mpComputerUpArr, mpKeysOfcomputerUpArr,miPokerTypeID)) {
//            for (int i=0; i<mpSelectValueArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//                sp->removeFromParent();
//            }
//
//            for (int i=0; i<mpUpComputerSelectArr.size(); i++) {
//                Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//                sp->setAnchorPoint(Vec2(0, 0));
//                sp->setPosition(Vec2(200+i*20, 150));
//                this->addChild(sp);
//            };
//            upcomputerIsOutOfCards=true;
//            //本轮上家电脑出牌了
//            mpComputerUpArr.erase(mpUpComputerSelectArr);
//            mpKeysOfcomputerUpArr.erase(mpKeysOfupComputerSelectArr);
//            //上家电脑出过的牌从手中删除
//
//            mpSelectValueArr->removeAllObjects();
//            //出完牌记录选中nextcomputer牌的数组清零
//            mpSelectKeysArr->removeAllObjects();
//            //出完牌记录选中nextcomputer牌的数组及对应的key清零
//        }else
//        {
//            upcomputerIsOutOfCards=false;
//            //本轮上家电脑没有出牌
//            mpComputerUpLabel->setString("不出");
//            mpComputerUpLabel->setPosition(Vec2(100, 200));
//            schedule(schedule_selector(StartGame::upclearPersonShowPokers),0.01);
//
//        }
//    }
//
//    //玩家和下家电脑都没有出牌
//    if(!personIsOutOfCards&&!nextcomputerIsOutOfCards)//本轮玩家和玩家上家都没有出牌
//    {
//
//
//        for (int i=0; i<mpKeysOfupComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//            sp->removeFromParent();
//            //上家出牌后无人出牌 自己移除桌面上的精灵
//        }
//        mpUpComputerSelectArr->removeAllObjects();
//        mpKeysOfupComputerSelectArr->removeAllObjects();
//
//        nextcomputerIsOutOfCards=true;
//        //本轮下家电脑有出牌
//        Sprite * sp=(Sprite *)mpComputerUpArr.at(mpComputerUpArr.size()-1);
//        sp->setAnchorPoint(Vec2(0, 0));
//        sp->setPosition(Vec2(200, 150));
//        this->addChild(sp);
//        mpUpComputerSelectArr.push_back(sp);
//        mpKeysOfupComputerSelectArr.push_back(mpKeysOfcomputerUpArr.at(mpKeysOfcomputerUpArr.size()-1));
//
//        mpComputerUpArr->removeObject(sp);
//        mpKeysOfcomputerUpArr->removeObject(mpKeysOfcomputerUpArr.at(mpKeysOfcomputerUpArr.size()-1));
//
//        clearSelectedPokersType();
//        //清空出牌类型
//    }
//    displaytime=0;//person倒计时基数归零
//    schedule(schedule_selector(StartGame::personConsiderTimeCountDown), 0.01);
//    clearSelectedPokersType();
//    //清空出牌类型
//    //上家电脑出完牌 玩家可以出牌
//        mpPersonLabel->setPositionY(OUT_OF_SCREEN_POINT_Y);
//
//    }
//
//}
//#pragma mark ------如果本轮只有玩家出牌，上家过牌后，定时删除----
//float upClearPerson=0;
//void StartGame::upclearPersonShowPokers(float t)
//{
//    upClearPerson+=t;
//    if (upClearPerson>=2) {
//        for (int i=0; i<mpSelectValueArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//            sp->removeFromParent();
//        }
//        mpSelectValueArr->removeAllObjects();
//        //出完牌记录选中nextcomputer牌的数组清零
//        mpSelectKeysArr->removeAllObjects();
//        //出完牌记录选中nextcomputer牌的数组及对应的key清零
//        CCLOG("value c=%d,keys c=%d",mpSelectValueArr.size(),mpSelectKeysArr.size());
//        upClearPerson=0;
//        unschedule(schedule_selector(StartGame::upclearPersonShowPokers));
//    }
//}
//#pragma mark ------清空出牌的类型----
//void StartGame::clearSelectedPokersType()
//{
//
//}
//
#pragma mark ------初始化-----
void StartGame::initArraysAndRootDic()
{
    mpPokerWhetherMoveArr=std::vector<std::string>();
    //记录每个排当前的状态
    mpPokerIsSlectArr=std::vector<std::string>();
    //记录选中的牌
    mpSelectValueArr=std::vector<Sprite *>();
    mpSelectKeysArr=std::vector<std::string>();

    mpArrByRand=std::vector<Sprite *>();
    mpKeyArrByRand=std::vector<std::string>();
    //储存随机后的牌

    mpComputerUpArr=std::vector<Sprite *>();
    mpPersonArr=std::vector<Sprite *>();
    mpComputerNextArr=std::vector<Sprite *>();
    mpLastThreeArr=std::vector<Sprite *>();

    mpKeysOfcomputerUpArr=std::vector<std::string>();
    mpKeysOfpersonArr=std::vector<std::string>();
    mpKeysOfcomputerNextArr=std::vector<std::string>();
    mpKeysOflastThreeArr=std::vector<std::string>();
    //储存玩家，上家电脑，下家电脑，底牌及相应的key

    mpNextComputerSelectArr=std::vector<Sprite *>();
    mpKeysOfnextComputerSelectArr=std::vector<std::string>();
    //记录下家电脑应该出得牌

    mpUpComputerSelectArr=std::vector<Sprite *>();
    mpKeysOfupComputerSelectArr=std::vector<std::string>();
    //记录上家电脑应该出的牌

    mpNextComIdentityLabel=Label::create();
    mpNextComIdentityLabel->setSystemFontSize(START_GAME_LABEL_SIZE);
    
    mpUpComIdentityLabel=Label::create();
    mpUpComIdentityLabel->setSystemFontSize(START_GAME_LABEL_SIZE);
    
    mpPersonIdentityLabel=Label::create();
    mpPersonIdentityLabel->setSystemFontSize(START_GAME_LABEL_SIZE);

    mpNextComIdentityLabel->setPosition(Vec2(430, 230));
    mpNextComIdentityLabel->setColor(Color3B(0, 255, 255));
    addChild(mpNextComIdentityLabel);

    mpUpComIdentityLabel->setPosition(Vec2(50, 230));
    mpUpComIdentityLabel->setColor(Color3B(255, 255, 0));
    addChild(mpUpComIdentityLabel);

    mpPersonIdentityLabel->setPosition(Vec2(450, 80));
    mpPersonIdentityLabel->setColor(Color3B(255, 0, 255));
    addChild(mpPersonIdentityLabel);
    //显示玩家的身份

    std::string pNextStr = std::to_string(UserDefault::getInstance()->getIntegerForKey("CoinsOfNextComputer"));
    
    std::string pUpStr=std::to_string(UserDefault::getInstance()->getIntegerForKey("CoinsOfUpComputer"));
    std::string pPerStr=std::to_string(UserDefault::getInstance()->getIntegerForKey("CoinsOfPerson"));

    mpPersonHaveCoinsLabel=Label::create();
    mpPersonHaveCoinsLabel->setString(pPerStr);
    mpPersonHaveCoinsLabel->setSystemFontSize(START_GAME_LABEL_SIZE);
    
    mpNextComHaveCoinsLabel=Label::create();
    mpNextComHaveCoinsLabel->setString(pNextStr);
    mpNextComHaveCoinsLabel->setSystemFontSize(START_GAME_LABEL_SIZE);
    
    mpUpComHaveCoinsLabel=Label::create();
    mpUpComHaveCoinsLabel->setString(pUpStr);
    mpUpComHaveCoinsLabel->setSystemFontSize(START_GAME_LABEL_SIZE);

    mpNextComHaveCoinsLabel->setPosition(Vec2(430, 255));
    mpNextComHaveCoinsLabel->setColor(Color3B(0, 255, 255));
    addChild(mpNextComHaveCoinsLabel);

    mpUpComHaveCoinsLabel->setPosition(Vec2(50, 255));
    mpUpComHaveCoinsLabel->setColor(Color3B(255, 255, 0));
    addChild(mpUpComHaveCoinsLabel);

    mpPersonHaveCoinsLabel->setPosition(Vec2(450, 105));
    mpPersonHaveCoinsLabel->setColor(Color3B(255, 0, 255));
    addChild(mpPersonHaveCoinsLabel);
    //显示每个玩家拥有多少金币

    mpComputerNextLabel=Label::create();
    mpComputerNextLabel->setSystemFontSize(20);
    mpComputerNextLabel->setColor(Color3B(255, 255, 0));
    addChild(mpComputerNextLabel);

    mpComputerUpLabel=Label::create();
    mpComputerUpLabel->setSystemFontSize(20);
    mpComputerUpLabel->setColor(Color3B(255, 255, 0));
    addChild(mpComputerUpLabel);

    mpPersonLabel=Label::create();
    mpPersonLabel->setSystemFontSize(20);
    mpPersonLabel->setColor(Color3B(255, 255, 0));
    addChild(mpPersonLabel);
    //创建不出 label

    mpGameAgainLabel=Label::create();
    mpGameAgainLabel->setString("继续游戏");
    mpGameAgainLabel->setSystemFontSize(30);
    mpGameAgainLabel->setPosition(Vec2(OUT_OF_SCREEN_POINT_Y, OUT_OF_SCREEN_POINT_Y));
    mpGameAgainLabel->setColor(Color3B(255, 255, 0));
    addChild(mpGameAgainLabel,10);
    //创建继续游戏 label

    mpGameOverLabel=Label::create();
    mpGameOverLabel->setSystemFontSize(30);
    mpGameOverLabel->setPosition(Vec2(OUT_OF_SCREEN_POINT_Y, OUT_OF_SCREEN_POINT_Y));
    mpGameOverLabel->setColor(Color3B(0, 255, 255));
    addChild(mpGameOverLabel,10);
    //游戏结束显示胜负

    gameStart();//开始游戏

}

#pragma mark------开始游戏
void StartGame::gameStart()
{

    mpRootDic = PokerInit::sharedPokerInit()->initArraysAndRootDic();
    mpRootKeys = std::vector<std::string>();
    
    for (const auto& iter : mpRootDic)
    {
        mpRootKeys.push_back(iter.first);
    }


    std::string str= "@";
    for(int i=0;i<20;i++)
    {
        mpPokerWhetherMoveArr.push_back(str);//.push_back(str);//初始化牌的状态
        mpPokerIsSlectArr.push_back(str);//初始化选中的牌

    }


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

//    this->adjustPokerOrder();//洗牌
}

//void StartGame:: registerWithTouchDispatcher(void)
//{
//    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate
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
//    for (int i=0; i<mpPersonArr.size(); i++) {
//        Sprite * sp=(Sprite *)getChildByTag(TAG+i);
//        CCRect rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),mfWidth,sp->boundingBox().size.height);
//        //重新划分触摸响应区域
//        if (i==mpPersonArr.size()-1) {
//            rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),sp->boundingBox().size.width,sp->boundingBox().size.height);
//            //最后一张牌划分单独区域
//        }
//        if (rectForTouch.containsPoint(pTouch->getLocation())) {
//            std::string decide=CCString::createWithFormat("%d",1);
//            if ((mpPokerWhetherMoveArr.at(i)).compare(decide)) {
//                std::string strIsMove=CCString::createWithFormat("%d",0);
//                mpPokerWhetherMoveArr->replaceObjectAtIndex(i,strIsMove);
//            }
//            else{
//                std::string strIsNotMove=CCString::createWithFormat("%d",1);
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
//    std::string decide=CCString::createWithFormat("%d",1);
//    for (int i=0; i<mpPersonArr.size(); i++) {
//        Sprite * sp=(Sprite *)getChildByTag(TAG+i);
//        CCRect rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),mfWidth,sp->boundingBox().size.height);
//        //重新划分触摸响应区域
//        if (i==mpPersonArr.size()-1) {
//            rectForTouch=CCRect(sp->getPositionX(),sp->getPositionY(),sp->boundingBox().size.width,sp->boundingBox().size.height);
//            //最后一张牌划分单独区域
//        }
//        if (rectForTouch.containsPoint(pTouch->getLocation()))
//        {
//            if ((mpPokerWhetherMoveArr.at(i)).compare(decide))
//            {
//                sp->setPositionY(sp->getPositionY()+20);
//                std::string strIsSelect=CCString::createWithFormat("%d",1);
//                mpPokerIsSlectArr->replaceObjectAtIndex(i,strIsSelect);
//                mpSelectValueArr.push_back(sp);
//                //保存选中的牌
//                mpSelectKeysArr.push_back(mpKeysOfpersonArr.at(i));
//                //保存选中的牌对应的key
//
//            }
//            else
//            {
//                sp->setPositionY(sp->getPositionY()-20);
//                std::string strIsNotSelect=CCString::createWithFormat("%d",0);
//                mpPokerIsSlectArr->replaceObjectAtIndex(i,strIsNotSelect);
//                mpSelectValueArr->removeObject(sp);
//                //删除取消选中的牌
//                mpSelectKeysArr->removeObject(mpKeysOfpersonArr.at(i));
//                //删除取消选中的牌的key
//            }
//
//        }
//    }
//    }
//}

//#pragma mark------重新开始游戏
//void StartGame::gameAgain()
//{
//    clearScreenAndManyArr();
//}
//
//#pragma mark------清理桌面 清空数组
//void StartGame::clearScreenAndManyArr()
//{
//    if (mpPersonArr.size()>0) {
//        for (int i=0; i<mpPersonArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpPersonArr.at(i);
//            if (sp->getParent()) {
//                sp->removeFromParentAndCleanup(true);
//            }
//        }
//    }
//
//    if (mpSelectValueArr.size()>0) {
//        for (int i=0; i<mpSelectValueArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpSelectValueArr.at(i);
//            if (sp->getParent()) {
//                sp->removeFromParentAndCleanup(true);
//            }
//        }
//    }
//
//    if (mpNextComputerSelectArr.size()>0) {
//        for (int i=0; i<mpNextComputerSelectArr.size(); i++) {
//            Sprite * sp=(Sprite *)mpNextComputerSelectArr.at(i);
//            if (sp->getParent()) {
//                sp->removeFromParentAndCleanup(true);
//            }
//        }
//    }
//
//    if (mpUpComputerSelectArr.size()>0) {
//        for (int i=0; i<mpUpComputerSelectArr.size();i++) {
//            Sprite * sp=(Sprite *)mpUpComputerSelectArr.at(i);
//            if (sp->getParent()) {
//                sp->removeFromParentAndCleanup(true);
//            }
//        }
//    }
//
//    mpRootDic->removeAllObjects();
//    mpArrByRand->removeAllObjects();
//    mpKeyArrByRand->removeAllObjects();
//
//    mpPersonArr->removeAllObjects();
//    mpKeysOfpersonArr->removeAllObjects();
//
//    mpComputerNextArr->removeAllObjects();
//    mpKeysOfcomputerNextArr->removeAllObjects();
//    mpComputerUpArr->removeAllObjects();
//    mpKeysOfcomputerUpArr->removeAllObjects();
//
//    mpLastThreeArr->removeAllObjects();
//    mpKeysOflastThreeArr->removeAllObjects();
//
//    mpPokerWhetherMoveArr->removeAllObjects();
//    mpPokerIsSlectArr->removeAllObjects();
//
//    mpSelectKeysArr->removeAllObjects();
//    mpSelectValueArr->removeAllObjects();
//
//    mpNextComputerSelectArr->removeAllObjects();
//    mpKeysOfnextComputerSelectArr->removeAllObjects();
//    mpUpComputerSelectArr->removeAllObjects();
//    mpKeysOfupComputerSelectArr->removeAllObjects();
//
//    mpUpComIdentityLabel->setString("");
//    mpPersonIdentityLabel->setString("");
//    mpNextComIdentityLabel->setString("");
//    //身份清空
//    mpComputerUpLabel->setString("");
//    mpComputerNextLabel->setString("");
//    mpPersonLabel->setString("");
//
//    mpGameAgainLabel->setPositionX(OUT_OF_SCREEN_POINT_Y);
//    mpGameOverLabel->setPositionX(OUT_OF_SCREEN_POINT_Y);
//
//
//
//
//    //////////////////////////////////////////////////////////////////////////////
//    gameStart();//重新开始游戏
//
//}

//StartGame::~StartGame()
//{
//    CC_SAFE_RELEASE(mpRootDic);
//
//    CC_SAFE_DELETE(mpArrByRand);
//    CC_SAFE_DELETE(mpKeyArrByRand);
//
//    CC_SAFE_DELETE(mpPersonArr);
//    CC_SAFE_DELETE(mpKeysOfpersonArr);
//    CC_SAFE_DELETE(mpComputerNextArr);
//    CC_SAFE_DELETE(mpKeysOfcomputerNextArr);
//    CC_SAFE_DELETE(mpComputerUpArr);
//    CC_SAFE_DELETE(mpKeysOfcomputerUpArr);
//    CC_SAFE_DELETE(mpLastThreeArr);
//    CC_SAFE_DELETE(mpKeysOflastThreeArr);
//
//    CC_SAFE_RELEASE(mpPokerWhetherMoveArr);
//    CC_SAFE_RELEASE(mpPokerIsSlectArr);
//
//    CC_SAFE_DELETE(mpSelectValueArr);
//    CC_SAFE_DELETE(mpSelectKeysArr);
//
//    CC_SAFE_DELETE(mpNextComputerSelectArr);
//    CC_SAFE_DELETE(mpKeysOfnextComputerSelectArr);
//    CC_SAFE_DELETE(mpUpComputerSelectArr);
//    CC_SAFE_DELETE(mpKeysOfupComputerSelectArr);
//}
//
//Scene * StartGame::creatWithSenceTarget(TargetPlayScence target)
//{
//    StartGame * start=StartGame::create();
//    if (start&&start->initWithSenceTarget(target)) {
//        Scene * sence=Scene::create();
//        sence->addChild(start);
//        return sence;
//    }
//    return NULL;
//}
//bool StartGame::initWithSenceTarget(TargetPlayScence target)
//{
//    if (!this->init()) {
//        return false;
//    }
//    targetPlayScence=target;
//    this->schedule(schedule_selector(StartGame::reolaceScenceUpdate), 1.0f);
//    return true;
//
//}
//void StartGame::reolaceScenceUpdate(float t)
//{
//
//}
//void StartGame:: onEnter()
//{
//    CCLayer::onEnter();
//}
//void StartGame:: onExit()
//{
//    CCLayer::onExit();
//    unscheduleInStartGameAllUpdate();
//    displaytime=0;
//}
//void StartGame:: onEnterTransitionDidFinish()
//{
//    CCLayer::onEnterTransitionDidFinish();
//}

void StartGame::menuCloseCallback()
{
    //CCTransitionSplitRows

    TransitionSplitRows * transition= TransitionSplitRows::create(1.0f,
                                                                   HelloWorld::createScene());
    Director::getInstance()->replaceScene(transition);

}
