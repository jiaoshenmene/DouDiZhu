//
//  GameSetting.cpp
//  MyGame
//
//  Created by user on 14-4-22.
//
//

#include "GameSetting.h"
#include "TypeEnmu.h"
#include "HelloWorldScene.h"

CCScene* GameSetting::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameSetting *layer = GameSetting::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSetting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    auto pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",CC_CALLBACK_0(GameSetting::menuCloseCallback, this));
    
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pSprite = CCSprite::create("backgroundimage.png");
    pSprite->setRotation(90);
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    mpBackGroundMusic=CCLabelTTF::create("背景音乐：", "", 30);
    mpBackGroundMusic->setColor(ccc3(255, 255, 0));
    mpBackGroundMusic->setPosition(ccp(size.width/2+80, size.height/2+30));
    addChild(mpBackGroundMusic);
    
    mpBackGroundMusicTT=CCLabelTTF::create("", "", 30);
    mpBackGroundMusicTT->setColor(ccc3(255, 255, 0));
    mpBackGroundMusicTT->setPosition(ccp(size.width/2+160, size.height/2+30));
    addChild(mpBackGroundMusicTT);
    
    mpBackGroundSoundEffect=CCLabelTTF::create("游戏音效：", "", 30);
    mpBackGroundSoundEffect->setColor(ccc3(0, 255, 255));
    mpBackGroundSoundEffect->setPosition(ccp(size.width/2+80, size.height/2-30));
    addChild(mpBackGroundSoundEffect);
    
    mpBackGroundSoundEffectTT=CCLabelTTF::create("", "", 30);
    mpBackGroundSoundEffectTT->setColor(ccc3(0, 255, 255));
    mpBackGroundSoundEffectTT->cocos2d::CCNode::setPosition(ccp(size.width/2+160, size.height/2-30));
    addChild(mpBackGroundSoundEffectTT);
    
    int bValue=CCUserDefault::sharedUserDefault()->getIntegerForKey("BackGroundMusic");
    int gValue=CCUserDefault::sharedUserDefault()->getIntegerForKey("SoundEffectMusic");
    //读取游戏设置
    if (bValue==GAME_MUSIC_OPEN) {
        mbBMusicIsOpen=true;
        mpBackGroundMusicTT->setString("开");
    }
    else
    {
        mbBMusicIsOpen=false;
        mpBackGroundMusicTT->setString("关");
    }
    
    if (gValue==GAME_MUSIC_OPEN) {
        mbGMusicIsOpen=true;
        mpBackGroundSoundEffectTT->setString("开");
    }
    else{
        mbGMusicIsOpen=false;
        mpBackGroundSoundEffectTT->setString("关");
    }
    //根据游戏设置显示状态
    setTouchEnabled(true);
    
    return true;
}

//void GameSetting::registerWithTouchDispatcher(void)
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 5, true);
//}
//bool GameSetting::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCPoint touchPoint=pTouch->getLocation();
//    if (mpBackGroundMusicTT->boundingBox().containsPoint(touchPoint)) {
//        if (mbBMusicIsOpen) {
//            mbBMusicIsOpen=false;
//            mpBackGroundMusicTT->setString("关");
//            CCUserDefault::sharedUserDefault()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_CLOSE);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//        else
//        {
//            mbBMusicIsOpen=true;
//            mpBackGroundMusicTT->setString("开");
//            CCUserDefault::sharedUserDefault()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_OPEN);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//    }
//
//    if (mpBackGroundSoundEffectTT->boundingBox().containsPoint(touchPoint)) {
//        if (mbGMusicIsOpen) {
//            mbGMusicIsOpen=false;
//            mpBackGroundSoundEffectTT->setString("关");
//            CCUserDefault::sharedUserDefault()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_CLOSE);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//        else
//        {
//            mbGMusicIsOpen=true;
//            mpBackGroundSoundEffectTT->setString("开");
//            CCUserDefault::sharedUserDefault()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_OPEN);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//    }
//    //若 更改游戏设置 记录
//    return false;
//}





bool GameSetting::initWithSenceTarget(TargetSettingScence target)
{
    if (!this->init()) {
        return false;
    }
    targetScence=target;
    this->schedule(schedule_selector(GameSetting::reolaceScenceUpdate), 1.0f);
    return true;
    
}
void GameSetting::reolaceScenceUpdate(float t)
{
    
}
void GameSetting:: onEnter()
{
    CCLayer::onEnter();
}
void GameSetting:: onExit()
{
    CCLayer::onExit();
}
void GameSetting:: onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void GameSetting::menuCloseCallback()
{
    //CCTransitionSplitRows
    
    CCTransitionShrinkGrow * transition=CCTransitionShrinkGrow::create(1.0f,
                                                                     HelloWorld::createScene());
    CCDirector::sharedDirector()->replaceScene(transition);
    
}
