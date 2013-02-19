//
//  UIRollNum.h
//  Fishing
//
//  Created by 朱亚斌 on 13-2-17.
//
//

#ifndef __Fishing__UIRollNum__
#define __Fishing__UIRollNum__

#include "cocos2d.h"
#include "UINumber.h"

class UIRollNum : public cocos2d::CCSprite
{
public:
    UIRollNum(void);
    ~UIRollNum();
    CREATE_FUNC(UIRollNum);
    NumStyle style;
    virtual bool init();
    
    void rebuildEffect();
    void clearEffect();
    void setNumber(int num);
    int getNumber();
    
private:
    int m_nNumber;
    int m_maxCol;
    cocos2d::CCArray *numArray;
    cocos2d::CCPoint m_point;
    bool zeroFill;
    
};

#endif /* defined(__Fishing__UIRollNum__) */
