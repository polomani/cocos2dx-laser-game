#ifndef _HUD_H_
#define _HUD_H_

#include "cocos2d.h"
using namespace cocos2d;

class GameGUIFacade;
class HudMenu : public Layer
{
private:
	Label* _score;
public:
	
	static HudMenu* create(GameGUIFacade* gui) {
		HudMenu* ret = new(std::nothrow) HudMenu();
		if (ret && ret->init(gui)) { 
			ret->autorelease();
			return ret;
		}
		else {
			delete ret;
			ret = nullptr;
			return nullptr;
		}
	}

	virtual bool init(GameGUIFacade* gui);

	void setScore(int);
};

#endif