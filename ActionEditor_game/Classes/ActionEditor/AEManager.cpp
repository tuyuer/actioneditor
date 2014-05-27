//
//  AEManager.cpp
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#include "AEManager.h"

static AEManager * s_sharedAEManager = NULL;
AEManager * AEManager::getInstance(){
    if (!s_sharedAEManager) {
        s_sharedAEManager = new AEManager();
    }
    return s_sharedAEManager;
}

void AEManager::setWorld(b2World * world){
    _world = world;
}

b2World * AEManager::getWorld(){
    return _world;
}

void AEManager::setWorldNode(Node * worldNode){
    _worldNode = worldNode;
}

Node * AEManager::getWorldNode(){
    return _worldNode;
}








