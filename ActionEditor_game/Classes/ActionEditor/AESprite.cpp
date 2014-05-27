//
//  AESprite.cpp
//  ActionEditor
//
//  Created by huxiaozhou on 14-5-23.
//
//

#include "AESprite.h"
#include "AEManager.h"

AESprite* AESprite::create(const std::string& filename){
    AESprite * sprite = AESprite::create();
    sprite->initWithFile(filename);
    return sprite;
}

AESprite* AESprite::createWithSpriteFrameName(const std::string& spriteFrameName){
    AESprite * sprite = AESprite::create();
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    sprite->initWithSpriteFrame(frame);
    return sprite;
}

void AESprite::spriteFrameChanged(int index){
    //销毁当前collisionList内的body
    std::vector<b2Body*>::iterator iter;
    for (iter=collisionAreas.begin();iter!=collisionAreas.end();iter++)
    {
        AEManager::getInstance()->getWorld()->DestroyBody(*iter);
    }
    collisionAreas.clear();
    
    Vec2 targetPos;
    static int mmssf = 1;
    if (mmssf % 3 == 0 ) {
        targetPos= Vec2(0, 120);
    }else if(mmssf % 3 == 1){
        targetPos= Vec2(100, 120);
    }else{
        targetPos= Vec2(200, 120);
    }
    mmssf++;
    
    targetPos = this->convertToWorldSpace(targetPos);
    
    //重新生成collisionList内的body
    b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(targetPos.x/PTM_RATIO, targetPos.y/PTM_RATIO);
	b2Body *body = AEManager::getInstance()->getWorld()->CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);//These are mid points for our 1m box
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
    body->SetGravityScale(4.0);
    
    
    //加入到碰撞区域
    collisionAreas.push_back(body);
}







