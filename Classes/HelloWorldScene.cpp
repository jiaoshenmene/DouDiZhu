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
#include "PublicItem.h"


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

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    if (!UserDefault::getInstance()->getBoolForKey("GameSettingXML")) {
        UserDefault::getInstance()->setBoolForKey("GameSettingXML", true);
        UserDefault::getInstance()->setIntegerForKey("BackGroundMusic", GAME_MUSIC_OPEN);
        UserDefault::getInstance()->setIntegerForKey("SoundEffectMusic", GAME_MUSIC_OPEN);
        
        UserDefault::getInstance()->setIntegerForKey("CoinsOfPerson", EVERY_PLAYER_COINS_NUMBER);
        UserDefault::getInstance()->setIntegerForKey("CoinsOfUpComputer", EVERY_PLAYER_COINS_NUMBER);
        UserDefault::getInstance()->setIntegerForKey("CoinsOfNextComputer",EVERY_PLAYER_COINS_NUMBER);
        UserDefault::getInstance()->flush();
        //初始化游戏设置
        //        CCLOG("文件不存在 创建文件");
    }
    else
    {
        //        CCLOG("文件已经存在");
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    Sprite* pSprite = PublicItem::backgroundSprite();
    this->addChild(pSprite, 0);
    
    
    auto startItem = MenuItemFont::create("开始游戏", CC_CALLBACK_0(HelloWorld::startGame, this));
    startItem->setFontName("Arial");
    startItem->setFontSizeObj(32);
    startItem->setColor(Color3B(128, 255, 255));
    startItem->setPosition(Vec2(3*size.width/4, 3.5*size.height/5));
    
    

    auto settingItem = MenuItemFont::create("游戏设置", CC_CALLBACK_0(HelloWorld::settingGame, this));
    settingItem->setFontName("Arial");
    settingItem->setFontSizeObj(32);
    settingItem->setColor(Color3B(128, 255, 255));
    settingItem->setPosition(Vec2(3*size.width/4, 2.5*size.height/5));
    
    
    auto exitItem = MenuItemFont::create("退出游戏", CC_CALLBACK_0(HelloWorld::menuCloseCallback, this));
    exitItem->setFontName("Arial");
    exitItem->setFontSizeObj(32);
    exitItem->setColor(Color3B(128, 255, 255));
    exitItem->setPosition(Vec2(3*size.width/4, 1.5*size.height/5));
    
    
    auto startMenu = Menu::create(startItem,settingItem,exitItem, NULL);
    startMenu->setPosition(Vec2::ZERO);
    this->addChild(startMenu, 1);
    
    return true;
}
#pragma mark -----进入游戏界面

void HelloWorld::startGame()
{
    TransitionSlideInL *transition = TransitionSlideInR::create(0.2f, StartGame::scene());
    Director::getInstance()->replaceScene(transition);
}
#pragma mark -----进入最高分界面
void HelloWorld::settingGame()
{
    TransitionSlideInL * transition = TransitionSlideInR::create(0.2f, GameSetting::scene());
    Director::getInstance()->replaceScene(transition);
}

void HelloWorld::menuCloseCallback()
{
    printf("menuCloseCallback");
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
