//
//  BattleScene.cpp
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#include "BattleScene.h"
#include "VisibleRect.h"
#include "DebugDrawLayer.h"
#include "AESprite.h"
#include "AEManager.h"


USING_NS_CC;

BattleScene::~BattleScene(){
    delete m_world;
    delete m_debugDraw;
    m_world = NULL;
    m_debugDraw = NULL;
    
    _eventDispatcher->removeEventListener(_touchListener);
}

Scene* BattleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BattleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    auto debugDrawLayer = DebugDrawLayer::create();
    debugDrawLayer->setWorld(layer->getWorld());
    scene->addChild(debugDrawLayer,1000000);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initPhysicsWorld();
    this->initListeners();
    this->scheduleUpdate();
    
    AEManager::getInstance()->setWorld(m_world);
    AEManager::getInstance()->setWorldNode(this);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guanyu.plist");
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    auto spriteBack = Sprite::create("HelloWorld.png");
//    this->addChild(spriteBack);
//    spriteBack->setPosition(Vec2(240, 160));
    
    auto spriteAxeMan = AESprite::createWithSpriteFrameName("guanyu_1.png");
    this->addChild(spriteAxeMan);
    spriteAxeMan->setPosition(Vec2(240, 160));
    
    Vector<SpriteFrame*> aniFrames;
    for (int i=0; i< 37; i++) {
        auto frameName = StringUtils::format("guanyu_%d.png",i+1);
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        aniFrames.pushBack(spriteFrame);
    }
    
    auto axeManAttack = Animation::createWithSpriteFrames(aniFrames);
    axeManAttack->setDelayPerUnit(0.08);
    
    auto animate = Animate::create(axeManAttack);
    spriteAxeMan->runAction(RepeatForever::create(animate));
    
    return true;
}

bool BattleScene::onTouchBegan(Touch* touch, Event* event){
    this->addNewSpriteAtPosition(touch->getLocation());
    return true;
}
void BattleScene::onTouchMoved(Touch* touch, Event* event){
    
}
void BattleScene::onTouchEnded(Touch* touch, Event* event){
    
}

#pragma -
#pragma protectd methods


void BattleScene::update(float delta){
    
    int32 velocityIterations = 8;
	int32 positionIterations = 1;
    m_world->Step(delta, velocityIterations, positionIterations);
    
    
    for( b2Body *b = m_world->GetBodyList();b;b = b->GetNext() )
    {
        if(b->GetUserData() != NULL)
        {
            auto *myActor = (Sprite*)b->GetUserData();
            //,
            myActor->setPosition(Vec2((b->GetPosition().x )* PTM_RATIO,b->GetPosition().y * PTM_RATIO));
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );//设置精灵旋转方向
        }
    }
}


#pragma -
#pragma private methods
void BattleScene::initPhysicsWorld(){
    
    //设置DebugDraw
    uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
//	flags += b2Draw::e_jointBit;
//	flags += b2Draw::e_aabbBit;
//	flags += b2Draw::e_centerOfMassBit;
    
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	m_debugDraw->SetFlags(flags);
    
    //初始化世界
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    
    m_world = new b2World(gravity);
    m_world->SetDebugDraw(m_debugDraw);
    m_world->SetContactListener(this);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
}

void BattleScene::initListeners(){
    // Adds Touch Event Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BattleScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BattleScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(listener, -10);
    _touchListener = listener;
}

void BattleScene::addNewSpriteAtPosition(Vec2 p)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
	b2Body *body = m_world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
    
    auto spriteIcon = Sprite::create("Icon-29.png");
    this->addChild(spriteIcon);
    body->SetUserData(spriteIcon);
}


#pragma -
#pragma methods for b2ContactListener

void BattleScene::BeginContact(b2Contact* contact){
    static int beginContactCount = 0;
    log("begin_contact = %d",beginContactCount++);
}

void BattleScene::EndContact(b2Contact* contact){
    static int endContactCount = 0;
    log("end_contact = %d",endContactCount++);
}

void BattleScene::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){

}

void BattleScene::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){

}






















