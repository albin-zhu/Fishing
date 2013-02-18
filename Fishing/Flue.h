//
//  Flue.h
//  Fishing
//
//  Created by 朱亚斌 on 13-2-17.
//
//  渔网，flue朗道上查到的，要是用我自己的叫法就做FishNet了，哈哈，咱要专业一点
//

#ifndef __Fishing__Flue__
#define __Fishing__Flue__

#include "cocos2d.h"

class Flue : public cocos2d::CCSprite
{
public:
    Flue(void);
    ~Flue();
    
    CREATE_FUNC(Flue);
    bool isCatching;
};

#endif /* defined(__Fishing__Flue__) */
