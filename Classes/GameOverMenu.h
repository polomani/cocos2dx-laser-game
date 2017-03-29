#ifndef _GAME_OVER_MENU_H_
#define _GAME_OVER_MENU_H_
#include "cocos2d.h"

class GameScene;
class GameOverMenu : public LayerColor
{
private:
	MenuItemLabel* _recordLabel;
	MenuItemLabel* _currentPointsLabel;
public:
	CREATE_FUNC(GameOverMenu);

	GameOverMenu();

	virtual bool init();

	void show(int score);

	void menuRestartClick(Ref* pSender);
	void currentPoints(int points);
};

#endif

