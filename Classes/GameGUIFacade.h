#ifndef __GameGUI_h__
#define __GameGUI_h__

#include "cocos2d.h"
#include "GameOverMenu.h"
#include "HUD.h"

using namespace cocos2d;

class GameGUIFacade : public Layer
{
private:
	HudMenu* _hudMenu;
	GameOverMenu* _gameOverMenu;
public:	
	CREATE_FUNC(GameGUIFacade);
	virtual bool init();

	void showGameOverMenu();
	void setScore(int);
};

#endif

