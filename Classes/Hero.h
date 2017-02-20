#ifndef __HERO_H__
#define __HERO_H__
#define _HERO_PNG_ "hero.png"

#include "cocos2d.h"

class Hero : public cocos2d::Sprite
{
public:
	Hero();
	void jump(cocos2d::Vec2 to);
	static Hero* create()
	{
		Hero* hero = new (std::nothrow) Hero;
		if (hero && hero->initWithFile(_HERO_PNG_))
		{
			hero->autorelease();
			return hero;
		}
		CC_SAFE_DELETE(hero);
		return nullptr;
	};

	virtual bool init();
};

#endif