#ifndef __GameGUI_h__
#define __GameGUI_h__

#include "cocos2d.h"
#include "GameOverMenu.h"

USING_NS_CC;

class GameGUI : public Layer
{
private:
	Label* _score;
	GameOverMenu* _gameOverMenu;
public:	

	CREATE_FUNC(GameGUI);
	virtual bool init();

	void showGameOverMenu();
	void setScore(int);
};

#endif

