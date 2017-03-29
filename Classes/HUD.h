#ifndef _HUD_H_
#define _HUD_H_

#include "Static.h"

class GameGUIFacade;
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