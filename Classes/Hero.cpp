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
	
	float length = movement.length();
	float duration = length * JUMP_SPEED;

	CallFunc* endJumpCallBack = CallFunc::create([this]() { this->endJumping(); });
	Sequence* jumpSequence = Sequence::create(
		CCMoveTo::create(duration, to),
		endJumpCallBack,
		NULL
	);

	float scale = getScaleOnJump(length);

	Sequence* scaleSequesnce = Sequence::create(
		ScaleBy::create(duration / 2, scale),
		ScaleBy::create(duration / 2, 1 / scale),
		nullptr
		);


	// run parallel actions
	this->runAction(Spawn::create(jumpSequence, scaleSequesnce, nullptr));
}

void Hero::endJumping()
{
	jumpInProcess = false;
}

float Hero::getScaleOnJump(float length)
{
	Size size = Director::getInstance()->getVisibleSize();

	// maximum distans player can jump
	float diagonal = sqrt(size.width*size.width + size.height*size.height);

	float jumpRatio =  (length / diagonal) * 5;

	// max posible jump scale is 5, but posible values smaller then 1
	// so allow only scale from 2 to 4
	if (jumpRatio < 2)
		return 2;
	if (jumpRatio > 4)
		return 4;
	return jumpRatio;
}