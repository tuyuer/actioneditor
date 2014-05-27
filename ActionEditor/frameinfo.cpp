#include "frameinfo.h"

FrameInfo::FrameInfo(){
    frameId = 0;
}

void FrameInfo::addDot(CollisionDot * dot){
    collisionDotList.push_back(dot);
}

void FrameInfo::removeDot(CollisionDot * dot){
    auto iter = std::find(collisionDotList.begin(), collisionDotList.end(), dot);
    if (iter != collisionDotList.end())
    {
         collisionDotList.erase(iter);
    }
}
