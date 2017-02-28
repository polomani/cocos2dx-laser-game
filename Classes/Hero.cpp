#include "Hero.h"
#include "PhysicsShapeCache.h"
#include "cocos2d.h"

USING_NS_CC;

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

void Hero::jump(cocos2d::Vec2 to)
{
	if (jumpInProcess)
		return;

	jumpInProcess = true;

	cocos2d::Vec2 movement = Vec2(to.y - this->getPositionY(),
								  to.x - this->getPositionX());
	float angle = atan2(movement.x, movement.y);
	this->setRotation(90 - angle / M_PI * 180);

	CallFunc* onJumpEndCallBack = CallFunc::create(this, callfunc_selector(Hero::onJumpEnd));
	Sequence* sequence = Sequence::create(
		CCMoveTo::create(movement.length()*JUMP_SPEED, to),
		onJumpEndCallBack,
		NULL
	);
	this->runAction(sequence);
}

void Hero::onJumpEnd()
{
	jumpInProcess = false;
}