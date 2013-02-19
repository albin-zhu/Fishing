//
//  UINumber.cpp
//  Fishing
//
//  Created by Albin Zhu on 13-2-17.
//
//

#include "UINumber.h"

using namespace cocos2d;

UINumber::UINumber(void)
{
    nTexture = NULL;
}

UINumber::~UINumber()
{
    CC_SAFE_DELETE(this->nTexture);
    this->unscheduleAllSelectors();
}

bool UINumber::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!CCSprite::init());
        bRet = true;
        m_style = NumStyleNormal;
        m_num = 0;
        m_nPosCur = 0;
        m_nPosEnd = 0;
        this->setup();
        
    } while (0);
    
    return bRet;
}

bool UINumber::init(NumStyle style)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!CCSprite::init());
        bRet = true;
        m_style = style;
        m_num = 0;
        m_nPosCur = 0;
        m_nPosEnd = 0;
        this->setup();
        
    } while (0);
    
    return bRet;
}

void UINumber::setup()
{
    CCImage* image = new CCImage();
    image->initWithImageFile("number.png");
    nTexture = new CCTexture2D();
    nTexture->initWithImage(image);
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(nTexture, CCRectMake(0, 0, NUM_WIDTH, NUM_HEIGHT));
    this->setDisplayFrame(frame);
}

void UINumber::setNumber(int num)
{
    m_nPosCur = NUM_HEIGHT * m_num;
    m_nPosEnd = NUM_HEIGHT * num;
    if (NumStyleNormal == m_style)
    {
        m_nMoveLen = 4;
    }
    else if (NumStyleSameTime == m_style)
    {
        m_nMoveLen = (m_nPosEnd-m_nPosCur)/20;
    }
    
    if (m_num > num)
    {
        this->schedule(schedule_selector(UINumber::onRollUp), 0.03);
    }
    else
    {
        this->schedule(schedule_selector(UINumber::onRollDown), 0.03);
    }
    m_num = num;
}

void UINumber::onRollDown(CCTime dt)
{
    m_nPosCur += m_nMoveLen;
    if (m_nPosCur >= m_nPosEnd) {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(UINumber::onRollDown));
    }
    
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(nTexture, CCRectMake(0, m_nPosCur, NUM_WIDTH, NUM_HEIGHT));
    this->setDisplayFrame(frame);
}

void UINumber::onRollUp(CCTime dt)
{
    m_nPosCur -= 4;
    if (m_nPosCur <= m_nPosEnd)
    {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(UINumber::onRollUp));
    }
    
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(nTexture, CCRectMake(0, m_nPosCur, NUM_WIDTH, NUM_HEIGHT));
    this->setDisplayFrame(frame);
}
