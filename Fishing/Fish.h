//
//  Fish.h
//  Fishing
//
//  Created by 朱亚斌 on 13-2-17.
//
//  这个名字我会起，鱼，没查字典，英语差真是硬伤啊，加油！
//

#ifndef __Fishing__Fish__
#define __Fishing__Fish__

#include "cocos2d.h"

typedef enum
{
    FishNormal = 0,
    FishGold,
    FishShark
} FishType;

class Fish : public cocos2d::CCSprite
{
public:
    Fish(void);
    ~Fish();
    bool isCatch;
    CREATE_FUNC(Fish);

public:
    bool randomCatch(int level);
    void addPath();
    
    /**
     * 有鱼出没，咱要知道他的抛物线，起始点与起始角度，以及持续时间
     *
     **/
    void move(cocos2d::CCSprite *parabola, const cocos2d::CCPoint startP, const cocos2d::CCPoint endP,  float startAngle, float endAngle, float dirTime);
    

private:
    FishType type;
    cocos2d::CCAction *path;
    
    void removeSelf();
};

#endif /* defined(__Fishing__Fish__) */
