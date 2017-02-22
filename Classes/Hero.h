#ifndef __HERO_H__
#define __HERO_H__
#define _HERO_PNG_ "hero.png"

#include "cocos2d.h"
USING_NS_CC;

class Hero : public Sprite
{
public:
	CREATE_FUNC(Hero);
	virtual bool init();

	void jump(Vec2 to);
};

#endif