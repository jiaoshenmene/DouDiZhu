//
//  StartGame.h
//  MyGame
//
//  Created by 秦晶 on 14-1-3.
//
//

#ifndef __MyGame__StartGame__
#define __MyGame__StartGame__


#include "cocos2d.h"
USING_NS_CC;

typedef enum TargetPlayScence
{
    TargetPlayScenceHelloWorld,
}TargetPlayScence;
class StartGame : public cocos2d::Layer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::Scene* scene();
    
//    virtual void registerWithTouchDispatcher(void);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    ~StartGame();
public:
    //用来存放所有的牌
    std::map<std::string, std::vector<Sprite *>> mpRootDic;
    std::vector<std::string> mpRootKeys;
  
    
    CCArray * mpArrByRand;
    //储存随机后的精灵
    CCArray * mpKeyArrByRand;
    //储存随机后的精灵对应的key
    
    CCArray * mpPersonArr;
    CCArray * mpKeysOfpersonArr;
    //储存玩家的牌及对应的key
    CCArray * mpComputerNextArr;
    CCArray * mpKeysOfcomputerNextArr;
    //储存玩家下家的牌及对应的key
    CCArray * mpComputerUpArr;
    CCArray * mpKeysOfcomputerUpArr;
    //储存玩家上家的牌及对应的key
    CCArray * mpLastThreeArr;
    CCArray * mpKeysOflastThreeArr;
    //储存底牌及对应的key
    CCArray * mpPokerWhetherMoveArr;
    //储存移动状态
    CCArray * mpPokerIsSlectArr;
    
    CCArray * mpSelectValueArr;
    CCArray * mpSelectKeysArr;
    //用来存储选中玩家的精灵和对应的key
   
    CCArray * mpNextComputerSelectArr;
    CCArray * mpKeysOfnextComputerSelectArr;
    //下家电脑应该出的牌
    CCArray * mpUpComputerSelectArr;
    CCArray * mpKeysOfupComputerSelectArr;;
    //上家电脑应该出的牌 
    
    CCLabelTTF * mpUpComIdentityLabel;
    CCLabelTTF * mpPersonIdentityLabel;
    CCLabelTTF * mpNextComIdentityLabel;//显示每个玩家身份的Label
    
    Label * mpTimerCountDown;
    Label * mpNextComputertimerCountDown;
    Label * mpUpComputertimerCountDown;
    //显示倒计时
    CCLabelTTF * mpComputerUpLabel;
    CCLabelTTF * mpPersonLabel;
    CCLabelTTF * mpComputerNextLabel;
    //显示各个玩家不出的label
    
    CCLabelTTF * mpPersonHaveCoinsLabel;
    CCLabelTTF * mpUpComHaveCoinsLabel;
    CCLabelTTF * mpNextComHaveCoinsLabel;
    //显示各个玩家拥有的金币数
    
    CCLabelTTF * mpGameOverLabel;
    CCLabelTTF * mpGameAgainLabel;
    //继续游戏的label
    
    bool upcomputerIsOutOfCards;
    //记录上家电脑本轮过牌还是出牌
    bool personIsOutOfCards;
    //记录玩家本轮过牌还是出牌
    bool nextcomputerIsOutOfCards;
    //记录下家电脑本轮过牌还是出牌
    
    
    bool mbPersonIsWin;
    bool mbUpComputerIsWin;
    bool mbNextComputerIsWin;
    
    
    bool mbPersonTimeOutOfCards;//判断玩家思考时间超过限制时间
    bool mbCanOrCannotOutOfCards;//判断玩家是否可以出牌
    bool mbPersonFirstIsOutOfCards;
    
    int miPokerTypeID;//记录牌的类型

    float mfWidth;//玩家牌之间的距离
    int   miBaseTime;//基于底分得翻倍数

    bool mbPersonIsLandlord;
    bool mbUpComputerIsLandlord;
    bool mbNextComputerISLandlord;
    
    bool mbGameIsOver;
    
public:
    void initArraysAndRootDic();//初始化
    void gameStart();//开始游戏
//    void update(float);
    void adjustPokerOrder();//调整牌序
    void sendPokerOutEveryPlayer();//发牌到每个玩家
    void displayPersonPoker();//显示person手中的牌
    void sortedForArray(CCArray *,CCArray *);//发到手中的牌排序
    void outOfTheCards();//符合规则出牌
    void personConsiderTimeRunOutAndRandOneOfPersonPokers();
    void passThisRecycle();//过牌

    void personConsiderTimeCountDown(float considerTime);
    void nextConsiderTimeCountDown(float considerTime);
    void upConsiderTimeCountDown(float considerTime);

    void nextComputeroutOfTheCards();
    //下家电脑出牌
    void personOutOfCardsManyTimeNextStartConsider(float t);
    //玩家出牌几秒后下家电脑考虑出牌
    void upComputeroutOfTheCards();
    //上家电脑出牌
    void nextComputerOutOfCardsManyTimeUpStartConsider(float t);
    //下家电脑出牌几秒后上家电脑考虑出牌
    void upclearPersonShowPokers(float t);
    //如果本轮只有玩家出牌，上家过牌后，定时删除
    void clearSelectedPokersType();
    void refreshGameOverScreenDisplay(int decide);
    void gameAgain();//重新开始游戏
    void clearScreenAndManyArr();
    void unscheduleInStartGameAllUpdate();

public:
    void menuCloseCallback();
    TargetPlayScence targetPlayScence;
//
//    virtual void onEnter();
//    virtual void onExit();
//    virtual void onEnterTransitionDidFinish();
//    
    static Scene * creatWithSenceTarget(TargetPlayScence target);
    bool initWithSenceTarget(TargetPlayScence target);
    void reolaceScenceUpdate(float t);

    static StartGame *create();
};

#endif /* defined(__MyGame__StartGame__) */
