#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameConfig.h"

#define MAX_ENEMY 50
#define MOVESPEED 15

#define KProgressTag 100

using namespace cocos2d;
using namespace CocosDenshion;

const int GameConfig::WinWidth = 1024;
const int GameConfig::WinHeight = 768;

float GameConfig::sx = 1;
float GameConfig::sy = 1;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    GameConfig::sx = size.width / GameConfig::WinWidth;
    GameConfig::sy = size.height / GameConfig::WinHeight;

    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    Energy = 1000;
    maxEnergy = 1000;
    this->setTouchEnabled(true);
    this->loadTexture();
    this->initUITab();
    
    srand(time(NULL));
    
    while (fishSheet->getChildren()->count() < MAX_ENEMY)
    {
        this->addFish();
    }
    
    this->schedule(schedule_selector(HelloWorld::updateGame), 0.05);

    
    return true;
}


void HelloWorld::loadTexture()
{
    CCSprite *bg = new CCSprite();
    bg->initWithFile("bj01.jpg");
    bg->setPosition(ccp(512, 368));
    this->addChild(bg);
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("fish.plist");
    cache->addSpriteFramesWithFile("fish2.plist");
    cache->addSpriteFramesWithFile("fish3.plist");
    cache->addSpriteFramesWithFile("cannon.plist");
    
    fishSheet = CCSpriteBatchNode::create("fish.png");
    fish2Sheet = CCSpriteBatchNode::create("fish2.png");
    flueSheet = CCSpriteBatchNode::create("fish3.png");
    cannonSheet = CCSpriteBatchNode::create("cannon.png");
    
    this->addChild(fishSheet);
    this->addChild(fish2Sheet);
    this->addChild(flueSheet);
}

void HelloWorld::initUITab()
{
    float sx = GameConfig::sx;
    float sy = GameConfig::sy;
    CCSprite* energyBox = new CCSprite();
    energyBox->initWithFile("ui_2p_004.png");
    energyBox->setAnchorPoint(ccp(0.5, 0.5));
    energyBox->setScale(MIN(sx, sy)); // 圆形要等比例缩放
    energyBox->setPosition(ccp(520 * sx, 30 * sy));
   
    this->addChild(energyBox);
    
    this->engryPointer = new CCSprite();
    this->engryPointer->initWithFile("ui_2p_005.png");
    engryPointer->setAnchorPoint(ccp(0.5, 0.5));
    engryPointer->setScale(MIN(sx, sy)); // 圆形要等比例缩放
    this->engryPointer->setPosition(ccp(520 * sx, 30 * sy));
    this->engryPointer->setRotation(180);

    this->addChild(this->engryPointer);
    
    
    CCSprite *bgExp = new CCSprite();
    bgExp->setScaleX(sx);
    bgExp->setScaleY(sy);
    bgExp->initWithFile("ui_box_01.png");
    bgExp->setPosition(ccp(500 * sx, 705 * sy));
    this->addChild(bgExp);
    
    CCSprite *bgNum =new CCSprite();
    bgNum->setScaleX(sx);
    bgNum->setScaleY(sy);
    bgNum->initWithFile("ui_box_02.png");
    bgNum->setPosition(ccp(440 * sx, 90 * sy));
    this->addChild(bgNum);
    
    this->addChild(cannonSheet);
    
    score1 = UIRollNum::create();
    score1->setScaleX(sx);
    score1->setScaleY(sy);
    score1->setNumber(10000);
    score1->setPosition(ccp(365 * sx, 17 * sy));
    this->addChild(score1, 100);
    
    gun = CCSprite::createWithSpriteFrameName("actor_cannon1_71.png");
    gun->setScaleX(sx);
    gun->setScaleY(sy);
    gun->setPosition(ccp(520 * sx, 50 * sy));
    cannonSheet->addChild(gun);
}

