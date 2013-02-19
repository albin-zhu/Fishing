//
//  UIRollNum.cpp
//  Fishing
//
//  Created by Albin Zhu on 13-2-17.
//
//

#include "UIRollNum.h"

using namespace cocos2d;

UIRollNum::UIRollNum(void)
{
    
}

UIRollNum::~UIRollNum()
{
    CC_SAFE_DELETE_ARRAY(this->numArray);
}

bool UIRollNum::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!CCSprite::init());
        bRet = true;
        m_nNumber = 0;
        m_maxCol = 6;
        numArray = CCArray::create();
        numArray->retain();
        zeroFill = true;
        style = NumStyleNormal;
        this->clearEffect();
        
    } while (0);
    return bRet;
}

int UIRollNum::getNumber()
{
    return m_nNumber;
}

void UIRollNum::setNumber(int num)
{
    if (m_nNumber != num)
    {
        m_nNumber = num;
        this->rebuildEffect();
    }
}

void UIRollNum::rebuildEffect()
{
    int i=0;
    int num = m_nNumber;
    while (1) {
        if (num<=0) {
            if(m_maxCol<=i && zeroFill)
                break;
        }
        int showNum = num%10;
        
        UINumber* pNumber = (UINumber*)numArray->objectAtIndex(i);
        pNumber->setNumber(showNum);
        i++;
        num = num/10;
    }
}

void UIRollNum::clearEffect()
{
    for(int i=0;i<numArray->count();i++)
    {
        
        UINumber* pNumber = (UINumber *)numArray->objectAtIndex(i);
        this->removeChild(pNumber, true);
    }
    numArray->removeAllObjects();
    
    for (int i=0; i< m_maxCol; i++) {
        
        UINumber* pNumber = new UINumber;
        pNumber->init(style);
        numArray->addObject(pNumber);
        pNumber->setNumber(0);
        pNumber->setPosition(ccp(m_point.x - i*NUM_WIDTH, m_point.y));
        pNumber->setAnchorPoint(ccp(1, 0.5));
        this->addChild(pNumber, 100);

    }

}