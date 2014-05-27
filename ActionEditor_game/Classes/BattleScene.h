//
//  BattleScene.h
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#ifndef __ActionEditor__BattleScene__
#define __ActionEditor__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "GLES-Render.h"
USING_NS_CC;


class BattleScene : public cocos2d::Layer, public b2ContactListener
{
private:
    EventListenerTouchOneByOne * _touchListener;
    
private:
    void initPhysicsWorld();
    void initListeners();
    void addNewSpriteAtPosition(Vec2 p);
protected:
    b2World * m_world;
    GLESDebugDraw * m_debugDraw;
protected:
    virtual void update(float delta);
public:
    ~BattleScene();
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(BattleScene);
    
    
    // methods for b2ContactListener
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    
    // virtual void registerWithTouchDispatcher();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
public:
    b2World * getWorld(){ return m_world;};
};

#endif /* defined(__ActionEditor__BattleScene__) */
