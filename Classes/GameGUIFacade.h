#ifndef __GameGUI_h__
#define __GameGUI_h__

#include "Static.h"
#include "HUD.h"
#include "GameOverMenu.h"


class PauseWindow;
class GameGUIFacade : public Layer
{
private:
	static GameGUIFacade* _gui;
	HudMenu* _hudMenu;
	GameOverMenu* _gameOverMenu;
	PauseWindow* _pauseWindow;
	CREATE_FUNC(GameGUIFacade);
public:	
	virtual bool init();

	static GameGUIFacade* getInstance();
	void showGameOverMenu(int);
	void setScore(int);
	void showPauseWindow();
	void showPauseWindowClick(Event* event);
	bool showPauseWindowTouch(Touch* touch, Event* event);
	void closePauseWindow(Event* event);
};

#endif

