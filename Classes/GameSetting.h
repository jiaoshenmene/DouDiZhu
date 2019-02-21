//
//  GameSetting.h
//  MyGame
//
//  Created by user on 14-4-22.
//
//

#ifndef __MyGame__GameSetting__
#define __MyGame__GameSetting__

#include "cocos2d.h"
USING_NS_CC;

typedef enum TargetSettingScence
{
    TargetSettingScenceHelloWorld,
}TargetSettingScence;
class GameSetting : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameSetting);
    
public:
    CCLabelTTF * mpBackGroundMusic;
    CCLabelTTF * mpBackGroundSoundEffect;
    CCLabelTTF * mpBackGroundMusicTT;
    CCLabelTTF * mpBackGroundSoundEffectTT;
//    virtual void registerWithTouchDispatcher(void);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

public:
    //界面切换
    TargetSettingScence targetScence;
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    static CCScene * creatWithSenceTarget(TargetSettingScence target);
    bool initWithSenceTarget(TargetSettingScence target);
    void reolaceScenceUpdate(float t);
    
    void menuCloseCallback();
private:
    bool mbBMusicIsOpen;
    bool mbGMusicIsOpen;
    
};
#endif /* defined(__MyGame__GameSetting__) */
