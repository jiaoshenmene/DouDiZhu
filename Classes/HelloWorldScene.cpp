/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TypeEnmu.h"
#include "StartGame.h"
#include "GameSetting.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("GameSettingXML")) {
        CCUserDefault::sharedUserDefault()->setBoolForKey("GameSettingXML", true);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_OPEN);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_OPEN);
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfPerson", EVERY_PLAYER_COINS_NUMBER);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfUpComputer", EVERY_PLAYER_COINS_NUMBER);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinsOfNextComputer",EVERY_PLAYER_COINS_NUMBER);
        CCUserDefault::sharedUserDefault()->flush();
        //初始化游戏设置
        //        CCLOG("文件不存在 创建文件");
    }
    else
    {
        //        CCLOG("文件已经存在");
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("Backgroundimage.png");
    pSprite->setRotation(90);
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    startLabel=CCLabelTTF::create("开始游戏", "", 30);
    startLabel->setColor(ccc3(128, 255, 255));
    startLabel->setPosition(ccp(3*size.width/4, 3.5*size.height/5));
    addChild(startLabel);
    
    settingLabel=CCLabelTTF::create("游戏设置", "", 30);
    settingLabel->setColor(ccc3(128, 255, 255));
    settingLabel->setPosition(ccp(3*size.width/4, 2.5*size.height/5));
    addChild(settingLabel);
    
    exitLabel=CCLabelTTF::create("退出游戏", "", 30);
    exitLabel->setColor(ccc3(128, 255, 255));
    exitLabel->setPosition(ccp(3*size.width/4, 1.5*size.height/5));
    addChild(exitLabel);
    
    
    return true;
}
#pragma mark -----进入游戏界面

void HelloWorld::startGame()
{
    CCTransitionSlideInL * transition=CCTransitionSlideInR::create(0.2f,
                                                                   StartGame::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}
#pragma mark -----进入最高分界面
void HelloWorld::settingGame()
{
    CCTransitionSlideInL * transition=CCTransitionSlideInR::create(0.2f,
                                                                   GameSetting::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
