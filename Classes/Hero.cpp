#include "Hero.h"
#include "PhysicsShapeCache.h"
#include "Static.h"
#include "AudioUtil.h"


#define HERO_PHYSICS_BODY "hero"
#define HERO_PNG "hero.png"
#define JUMP_SPEED 0.001
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define JUMP_SPEED 0.0005
#endif

bool Hero::init() 
{
	if (!Sprite::initWithFile(HERO_PNG))
		return false;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(size.width / 2 + origin.x, size.height / 2 + origin.y));
	this->setScale(size.width / 10 / 250);

	auto physicsBody = PhysicsShapeCache::getInstance()->createBodyWithName(HERO_PHYSICS_BODY);
	physicsBody->setDynamic(false);
	setPhysicsBody(physicsBody);

	return true;
}

void Hero::jump(Vec2 to)
{
	if (jumpInProcess)
		return;

	AudioUtil::jumpEffect();
	jumpInProcess = true;

	Vec2 movement = Vec2(to.y - this->getPositionY(),
								  to.x - this->getPositionX());
	float angle = atan2(movement.x, movement.y);
	this->setRotation(90 - angle / M_PI * 180);
	
	auto callback = CallFunc::create([this]() { this->endJumping(); });
	Sequence* sequence = Sequence::create(
		CCMoveTo::create(movement.length()*JUMP_SPEED, to),
		callback,
		NULL
	);
	this->runAction(sequence);
}

void Hero::endJumping()
{
	jumpInProcess = false;
}