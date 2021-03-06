#ifndef __HERO_H__
#define __HERO_H__

#include "Static.h"

class Hero : public Sprite
{
private:
	bool jumpInProcess = false;

	float getScaleOnJump(float length);
public:
	CREATE_FUNC(Hero);
	virtual bool init();

	bool jumping() const { return jumpInProcess; };
	void jump(Vec2 to);

	// std required callback's functions to be public
	void endJumping();
};

#endif