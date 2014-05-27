//
//  AECollisionInfo.cpp
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#include "AECollisionInfo.h"

AECollisionInfo * AECollisionInfo::create(){
    AECollisionInfo * collisionInfo = new AECollisionInfo();
    collisionInfo->autorelease();
    return collisionInfo;
}