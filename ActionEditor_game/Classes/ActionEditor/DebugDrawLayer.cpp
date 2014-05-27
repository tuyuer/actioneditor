//
//  DebugDrawLayer.cpp
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#include "DebugDrawLayer.h"


DebugDrawLayer::~DebugDrawLayer(){
    m_world = NULL;
}

void DebugDrawLayer::setWorld(b2World * world){
    m_world = world;
}

void DebugDrawLayer::drawBox2dDebugData(){
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    m_world->DrawDebugData();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void DebugDrawLayer::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated){
    CCLayer::draw(renderer, transform, transformUpdated);
    
    //擦，改成渲染管道线了
    _customDebugDrawCommand.init(10000000);
    _customDebugDrawCommand.func = CC_CALLBACK_0(DebugDrawLayer::drawBox2dDebugData, this);
    renderer->addCommand(&_customDebugDrawCommand);
}









