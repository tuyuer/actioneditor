//
//  AESprite.h
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#ifndef __ActionEditor__AESprite__
#define __ActionEditor__AESprite__

#include <iostream>
#include "cocos2d.h"
#include "GLES-Render.h"
USING_NS_CC;

class AESprite:public Sprite {
private:
    std::vector<b2Body*> collisionAreas;
private:
    virtual void spriteFrameChanged(int index);
public:
    CREATE_FUNC(AESprite);
    static AESprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    static AESprite* create(const std::string& filename);
};


#endif /* defined(__ActionEditor__AESprite__) */
