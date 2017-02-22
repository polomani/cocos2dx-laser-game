#include "Hero.h"
#include "cocos2d.h"
USING_NS_CC;

bool Hero::init() 
{
	if (!Sprite::initWithFile(_HERO_PNG_))
		return false;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(size.width / 2 + origin.x, size.height / 2 + origin.y));
	this->setScale(size.width / 10 / 196);

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
		CCMoveTo::create(movement.length()*0.001, to),
		onJumpEndCallBack,
		NULL
	);
	this->runAction(sequence);
}

void Hero::onJumpEnd()
{
	jumpInProcess = false;
}