void HelloWorld::updateGame(cocos2d::CCTime dt)
{
    CCObject *fish0;
    CCObject *flue0;
    Fish *fish;
    Flue *flue;
    CCScaleTo *scale0 = CCScaleTo::create(0.3, 1.1);
    CCScaleTo *scale1 = CCScaleTo::create(0.3, 0.9);
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCARRAY_FOREACH(fishSheet->getChildren(), fish0)
    {
        fish = (Fish*)fish0;
        if(fish->isCatch)
            continue;
        
        // 碰撞
        CCARRAY_FOREACH(fish2Sheet->getChildren(), flue0)
        {
            flue = (Flue*)flue0;
            // 碰到了
            if(fish->boundingBox().containsPoint(flue->getPosition()))
            {
                if(!fish->randomCatch(fish->getTag()))
                {
                    flue->isCatching = false;
                    break;
                }
                else
                {
                    flue->isCatching = (false);
                    fish->isCatch = true;
                    
                    CCArray *fishi01 = CCArray::create();
                    for (int i = 1; i < 3; i++)
                    {
                        fishi01->addObject(cache->spriteFrameByName(CCString::createWithFormat("fish0%d_catch_0%d.png", fish->getTag(), i)->getCString()));
                    }
                    
                    CCActionInterval *fish01_catch_act = CCRepeat::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(fishi01, 0.2f)), 2);
                    
                    CCSequence* fishSeq = CCSequence::create(fish01_catch_act, CCCallFuncO::create(this, callfuncO_selector(HelloWorld::afterCatch), fish), NULL);
                    
                    fish->stopAllActions();
                    fish->runAction(fishSeq);
                    
                    CCSprite *gold = new CCSprite();
                    gold->initWithFile("+5.png");
                    gold->setPosition(fish->getPosition());
                    
                    CCSequence * goldSeq = CCSequence::create(scale0, scale1, scale0, scale1, CCCallFuncO::create(this, callfuncO_selector(HelloWorld::afterShow), gold), NULL);
                    gold->runAction(goldSeq);
                    
                    this->addChild(gold);
                    
                }
            }
            
        }
    }
    
    CCARRAY_FOREACH(fish2Sheet->getChildren(), flue0)
    {
        flue = (Flue*)flue0;
        if(flue->isCatching)
            continue;
        
        flue->removeFromParentAndCleanup(false);
        
        Flue *tapFlue = (Flue*)Flue::createWithSpriteFrameName("net01.png");
        tapFlue->setPosition(flue->getPosition());
        
        CCSequence * flueSeq = CCSequence::create(scale0, scale1, scale0, scale1, CCCallFuncO::create(this, callfuncO_selector(HelloWorld::afterShowFlue), tapFlue), NULL);
        
        tapFlue->runAction(flueSeq);
        flueSheet->addChild(tapFlue);
        score1->setNumber(score1->getNumber() + 5);
    }
    
    while (fishSheet->getChildren()->count() < MAX_ENEMY)
    {
        this->addFish();
    }
}

void HelloWorld::updateEnermy(int en)
{
    if (Energy <= 0)
    {
        return;
    }
    
    Energy -= en;
    
    float rotation = 180.0 * Energy / maxEnergy;
    
    engryPointer->setRotation(rotation);
}

void HelloWorld::addFish()
{
    int type = rand() % 8 + 1;
    CCArray *fishi01 = CCArray::create();
    for(int i = 1; i <10; i++)
    {
        fishi01->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("fish0%d_0%d.png",type,i)->getCString()));
    }
    
    fish01_act = CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(fishi01, 0.2f)));
    
    Fish *fish = (Fish*)Fish::createWithSpriteFrameName(CCString::createWithFormat("fish0%d_0%d.png",type,1)->getCString());
    fish->setScale(1.2f);
    fish->setTag(type);
    fish->isCatch = false;
    fish->runAction(fish01_act);
    fish->addPath();
    fishSheet->addChild(fish);
}

void HelloWorld::turnGun(cocos2d::CCPoint &pos)
{
    float angle = (pos.y - gun->getPosition().y) / (pos.x - gun->getPosition().x);
    angle = atanf(angle) / M_PI * 180;;
    
    if(angle < 0)
    {
        gun->setRotation(-(90 + angle));
    }
    else if(angle > 0)
    {
        gun->setRotation(90 - angle);
    }
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint pos = touch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_72.png"));
    this->turnGun(pos);
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint pos = touch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_72.png"));
    this->turnGun(pos);
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    float sx = GameConfig::sx;
    float sy = GameConfig::sy;
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint pos = touch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_71.png"));
    
    score1->setNumber(score1->getNumber() - (rand()%20) - 2);
    Flue *labelBoard = (Flue*)Flue::createWithSpriteFrameName("bullet01.png");
    labelBoard->setPosition(ccp(512 * sx, 50 * sy));
    labelBoard->isCatching = (true);
    
    CCMoveTo *move = CCMoveTo::create(1.0, pos);
    CCSequence *flueSeq = CCSequence::create(move, CCCallFuncO::create(this, callfuncO_selector(HelloWorld::ShowFlue), labelBoard), NULL);
    
    labelBoard->setRotation(gun->getRotation());
    labelBoard->runAction(flueSeq);
    fish2Sheet->addChild(labelBoard);
    
    this->updateEnermy(rand() % 20);
}

void HelloWorld::ShowFlue(cocos2d::CCNode *sender)
{
    CCSprite *sp = (CCSprite*)sender;
    
    fish2Sheet->removeChild(sp, false);
    sp->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("net01.png"));
    CCScaleTo *scale0 = CCScaleTo::create(0.3, 1.1);
    CCScaleTo *scale1 = CCScaleTo::create(0.3, 0.9);
    CCSequence *flueSeq = CCSequence::create(scale0, scale1, scale0, scale1, CCCallFuncO::create(this, callfuncO_selector(HelloWorld::afterShowFlue), sp), NULL);
    sp->runAction(flueSeq);
    flueSheet->addChild(sp);
}

void HelloWorld::afterShowFlue(cocos2d::CCNode *sender)
{
    CCSprite *sp = (CCSprite*)sender;
    flueSheet->removeChild(sp, false);
}

void HelloWorld::afterShow(cocos2d::CCNode *sender)
{
    CCSprite *sp = (CCSprite*)sender;
    this->removeChild(sp, false);
}

void HelloWorld::afterCatch(cocos2d::CCNode *sender)
{
    CCSprite *sp = (CCSprite*)sender;
    fishSheet->removeChild(sp, false);
}