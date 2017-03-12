#ifndef _GAME_OVER_MENU_H_
#define _GAME_OVER_MENU_H_
#include "cocos2d.h"

class GameScene;
class GameOverMenu : public cocos2d::LayerColor
{
private:
	GameScene* _gameScene;
public:
	CREATE_FUNC(GameOverMenu);

	GameOverMenu();

	virtual bool init();

	void show();

	void setGameScene(GameScene* h) { _gameScene = h; };

	void menuRestartClick(cocos2d::Ref* pSender);
};

#endif

