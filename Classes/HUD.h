#ifndef _HUD_H_
#define _HUD_H_

#include "cocos2d.h"
using namespace cocos2d;

class HudMenu : public Layer
{
private:
	Label* _score;
public:
	CREATE_FUNC(HudMenu);
	virtual bool init();

	void setScore(int);
};

#endif