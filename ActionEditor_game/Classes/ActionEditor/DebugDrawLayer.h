//
//  DebugDrawLayer.h
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#ifndef __ActionEditor__DebugDrawLayer__
#define __ActionEditor__DebugDrawLayer__

#include <iostream>
#include "cocos2d.h"
#include "GLES-Render.h"
USING_NS_CC;


class DebugDrawLayer : public cocos2d::Layer
{
private:
    CustomCommand _customDebugDrawCommand;
private:

protected:
    b2World * m_world;
protected:
    virtual void drawBox2dDebugData();
    void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated);
public:
    ~DebugDrawLayer();
    CREATE_FUNC(DebugDrawLayer);
public:
    void setWorld(b2World * world);
};



#endif /* defined(__ActionEditor__DebugDrawLayer__) */
