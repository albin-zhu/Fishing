#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Fish.h"
#include "Flue.h"
#include "UIRollNum.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(HelloWorld);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    cocos2d::CCSpriteBatchNode *flueSheet;
    cocos2d::CCSpriteBatchNode *fishSheet;
    cocos2d::CCSpriteBatchNode *fish2Sheet;
    cocos2d::CCSpriteBatchNode *cannonSheet;
    cocos2d::CCAction *fish01_act;
    UIRollNum *score1;
    cocos2d::CCSprite *gun;
    int Energy;
    int maxEnergy;
    cocos2d::CCSprite *engryPointer;
    
private:
    void turnGun(cocos2d::CCPoint &pos);
    void loadTexture();
    void initUITab();
    void addFish();
    void updateGame(cocos2d::CCTime dt);
    void ShowFlue(CCNode*);
    void afterCatch(CCNode*);
    void afterShow(CCNode*);
    void afterShowFlue(CCNode*);
    void updateEnermy(int);
};



#endif // __HELLOWORLD_SCENE_H__
