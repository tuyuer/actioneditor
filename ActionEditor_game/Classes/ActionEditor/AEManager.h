//
//  AEManager.h
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#ifndef __ActionEditor__AEManager__
#define __ActionEditor__AEManager__

#include <iostream>
#include "cocos2d.h"
#include "GLES-Render.h"
#define PTM_RATIO 32
USING_NS_CC;

class AEManager {
private:
    b2World * _world;
    Node * _worldNode;
public:
    void setWorld(b2World * world);
    b2World * getWorld();
    
    void setWorldNode(Node * worldNode);
    Node * getWorldNode();

    static AEManager * getInstance();
};

#endif /* defined(__ActionEditor__AEManager__) */
