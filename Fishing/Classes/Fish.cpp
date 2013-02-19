//
//  Fish.cpp
//  Fishing
//
//  Created by Albin Zhu on 13-2-17.
//
//

#include "Fish.h"
#include "GameConfig.h"

using namespace cocos2d;

Fish::Fish(void)
{
    path = NULL;
    type = FishNormal;
    isCatch = false;
}

Fish::~Fish()
{
    // TODO sth
}

bool Fish::randomCatch(int level)
{
    isCatch =rand() % 10 >= level;
    return isCatch;
}

void Fish::move(CCSprite* para, const cocos2d::CCPoint startPoint, const cocos2d::CCPoint endPoint, float startAngle, float endAngle, float dirTime)
{
    float sx = startPoint.x;
    float sy = startPoint.y;
    float ex =endPoint.x+rand()%50;
    float ey =endPoint.y+rand()%150;
    int h = para->getContentSize().height * 0.5;
    
    CCPoint pos = ccp(sx-200+rand()%400, sy-200+rand()%400);
    para->setPosition(pos);
    para->setRotation(startAngle);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(sx, sy); // 起始点
    bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+rand()%300); //控制点
    bezier.endPosition = ccp(endPoint.x-30, endPoint.y+h); // 结束位置
    CCBezierTo *actionMove = CCBezierTo::create(dirTime, bezier);
    CCRotateTo *actionRotate = CCRotateTo::create(dirTime, endAngle);
    
    CCActionInterval *action = CCSpawn::createWithTwoActions(actionMove, actionRotate);
    CCSequence *sq = CCSequence::create(action, CCCallFunc::create(this, callfunc_selector(Fish::removeSelf)), NULL);
    
    para->runAction(sq);
    
}

void Fish::removeSelf()
{
    this->removeFromParentAndCleanup(true);
}

void Fish::addPath()
{
    float sx = GameConfig::sx;
    float sy = GameConfig::sy;
    
    switch (rand() % 7)
    {
        case 0:
            this->move(this, ccp(1200 * sx, 200 * sy), ccp(-500 * sx, 800 * sy), 0, 20, rand()%10+15);
            break;
        case 1:
            this->move(this, ccp(-200 * sx, 300 * sy), ccp(1300 * sx, 400 * sy), 180, 170, rand()%10+18);
            break;
        case 2:
            this->move(this, ccp(-200 * sx, 300 * sy), ccp(1000 * sx, -200 * sy), 190, 200, rand()%10+18);
            break;
        case 3:
            this->move(this, ccp(1300 * sx, 400 * sy), ccp(-200 * sx, 300 * sy), 10, 5, rand()%10+18);
            break;
        case 4:
            this->move(this, ccp(400 * sx, -1200 * sy), ccp(600 * sx, 1000 * sy), 90, 93, rand()%10+18);
            break;
        case 5:
            this->move(this, ccp(600 * sx, 1000 * sy), ccp(400 * sx, -200 * sy), -70, -80, rand()%10+18);
            break;
        case 6:
            this->move(this, ccp(1200 * sx, 2100 * sy), ccp(-200 * sx, 300 * sy), 30, -30, rand()%10+18);
            break;
    }
}

