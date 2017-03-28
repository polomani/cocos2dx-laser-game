#ifndef __GameGUI_h__
#define __GameGUI_h__

#include "cocos2d.h"
#include "GameOverMenu.h"
#include "HUD.h"

using namespace cocos2d;

class PauseWindow;
class GameGUIFacade : public Layer
{
private:
	HudMenu* _hudMenu;
	GameOverMenu* _gameOverMenu;
	PauseWindow* _pauseWindow;
public:	
	CREATE_FUNC(GameGUIFacade);
	virtual bool init();

	void showGameOverMenu(int);
	void setScore(int);
	void showPauseWindowClick(Event* event);
	bool showPauseWindowTouch(Touch* touch, Event* event);
	void closePauseWindow(Event* event);
};

#endif

