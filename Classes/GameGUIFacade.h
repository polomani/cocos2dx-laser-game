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

