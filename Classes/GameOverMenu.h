#ifndef _GAME_OVER_MENU_H_
#define _GAME_OVER_MENU_H_
#include "cocos2d.h"

class GameScene;
class GameOverMenu : public cocos2d::LayerColor
{
private:
	cocos2d::MenuItemLabel* _recordLabel;
	cocos2d::MenuItemLabel* _currentPointsLabel;
public:
	CREATE_FUNC(GameOverMenu);

	GameOverMenu();

	virtual bool init();

	void show(int score);

	void menuRestartClick(cocos2d::Ref* pSender);
	void currentPoints(int points);
};

#endif

