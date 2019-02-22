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
#include "PublicItem.h"

Scene* GameSetting::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",CC_CALLBACK_0(GameSetting::menuCloseCallback, this));
    
    pCloseItem->setPosition( Vec2(Director::getInstance()->getWinSize().width - 100, 20) );
    
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition( Vec2::ZERO );
    this->addChild(pMenu, 1);
    
    Size size = Director::getInstance()->getWinSize();
    Sprite* pSprite = PublicItem::backgroundSprite();
    this->addChild(pSprite, 0);
    
    mpBackGroundMusic=Label::create();
    mpBackGroundMusic->setString("背景音乐：");
    mpBackGroundMusic->setSystemFontSize(30);
    mpBackGroundMusic->setColor(Color3B(255, 255, 0));
    mpBackGroundMusic->setPosition(Vec2(size.width/2+80, size.height/2+30));
    addChild(mpBackGroundMusic);
    
    mpBackGroundMusicTT=CCLabelTTF::create("", "", 30);
    mpBackGroundMusicTT->setColor(Color3B(255, 255, 0));
    mpBackGroundMusicTT->setPosition(Vec2(size.width/2+160, size.height/2+30));
    addChild(mpBackGroundMusicTT);
    
    mpBackGroundSoundEffect=Label::create();
    mpBackGroundSoundEffect->setString("游戏音效：");
    mpBackGroundSoundEffect->setSystemFontSize(30);
    mpBackGroundSoundEffect->setColor(Color3B(0, 255, 255));
    mpBackGroundSoundEffect->setPosition(Vec2(size.width/2+80, size.height/2-30));
    addChild(mpBackGroundSoundEffect);
    
    
    mpBackGroundSoundEffectTT=CCLabelTTF::create("", "", 30);
    mpBackGroundSoundEffectTT->setColor(Color3B(0, 255, 255));
    mpBackGroundSoundEffectTT->setPosition(Vec2(size.width/2+160, size.height/2-30));
    addChild(mpBackGroundSoundEffectTT);
    
    int bValue=UserDefault::getInstance()->getIntegerForKey("BackGroundMusic");
    int gValue=UserDefault::getInstance()->getIntegerForKey("SoundEffectMusic");
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

    
    return true;
}

//void GameSetting::registerWithTouchDispatcher(void)
//{
//    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 5, true);
//}
//bool GameSetting::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCPoint touchPoint=pTouch->getLocation();
//    if (mpBackGroundMusicTT->boundingBox().containsPoint(touchPoint)) {
//        if (mbBMusicIsOpen) {
//            mbBMusicIsOpen=false;
//            mpBackGroundMusicTT->setString("关");
//            UserDefault::getInstance()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_CLOSE);
//            UserDefault::getInstance()->flush();
//        }
//        else
//        {
//            mbBMusicIsOpen=true;
//            mpBackGroundMusicTT->setString("开");
//            UserDefault::getInstance()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_OPEN);
//            UserDefault::getInstance()->flush();
//        }
//    }
//
//    if (mpBackGroundSoundEffectTT->boundingBox().containsPoint(touchPoint)) {
//        if (mbGMusicIsOpen) {
//            mbGMusicIsOpen=false;
//            mpBackGroundSoundEffectTT->setString("关");
//            UserDefault::getInstance()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_CLOSE);
//            UserDefault::getInstance()->flush();
//        }
//        else
//        {
//            mbGMusicIsOpen=true;
//            mpBackGroundSoundEffectTT->setString("开");
//            UserDefault::getInstance()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_OPEN);
//            UserDefault::getInstance()->flush();
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
    
    TransitionShrinkGrow * transition=TransitionShrinkGrow::create(1.0f,HelloWorld::createScene());
    Director::getInstance()->replaceScene(transition);
    
}
