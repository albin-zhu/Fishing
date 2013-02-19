//
//  UINumber.h
//  Fishing
//
//  Created by 朱亚斌 on 13-2-17.
//
//

#ifndef __Fishing__UINumber__
#define __Fishing__UINumber__

#define NUM_WIDTH 20
#define NUM_HEIGHT 20

#include "cocos2d.h"

typedef enum
{
    NumStyleNormal,
    NumStyleSameTime,
}NumStyle;

class UINumber : public cocos2d::CCSprite
{
public:
    UINumber(void);
    ~UINumber();
    
    CREATE_FUNC(UINumber);
    
public:
    bool init(NumStyle style);
    virtual bool init();
    void setNumber(int num);
    void onRollDown(cocos2d::CCTime dt);
    void onRollUp(cocos2d::CCTime dt);
    void setup();
    
private:
    NumStyle m_style;
    int m_num;
    int m_nPosCur;
    int m_nPosEnd;
    int m_nMoveLen;
    
    CC_SYNTHESIZE(cocos2d::CCTexture2D*, nTexture, NTextTure);
    
};

#endif /* defined(__Fishing__UINumber__) */
